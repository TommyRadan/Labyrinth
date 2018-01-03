#pragma once

#include <RenderingEngine/Renderers/Renderer.hpp>

namespace RenderingEngine
{
	namespace Renderers
	{
		class TexturedRenderer : public Renderer
		{
			TexturedRenderer();

		public:
			static TexturedRenderer* GetInstance();

			~TexturedRenderer();
		};
	}
}
