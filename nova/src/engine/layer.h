#pragma once
#include"core.h"
#include<iostream>
#include"../event/event.h"

namespace nova{
    class NOVA_API Layer{
        std::string m_DebugName;
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void onAttach(){}
        virtual void onDetach(){}
        virtual void onUpdate(){}
        virtual void onEvent(Event& e){}

        inline const std::string& getName(){return m_DebugName;}
    };
}