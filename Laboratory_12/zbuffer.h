#include "vec2.h"
#include "vec4.h"
#include <vector>

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512;

namespace egc {

	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma);

	void drawTriangleInZBuffer(std::vector<egc::vec4> triangle, float depthBuffer[WINDOW_HEIGHT][WINDOW_WIDTH], float& zmin, float& zmax);

}
