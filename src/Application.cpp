#include "Application.hpp"
#include "Window/Window.hpp"
#include "Events/Event.hpp"
#include "Events/Events.hpp"
#include "Events/EventManager.hpp"
#include "Window/KeyCodes.hpp"
#include "DataStructures/Stack.hpp"

#include "Graphic/Graphic.hpp"
#include "Graphic/Camera/Camera.hpp"
#include "Player/Player.hpp"
#include "ImGuiWrapper.hpp"

#include <glm/vec3.hpp>
#include <glm/ext.hpp>



static bool walkCallback(Player* player, Event* e)
{
    if (Window::GetI().isInGuiMode()){return true;}
    
    KeyPressedEvent* E = (KeyPressedEvent*)e;
    int keycode = E->keycode;
    float sens = 0.005;

    if (keycode==KEY_D || keycode==KEY_A)
    {
        float sign = (keycode==KEY_D) ? 1.0f : -1.0f;
        glm::vec3 right = glm::normalize(glm::cross(player->getDir(), {0.0f, 1.0f, 0.0f}));
        player->setPos(player->getPos() + sens*sign*right);
    }
    else if (keycode==KEY_W || keycode==KEY_S)
    {
        float sign = (keycode==KEY_W) ? 1.0f : -1.0f;
        player->setPos(player->getPos() + sens*sign*player->getDir());
    }
    else if (keycode==KEY_SPACE || keycode==KEY_LEFT_SHIFT)
    {
        float sign = (keycode==KEY_SPACE) ? 1.0f : -1.0f;
        player->setPos(player->getPos() + sens*sign*glm::vec3(0.0f, 1.0f, 0.0f));
    }

    return true;
}

static bool guiSwitchCallback(Event* e)
{
    KeyReleasedEvent* E = (KeyReleasedEvent*)e;
    int keycode = E->keycode;

    if (keycode==KEY_TAB){
        Window::GetI().switchGuiMode();
        ImGuiWrapper::GetI().swithAccess();
    }

    return true;
}

static bool cameraMoveCallback(Player* player, Event* e)
{
    if (Window::GetI().isInGuiMode()){return true;}

    MouseMovedEvent* E = (MouseMovedEvent*)e;
    float dy = E->dy;
    float dx = E->dx;

    float sens = 0.001f;
    auto [pitch, yaw] = player->getRotation();
    player->setRotation(pitch - sens*dy, yaw + sens*dx);
    
    return true;
}

int Application::run()
{
    Window::GetI().Init(1024, 768);
    ImGuiWrapper::GetI().Init();
    Renderer::GetI().Init();
    EventManager::GetI().Init();

    Camera camera;
    Player player(&camera, glm::vec3(0.0f));

    // Sky Box
    SkyBoxPipeline skyboxPipe;
    skyboxPipe.camera = &camera;
    skyboxPipe.shader.Init("D:\\kubiki\\resources\\shaders\\skyBoxVertex.shader", "D:\\kubiki\\resources\\shaders\\skyBoxFragment.shader");
    skyboxPipe.enable();
    Renderer::GetI().addPipeline("SkyBoxPipeline", &skyboxPipe);

    // Primitives
    PrimitivePipeline primitivePipe;
    primitivePipe.camera = &camera;
    primitivePipe.shader.Init("D:\\kubiki\\resources\\shaders\\vertex.shader", "D:\\kubiki\\resources\\shaders\\fragment.shader");
    
    Triangle triangle2({2.0f, 0.0f, 1.0f});
    primitivePipe.addMesh(&triangle2.mesh);
    Triangle triangle;
    primitivePipe.addMesh(&triangle.mesh);

    std::vector<Cube> cubeVec;
    for (int x=-50; x<50; x+=2){
        for (int z=-50; z<50; z+=2){
            glm::vec3 pos = {(float)x, -2.0f, (float)z};
            cubeVec.emplace_back(pos);
        }
    }

    for (int i=0; i<cubeVec.size(); i++){
        primitivePipe.addMesh(&(cubeVec[i].mesh));
    }

    primitivePipe.enable();
    Renderer::GetI().addPipeline("PrimitivePipeline", &primitivePipe);

    // Callbacks
    EventManager::GetI().addCallback(Event::EventType::KEY_PRESSED_E, std::bind(walkCallback, &player, std::placeholders::_1));
    EventManager::GetI().addCallback(Event::EventType::MOUSE_MOVED_E, std::bind(cameraMoveCallback, &player, std::placeholders::_1));
    EventManager::GetI().addCallback(Event::EventType::KEY_RELEASED_E, guiSwitchCallback);

    EventManager::GetI().addCallback(Event::EventType::KEY_PRESSED_E, [](Event* e){
        KeyPressedEvent* E = (KeyPressedEvent*)e;
        if (E->keycode == KEY_ESCAPE){
            Window::GetI().close();
        }
        return true;
    });

    bool show_another_window = false;
    glm::vec4 clear_color = {0.45f, 0.55f, 0.60f, 1.00f};

    while (!Window::GetI().isShouldClose())
    {
        Window::GetI().SwapBuffers();
        Renderer::GetI().clear();
        Window::GetI().PullEvents();
        EventManager::GetI().processEvents();

        ImGuiWrapper::GetI().NewFrame();

        {
            static float fov = 100.0f;
            static int counter = 0;

            ImGuiWrapper::GetI().Begin("Hello, world!");

            ImGuiWrapper::GetI().Text("This is some useful text.");
            ImGuiWrapper::GetI().Checkbox("Another Window", &show_another_window);
            ImGuiWrapper::GetI().Text("Is in gui mode: %d", (int)Window::GetI().isInGuiMode());

            ImGuiWrapper::GetI().SliderFloat("FOV", &fov, 5.0f, 175.0f);
            camera.setFOV(fov);
            ImGuiWrapper::GetI().ColorEdit3("clear color", (float*)&clear_color);

            if (ImGuiWrapper::GetI().Button("Button"))
                counter++;
            ImGuiWrapper::GetI().SameLine();
            ImGuiWrapper::GetI().Text("counter = %d", counter);

            float fps = ImGuiWrapper::GetI().getFramerate();
            ImGuiWrapper::GetI().Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / fps, fps);
            ImGuiWrapper::GetI().End();
        }

        Renderer::GetI().render();
        ImGuiWrapper::GetI().Render();
    }

    exit(EXIT_SUCCESS);
}