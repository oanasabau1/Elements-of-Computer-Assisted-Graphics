#pragma once

#include <iostream>
#include "include/SDL.h"

#include "mat4.h"
#include "vec4.h"
#include "transform.h"
#include "camera.h"
#include "projection.h"

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"


//The window
SDL_Window *window = NULL;
//The window renderer
SDL_Renderer* renderer = NULL;
SDL_Event currentEvent;
float cameraZ = 3.0f;

int mouseX, mouseY;
float rotationAngle = 0.0f;

bool backFaceCulling = true;
bool displayNormals = false;
bool quit = false;

std::vector<tinyobj::shape_t> readOBJ(std::string inputfile)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(shapes, materials, err, inputfile.c_str());

	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	if (!ret) {
		exit(1);
	}

#ifdef PRINTINFO
	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	std::cout << "# of materials : " << materials.size() << std::endl;

	for (size_t i = 0; i < shapes.size(); i++) {
		printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
		printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
		printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());

		assert((shapes[i].mesh.indices.size() % 3) == 0);
		for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
			printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, shapes[i].mesh.indices[3 * f + 0], shapes[i].mesh.indices[3 * f + 1], shapes[i].mesh.indices[3 * f + 2], shapes[i].mesh.material_ids[f]);
		}

		printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
		assert((shapes[i].mesh.positions.size() % 3) == 0);
		for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
			printf("  v[%ld] = (%f, %f, %f)\n", v,
				shapes[i].mesh.positions[3 * v + 0],
				shapes[i].mesh.positions[3 * v + 1],
				shapes[i].mesh.positions[3 * v + 2]);
		}
	}
#endif
	return shapes;
}



void destroyWindow()
{
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	//Quit SDL
	SDL_Quit();
}

void handleMouseEvents()
{
	//Mouse event -> pressed button
	if (currentEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		if (currentEvent.button.button == SDL_BUTTON_LEFT)
		{
			SDL_GetMouseState(&mouseX, &mouseY);

		}

		if (currentEvent.button.button == SDL_BUTTON_RIGHT)
		{
			SDL_GetMouseState(&mouseX, &mouseY);

		}
	}

}

void handleKeyboardEvents()
{
	//Keyboard event
	if (currentEvent.type == SDL_KEYDOWN)
	{
		switch (currentEvent.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			quit = true;
			break;

		case SDLK_a:
			rotationAngle += 10.0f;
			break;

		case SDLK_d:
			rotationAngle -= 10.0f;
			break;

		case SDLK_w:
			cameraZ -= 0.5f;
			break;

		case SDLK_s:
			cameraZ += 0.5f;
			break;

		case SDLK_z:
			backFaceCulling = true;
			break;

		case SDLK_c:
			backFaceCulling = false;
			break;

		case SDLK_q:
			displayNormals = true;
			break;

		case SDLK_e:
			displayNormals = false;
			break;

		default:
			break;
		}
	}
}

