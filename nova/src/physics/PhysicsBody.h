#pragma once
#include "physicscore.h"

namespace nova {
    //  Axis-Aligned Bounding Box for collision
    struct NOVA_API AABB {
        Vec2 min;   
        Vec2 max;   

        AABB() = default;
        AABB(Vec2 min, Vec2 max) : min(min), max(max) {}

        float width()  const { return max.x - min.x; }
        float height() const { return max.y - min.y; }
    };

    struct NOVA_API PhysicsBody {

        Vec2 position;          
        Vec2 velocity;          
        Vec2 acceleration;      

        float restitution = 0.5f;   
        float mass        = 1.0f;   
        float friction    = 0.1f;   

        Vec2 halfSize = { 0.5f, 0.5f };

        bool is_static  = false;    
        bool use_gravity = true;    

        Vec2 force_accumulator;

        void apply_force(Vec2 f) {
            force_accumulator += f;
        }

        AABB get_aabb() const {
            return {
                { position.x - halfSize.x, position.y - halfSize.y },
                { position.x + halfSize.x, position.y + halfSize.y }
            };
        }
    };

} 
