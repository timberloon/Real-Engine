#pragma once
#include "PhysicsBody.h"
#include"physicscore.h"

namespace nova {
    struct CollisionInfo {
        bool      colliding = false;
        Vec2      normal;           
        float     penetration = 0;  
        PhysicsBody* bodyA = nullptr;
        PhysicsBody* bodyB = nullptr;
    };

    class NOVA_API PhysicsWorld {
    public:

       
        Vec2  gravity      = { 0.0f, -9.8f };  
        float time_scale   = 1.0f;             
        int   iterations   = 5;                 

        
        PhysicsWorld()  = default;
        ~PhysicsWorld() = default;

        
        PhysicsBody* create_body();                      
        void         remove_body(PhysicsBody* body);       
        void         clear();                               

        const std::vector<std::unique_ptr<PhysicsBody>>& get_bodies() const { return m_bodies; }

       
        void update(float dt);

    
        PhysicsBody* raycast(Vec2 origin, Vec2 direction, float max_dist = 1000.0f) const;

    private:
        std::vector<std::unique_ptr<PhysicsBody>> m_bodies;

    
        void integrate(float dt);                         
        void detect_and_resolve();                        

        
        CollisionInfo aabb_vs_aabb(PhysicsBody* a, PhysicsBody* b) const;
        void          resolve_collision(const CollisionInfo& info);
        void          positional_correction(const CollisionInfo& info);
    };

} 
