#pragma once
#include "../stl_headers.hpp"
#include "../Events/Event.hpp"
#include "Window.hpp"


/*

TEMPLATE

class _Event: public Event
{
public:
    inline static const std::string name = "_Event";

    _Event():
    Event(Event::EventType::),{}

    std::string repr() override{
        std::string s = (name + );
        return s;
    }
};
*/

class TestEvent: public Event
{
public:
    inline static const std::string name = "TestEvent";

    TestEvent():
    Event(Event::EventType::TEST_E){}

    std::string repr() override{
        std::string s = (name + " -");
        return s;
    }
};

class KeyPressedEvent: public Event
{
public:
    inline static const std::string name = "KeyPressedEvent";
    int keycode;
    float duration;

    KeyPressedEvent(int keycode, float duration):
    Event(Event::EventType::KEY_PRESSED_E), keycode(keycode), duration(duration){}

    std::string repr() override{
        std::string s = (name + " : " + Window::GetI().getKeyName(keycode) + " for " + std::to_string(duration) + " seconds");
        return s;
    }
};

class KeyReleasedEvent: public Event
{
public:
    inline static const std::string name = "KeyReleasedEvent";
    int keycode;
    float duration;

    KeyReleasedEvent(int keycode, float duration):
    Event(Event::EventType::KEY_RELEASED_E), keycode(keycode), duration(duration){}

    std::string repr() override{
        std::string s = (name + " : " + Window::GetI().getKeyName(keycode) + " for " + std::to_string(duration) + " seconds");
        return s;
    }
};

class MouseMovedEvent: public Event
{
public:
    inline static const std::string name = "MouseMovedEvent";
    float dx;
    float dy;
    char c[1024];

    MouseMovedEvent(float dx, float dy): 
    Event(Event::EventType::MOUSE_MOVED_E), dx(dx), dy(dy){}

    std::string repr() override{
        std::string s = (name + " - dx: " + std::to_string(dx) + 
                        "; dy: " + std::to_string(dy));
        return s;
    }
};

class MouseScrolledEvent: public Event
{
public:
    inline static const std::string name = "MouseScrolledEvent";
    float offset;

    MouseScrolledEvent(float offset):
    Event(Event::EventType::MOUSE_SCROLLED_E), offset(offset){}

    std::string repr() override{
        std::string s = (name + " - offset: " + std::to_string(offset));
        return s;
    }
};

class MousePressedEvent: public Event
{
public:
    inline static const std::string name = "MousePressedEvent";
    int keycode;
    float duration;

    MousePressedEvent(int keycode, float duration):
    Event(Event::EventType::MOUSE_PRESSED_E), keycode(keycode), duration(duration){}

    std::string repr() override{
        std::string s = (name + " : " + Window::GetI().getKeyName(keycode) + " for " + std::to_string(duration) + " seconds");
        return s;
    }
};

class MouseReleasedEvent: public Event
{
public:
    inline static const std::string name = "MouseReleasedEvent";
    int keycode;
    float duration;

    MouseReleasedEvent(int keycode, float duration):
    Event(Event::EventType::MOUSE_RELEASED_E), keycode(keycode), duration(duration){}

    std::string repr() override{
        std::string s = (name + " : " + Window::GetI().getKeyName(keycode) + " for " + std::to_string(duration) + " seconds");
        return s;
    }
};