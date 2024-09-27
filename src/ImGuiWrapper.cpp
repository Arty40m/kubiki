#include "ImGuiWrapper.hpp"
#include "logging.hpp"

#include "Window/Window.hpp"



ImGuiWrapper& ImGuiWrapper::GetI()
{
    static ImGuiWrapper instance;
    return instance;
}

void ImGuiWrapper::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NoKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
    accessible = false;

    Window::GetI().imguiInit();

    ImGui_ImplOpenGL3_Init();
}

ImGuiWrapper::ImGuiWrapper(){}

ImGuiWrapper::~ImGuiWrapper()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiWrapper::swithAccess()
{
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags ^= ImGuiConfigFlags_NoKeyboard;
    io.ConfigFlags ^= ImGuiConfigFlags_NoMouse;
    if (accessible){
        io.ConfigFlags ^= ImGuiConfigFlags_NavEnableKeyboard;
    } else {
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;        
    }
    accessible = !accessible;
}

void ImGuiWrapper::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiWrapper::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

float ImGuiWrapper::getFramerate()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    return io.Framerate;
}


void ImGuiWrapper::Begin(const char* name)
{
    ImGui::Begin(name);
}

void ImGuiWrapper::End()
{
    ImGui::End();
}

void ImGuiWrapper::Checkbox(const char* label, bool* v)
{
    ImGui::Checkbox(label, v);
}

void ImGuiWrapper::SliderFloat(const char* label, float *v, float v_min, float v_max, const char* format)
{
    ImGui::SliderFloat(label, v, v_min, v_max, format); 
}

void ImGuiWrapper::ColorEdit3(const char* label, float* col)
{
    ImGui::ColorEdit3(label, col);
}

bool ImGuiWrapper::Button(const char* label)
{
    return ImGui::Button(label);
}

void ImGuiWrapper::SameLine(){}