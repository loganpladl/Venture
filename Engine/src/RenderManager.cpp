#include "../include/RenderManager.h"

namespace Venture {
	RenderManager::RenderManager(HWND window) : m_window(window), m_direct3DManager(window) {}

	int RenderManager::Init() {
		int error = m_direct3DManager.Init();
		return error;
	}

	void RenderManager::Render() {
		m_direct3DManager.Present();
	}
}