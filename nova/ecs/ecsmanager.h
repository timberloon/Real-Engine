#pragma once

#include <unordered_map>
#include <iostream> 
#include "entity.h"
#include "component.h"
#include "system.h"
#include "spdlog/spdlog.h"

class ECSManager {
private:
    EntityManager entityManager;

public:
    // Component storage
    std::unordered_map<Entity, Position> positions;
    std::unordered_map<Entity, Velocity> velocities;

    // Create entity
    Entity createEntity() {
        return entityManager.createEntity();
    }

    // Add components
    void addPosition(Entity e, float x, float y) {
        positions[e] = {x, y};
    }

    void addVelocity(Entity e, float dx, float dy) {
        velocities[e] = {dx, dy};
    }

    //CORE UPDATE FUNCTION
    void update() {
        for (auto &pair : positions) {
            Entity entity = pair.first;

            //Only process entities having velocity
            if (velocities.find(entity) != velocities.end()) {

                Position &pos = positions[entity];
                Velocity &vel = velocities[entity];

                //Apply system logic
                MovementSystem(pos, vel);

                //PRIMARY OUTPUT (spdlog)
                spdlog::info("Entity {} -> Position: ({}, {})",
                             entity, pos.x, pos.y);

                //FALLBACK OUTPUT (in case spdlog fails)
                std::cout << "Entity " << entity
                          << " -> Position: ("
                          << pos.x << ", "
                          << pos.y << ")"
                          << std::endl;
            }
        }
    }
};