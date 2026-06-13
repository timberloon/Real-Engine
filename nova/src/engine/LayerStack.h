#pragma once
#include"core.h"
#include"layer.h"
#include<iostream>
#include<vector>

namespace nova{
    class NOVA_API LayerStack{
        std::vector<nova::Layer*> m_layers;
        std::vector<nova::Layer*>::iterator m_LayerInsert;
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        inline std::vector<nova::Layer*>::iterator begin(){return m_layers.begin();}
        inline std::vector<nova::Layer*>::iterator end(){return m_layers.end();}
    };
}
