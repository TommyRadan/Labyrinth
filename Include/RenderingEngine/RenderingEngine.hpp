#pragma once

#include <Infrastructure/Component.hpp>

namespace RenderingEngine
{
    class Context : public Component
    {
        Context() = default;

    public:
        static Context* GetInstance();

        void Init() final;
        void Quit() final;

        void Render();
    };
}
