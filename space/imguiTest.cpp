#include<novapch.h>
#include<nova.h>

int main(){
    nova::log::init();
    nova::log::log_to_client();

    {
        nova::window myWindow(960,540,"MyWindow");
        const char* glsl_version = "#version 130";
        float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();

        style.ScaleAllSizes(main_scale);
        style.FontScaleDpi = main_scale;

        ImGui_ImplGlfw_InitForOpenGL(myWindow.getWindow(),true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        ImVec4 clear_color = ImVec4(0,0,0,0);

        while(!myWindow.ShouldClose()){
            myWindow.clear();

            ImGui_ImplGlfw_NewFrame();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();

            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                
                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
                ImGui::Text("More useful text");

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }

            {
                static float gravity = 0.0f;
                
                ImGui::SetNextWindowPos(ImVec2(0,0),ImGuiCond_Always);
                ImGui::SetNextWindowSize(ImVec2(250,400),ImGuiCond_Always);

                ImGui::Begin("Physics Settings!",nullptr,ImGuiWindowFlags_NoMove);
                ImGui::Text("Edit all the physics properties from here!");

                ImGui::SliderFloat("Gravity",&gravity,1.0f,15.0f);
                ImGui::Text("Edit Gravity");
                ImGui::End();
            }

            ImGui::Render();

            int display_w, display_h;
            myWindow.getFrameBufferSize(&display_w,&display_h);
            glViewport(0, 0, display_w, display_h);

            myWindow.ClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            myWindow.SwapBuffers();
            myWindow.PollEvents();
            myWindow.update();
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
