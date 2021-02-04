#pragma once
#include "Material.h"

// Static factory class for default materials
namespace Venture {
	class DefaultMaterials {
	private:
		static Material* unlitWhite;
		static Material* unlitBlue;
		static Material* unlitRed;
	public:
		inline static Material* UnlitWhite() {
			return unlitWhite;
		}
		inline static Material* UnlitBlue() {
			return unlitBlue;
		}
		inline static Material* UnlitRed() {
			return unlitRed;
		}
	};
}