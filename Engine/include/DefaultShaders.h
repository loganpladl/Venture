#pragma once
#include "VertexShader.h"
#include "PixelShader.h"

namespace Venture {
	class DefaultShaders {
	private:
		// Use "construct on first use" idiom to avoid static initialization order disaster
		// in which materials are created before referenced shaders
	public:
		inline static VertexShader* VertexUnlit() {
			static VertexShader* vertexUnlit = new VertexShader("VertexShader.cso");
			return vertexUnlit;
		}
		inline static PixelShader* PixelUnlit() {
			static PixelShader* pixelUnlit = new PixelShader("PixelShader.cso");
			return pixelUnlit;
		}
	};
}