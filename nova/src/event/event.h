#pragma once
#include<iostream>
#include"core.h"

namespace nova{
    enum EventCategory{
        None = 0,

        CategoryApplication = BIT(0),
        CategoryInput       = BIT(1),
        CategoryKeyboard    = BIT(2),
        CategoryMouse       = BIT(3)
    };  

    enum class EventType{
        none = 0,

        WindowResize, WindowClose,
        KeyPressed, KeyReleased,
        MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled
    };

    #define EVENT_CLASS_TYPE(type)\
        static EventType getStaticType(){return EventType::type;}\
        EventType getEventType()const override{return getStaticType();}\
        const char* getName()const{return #type;}

    #define EVENT_CLASS_CATEGORY(category)\
        int getCategoryFlags()const override{return category;}


    class NOVA_API Event{
        friend class EventDispatcher;
    public:
        bool m_handled = false;
        
        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual int getCategoryFlags() const = 0;

        virtual std::string to_string() const {return getName();}

        inline bool isInCategory(EventCategory category)const{
            return static_cast<int>(category) & getCategoryFlags();
        }
    };

    class NOVA_API EventDispatcher{
        Event& m_event;
    public:
        EventDispatcher(Event& ev) : m_event(ev) {}

        template<typename t,typename F>
        bool dispatch(const F& func){
            if(m_event.getEventType() == t::getStaticType()){
                m_event.m_handled = func(static_cast<t&>(m_event));
                return true;
            }
            return false;
        }
    };
}