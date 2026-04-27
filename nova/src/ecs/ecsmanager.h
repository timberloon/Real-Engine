#pragma once

#include <unordered_map>
#include <iostream> 
#include <GL/glew.h>
#include "entity.h"
#include "component.h"
#include "system.h"
#include "spdlog/spdlog.h"

class ECSManager {
private:
    EntityManager entityManager;

public:
    std::unordered_map<Entity, Position> positions;
    std::unordered_map<Entity, Velocity> velocities;
    std::unordered_map<Entity, Shape> shapes;

    void addShape(Entity e, ShapeType type) {
        shapes[e] = {type};
    }

    Entity createEntity() {
        return entityManager.createEntity();
    }

    void addPosition(Entity e, float x, float y) {
        positions[e] = {x, y};
    }

    void addVelocity(Entity e, float dx, float dy) {
        velocities[e] = {dx, dy};
    }

    void update() {
        for (auto &pair : positions) {
            Entity entity = pair.first;

            if (velocities.find(entity) != velocities.end()) {

                Position &pos = positions[entity];
                Velocity &vel = velocities[entity];

                MovementSystem(pos, vel);

                spdlog::info("Entity {} -> Position: ({}, {})",
                             entity, pos.x, pos.y);

                std::cout << "Entity " << entity
                          << " -> Position: ("
                          << pos.x << ", "
                          << pos.y << ")"
                          << std::endl;
            }
        }
    }

    inline void RenderSystem(Position &pos, Shape &shape) {
        glPushMatrix();
        glTranslatef(pos.x, pos.y, 0.0f);

        switch (shape.type) {
            case ShapeType::TRIANGLE:
                glBegin(GL_TRIANGLES);
                glVertex2f(0.0f, 0.1f);
                glVertex2f(-0.1f, -0.1f);
                glVertex2f(0.1f, -0.1f);
                glEnd();
                break;

            case ShapeType::SQUARE:
                glBegin(GL_QUADS);
                glVertex2f(-0.1f, 0.1f);
                glVertex2f(0.1f, 0.1f);
                glVertex2f(0.1f, -0.1f);
                glVertex2f(-0.1f, -0.1f);
                glEnd();
                break;
        }

        glPopMatrix();
    }

    void render() {
    for (auto &pair : shapes) {
        Entity entity = pair.first;

        if (positions.find(entity) != positions.end()) {
            Position &pos = positions[entity];
            Shape &shape = shapes[entity];

            RenderSystem(pos, shape);
        }
    }
}
};