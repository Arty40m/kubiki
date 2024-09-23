#pragma once
#include "stlh.hpp"


class Event{
public:
    enum class EventType : int
    {
        // KEYS
        TEST_E = 0,
        KEY_PRESSED_E,
        KEY_RELEASED_E,
        KEY_CLICKED_E,

        // MOUSE
        MOUSE_MOVED_E,
        MOUSE_SCROLLED_E,

        MOUSE_PRESSED_E,
        MOUSE_RELEASED_E,
        MOUSE_CLICKED_E,

        // OTHER
        PLAYER_MOVED,

        //
        COUNT
    };

protected:
    EventType type;
    bool canceled;
    Event(EventType type): type(type), canceled(false){}

public:
    ~Event() = default;
    Event(const Event&) = delete;

    virtual std::string repr() = 0;
    inline EventType getType() const {return type;}
    inline bool isCanceled() const {return canceled;}
    inline void cancel() {canceled = true;}
};