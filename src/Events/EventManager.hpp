#pragma once
#include "../stl_headers.hpp"
#include "Event.hpp"
#include "../DataStructures/Stack.hpp"


class EventManager
{
public:
    typedef std::vector<std::pair<Event*, size_t>> EventBuffer;
    typedef std::function<bool(Event*)> EventCallback;
    typedef std::vector<EventCallback> CallbacksList;

    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    
    static EventManager& GetI();

    // Instance methods
    void Init(int initEventBufferSize = 128);
    int numEvents() const;
    void processEvents();
    void addCallback(Event::EventType type, EventCallback callback);

    template<typename E, typename... Types>
    void emplaceEvent(Types&& ... args);

private:
    EventBuffer eBuffer1;
    EventBuffer eBuffer2;
    Stack eStack1;
    Stack eStack2;
    bool firstBufferIsCurrent;

    std::vector<CallbacksList> Callbacks;

    EventManager();
    ~EventManager();
};


template<typename E, typename... Types>
void EventManager::emplaceEvent(Types&& ... args)
{
    EventBuffer& eBuffer = (firstBufferIsCurrent) ? eBuffer1 : eBuffer2;
    Stack& eStack = (firstBufferIsCurrent) ? eStack1 : eStack2;

    Event* e = (Event*)(new (eStack.aloc(sizeof(E))) E(args...));
    eBuffer.push_back({e, sizeof(E)});
}