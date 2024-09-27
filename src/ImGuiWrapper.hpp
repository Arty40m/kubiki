#pragma once
#include "stlh.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


class ImGuiWrapper
{
public:
    ImGuiWrapper(const ImGuiWrapper&) = delete;
    ImGuiWrapper& operator=(const ImGuiWrapper&) = delete;

    static ImGuiWrapper& GetI();
    
    // Instance methods
    void Init();
    void swithAccess();
    void NewFrame();
    void Render();
    float getFramerate();

    void Begin(const char *name);
    void End();

    template<typename ...Args>
    void Text(const char *fmt, Args&& ... args);
    void Checkbox(const char *label, bool *v);
    void SliderFloat(const char *label, float *v, float v_min, float v_max, const char *format = "%.3f");
    void ColorEdit3(const char *label, float *col);
    bool Button(const char *label);
    void SameLine();

private:
    bool accessible;

    ImGuiWrapper();
    ~ImGuiWrapper();    
};


template<typename ...Args>
inline void ImGuiWrapper::Text(const char *fmt, Args&& ... args)
{
    ImGui::Text(fmt, std::forward<Args>(args)...);
}