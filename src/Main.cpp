#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <array>
#include "Application.h"

// #defines are from https://en.wikipedia.org/wiki/Kernel_(image_processing)
#define identity std::array<float, 9>{0,0,0 ,0,1,0, 0,0,0}
#define edge0 std::array<float, 9>{1,0,-1, 0,0,0, -1,0,1}
#define edge1 std::array<float, 9>{0,1,0, 1,-4,1, 0,1,0}
#define edge2 std::array<float, 9>{-1,-1,-1, -1,8,-1, -1,-1,-1}
#define sharpen std::array<float, 9>{0,-1,0, -1,5,-1, 0,-1,0}
#define box_blur std::array<float, 9>{0.1111f,0.1111f,0.1111f, 0.1111f,0.1111f,0.1111f, 0.1111f,0.1111f,0.1111f} 
#define gaussian_blur std::array<float, 9>{0.0625f,0.125f,0.0625f, 0.125f,0.25f,0.125f, 0.0625f,0.125f,0.0625f}
#define horizontal_emboss std::array<float, 9>{0,1,0, 0,0,0, 0,-1,0}
#define vertical_emboss std::array<float, 9>{0,0,0, 1,0,-1, 0,0,0}
#define low_pass std::array<float, 9>{0.0625f,0.0625f,0.0625f, 0.0625f,0.5f,0.0625f, 0.0625f,0.0625f,0.0625f}

int main() {
	
	sf::Font font;
	std::vector<std::array<float, 9>> kernels{identity, edge0, edge1, edge2, sharpen, box_blur, gaussian_blur, horizontal_emboss, vertical_emboss, low_pass};
	std::vector<std::string> kernelNames{ "identity", "edge0", "edge1", "edge2", "sharpen", "box_blur", "gaussian_blur", "horizontal_emboss", "vertical_emboss", "low_pass" };

	Application app("input.png", "output.png", "verdana.ttf", &kernels, &kernelNames);

	while (app.isOpen()) {
		app.pollEvents();
		app.render();
	}

	return 0;
}