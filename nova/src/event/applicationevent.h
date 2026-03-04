#include"event.h"
#include<sstream>

namespace nova{
    class NOVA_API WindowResizeEvent : public Event{
    public:
        WindowResizeEvent(int width,int height) : m_width(width),m_height(height){}

        EVENT_CLASS_CATEGORY(application_event);
        EVENT_CLASS_TYPE(window_resize_event);

        std::string to_string() const override{
            std::stringstream ss;
            ss << "window resize event: " << m_width << ' ' << m_height << '\n';
            return ss.str();
        }
    private:
        unsigned int m_width,m_height;
    };

    class NOVA_API WindowCloseEvent : public Event{
    public:
        WindowCloseEvent(){}

        EVENT_CLASS_CATEGORY(application_event);
        EVENT_CLASS_TYPE(window_close_event);
    };

    class NOVA_API apptickevent : public Event{
    public:
        apptickevent(){}

        EVENT_CLASS_CATEGORY(application_event);
        EVENT_CLASS_TYPE(apptick_event);
    };

    class NOVA_API AppUpdateEvent : public Event{
    public:
        AppUpdateEvent(){}

        EVENT_CLASS_CATEGORY(application_event);
        EVENT_CLASS_TYPE(app_update_event);
    };

    class NOVA_API ApprenderEvent : public Event{
    public:
        ApprenderEvent(){}

        EVENT_CLASS_CATEGORY(application_event);
        EVENT_CLASS_TYPE(app_render_event);
    };
}