#include "Application.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include "Renderer/Renderer.h"
#include "Assets/AssetManager.h"

namespace RenderToy
{
    Application::Application()
    {
        assert(glfwInit());

        const char* glsl_version = "#version 330";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

        // Create window with graphics context
        m_Window = glfwCreateWindow(1280, 720, "RenderToy", nullptr, nullptr);
        assert(m_Window != nullptr);

        glfwMakeContextCurrent(m_Window);
        gladLoadGL();
        glfwSwapInterval(1); // Enable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        //ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        Renderer::Initialise(1280, 720);
        AssetManager::Initialise();

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

        m_Running = true;
    }

    void Application::Run()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ShaderProgram modelShaders(RESOURCES_PATH "shaders/modelCombined.shader");

        AssetManager::CreateModel(RESOURCES_PATH "backpack/backpack.obj");
        AssetManager::CreateModel(RESOURCES_PATH "cube/cube.obj");

        float position[3] = { 0, 0, 0 };
        float scale[3] = { 10, 10, 10 };
        float rotation = 0;
        float pointOfRotation[3] = { 0, 0, 1 };

        while (m_Running)
        {
            if (glfwWindowShouldClose(m_Window)) m_Running = false;

            glfwPollEvents();
            if (glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED) != 0)
            {
                ImGui_ImplGlfw_Sleep(10);
                continue;
            }

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::DockSpaceOverViewport();

            if (glfwGetKey(m_Window, GLFW_KEY_D))
                m_State.showDemoWindow = !m_State.showDemoWindow;

            if (m_State.showDemoWindow)
                ImGui::ShowDemoWindow(&m_State.showDemoWindow);

            // main
            {
                ImGui::Begin("Main");
                Renderer::StartFrame();

                ImVec2 windowSize = ImGui::GetContentRegionAvail();
                ImVec2 windowPosition = ImGui::GetCursorScreenPos();

                Camera* camera = Renderer::GetCamera();
                camera->SetAspectRatio(windowSize.x, windowSize.y);

                for (size_t i = 0; i < 10; i++)
                {
                    float angle = 20.0f * i;

                    Renderer::Submit(2, modelShaders, TransformData(cubePositions[i], {5, 5, 5}, angle, { 0.5f, 1.0f, 0.0f }));
                }

                TransformData backpackTransform =
                {
                    {position[0], position[1], position[2]},
                    {scale[0], scale[1], scale[2]},
                    rotation,
                    {pointOfRotation[0], pointOfRotation[1], pointOfRotation[2]}
                };

                Renderer::Submit(1, modelShaders, backpackTransform);

                Renderer::EndFrame();

                // The first parameter of the Add image function takes an OpenGL image ID
                // The second and third parameters define the size of the image, 
                // the first being upper left while the second is the lower right
                // The final two parameters define normalised texture coordinates
                // (we're setting the same ones as openGL here)

                ImGui::GetWindowDrawList()->AddImage(
                    Renderer::GetFramebufferTextureID() ,
                    ImVec2(windowPosition.x, windowPosition.y),
                    ImVec2(windowPosition.x + windowSize.x, windowPosition.y + windowSize.y),
                    ImVec2(0, 1),
                    ImVec2(1, 0));

                ImGui::End();
            }

            // Sidebar
            {
                ImGui::Begin("Sidebar");
                ImGui::Text("%.1f FPS (%.3f ms/frame)", io.Framerate, 1000.0f / io.Framerate);

                Camera* camera = Renderer::GetCamera();

                glm::vec3 cameraPosition = camera->GetPosition();

                ImGui::SeparatorText("Camera Transform");

                ImGui::SliderFloat("Camera X", &cameraPosition.x, -200.0f, 200.0f);
                ImGui::SliderFloat("Camera Y", &cameraPosition.y, -200.0f, 200.0f);
                ImGui::SliderFloat("Camera Z", &cameraPosition.z, -200.0f, 200.0f);
                camera->SetPosition(cameraPosition);

                ImGui::SeparatorText("Backpack Transform");

                ImGui::InputFloat3("Position", position);
                ImGui::InputFloat3("scale", scale);
                ImGui::InputFloat("rotation", &rotation);
                ImGui::InputFloat3("Point of rotation", pointOfRotation);

                ImGui::End();
            }

            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(m_Window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);

            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }

            glfwSwapBuffers(m_Window);
        }
    }

    Application::~Application()
    {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

}