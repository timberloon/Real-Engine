#pragma once
#include"ecscore.h"
#include"component.h"
#include<sstream>

namespace nova{
    static inline componentID getComponentTypeID(){
        static componentID currID = 0;
        return currID++;
    }
    template<typename t>
    static inline componentID getComponentTypeID(){
        static componentID componentTypeID = getComponentTypeID();
        return componentTypeID;
    }

    static inline entity createEntity(){
        static entity currEnt = 0;
        return currEnt++;
    }

    class NOVA_API registry {
        std::tuple<
            componentArray(TransformComponent),
            componentArray(SpriteComponent), 
            componentArray(ColorComponent),
            componentArray(MassComponent),
            componentArray(VelocityComponent),
            componentArray(AccelarationComponent),
            componentArray(ForceComponent)  
        > m_components;
        
    public:
        registry() = default;
        
        inline entity createEntity(){return nova::createEntity();}

        template<typename t,typename...args>
        std::unique_ptr<t> createComponent(args&&...Vargs){
            auto comp = std::make_unique<t>(std::forward<args>(Vargs)...);
            comp->m_componentID = getComponentTypeID<t>();
            return comp;
        }

        template<typename component>
        void addComponents(entity& e,std::unique_ptr<component>&& u_component){
            auto& arr = std::get<componentArray(component)>(m_components);
            arr[e] = std::move(u_component);
        }
        template<typename t,typename...args>
        void addComponents(entity& e,std::unique_ptr<t>&& first,std::unique_ptr<args>&& ...rest){
            addComponents(e,std::move(first));
            if constexpr (sizeof...(rest) > 0) addComponents(e,std::move(rest)...);
        }

        template<typename t>
        t* getComponent(const entity& e){
            auto& array =  std::get<componentArray(t)>(m_components);
            return array[e].get();
        }

        inline void TransformEntity(const entity& e,nova::mat2& transform){
            auto& component = std::get<componentArray(TransformComponent)>(m_components)[e];
            for(int i=0;i<8;i+=2){
                nova::vec2 vec(component->m_points[i],component->m_points[i+1]);
                auto temp = transform*vec;
                std::stringstream ss;
                ss<< "Translating: " << component->m_points[i] << ',' << component->m_points[i+1] << " -> " << temp.a << ',' <<temp.b << '\n';
                nova::log::log_message(ss.str());
                component->m_points[i] = temp.a;
                component->m_points[i+1] = temp.b;
                if(i == 0){
                    component->m_pos = temp;
                }
            }
        }

        inline void TransformEntity(const entity& e,nova::mat3& transform){
            auto& component = std::get<componentArray(TransformComponent)>(m_components)[e];

            for(int i=0;i<8;i+=2){
                nova::vec3 vec(component->m_points[i],component->m_points[i+1],1);
                auto temp = transform*vec;
                std::stringstream ss;
                ss<< "Translating: " << component->m_points[i] << ',' << component->m_points[i+1] << " -> " << temp.a << ',' <<temp.b << '\n';
                nova::log::log_message(ss.str());
                component->m_points[i] = temp.a;
                component->m_points[i+1] = temp.b;
                if(i == 0){
                    component->m_pos.a = temp.a;
                    component->m_pos.b = temp.b;
                }
            }
        }
        inline void TransformEntity(const entity& e,nova::mat3&& transform){
            auto& component = std::get<componentArray(TransformComponent)>(m_components)[e];

            for(int i=0;i<8;i+=2){
                nova::vec3 vec(component->m_points[i],component->m_points[i+1],1);
                auto temp = transform*vec;
                std::stringstream ss;
                ss<< "Translating: " << component->m_points[i] << ',' << component->m_points[i+1] << " -> " << temp.a << ',' <<temp.b << '\n';   
                component->m_points[i] = temp.a;
                component->m_points[i+1] = temp.b;
                if(i == 0){
                    component->m_pos.a = temp.a;
                    component->m_pos.b = temp.b;
                }
            }
        }
 
    };
}
