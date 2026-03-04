#pragma once
#include"event.h"
#include<sstream>

namespace nova{
    class NOVA_API KeyEvent : public Event{
    public:
        EVENT_CLASS_CATEGORY(keyboard_event | input_event);

        inline int get_keycode(){return m_keycode;}
    protected:
        int m_keycode;

        KeyEvent(int keycode) : m_keycode(keycode){}
    };

    class NOVA_API KeyPressEvent : public KeyEvent{
    public:
        EVENT_CLASS_TYPE(keypress);

        KeyPressEvent(int keycode,int repeat) : KeyEvent(keycode) , m_repeatcount(repeat){}
        inline int get_repeat_count(){return m_repeatcount;}

        std::string to_string()const override{
            std::stringstream ss;
            ss << "keycode: " << m_keycode << '(' << "repeated " << m_repeatcount << " times" << ')' << '\n';
            return ss.str();
        }

    private:
        int m_repeatcount;
    };

    class NOVA_API KeyReleaseEvent : public KeyEvent{
    public:
        KeyReleaseEvent(int keycode) : KeyEvent(keycode) {}

        EVENT_CLASS_TYPE(keyrelease);

        std::string to_string() const override{
            std::stringstream ss;
            ss << "released: " << m_keycode << '\n';
            return ss.str();
        }
    };
}