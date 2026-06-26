#pragma once

#include"core.h"
#include"renderer/glcore.h"
#include"renderer/bufferlayout.h"
#include"renderer/indexbuffer.h"
#include"renderer/renderer.h"
#include"renderer/shader.h"
#include"renderer/texture.h"
#include"renderer/vertexarray.h"
#include"renderer/vertexbuffer.h"
#include"math/matrix.h"

#include<vector>
#include<array>
#include<memory>
#include<type_traits>
#include<tuple>

#define entity unsigned int
#define componentID unsigned int
#define maxEntities 32

#define componentArray(componentType) std::array<std::unique_ptr<componentType>,maxEntities>
