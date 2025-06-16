#include "Application.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <iostream>

#include "Renderer/Renderer.h"
#include "Assets/AssetManager.h"
#include "Entities/EntityManager.h"
#include "Entities/Object.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        EntityManager::Initialise();

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

        m_Running = true;
    }

    void Application::Run()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;

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

        ShaderProgram modelShaders(RESOURCES_PATH "shaders/modelCombined.shader");

        AssetManager::CreateModel(RESOURCES_PATH "backpack/backpack.obj");
        AssetManager::CreateModel(RESOURCES_PATH "cube/cube.obj");

        EntityManager::CreateObject(EntityType::OBJECT, 1);
        EntityManager::CreateObject(EntityType::OBJECT, 2);

        static int objectSelected = 0;

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

            ImGui::BeginMainMenuBar();
                if (ImGui::BeginMenu("File"))
                {
                    // TODO: Add actual functionality not just placeholders

                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Edit"))
                {
                    // TODO: Add actual functionality not just placeholders

                    if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                    if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {} // Disabled item
                    ImGui::Separator();
                    if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                    if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                    if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Help"))
                {

                    // TODO: Fill in

                    ImGui::EndMenu();
                }
            ImGui::EndMainMenuBar();
            

            // Scene View
            {
                ImGui::Begin("Scene View");
                Renderer::StartFrame();

                ImVec2 windowSize = ImGui::GetContentRegionAvail();
                ImVec2 windowPosition = ImGui::GetCursorScreenPos();

                Camera* camera = Renderer::GetCamera();
                camera->SetAspectRatio(windowSize.x, windowSize.y);

                for (size_t i = 0; i < 10; i++)
                {
                    float angle = 20.0f * i;

                    //Renderer::Submit(2, modelShaders, TransformData(cubePositions[i], {5, 5, 5}, angle, { 0.5f, 1.0f, 0.0f }));
                }

                Object* object = (Object*)EntityManager::GetEntityByHandle(1);
                Object* objecta = (Object*)EntityManager::GetEntityByHandle(2);

                for (size_t i = 1; i < EntityManager::Size(); i++)
                {
                    Renderer::Submit(i, modelShaders);
                }

                //Renderer::Submit(1, modelShaders, backpackTransform);

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

            // Properties
            {
                ImGui::Begin("Properties");
                ImGui::Text("%.1f FPS (%.3f ms/frame)", io.Framerate, 1000.0f / io.Framerate);

                Entity* selectedEntity = EntityManager::GetEntityByHandle(objectSelected);

                switch (selectedEntity->Type)
                {
                case EntityType::NULLENTITY:
                    break;

                case EntityType::OBJECT:

                    Object* object = (Object*)selectedEntity;

                    TransformData* transform = object->GetTransformData();

                    ImGui::InputFloat3("Position", glm::value_ptr(transform->Position));
                    ImGui::InputFloat3("scale", glm::value_ptr(transform->Scale));
                    ImGui::InputFloat("rotation", &transform->Rotation);
                    ImGui::InputFloat3("Point of rotation", glm::value_ptr(transform->PointOfRotation));

                    break;
                }

                Camera* camera = Renderer::GetCamera();

                glm::vec3 cameraPosition = camera->GetPosition();

                ImGui::SeparatorText("Camera Transform");

                ImGui::SliderFloat("Camera X", &cameraPosition.x, -200.0f, 200.0f);
                ImGui::SliderFloat("Camera Y", &cameraPosition.y, -200.0f, 200.0f);
                ImGui::SliderFloat("Camera Z", &cameraPosition.z, -200.0f, 200.0f);
                camera->SetPosition(cameraPosition);

                ImGui::End();
            }

            // Asset Tray
            {
                ImGui::Begin("Asset Tray");

                ImGui::End();
            }

            // Scene Hierarchy
            {
                ImGui::Begin("Scene Hierarchy");

                ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

                for (size_t i = 1; i < EntityManager::Size(); i++)
                {
                    std::string entityName = std::to_string(i) + ". " + EntityManager::GetNameOfType(EntityManager::GetEntityByHandle(i)->Type);

                    if (ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, entityName.c_str()))
                    {
                        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                        {
                            objectSelected = i;
                        }
                    }
                }

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