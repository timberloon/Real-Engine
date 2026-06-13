#pragma once
#include"event.h"
#include<sstream>

namespace nova{
    class NOVA_API WindowResizeEvent : public Event{
        float m_width,m_height;
    public:
        WindowResizeEvent(int w,int h) : m_width(w), m_height(h) {}

        std::string to_string() const override {
            std::stringstream ss;
            ss << "Window Resize Event\n" << "Width: " << m_width << " Height: " << m_height << '\n';
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize);
        EVENT_CLASS_CATEGORY(CategoryApplication);
    };

    class NOVA_API WindowCloseEvent : public Event{
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_CATEGORY(CategoryApplication);
        EVENT_CLASS_TYPE(WindowClose);
    };
}