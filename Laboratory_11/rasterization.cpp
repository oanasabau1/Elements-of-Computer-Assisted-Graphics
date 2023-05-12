#include "rasterization.h"

namespace egc {
	float xMin, xMax, yMin, yMax;

	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma)
	{
		egc::vec4 a = triangleVertices.at(0);
		egc::vec4 b = triangleVertices.at(2);
		egc::vec4 c = triangleVertices.at(1);

		float Fac = (a.y - b.y) * pixel.x + (b.x - a.x) * pixel.y + a.x * b.y - b.x * a.y;
		float Facxy = (a.y - b.y) * c.x + (b.x - a.x) * c.y + a.x * b.y - b.x * a.y;
		float Fbc = (c.y - b.y) * pixel.x + (b.x - c.x) * pixel.y + c.x * b.y - b.x * c.y;
		float Fbcxy = (c.y - b.y) * a.x + (b.x - c.x) * a.y + c.x * b.y - b.x * c.y;

		alpha = Fbc / Fbcxy;
		beta = Fac / Facxy;
		gamma = 1 - alpha - beta;
	}

	void computeBoundingBox(const std::vector<egc::vec4>& triangleVertices) {
		xMin = triangleVertices.at(0).x;
		yMin = triangleVertices.at(0).y;
		xMax = triangleVertices.at(0).x;
		yMax = triangleVertices.at(0).y;

		for (int i = 1; i < 3; i++) {
			if (triangleVertices.at(i).x < xMin) {
				xMin = triangleVertices.at(i).x;
			}
			else if (triangleVertices.at(i).x > xMax) {
				xMax = triangleVertices.at(i).x;
			}

			if (triangleVertices.at(i).y < yMin) {
				yMin = triangleVertices.at(i).y;
			}
			else if (triangleVertices.at(i).y > yMax) {
				yMax = triangleVertices.at(i).y;
			}
		}
	}

	void rasterizeTriangle(SDL_Renderer* renderer, const std::vector<egc::vec4>& triangleVertices, const std::vector<egc::vec4>& triangleColors) {
		//TO DO - Implement the triangle rasterization algorithm
		vec2 pixel;
		float alpha = 0.0;
		float beta, gamma;
		vec4 color;

		computeBoundingBox(triangleVertices);
		for (float i = xMin; i < xMax; i += 1.0) {
			for (float j = yMin; j < yMax; j += 1.0) {
				pixel.x = i;
				pixel.y = j;
				computeAlphaBetaGamma(triangleVertices, pixel, alpha, beta, gamma);
				if (alpha > 0 && alpha < 1 && beta > 0 && beta < 1 && gamma > 0 && gamma < 1) {
							color = triangleColors.at(0) * alpha + triangleColors.at(1) * beta + triangleColors.at(2) * gamma;
							SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, 255);
							SDL_RenderDrawPoint(renderer, pixel.x, pixel.y);
				}
			}
		}
	}
}