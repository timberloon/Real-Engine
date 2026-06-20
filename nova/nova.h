#pragma once

//? --------- engine core --------------
#include"src/engine/application.h"
#include"src/engine/log.h"
#include"src/engine/window.h"
#include"src/engine/scene.h"
#include"src/engine/layer.h"
#include"src/engine/LayerStack.h"

//? --------- events -------------------
#include"src/event/event.h"
#include"src/event/ApplicationEvent.h"
#include"src/event/MouseEvent.h"
#include"src/event/KeyboardEvent.h"

//? ------ entity component system -----
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
#include"src/renderer/Srect.h"
#include"src/renderer/texturerect.h"

//? -------- input ----------------------
#include"src/input/input.h"
#include"src/input/keycodes.h"

//? -------- math -----------------------
#include"src/math/matrix.h"
