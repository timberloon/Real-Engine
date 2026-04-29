#pragma once

//? --------- engine core --------------
#include"src/engine/application.h"
#include"src/engine/log.h"
#include"src/engine/window.h"

//? --------- events -------------------
#include"src/event/applicationevent.h"
#include"src/event/keyevent.h"
#include"src/event/mouseevent.h"

//? ------ entity component system -----
#include"src/ecs/ecsmanager.h"
#include"src/ecs/entity.h"
#include"src/ecs/system.h"
#include"src/ecs/component.h"

//? -------- renderer -------------------
#include"src/renderer/indexbuffer.h"
#include"src/renderer/vertexbuffer.h"
#include"src/renderer/bufferlayout.h"
#include"src/renderer/vertexarray.h"
#include"src/renderer/shader.h"
#include"src/renderer/renderer.h"
#include"src/renderer/texture.h"

//? -------- input ----------------------
#include"src/input/input.h"
#include"src/input/keycodes.h"
