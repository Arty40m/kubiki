#include "logging.hpp"

#include "Application.hpp"
#include "Window/Window.hpp"
#include "Events/Event.hpp"
#include "Events/Events.hpp"
#include "Events/EventManager.hpp"

#include "ImGuiWrapper.hpp"
#include "Physics/PhysicsManager.hpp"

#include <glm/vec3.hpp>
#include <glm/ext.hpp>



static bool walkCallback(Player* player, Event* e)
{
    if (Window::GetI().isInGuiMode()){return true;}
    
    KeyPressedEvent* E = (KeyPressedEvent*)e;
    int keycode = E->keycode;

    if (!player->isOnGround())
        return true;

    if (keycode==KEY_A){
        player->stepLeft();
    } else if (keycode==KEY_D){
        player->stepRight();
    } else if (keycode==KEY_W){
        player->stepForward();
    } else if (keycode==KEY_S){
        player->stepBack();
    } else if (keycode==KEY_SPACE && E->isJustClicked()){
        player->jump();
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

Application::Application()
{
    Window::GetI().Init(1024, 768);
    ImGuiWrapper::GetI().Init();
    Renderer::GetI().Init();
    EventManager::GetI().Init();

    player = new Player(&camera, glm::vec3(0.0f));

    // Sky Box
    skyboxPipePtr = new SkyBoxPipeline;
    skyboxPipePtr->camera = &camera;
    skyboxPipePtr->shader.Init("D:\\kubiki\\resources\\shaders\\skyBoxVertex.shader", "D:\\kubiki\\resources\\shaders\\skyBoxFragment.shader");
    skyboxPipePtr->enable();
    Renderer::GetI().addPipeline("SkyBoxPipeline", skyboxPipePtr);

    // // Primitives
    primitivePipePtr = new PrimitivePipeline;
    primitivePipePtr->camera = &camera;
    primitivePipePtr->shader.Init("D:\\kubiki\\resources\\shaders\\vertex.shader", "D:\\kubiki\\resources\\shaders\\fragment.shader");
    primitivePipePtr->enable();
    Renderer::GetI().addPipeline("PrimitivePipeline", primitivePipePtr);

    for (int x=-50; x<50; x+=2){
        for (int z=-50; z<50; z+=2){
            glm::vec3 pos = {(float)x, -2.0f, (float)z};
            cubeVec.emplace_back(pos);
        }
    }

    for (int x=-50; x<50; x+=4){
        for (int z=-50; z<50; z+=4){
            glm::vec3 pos = {(float)x, 1.0f, (float)z};
            cubeVec.emplace_back(pos);
        }
    }

    for (int x=-50; x<50; x+=8){
        for (int z=-50; z<50; z+=8){
            glm::vec3 pos = {(float)x, 3.0f, (float)z};
            cubeVec.emplace_back(pos);
        }
    }

    for (int i=0; i<cubeVec.size(); i++){
        primitivePipePtr->addMesh(&(cubeVec[i].mesh));
    }

    // Callbacks
    EventManager::GetI().addCallback(Event::EventType::KEY_PRESSED_E, std::bind(walkCallback, player, std::placeholders::_1));
    EventManager::GetI().addCallback(Event::EventType::MOUSE_MOVED_E, std::bind(cameraMoveCallback, player, std::placeholders::_1));
    EventManager::GetI().addCallback(Event::EventType::KEY_RELEASED_E, guiSwitchCallback);

    EventManager::GetI().addCallback(
        Event::EventType::KEY_PRESSED_E, 
        std::bind(
            [](Engine* engPtr, Event* e){
                KeyPressedEvent* E = (KeyPressedEvent*)e;
                if (E->keycode == KEY_ESCAPE){
                    engPtr->shutdown();
                }
                return true;
            }, this, std::placeholders::_1
        )
    );
}

Application::~Application(){}

void Application::onUpdate()
{
    Window::GetI().SwapBuffers();
    Renderer::GetI().clear();
    Window::GetI().PullEvents();
    EventManager::GetI().processEvents();
    PhysicsManager::GetI().movePlayer(player, getDeltaTime());

    ImGuiWrapper::GetI().NewFrame();

    {
        static float fov = 100.0f;
        static int counter = 0;

        ImGuiWrapper::GetI().Begin("Hello, world!");
        ImGuiWrapper::GetI().Text("Is in gui mode: %d", (int)Window::GetI().isInGuiMode());

        ImGuiWrapper::GetI().SliderFloat("FOV", &fov, 5.0f, 175.0f);
        camera.setFOV(fov);

        ImGuiWrapper::GetI().SliderFloat("Jump strength", &player->jumpStrength, 1.0f, 250.0f);
        ImGuiWrapper::GetI().SliderFloat("Jump time", &player->jumpTime, 0.01f, 0.5f);
        ImGuiWrapper::GetI().SliderFloat("Move speed", &player->moveSpeed, 1.0f, 150.0f);
        ImGuiWrapper::GetI().SliderFloat("Deacceleration", &PhysicsManager::GetI().deacc, 0.01f, 10.0f);
        ImGuiWrapper::GetI().SliderFloat("Vel Th", &PhysicsManager::GetI().velTh, 0.5f, 10.0f);
        ImGuiWrapper::GetI().Text("Y: %.4f", player->getPos().y);
        
        glm::vec3 vel = player->pcomp.velocity;
        glm::vec3 force = player->pcomp.force;
        ImGuiWrapper::GetI().Text("Velocity: %.4f, %.4f, %.4f", vel.x, vel.y, vel.z);

        float fps = ImGuiWrapper::GetI().getFramerate();
        ImGuiWrapper::GetI().Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / fps, fps);
        ImGuiWrapper::GetI().Text("My %.3f ms/frame (%.1f FPS)", 1000.0f * getDeltaTime(), 1.0f / getDeltaTime());
        ImGuiWrapper::GetI().End();
    }

    Renderer::GetI().render();
    ImGuiWrapper::GetI().Render();
}