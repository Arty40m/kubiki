#pragma once
#include "../stl_headers.hpp"
#include "Event.hpp"


class EventManager
{
public:
    typedef std::function<bool(Event*)> EventCallback;
    typedef std::vector<EventCallback> CallbacksList;

    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    
    static EventManager& GetI();

    // Instance methods
    void Init(int initEventBufferSize = 128);
    void addEvent(Event* e);
    void addEventThisFrame(Event* e);
    int numEvents() const;
    void processEvents();
    void addCallback(Event::EventType type, EventCallback callback);

    template<typename E, typename... Types>
    E* createEvent(Types&& ... args);

    template<typename E, typename... Types>
    void emplaceEvent(Types&& ... args);

    template<typename E, typename... Types>
    void emplaceEventThisFrame(Types&& ... args);

private:
    std::vector<Event*> eBuffer1;
    std::vector<Event*> eBuffer2;
    bool firstBufferIsCurrent;
    bool isProcessing;

    std::vector<CallbacksList> Callbacks;

    EventManager();
    ~EventManager();
};


// Create event
template<typename E, typename... Types>
E* EventManager::createEvent(Types&& ... args)
{
    return new E(args...);
}

// Emplace event instance methods
template<typename E, typename... Types>
void EventManager::emplaceEvent(Types&& ... args){
    Event* e = (Event*)createEvent<E>(std::forward<Types>(args)...);
    return EventManager::addEvent(e);
}

template<typename E, typename... Types>
void EventManager::emplaceEventThisFrame(Types&& ... args){
    Event* e = (Event*)createEvent<E>(std::forward<Types>(args)...);
    return EventManager::addEventThisFrame(e);
}