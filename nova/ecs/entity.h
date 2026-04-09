#pragma once

using Entity = int;

class EntityManager {
private:
    Entity nextEntity = 0;

public:
    Entity createEntity() {
        return nextEntity++;
    }
};