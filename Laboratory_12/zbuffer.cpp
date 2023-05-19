#include "zbuffer.h"

namespace egc {

	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma)
	{
		//TO DO - Compute alfa, beta and gamma => we use the function's input parameters as the return mechanism
		//Store the final results in the input parameters

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

	void drawTriangleInZBuffer(std::vector<egc::vec4> triangle, float depthBuffer[WINDOW_HEIGHT][WINDOW_WIDTH], float& zmin, float& zmax) {

		//TO DO  -  implement the "drawing" of the triangle inside the depth buffer
		//The buffer has the same dimension as the screen - use it to fill in not the pixel color of each pixel in the triangel - but the pixel depth (Z component)
		//So you are going to fill in the Z of each pixel inside the triangle - use the algorithm from last week to access the inside of the triangle

		//While you compute the z for each pixel, you can also determine the zmin and zmax values ===> from all the points of the rabbit 
		//zmin and zmax are the minimum and maximum Z values FROM ALL THE VERICES OF THE RABBIT
		int i = 1;
		float alpha, beta, gamma;
		vec2 inc;

		const egc::vec4 first = triangle.at(0);
		const egc::vec4 second = triangle.at(1);
		const egc::vec4 third = triangle.at(2);

		int x_min = triangle.at(0).x;
		int x_max = triangle.at(0).x;
		int y_min = triangle.at(0).y;
		int y_max = triangle.at(0).y;
		while (i < triangle.size()) {

			float v_x = triangle.at(i).x;
			float v_y = triangle.at(i).y;
			if (x_min >= v_x) {
				x_min = v_x;
			}
			if (y_min >= v_y) {
				y_min = v_y;
			}
			if (x_max <= v_x) {
				x_max = v_x;
			}
			if (y_max <= v_y) {
				y_max = v_y;
			}
			i++;
		}
		for (inc.x = x_min; inc.x <= x_max; inc.x++) {
			for (inc.y = y_min; inc.y <= y_max; inc.y++) {

				computeAlphaBetaGamma(triangle, vec2(inc.x, inc.y), alpha, beta, gamma);

				if (0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1 && 0 <= gamma && gamma <= 1) {

					vec4 v = first * alpha + second * beta + third * gamma;
					if (v.z > zmin) {
						zmin = v.z;
					}
					if (v.z < zmax) {
						zmax = v.z;
					}
					if (depthBuffer[(int)inc.x][(int)inc.y] < v.z) {
						depthBuffer[(int)inc.x][(int)inc.y] = v.z;
					}
				}
			}
		}
	}

}

