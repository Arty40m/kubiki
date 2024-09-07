#pragma once
#include "../stl_headers.hpp"


class Event{
public:
    enum class EventType : int
    {
        // KEYS
        KEY_PRESSED = 1,
        KEY_HOLD,
        KEY_RELEASED,
        KEY_CLICKED,

        // MOUSE
        MOUSE_MOVED,
        MOUSE_SCROLLED,

        MOUSE_PRESSED,
        MOUSE_HOLD,
        MOUSE_RELEASED,
        MOUSE_CLICKED,

        // OTHER
        PLAYER_MOVED
    };

protected:
    EventType type;
    bool isCanceled;
    Event(EventType type): type(type), isCanceled(false){}

public:
    virtual ~Event() = 0;
    Event(const Event&) = delete;

    virtual std::string repr() = 0;
    inline EventType getType() const {return type;}
    inline bool isCanceled() const {return isCanceled;}
    inline void cancel() {isCanceled = true;}
};