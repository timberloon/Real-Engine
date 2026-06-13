#pragma once
#include"event.h"
#include<sstream>

namespace nova{
    class NOVA_API KeyEvent : public Event{
    protected: unsigned int m_keycode;
    
    public:
        KeyEvent(unsigned int key) : m_keycode(key) {}

        inline unsigned int getKey(){return m_keycode;}
        virtual std::string to_string() = 0;

        EVENT_CLASS_CATEGORY(CategoryInput | CategoryKeyboard);
    };

    class NOVA_API KeyPressedEvent : public KeyEvent{
        int m_repeatCount;
    public:
        KeyPressedEvent(unsigned int key,int repeat) : KeyEvent(key), m_repeatCount(repeat) {}

        std::string to_string() const override{
            std::stringstream ss;
            ss<< "Pressed key: " << m_keycode << ' ' << m_repeatCount << " times\n";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed);
    };

    class NOVA_API KeyReleasedEvent : public KeyEvent{
    public:
        KeyReleasedEvent(unsigned int key) : KeyEvent(key) {}

        std::string to_string()const override{
            std::stringstream ss;
            ss<< "Released key: " << m_keycode << '\n';
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased);
    };
} 