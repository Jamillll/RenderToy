#include "Application.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"
#include <stdio.h>
#include <iostream>

#include "Renderer/Renderer.h"

#include "Assets/AssetManager.h"
#include "Assets/Model.h"
#include "Assets/Texture.h"

#include "Entities/EntityManager.h"
#include "Entities/Object.h"
#include "Entities/CameraEntity.h"

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

        Texture icon(RESOURCES_PATH "backpack/diffuse.jpg");

        AssetManager::CreateModel(RESOURCES_PATH "backpack/backpack.obj", true);
        AssetManager::CreateModel(RESOURCES_PATH "cube/cube.obj");
        AssetManager::CreateModel(RESOURCES_PATH "plushie_shark/scene.gltf", false);

        EntityManager::CreateObject(EntityType::OBJECT, 1);
        EntityManager::CreateObject(EntityType::OBJECT, 3);

        unsigned int handleSelected = 0;
        bool handleIsEntity = false;

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

            if (glfwGetKey(m_Window, GLFW_KEY_D) && glfwGetKey(m_Window, GLFW_KEY_LEFT_CONTROL))
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
            

            // TODO: Rework RenderToy Handles to store type and to not just be linear unsigned ints
            // This would also mean reworking Entity and Asset managers to be maps and not vectors

            SceneView();
            Properties(handleSelected, handleIsEntity);
            AssetTray(&icon, &handleSelected, &handleIsEntity);
            SceneHierarchy(&handleSelected, &handleIsEntity);

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

    void Application::SceneView()
    {
        ImGui::Begin("Scene View");

        if (ImGui::IsWindowFocused())
        {
            m_State.SceneViewCaptured = true;
            glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            CameraEntity* cameraEntity = (CameraEntity*)EntityManager::GetEntityByHandle(1);
            cameraEntity->CameraInput(m_Window);

            if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
                ImGui::SetWindowFocus("Properties");
        }
        else
        {
            m_State.SceneViewCaptured = false;
            glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        Renderer::StartFrame();

        ImVec2 windowSize = ImGui::GetContentRegionAvail();
        ImVec2 windowPosition = ImGui::GetCursorScreenPos();

        Camera* camera = Renderer::GetCamera();
        camera->SetAspectRatio(windowSize.x, windowSize.y);

        for (size_t i = 1; i < EntityManager::Size(); i++)
        {
            Renderer::Submit(i);
        }

        Renderer::EndFrame();

        ImGui::GetWindowDrawList()->AddImage(
            Renderer::GetFramebufferTextureID(),
            ImVec2(windowPosition.x, windowPosition.y),
            ImVec2(windowPosition.x + windowSize.x, windowPosition.y + windowSize.y),
            ImVec2(0, 1),
            ImVec2(1, 0));

        ImGui::End();
    }

    void Application::AssetTray(void* texture, AssetHandle* assetSelected, bool* isEntity)
    {
        if (m_State.SceneViewCaptured) ImGui::Begin("Asset Tray", nullptr, ImGuiWindowFlags_NoInputs);
        else ImGui::Begin("Asset Tray");

        Texture* textureP = (Texture*)texture;

        //TODO: Make the amount of columns resize based on window size BUT keep each item 64 by 64

        if (ImGui::BeginTable("Asset Grid", 8))
        {
            for (size_t i = 1; i < AssetManager::Size(); i++)
            {
                ImGui::TableNextColumn();
                ImGui::BeginGroup();

                std::string label = "Image" + std::to_string(i);
                std::string name = AssetManager::GetAssetByHandle(i)->name;

                ImGui::Image(textureP->GetID(), { 96.0f, 96.0f });
                ImGui::Text(name.c_str());
                ImGui::EndGroup();

                if (ImGui::IsItemClicked(0))
                {
                    *assetSelected = i;
                    *isEntity = false;
                }

                ImGui::SameLine();
            }
            ImGui::EndTable();
        }

        ImGui::End();
    }

    void Application::SceneHierarchy(EntityHandle* entitySelected, bool* isEntity)
    {
        if (m_State.SceneViewCaptured) ImGui::Begin("Scene Hierarchy", nullptr, ImGuiWindowFlags_NoInputs);
        else ImGui::Begin("Scene Hierarchy");

        ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

        for (size_t i = 1; i < EntityManager::Size(); i++)
        {
            std::string entityName = EntityManager::GetEntityByHandle(i)->Name;

            if (ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, entityName.c_str()))
            {
                if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                {
                    *entitySelected = i;
                    *isEntity = true;
                }
            }
        }

        if (ImGui::TreeNodeEx((void*)(intptr_t)EntityManager::Size(), node_flags, "Create Object +"))
        {
            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
            {
                ImGui::OpenPopup("Create Entity");
            }

            // Always center this window when appearing
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("Create Entity", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                static int type;
                ImGui::Combo("Type", &type, "Object\0");

                if (type + 1 == EntityType::OBJECT)
                {
                    static std::string input;
                    ImGui::InputText("Asset To Use (By path)", &input);

                    if (ImGui::Button("Create Object", ImVec2(120, 0)))
                    {
                        EntityManager::CreateObject(EntityType::OBJECT, AssetManager::GetAssetByPath(input));
                        input = "";
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Cancel", ImVec2(120, 0)))
                    {
                        ImGui::CloseCurrentPopup();
                    }
                }

                ImGui::EndPopup();
            }
        }

        ImGui::End();
    }

    void Application::Properties(unsigned int handleSelected, bool isEntity)
    {
        if (m_State.SceneViewCaptured) ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoInputs);
        else ImGui::Begin("Properties");

        if (isEntity) EntityProperties(handleSelected);
        else AssetProperties(handleSelected); 

        ImGui::End();
    }

    void Application::EntityProperties(EntityHandle entitySelected)
    {
        Entity* selectedEntity = EntityManager::GetEntityByHandle(entitySelected);

        switch (selectedEntity->Type)
        {
        case EntityType::NULLENTITY:
            break;

        case EntityType::OBJECT:
        {
            Object* object = (Object*)selectedEntity;

            ImGui::InputText("Name", &object->Name);

            TransformData* transform = object->GetTransformData();

            ImGui::DragFloat3("Position", glm::value_ptr(transform->Position), 0.5f);
            ImGui::DragFloat3("Scale", glm::value_ptr(transform->Scale), 0.5f);
            ImGui::DragFloat3("Point of rotation", glm::value_ptr(transform->PointOfRotation), 0.5f);
            ImGui::SliderAngle("Rotation", &transform->Rotation);
        }
        break;

        case EntityType::CAMERA:
        {
            CameraEntity* camera = (CameraEntity*)selectedEntity;

            ImGui::InputText("Name", &camera->Name);

            ImGui::DragFloat3("Position", glm::value_ptr(camera->Position));
            ImGui::DragFloat3("Front", glm::value_ptr(camera->Front));

            ImGui::DragFloat("Fov", &camera->Fov, 0.5f);
            ImGui::DragFloat("Speed", &camera->Speed, 0.01f);
            ImGui::DragFloat("Sensitivity", &camera->Sensitivity, 0.001f);

            camera->UpdateCameraPosition();
        }

        break;
        }
    }

    void Application::AssetProperties(AssetHandle assetSelected)
    {
        Asset* selectedAsset = AssetManager::GetAssetByHandle(assetSelected);

        switch (selectedAsset->assetType)
        {
        case AssetType::NULLASSET:
            break;

        case AssetType::MODEL:
        {
            Model* model = (Model*)selectedAsset;

            ImGui::InputText("Name", &model->name);
        }
        break;

        }
    }
}