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
    
    static EventManager& GetInstance();
    
    // Class methods
    inline static void Init(int initEventBufferSize = 128) {EventManager::GetInstance()._Init(initEventBufferSize);}
    inline static void addEvent(Event* e) {EventManager::GetInstance()._addEvent(e);}
    inline static void addEventThisFrame(Event* e) {EventManager::GetInstance()._addEventThisFrame(e);}
    inline static int numEvents() {EventManager::GetInstance()._numEvents();}
    inline static void processEvents() {EventManager::GetInstance()._processEvents();}
    inline static void addCallback(Event::EventType type, EventCallback callback) {
        EventManager::GetInstance()._addCallback(type, callback);
    }

    template<typename E, typename... Types>
    static E* createEvent(Types&& ... args);

    // Instance methods
    void _Init(int initEventBufferSize = 128);
    void _addEvent(Event* e);
    void _addEventThisFrame(Event* e);
    int _numEvents() const;
    void _processEvents();
    void _addCallback(Event::EventType type, EventCallback callback);

    template<typename E, typename... Types>
    static E* _createEvent(Types&& ... args);


private:
    std::vector<Event*> eBuffer1;
    std::vector<Event*> eBuffer2;
    bool firstBufferIsCurrent;
    bool isProcessing;

    std::vector<CallbacksList> Callbacks;

    EventManager();
    ~EventManager();
};


template<typename E, typename... Types>
E* EventManager::createEvent(Types&& ... args)
{
    return EventManager::GetInstance()._createEvent<E>(std::forward<Types>(args)...);
}

template<typename E, typename... Types>
E* EventManager::_createEvent(Types&& ... args)
{
    return new E(args...);
}