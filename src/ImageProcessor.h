#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

class ImageProcessor {
public:

private:
	const sf::Image image;
	const std::array<float, 9> kernel;

public:
	ImageProcessor();
	ImageProcessor(const sf::Image& inputImage, std::array<float, 9> inputKernel);
	void applyConvolution();

private:
	std::array<sf::Color, 9> getNeighbourColours3x3(int x, int y);
	int limitToRange(int input, int max, int min) const;
};