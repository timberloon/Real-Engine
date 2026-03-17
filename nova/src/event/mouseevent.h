#pragma once
#include"event.h"

namespace nova{
    class NOVA_API MouseMoveEvent : public Event{
    private:
        float m_mouseX,m_mouseY;
    public:
        MouseMoveEvent(float x,float y) : m_mouseX(x),m_mouseY(y){}
        inline float getX()const{return m_mouseX;}
        inline float getY()const{return m_mouseY;}

        std::string to_string() const override{
            std::stringstream ss;
            ss << "moved: " << m_mouseX << ',' << m_mouseY << '\n';
            return ss.str();
        }

        EVENT_CLASS_CATEGORY(mouse_event | input_event);
        EVENT_CLASS_TYPE(mouse_move);
    };

    class NOVA_API MouseScrollEvent : public Event{
    private: float offsetX,offsetY;
    public:
        MouseScrollEvent(float x,float y) : offsetX(x) , offsetY(y){}
        float getX() const {return offsetX;}
        float getY() const {return offsetY;}

        std::string to_string() const override{
            std::stringstream ss;
            ss << "scroll offset: " << offsetX << ',' << offsetY << '\n';
            return ss.str();
        }

        EVENT_CLASS_CATEGORY(mouse_event | input_event);
        EVENT_CLASS_TYPE(mouse_scroll);
    };

    class NOVA_API MouseButtonEvent : public Event{
    protected:
        int m_button;
        MouseButtonEvent(int button) : m_button(button){}
    public:
        int get_button() const {return m_button;}
        EVENT_CLASS_CATEGORY(mouse_button_event | mouse_event | input_event);
    };

    class NOVA_API MouseButtonPressEvent : public MouseButtonEvent{
    public:
        MouseButtonPressEvent(int button) : MouseButtonEvent(button){}

        std::string to_string() const override{
            std::stringstream ss;
            ss << "Button pressed : " << m_button << '\n';
            return ss.str();
        }

        EVENT_CLASS_TYPE(mousebutton_press);
    };

    class NOVA_API MouseButtonReleaseEvent : public MouseButtonEvent{
    public:
        MouseButtonReleaseEvent(int button) : MouseButtonEvent(button) {}

        std::string to_string() const override{
            std::stringstream ss;
            ss << "Button released: " << m_button << '\n';
            return ss.str();
        }

        EVENT_CLASS_TYPE(mousebutton_release);
    };
}