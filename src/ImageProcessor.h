#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <string>

class ImageProcessor {
public:

private:
	sf::Image image;
	sf::Image outputImage;
	std::array<float, 9> kernel;
	std::string outputFile;

public:
	ImageProcessor();
	ImageProcessor(const sf::Image& inputImage, std::array<float, 9> inputKernel, std::string imageOutputFile);

	void applyConvolution();
	void setFileOutputLocation(std::string file);
	void setKernel(std::array<float, 9> inputKernel);
	void setInputImage(sf::Image newImage);
	sf::Image* getOutputImage();

private:
	std::array<sf::Color, 9> getNeighbourColours3x3(int x, int y);
	int limitToRange(int input, int min, int max) const;
};