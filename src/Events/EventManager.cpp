#include "../stl_headers.hpp"
#include "../logging.hpp"
#include "EventManager.hpp"



EventManager::EventManager():
    firstBufferIsCurrent(true),
    isProcessing(false) {}

EventManager::~EventManager() {}

EventManager& EventManager::GetInstance()
{
    static EventManager instance;
    return instance;
}

void EventManager::_Init(int initEventBufferSize)
{
    eBuffer1.reserve(initEventBufferSize);
    eBuffer2.reserve(initEventBufferSize);
}

void EventManager::_addEvent(Event* e)
{
    if (firstBufferIsCurrent){
        eBuffer1.push_back(e);
    } else {
        eBuffer2.push_back(e);
    }
}

void EventManager::_addEventThisFrame(Event* e)
{
    if (isProcessing)
    {
        if (firstBufferIsCurrent){
            eBuffer2.push_back(e);
        } else {
            eBuffer1.push_back(e);
        }
    } else {
        _addEvent(e);
    }
}

int EventManager::_numEvents() const
{
    if (firstBufferIsCurrent){
        return eBuffer1.size();
    } else {
        return eBuffer2.size();
    }
}

void EventManager::_processEvents()
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

        bool holdEvent = false;
        for (int j=0; j<callbacks.size(); j++)
        {
            bool holdEventResponse = callbacks[j](e);
            if (e->isCanceled()){
                holdEvent = false;
                break;
            }
            holdEvent = holdEvent || holdEventResponse;
        }
        if (holdEvent){
            _addEvent(e);
            // move in memory
        } else {
            delete e;
        }

        i++;
    }
    eBuffer.clear();
    isProcessing = false;
}

void EventManager::_addCallback(Event::EventType type, EventCallback callback)
{
    int callbackListIdx = (int)type;
    if (Callbacks.size() < (callbackListIdx+1)){
        Callbacks.resize(callbackListIdx+1);
    }
    Callbacks[callbackListIdx].push_back(callback);
}
