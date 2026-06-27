#pragma once
#include"core.h"
#include"renderer/graphics.h"
#include"ecs/system.h"

namespace nova{
    class NOVA_API scene{
        bool m_alive;
        nova::registry m_registry;
        
        nova::BufferLayout* m_layout;
        nova::VertexBuffer* m_vbo;
        nova::VertexArray* m_vao;
        nova::IndexBuffer* m_ibo;

        nova::shader m_solidShader;
        nova::shader m_textureShader;

        nova::renderer m_renderer;

    public:
        scene();
        void draw(entity& e);
        void update(entity& e,float delta);
        inline entity createEntity(){return m_registry.createEntity();} 
        
        template<typename...componentTypes>
        void addComponentToEntity(entity& e,std::unique_ptr<componentTypes>&&...others){
            if constexpr (sizeof...(others) > 0) 
                m_registry.addComponents<componentTypes...>(e,std::move(others)...);
        }

        template<typename componentType,typename...args>
        std::unique_ptr<componentType> createComponent(args&&...data){
            return m_registry.createComponent<componentType>(std::forward<args>(data)...);
        }

        inline void ScaleEntity(const entity& e,float xScale,float yScale){
            nova::log::log_error("Scaling\n");
            nova::mat3 scale(
                xScale, 0, 0,
                0, yScale,0,
                0,0,1
            );
            auto t = m_registry.getComponent<nova::TransformComponent>(e);
            nova::mat3 translate(
                1, 0, t->m_pos.a*(1-xScale),
                0, 1, t->m_pos.b*(1-yScale),
                0, 0, 1
            );
            nova::mat3 res = translate*scale;
            m_registry.TransformEntity(e,res);
        }
        inline void TranslateEntity(const entity& e,float x,float y){
            nova::log::log_error("Translating\n");
            nova::mat3 matrix(
                            1, 0, x,
                            0, 1, y,
                            0, 0, 1
                        );
            m_registry.TransformEntity(e,matrix);
        }
        inline void RotateEntity(const entity& e,float angle){
            nova::log::log_error("rotating\n");
            nova::mat3 rotate(
                cos(angle), -sin(angle),0,
                sin(angle), cos(angle),0,
                0, 0, 1
            );
            auto t = m_registry.getComponent<nova::TransformComponent>(e);
            auto x = t->m_pos.a, y = t->m_pos.b;
            nova::mat3 translate(
                1, 0, x*(1-cos(angle)) + y*sin(angle),
                0, 1, y*(1-cos(angle)) - x*sin(angle),
                0, 0, 1
            );
            nova::mat3 res = translate*rotate;
            m_registry.TransformEntity(e,res);
        }


        inline nova::shader& getSolidShader(){return m_solidShader;}
        inline nova::shader& getTextureShader(){return m_textureShader;}
        inline void kill(){m_alive = false;}
        inline void revive(){m_alive = true;}
        inline bool isAlive(){return m_alive;}
    };
}