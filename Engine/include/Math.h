#pragma once
#include <DirectXMath.h>
#include "Log.h"
#include <stdlib.h>

namespace Venture {
	namespace Math {
		class Float4 {
		public:
			inline Float4() : m_float4(DirectX::XMFLOAT4()) {

			}
			inline float& GetX() {
				return m_float4.x;
			}
			inline float& GetY() {
				return m_float4.y;
			}
			inline float& GetZ() {
				return m_float4.z;
			}
			inline float& GetW() {
				return m_float4.w;
			}
			inline float& SetX(float x) {
				m_float4.x = x;
			}
			inline float& SetY(float y) {
				m_float4.y = y;
			}
			inline float& SetZ(float z) {
				m_float4.z = z;
			}
			inline float& SetW(float w) {
				m_float4.w = w;
			}

			inline float& operator[](size_t i) {
				switch (i){
					case 0: return m_float4.x;
					case 1: return m_float4.y;
					case 2: return m_float4.z;
					case 3: return m_float4.w;
					default: 
						Log::DebugPrintF(0, Log::General, "ERROR: Float4 index out of bounds.\n");
						exit(-1);
				}
			}

		private:
			DirectX::XMFLOAT4 m_float4;
		};


		class Float4x4 {
		public:
			inline Float4x4() : m_float4x4(DirectX::XMFLOAT4X4()) {}

			// Initialize Float4x4 from 16 element float array
			inline Float4x4(const float* pArray) : m_float4x4(pArray) {}

			inline float& operator()(size_t row, size_t column) {
				return m_float4x4(row, column);
			}
			inline Float4x4 operator*(Float4x4 f) {

			}
		private:
			DirectX::XMFLOAT4X4 m_float4x4;
		};
	}
}