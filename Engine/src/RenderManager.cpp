#include "../include/RenderManager.h"
#include "../include/Time.h"

namespace Venture {
	RenderManager::RenderManager() {
		m_window = nullptr;
		m_direct3DManager;
	}

	int RenderManager::Init(HWND window) {
		int error = m_direct3DManager.Init(window);
		return error;
	}

	void RenderManager::Render() {
		m_direct3DManager.ClearBuffer(0.0f, 0.0f, 0.0f);
		m_direct3DManager.Triangle(static_cast<float>(Time::CurrentTime()));
		m_direct3DManager.Present();
	}
}