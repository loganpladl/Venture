#include "../include/DefaultMaterials.h"

namespace Venture {
	Material* DefaultMaterials::unlitWhite = new Material({ 1, 1, 1, 1 });
	Material* DefaultMaterials::unlitBlue = new Material({ 0, 1, 0, 1 });
	Material* DefaultMaterials::unlitRed = new Material({ 1, 0, 0, 1 });
}