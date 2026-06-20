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
        componentArray(TransformComponent) m_transform;
        componentArray(SpriteComponent) m_sprite;
        componentArray(ColorComponent) m_color;
        
    public:
        registry() = default;
        
        inline entity createEntity(){return nova::createEntity();}

        template<typename t,typename...args>
        std::unique_ptr<t> createComponent(args&&...Vargs){
            auto comp = std::make_unique<t>(std::forward<args>(Vargs)...);
            comp->m_componentID = getComponentTypeID<t>();
            return comp;
        }

        template<typename t>
        void addComponents(entity& e,t&& component){
            using RawType = std::decay_t<t>;

            if constexpr (std::is_same_v<RawType,std::unique_ptr<TransformComponent>>)
                m_transform[e] = std::move(component);
            else if constexpr(std::is_same_v<RawType,std::unique_ptr<SpriteComponent>>)
                m_sprite[e] = std::move(component);
            else if constexpr(std::is_same_v<RawType,std::unique_ptr<ColorComponent>>)
                m_color[e] = std::move(component);

            else nova::log::log_error("component not added\n");
            
        }
        template<typename t,typename...args>
        void addComponents(entity& e,t&& first,args&&...rest){
            addComponents(e,std::forward<t>(first));
            if constexpr (sizeof...(rest) > 0) addComponents(e,std::forward<args>(rest)...);
        }

        template<typename t>
        t* getComponent(const entity& e){
            using RawType = std::decay_t<t>;
            
            if constexpr (std::is_same_v<t,TransformComponent>)
                return m_transform[e].get();
            else if constexpr(std::is_same_v<t,SpriteComponent>)
                return m_sprite[e].get();
            else if constexpr(std::is_same_v<t,ColorComponent>)
                return m_color[e].get();

            nova::log::log_error("component not found returning null!\n");
            return nullptr;
        }

        inline void TransformEntity(const entity& e,nova::mat2& transform){
            #define component m_transform[e]
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
            #define component m_transform[e]
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
            #define component m_transform[e]
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
