#pragma once
#include "core.h"
#include<vector>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
namespace nova {

    // Abstract input interface — platform implementations override the impl_ methods.
    // Use the static methods from anywhere in engine or game code:
    //
    //   if (nova::input::is_key_pressed(NOVA_KEY_W))   { ... }
    //   if (nova::input::is_mouse_button_pressed(NOVA_MOUSE_BUTTON_LEFT)) { ... }
    //   auto [x, y] = nova::input::get_mouse_position();

    class NOVA_API input {
    public:
        // -------- Keyboard --------
        inline static bool is_key_pressed(int keycode) {
            return s_instance->impl_is_key_pressed(keycode);
        }

        // -------- Mouse --------
        inline static bool is_mouse_button_pressed(int button) {
            return s_instance->impl_is_mouse_button_pressed(button);
        }

        inline static float get_mouse_x() {
            return s_instance->impl_get_mouse_x();
        }

        inline static float get_mouse_y() {
            return s_instance->impl_get_mouse_y();
        }

        inline static std::pair<float, float> get_mouse_position() {
            return s_instance->impl_get_mouse_position();
        }

    protected:
        virtual bool impl_is_key_pressed(int keycode) = 0;
        virtual bool impl_is_mouse_button_pressed(int button) = 0;
        virtual float impl_get_mouse_x() = 0;
        virtual float impl_get_mouse_y() = 0;
        virtual std::pair<float, float> impl_get_mouse_position() = 0;

    private:
        static input* s_instance;
    };

} // namespace nova