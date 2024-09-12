#include "../stl_headers.hpp"
#include "../logging.hpp"
#include "Event.hpp"
#include "EventManager.hpp"



EventManager::EventManager():
    firstBufferIsCurrent(true),
    isProcessing(false) {}

EventManager::~EventManager() {}

EventManager& EventManager::GetI()
{
    static EventManager instance;
    return instance;
}

void EventManager::Init(int initEventBufferSize)
{
    eBuffer1.reserve(initEventBufferSize);
    eBuffer2.reserve(initEventBufferSize);
    Callbacks.resize((int)Event::EventType::COUNT);
}

void EventManager::addEvent(Event* e)
{
    if (firstBufferIsCurrent){
        eBuffer1.push_back(e);
    } else {
        eBuffer2.push_back(e);
    }
}

void EventManager::addEventThisFrame(Event* e)
{
    if (isProcessing)
    {
        if (firstBufferIsCurrent){
            eBuffer2.push_back(e);
        } else {
            eBuffer1.push_back(e);
        }
    } else {
        addEvent(e);
    }
}

int EventManager::numEvents() const
{
    if (firstBufferIsCurrent){
        return eBuffer1.size();
    } else {
        return eBuffer2.size();
    }
}

void EventManager::processEvents()
{
    std::vector<Event*>& eBuffer = (firstBufferIsCurrent) ? eBuffer1 : eBuffer2;
    firstBufferIsCurrent = !firstBufferIsCurrent;
    isProcessing = true;

    int i = 0;
    while (i < eBuffer.size())
    {
        Event* e = eBuffer[i];
        int callbackListIdx = (int)e->getType();
        CallbacksList& callbacks = Callbacks[callbackListIdx];

        bool dropEvent = true;
        for (int j=0; j<callbacks.size(); j++)
        {
            bool dropEventResponse = callbacks[j](e);
            if (e->isCanceled()){
                dropEvent = true;
                break;
            }
            dropEvent = dropEvent && dropEventResponse;
        }

        if (dropEvent){
            delete e;
        } else {
            addEvent(e);
            // move in memory
        }

        i++;
    }
    eBuffer.clear();
    isProcessing = false;
}

void EventManager::addCallback(Event::EventType type, EventCallback callback)
{
    Callbacks[(int)type].push_back(callback);
}
