#include"LayerStack.h"
#include<algorithm>

nova::LayerStack::LayerStack(){
    m_LayerInsert = m_layers.begin();
}

nova::LayerStack::~LayerStack(){
    for(auto layer : m_layers){
        delete layer;
    }
}

void nova::LayerStack::PushLayer(Layer* layer){
    m_LayerInsert = m_layers.emplace(m_LayerInsert,layer);
}

void nova::LayerStack::PushOverlay(Layer* overlay){
    m_layers.emplace_back(overlay);
}

void nova::LayerStack::PopLayer(Layer* layer){
    auto it = std::find(m_layers.begin(),m_layers.end(),layer);
    if(it != m_layers.end()){
        m_layers.erase(it);
        m_LayerInsert--;
    }
}

void nova::LayerStack::PopOverlay(Layer* overlay){
    auto it = std::find(m_layers.begin(),m_layers.end(),overlay);
    if(it != m_layers.end()) m_layers.erase(it);
}