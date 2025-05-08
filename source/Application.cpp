#include "Application.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include "renderer/ShaderProgram.h"
#include "renderer/Buffer.h"
#include "renderer/VertexArray.h"
#include "renderer/BufferLayout.h"
#include "renderer/Framebuffer.h"
#include "renderer/Camera.h"

#include "renderer/Renderer.h"

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

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

        m_Running = true;
    }

    void Application::Run()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            -10.5f, -10.5f, -10.5f,  0.0f, 0.0f, 0.0f,
             10.5f, -10.5f, -10.5f,  1.0f, 0.0f, 0.0f,
             10.5f,  10.5f, -10.5f,  1.0f, 1.0f, 0.0f,
             10.5f,  10.5f, -10.5f,  1.0f, 1.0f, 0.0f,
            -10.5f,  10.5f, -10.5f,  0.0f, 1.0f, 0.0f,
            -10.5f, -10.5f, -10.5f,  0.0f, 0.0f, 0.0f,
                               
            -10.5f, -10.5f,  10.5f,  0.0f, 0.0f, 0.0f,
             10.5f, -10.5f,  10.5f,  1.0f, 0.0f, 0.0f,
             10.5f,  10.5f,  10.5f,  1.0f, 1.0f, 0.0f,
             10.5f,  10.5f,  10.5f,  1.0f, 1.0f, 0.0f,
            -10.5f,  10.5f,  10.5f,  0.0f, 1.0f, 0.0f,
            -10.5f, -10.5f,  10.5f,  0.0f, 0.0f, 0.0f,
                               
            -10.5f,  10.5f,  10.5f,  1.0f, 0.0f, 0.0f,
            -10.5f,  10.5f, -10.5f,  1.0f, 1.0f, 0.0f,
            -10.5f, -10.5f, -10.5f,  0.0f, 1.0f, 0.0f,
            -10.5f, -10.5f, -10.5f,  0.0f, 1.0f, 0.0f,
            -10.5f, -10.5f,  10.5f,  0.0f, 0.0f, 0.0f,
            -10.5f,  10.5f,  10.5f,  1.0f, 0.0f, 0.0f,
                               
             10.5f,  10.5f,  10.5f,  1.0f, 0.0f, 0.0f,
             10.5f,  10.5f, -10.5f,  1.0f, 1.0f, 0.0f,
             10.5f, -10.5f, -10.5f,  0.0f, 1.0f, 0.0f,
             10.5f, -10.5f, -10.5f,  0.0f, 1.0f, 0.0f,
             10.5f, -10.5f,  10.5f,  0.0f, 0.0f, 0.0f,
             10.5f,  10.5f,  10.5f,  1.0f, 0.0f, 0.0f,
                                              
            -10.5f, -10.5f, -10.5f,  0.0f, 1.0f, 0.0f,
             10.5f, -10.5f, -10.5f,  1.0f, 1.0f, 0.0f,
             10.5f, -10.5f,  10.5f,  1.0f, 0.0f, 0.0f,
             10.5f, -10.5f,  10.5f,  1.0f, 0.0f, 0.0f,
            -10.5f, -10.5f,  10.5f,  0.0f, 0.0f, 0.0f,
            -10.5f, -10.5f, -10.5f,  0.0f, 1.0f, 0.0f,
                                              
            -10.5f,  10.5f, -10.5f,  0.0f, 1.0f, 0.0f,
             10.5f,  10.5f, -10.5f,  1.0f, 1.0f, 0.0f,
             10.5f,  10.5f,  10.5f,  1.0f, 0.0f, 0.0f,
             10.5f,  10.5f,  10.5f,  1.0f, 0.0f, 0.0f,
            -10.5f,  10.5f,  10.5f,  0.0f, 0.0f, 0.0f,
            -10.5f,  10.5f, -10.5f,  0.0f, 1.0f, 0.0f
        };

        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(20.0f,  50.0f, -150.0f),
            glm::vec3(-10.5f, -20.2f, -20.5f),
            glm::vec3(-30.8f, -20.0f, -120.3f),
            glm::vec3(20.4f, -0.4f, -30.5f),
            glm::vec3(-10.7f,  30.0f, -70.5f),
            glm::vec3(10.3f, -20.0f, -20.5f),
            glm::vec3(10.5f,  20.0f, -20.5f),
            glm::vec3(10.5f,  00.2f, -10.5f),
            glm::vec3(-10.3f,  10.0f, -10.5f)
        };

        BufferLayout layout =
        {
            {"Position", ShaderDataType::Float3},
            {"Colour", ShaderDataType::Float3}
        };

        VertexArray VAO(layout);
        VAO.UploadVertexData(sizeof(vertices), vertices, 36);

        ShaderProgram shaders(RESOURCES_PATH "shaders/basicCombined.shader");

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

                ImVec2 windowSize = ImGui::GetContentRegionAvail();
                ImVec2 position = ImGui::GetCursorScreenPos();

                Renderer::StartFrame();

                Camera* camera = Renderer::GetCamera();
                camera->SetAspectRatio(windowSize.x, windowSize.y);

                for (size_t i = 0; i < 10; i++)
                {
                    float angle = 20.0f * i;

                    Renderer::Submit(VAO, shaders, cubePositions[i], angle, glm::vec3(0.5f, 1.0f, 0.0f));
                }

                Renderer::EndFrame();

                // The first parameter of the Add image function takes an OpenGL image ID
                // The second and third parameters define the size of the image, 
                // the first being upper left while the second is the lower right
                // The final two parameters define normalised texture coordinates
                // (we're setting the same ones as openGL here)

                ImGui::GetWindowDrawList()->AddImage(
                    Renderer::GetFramebufferTextureID() ,
                    ImVec2(position.x, position.y),
                    ImVec2(position.x + windowSize.x, position.y + windowSize.y),
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

                ImGui::SliderFloat("Camera X", &cameraPosition.x, -200.0f, 200.0f);
                ImGui::SliderFloat("Camera Y", &cameraPosition.y, -200.0f, 200.0f);
                ImGui::SliderFloat("Camera Z", &cameraPosition.z, -200.0f, 200.0f);
                camera->SetPosition(cameraPosition);

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