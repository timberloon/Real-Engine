#pragma once
#include"core.h"
#include"renderer/graphics.h"
#include"ecs/system.h"

namespace nova{
    class NOVA_API scene{
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
        void draw(entity& e,nova::BufferLayout& lay,nova::VertexArray& vao,nova::VertexBuffer& vbo,nova::IndexBuffer& ibo,nova::renderer& ren);
        inline entity createEntity(){return m_registry.createEntity();} 
        
        template<typename...componentTypes>
        void addComponentToEntity(entity& e,componentTypes&&...others){
            if constexpr (sizeof...(others) > 0) 
                m_registry.addComponents<componentTypes...>(e,std::forward<componentTypes>(others)...);
        }

        template<typename componentType,typename...args>
        std::unique_ptr<componentType> createComponent(args&&...data){
            return m_registry.createComponent<componentType>(std::forward<args>(data)...);
        }

        inline nova::shader& getSolidShader(){return m_solidShader;}
        inline nova::shader& getTextureShader(){return m_textureShader;}
    };
}