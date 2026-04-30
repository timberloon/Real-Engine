// ============================================================
//  Nova Engine — Demo 1: Graphics Pipeline Showcase
//
//  Demonstrates each layer of the graphics pipeline explicitly:
//
//    Panel 1 (left)   — Flat colour quad, animated via u_clr uniform
//                       Shows: VBO + VAO + IBO + Shader + uniforms
//
//    Panel 2 (centre) — Textured quad (summer tree asset)
//                       Shows: Texture pipeline + texturevert/frag shaders
//
//    Panel 3 (right)  — Same texture, tinted amber via u_clr uniform
//                       Shows: combining texture + colour uniform in one shader
//
//  One shared unit-square VAO drives all three draw calls.
//  Position and size are set per-draw via u_offset / u_scale uniforms.
//  Press ESC to exit.
// ============================================================

#include "nova/novapch.h"
#include "nova.h"
#include "src/input/keycodes.h"

int main(){
    nova::log::init();
    nova::log::log_to_client();

    nova::window win(1280, 720, "Nova — Demo 1: Graphics Pipeline");

    {
        // ----------------------------------------------------------
        // Geometry: one unit square, centred at origin.
        // All three panels share this single VAO.
        // ----------------------------------------------------------
        float verts[] = {
            // pos (xy)      texcoord (uv)
            -0.5f, -0.5f,   0.0f, 0.0f,
             0.5f, -0.5f,   1.0f, 0.0f,
             0.5f,  0.5f,   1.0f, 1.0f,
            -0.5f,  0.5f,   0.0f, 1.0f,
        };
        uint indices[] = { 0,1,2, 0,2,3 };

        nova::BufferLayout layout;
        layout.push<float>(2); // position
        layout.push<float>(2); // texcoord

        nova::VertexBuffer vbo(verts, sizeof(verts));
        nova::VertexArray  vao;
        vao.addBuffer(vbo, layout);
        nova::IndexBuffer  ibo(indices, 6);

        // ----------------------------------------------------------
        // Shaders
        // ----------------------------------------------------------

        // Panel 1: flat colour, driven by u_clr uniform
        nova::shader flatShader(
            "nova/src/renderer/shaders/transform.glsl",
            "nova/src/renderer/shaders/fragment.glsl"
        );

        // Panels 2 & 3: textured (panel 3 also reads u_clr for tint)
        nova::shader texShader(
            "nova/src/renderer/shaders/texturetransform.glsl",
            "nova/src/renderer/shaders/texturefrag.glsl"
        );

        // Panel 3: tinted texture — reuse texShader but override colour
        // We'll use a second shader instance with a modified frag that
        // multiplies texture colour by u_clr.
        // We ship a small inline tint frag as a runtime-written temp file
        // so we don't need a new asset file in the repo.
        {
            std::ofstream tf("build/tintfrag_tmp.glsl");
            tf << "#version 330 core\n"
               << "out vec4 fragcolor;\n"
               << "uniform vec4 u_clr;\n"
               << "in vec2 TextureCoordinates;\n"
               << "uniform sampler2D myTexture;\n"
               << "void main(){\n"
               << "    fragcolor = texture(myTexture, TextureCoordinates) * u_clr;\n"
               << "}\n";
        }
        nova::shader tintShader(
            "nova/src/renderer/shaders/texturetransform.glsl",
            "build/tintfrag_tmp.glsl"
        );

        // ----------------------------------------------------------
        // Texture
        // ----------------------------------------------------------
        nova::texture tree("assets/summer_tree.png", false, GL_NEAREST, 0);

        nova::renderer ren;

        // ----------------------------------------------------------
        // Panel layout in NDC:
        //   Panel 1:  centre x = -0.6,  width = 0.55, height = 0.75
        //   Panel 2:  centre x =  0.0,  same size
        //   Panel 3:  centre x =  0.6,  same size
        // ----------------------------------------------------------
        const float pw = 0.50f; // half-width of each panel quad (scale x)
        const float ph = 0.65f; // half-height
        const float p1x = -0.62f, p2x = 0.0f, p3x = 0.62f;
        const float py  =  0.0f;

        // Background colour — dark slate so panels pop
        glClearColor(0.08f, 0.08f, 0.12f, 1.0f);

        // Colour cycle state for panel 1
        float hue = 0.0f;

        // Lambda: HSV → RGB (simple, no deps)
        auto hsv2rgb = [](float h, float s, float v,
                          float& r, float& g, float& b){
            int   i = (int)(h * 6.0f);
            float f = h * 6.0f - i;
            float p = v * (1 - s);
            float q = v * (1 - f * s);
            float t = v * (1 - (1 - f) * s);
            switch(i % 6){
                case 0: r=v; g=t; b=p; break;
                case 1: r=q; g=v; b=p; break;
                case 2: r=p; g=v; b=t; break;
                case 3: r=p; g=q; b=v; break;
                case 4: r=t; g=p; b=v; break;
                default:r=v; g=p; b=q; break;
            }
        };

        double lastTime = glfwGetTime();

        while(!win.ShouldClose()){
            // ESC to quit
            if(nova::input::is_key_pressed(NOVA_KEY_ESCAPE)) break;

            double now = glfwGetTime();
            float  dt  = (float)(now - lastTime);
            lastTime   = now;

            glClear(GL_COLOR_BUFFER_BIT);

            // --- Panel 1: animated flat colour ---
            hue += dt * 0.18f;
            if(hue > 1.0f) hue -= 1.0f;
            float r, g, b;
            hsv2rgb(hue, 0.75f, 0.95f, r, g, b);

            vao.bind(); ibo.bind();
            flatShader.bind();
            flatShader.addUniform2f("u_offset", p1x, py);
            flatShader.addUniform2f("u_scale",  pw,  ph);
            flatShader.addUniform4f("u_clr", r, g, b, 1.0f);
            ren.draw(vao, ibo, flatShader);

            // --- Panel 2: plain texture ---
            tree.bind();
            texShader.bind();
            texShader.addUniform2f("u_offset", p2x, py);
            texShader.addUniform2f("u_scale",  pw,  ph);
            texShader.addUniform1i("myTexture", 0);
            ren.draw(vao, ibo, texShader);

            // --- Panel 3: tinted texture (warm amber) ---
            tintShader.bind();
            tintShader.addUniform2f("u_offset", p3x, py);
            tintShader.addUniform2f("u_scale",  pw,  ph);
            tintShader.addUniform1i("myTexture", 0);
            tintShader.addUniform4f("u_clr", 1.0f, 0.72f, 0.25f, 1.0f);
            ren.draw(vao, ibo, tintShader);

            win.SwapBuffers();
            win.PollEvents();
        }
    }

    return 0;
}