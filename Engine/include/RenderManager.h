#pragma once
#include "Direct3DManager.h"

namespace Venture {
	class RenderManager {
	private:
		Direct3DManager m_direct3DManager;
		HWND m_window;
	public:
		RenderManager(HWND window);
		int Init();
		void Render();
	};
}