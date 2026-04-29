#pragma once

namespace nova{
    enum class event_type{
        window_resize_event,window_open_event,window_close_event,
        mouse_move,mousebutton_press,mousebutton_release,mouse_scroll,
        keypress,keyrelease,
        apptick_event,app_update_event,app_render_event
    };

    enum event_category{
        none = 0,
        application_event = BIT(0),
        input_event = BIT(1),
        keyboard_event = BIT(2),
        mouse_event = BIT(3),
        mouse_button_event = BIT(4)
    };

    #define EVENT_CLASS_TYPE(type) static event_type get_static_type(){return event_type::type; }\
                                 virtual event_type get_event_type() const override {return get_static_type();}\
                                 std::string get_name() {return #type;}
                                
    #define EVENT_CLASS_CATEGORY(type) virtual int get_category(){return type;}

    class NOVA_API Event{
        friend class event_dispatcher;
    protected: 
        bool m_handeled = false;
    public:
        virtual event_type get_event_type() const = 0;
        virtual event_category get_category() const = 0;
        virtual const char* get_name() const = 0;

        virtual std::string to_string() const {return get_name();}

        inline bool is_in_category(event_category category){
            return category & get_category();
        }
    };

    class NOVA_API event_dispatcher{
        template<typename t>
        using event_fn = std::function<bool(t&)>;
        
        protected: Event& m_event;
    
    public:
        event_dispatcher(Event& ev) : m_event(ev){}

        template<typename t>
        bool dispatch(t event){
            if(m_event.get_event_type() == t::get_static_type()){
                m_event.m_handeled = func(*(t*)& m_event);
                return true;
            }
            return false;
        }
    };

    std::ostream& operator<<(std::ostream& os,Event& ev){
        os << ev.to_string();
        return os;
    }
}