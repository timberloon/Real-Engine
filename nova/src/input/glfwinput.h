#pragma once
#include "input.h"

namespace nova {

    // GLFW implementation of the abstract input class.
    // Queries GLFW directly for key/mouse state each frame (polling model).
    // The window pointer is retrieved via glfwGetCurrentContext() so no
    // Window abstraction class is needed yet — matches your current setup
    // in space.cpp where glfwMakeContextCurrent(wnd) is called.

    class NOVA_API glfw_input : public input {
    protected:
        bool impl_is_key_pressed(int keycode) override {
            auto* window = glfwGetCurrentContext();
            auto state = glfwGetKey(window, keycode);
            return state == GLFW_PRESS || state == GLFW_REPEAT;
        }

        bool impl_is_mouse_button_pressed(int button) override {
            auto* window = glfwGetCurrentContext();
            auto state = glfwGetMouseButton(window, button);
            return state == GLFW_PRESS;
        }

        float impl_get_mouse_x() override {
            auto [x, y] = impl_get_mouse_position();
            return x;
        }

        float impl_get_mouse_y() override {
            auto [x, y] = impl_get_mouse_position();
            return y;
        }

        std::pair<float, float> impl_get_mouse_position() override {
            auto* window = glfwGetCurrentContext();
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            return { (float)xpos, (float)ypos };
        }
    };

} // namespace nova