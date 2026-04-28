#include "PhysicsWorld.h"
#include <cmath>
#include <algorithm>

namespace nova {
    PhysicsBody* PhysicsWorld::create_body() {
        auto body = std::make_unique<PhysicsBody>();
        PhysicsBody* ptr = body.get();
        m_bodies.push_back(std::move(body));
        return ptr;
    }

    void PhysicsWorld::remove_body(PhysicsBody* body) {
        m_bodies.erase(
            std::remove_if(m_bodies.begin(), m_bodies.end(),
                [body](const std::unique_ptr<PhysicsBody>& b) {
                    return b.get() == body;
                }),
            m_bodies.end()
        );
    }

    void PhysicsWorld::clear() {
        m_bodies.clear();
    }


    void PhysicsWorld::update(float dt) {
        if (dt <= 0.0f) return;

        float scaled_dt = dt * time_scale;

        
        integrate(scaled_dt);

       
        for (int i = 0; i < iterations; ++i) {
            detect_and_resolve();
        }
    }


    void PhysicsWorld::integrate(float dt) {
        for (auto& body_ptr : m_bodies) {
            PhysicsBody& b = *body_ptr;

            if (b.is_static) {
                b.force_accumulator = { 0, 0 };
                continue;
            }
            float inv_mass = (b.mass > 0.0f) ? 1.0f / b.mass : 0.0f;
            b.acceleration = b.force_accumulator * inv_mass;
            if (b.use_gravity) {
                b.acceleration += gravity;
            }
            b.velocity += b.acceleration * dt;

            b.velocity *= (1.0f - b.friction * dt);

            b.position += b.velocity * dt;

            b.force_accumulator = { 0, 0 };
        }
    }

 
    void PhysicsWorld::detect_and_resolve() {
        size_t n = m_bodies.size();

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                PhysicsBody* a = m_bodies[i].get();
                PhysicsBody* b = m_bodies[j].get();

                
                if (a->is_static && b->is_static) continue;

                CollisionInfo info = aabb_vs_aabb(a, b);
                if (info.colliding) {
                    resolve_collision(info);
                    positional_correction(info);
                }
            }
        }
    }

 

    CollisionInfo PhysicsWorld::aabb_vs_aabb(PhysicsBody* a, PhysicsBody* b) const {
        CollisionInfo info;
        info.bodyA = a;
        info.bodyB = b;

        AABB aabb_a = a->get_aabb();
        AABB aabb_b = b->get_aabb();

        
        float overlap_x_left  = aabb_b.max.x - aabb_a.min.x;
        float overlap_x_right = aabb_a.max.x - aabb_b.min.x;

        
        float overlap_y_bottom = aabb_b.max.y - aabb_a.min.y;
        float overlap_y_top    = aabb_a.max.y - aabb_b.min.y;

        
        if (overlap_x_left < 0 || overlap_x_right < 0 ||
            overlap_y_bottom < 0 || overlap_y_top < 0) {
            return info; 
        }

        info.colliding = true;

       
        float min_x = std::min(overlap_x_left,  overlap_x_right);
        float min_y = std::min(overlap_y_bottom, overlap_y_top);

        if (min_x < min_y) {
            info.penetration = min_x;
            info.normal = (overlap_x_left < overlap_x_right)
                ? Vec2{ -1.0f,  0.0f }   
                : Vec2{  1.0f,  0.0f };  
        } else {
            info.penetration = min_y;
            info.normal = (overlap_y_bottom < overlap_y_top)
                ? Vec2{  0.0f, -1.0f }  
                : Vec2{  0.0f,  1.0f };  
        }

        return info;
    }

    void PhysicsWorld::resolve_collision(const CollisionInfo& info) {
        PhysicsBody* a = info.bodyA;
        PhysicsBody* b = info.bodyB;

        float inv_mass_a = (!a->is_static && a->mass > 0) ? 1.0f / a->mass : 0.0f;
        float inv_mass_b = (!b->is_static && b->mass > 0) ? 1.0f / b->mass : 0.0f;
        float total_inv  = inv_mass_a + inv_mass_b;

        if (total_inv == 0.0f) return; 

        Vec2  rel_vel = b->velocity - a->velocity;
        float vel_along_normal = rel_vel.x * info.normal.x + rel_vel.y * info.normal.y;

        if (vel_along_normal > 0) return;

        float e = std::min(a->restitution, b->restitution);

        float j = -(1.0f + e) * vel_along_normal / total_inv;

    
        Vec2 impulse = info.normal * j;

        a->velocity -= impulse * inv_mass_a;
        b->velocity += impulse * inv_mass_b;
    }


    void PhysicsWorld::positional_correction(const CollisionInfo& info) {
        const float percent = 0.4f;   // correction strength  [0.2 – 0.8]
        const float slop    = 0.01f;  // ignore penetrations smaller than this

        PhysicsBody* a = info.bodyA;
        PhysicsBody* b = info.bodyB;

        float inv_mass_a = (!a->is_static && a->mass > 0) ? 1.0f / a->mass : 0.0f;
        float inv_mass_b = (!b->is_static && b->mass > 0) ? 1.0f / b->mass : 0.0f;
        float total_inv  = inv_mass_a + inv_mass_b;

        if (total_inv == 0.0f) return;

        float mag = std::max(info.penetration - slop, 0.0f) / total_inv * percent;
        Vec2 correction = info.normal * mag;

        a->position -= correction * inv_mass_a;
        b->position += correction * inv_mass_b;
    }



    PhysicsBody* PhysicsWorld::raycast(Vec2 origin, Vec2 direction, float max_dist) const {
        PhysicsBody* closest = nullptr;
        float        closest_t = max_dist;

        for (const auto& body_ptr : m_bodies) {
            PhysicsBody& b  = *body_ptr;
            AABB         ab = b.get_aabb();

           
            float dir_x = (direction.x != 0) ? direction.x : 1e-6f;
            float dir_y = (direction.y != 0) ? direction.y : 1e-6f;

            float tx1 = (ab.min.x - origin.x) / dir_x;
            float tx2 = (ab.max.x - origin.x) / dir_x;
            float ty1 = (ab.min.y - origin.y) / dir_y;
            float ty2 = (ab.max.y - origin.y) / dir_y;

            float tmin = std::max(std::min(tx1, tx2), std::min(ty1, ty2));
            float tmax = std::min(std::max(tx1, tx2), std::max(ty1, ty2));

            if (tmax >= 0 && tmin <= tmax && tmin < closest_t) {
                closest_t = tmin;
                closest   = &b;
            }
        }

        return closest;
    }

} 
