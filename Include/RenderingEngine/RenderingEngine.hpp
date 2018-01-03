#pragma once

#include <Infrastructure/Component.hpp>
#include <RenderingEngine\Renderables\Renderable.hpp>
#include <vector>

namespace RenderingEngine
{
    class Context : public Component
    {
        Context() = default;

    public:
        static Context* GetInstance();

        void Init() final;
        void Quit() final;

		void AddRenderable(Renderable* renderable);
        void Render();

	private:
		std::vector<Renderable*> m_Renderables;
    };
}
