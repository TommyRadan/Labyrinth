#pragma once

#include <Infrastructure/Component.hpp>
#include <string>

namespace RenderingEngine
{
    class Window : public Component
    {
        Window();

    public:
        static Window* GetInstance();

        void Init() final;
        void Quit() final;

        void Clear();
        void SwapBuffers();
        void ShowMessage(const std::string& title, const std::string& message);

    private:
        void* m_Window;
        void* m_GlContext;
    };
}
