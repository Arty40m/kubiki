#include "logging.hpp"
#include "Event.hpp"
#include "EventManager.hpp"



EventManager::EventManager():
    firstBufferIsCurrent(true){}

EventManager::~EventManager() {
    LOG_DEBUG("Final stack1 cap: {}", eStack1.capacity());
    LOG_DEBUG("Final stack2 cap: {}", eStack2.capacity());
}

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

    // eStack1
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
    EventBuffer& eBuffer = (firstBufferIsCurrent) ? eBuffer1 : eBuffer2;
    EventBuffer& eBufferNext = (firstBufferIsCurrent) ? eBuffer2 : eBuffer1;
    Stack& eStack = (firstBufferIsCurrent) ? eStack1 : eStack2;
    Stack& eStackNext = (firstBufferIsCurrent) ? eStack2 : eStack1;
    firstBufferIsCurrent = !firstBufferIsCurrent;

    int i = 0;
    while (i < eBuffer.size())
    {
        auto [e, eSize] = eBuffer[i];
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

        // if (dropEvent){delete e;} else {addEvent(e);}
        if (!dropEvent){
            eBufferNext.push_back({e, eSize});
            std::memcpy(eStackNext.aloc(sizeof(eSize)), e, eSize);
        }

        i++;
    }
    eBuffer.clear();
    eStack.clear();
}

void EventManager::addCallback(Event::EventType type, EventCallback callback)
{
    Callbacks[(int)type].push_back(callback);
}
