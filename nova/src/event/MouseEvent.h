#pragma once
#include"event.h"
#include<sstream>

namespace nova{
    class NOVA_API MouseMoveEvent : public Event{
        float m_mousebutton_x, m_mousebutton_y;
    public:
        MouseMoveEvent(float x,float y) : m_mousebutton_x(x), m_mousebutton_y(y) {}

        inline float getX(){return m_mousebutton_x;}
        inline float getY(){return m_mousebutton_y;}

        std::string to_string() const override{
            std::stringstream ss;
            ss<< "Mouse Moved to: " << m_mousebutton_x << " , " << m_mousebutton_y << '\n';
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved);
        EVENT_CLASS_CATEGORY(CategoryInput | CategoryMouse);
    };

    class NOVA_API MouseScrollEvent : public Event{
        float m_offset_x,m_offset_y;
    public:
        MouseScrollEvent(int x,int y) : m_offset_x(x), m_offset_y(y) {}

        inline float getX(){return m_offset_x;}
        inline float getY(){return m_offset_y;}

        std::string to_string()const override{
            std::stringstream ss;
            ss<< "Mouse Scrolled to m_offset: " << m_offset_x << " , " << m_offset_y << '\n';
            return ss.str();
        }

        EVENT_CLASS_CATEGORY(CategoryInput | CategoryMouse);
        EVENT_CLASS_TYPE(MouseScrolled);
    };

    class NOVA_API MouseButtonEvent : public Event{
    protected: unsigned int m_button;
    public:     
        MouseButtonEvent(unsigned int button) : m_button(button) {}

        inline unsigned int getButton(){return m_button;}

        EVENT_CLASS_CATEGORY(CategoryInput | CategoryMouse);
    };

    class NOVA_API MouseButtonPressedEvent : public MouseButtonEvent{
    public:
        MouseButtonPressedEvent(unsigned int button) : MouseButtonEvent(button) {}

        std::string to_string() const override{
            std::stringstream ss;
            ss<< "Mouse Button Pressed: " << m_button << '\n';
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed);
    };

    class NOVA_API MouseButtonReleasedEvent : public MouseButtonEvent{
    public:
        MouseButtonReleasedEvent(unsigned int button) : MouseButtonEvent(button) {}

        std::string to_string() const override{
            std::stringstream ss;
            ss<< "Mouse Button Released: " << m_button << '\n';
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased);
    };
}