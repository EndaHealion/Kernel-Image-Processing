#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {}

ImageProcessor::ImageProcessor(const sf::Image& inputImage, std::array<float, 9> inputKernel) : image(inputImage), kernel(inputKernel) {
}

void ImageProcessor::applyConvolution() {
	const sf::Vector2u imageSize = image.getSize();

	sf::Image newImage;
	newImage.create(imageSize.x, imageSize.y, sf::Color::White);

	// applies kernel to every pixel in the input image
	for (int y = 0; y < imageSize.y; y++) {
		for (int x = 0; x < imageSize.x; x++) {
			int colourRAccumulator = 0;
			int colourGAccumulator = 0;
			int colourBAccumulator = 0;

			std::array<sf::Color, 9> neighbours = getNeighbourColours3x3(x, y);

			for (int i = 0; i < neighbours.size(); i++) {
				colourRAccumulator += (neighbours[i].r * kernel[i]);
				colourGAccumulator += (neighbours[i].g * kernel[i]);
				colourBAccumulator += (neighbours[i].b * kernel[i]);
			}

			colourRAccumulator = limitToRange(colourRAccumulator, 0, 255);
			colourGAccumulator = limitToRange(colourGAccumulator, 0, 255);
			colourBAccumulator = limitToRange(colourBAccumulator, 0, 255);

			sf::Color accumulatedColour = sf::Color(colourRAccumulator, colourGAccumulator, colourBAccumulator);
			newImage.setPixel(x, y, accumulatedColour);
		}
	}
	newImage.saveToFile("outputImage.png");
}

// Gets the colours around a given pixel of an image.
// Neighbouring pixels can wrap around to the other side of the screen
std::array<sf::Color, 9> ImageProcessor::getNeighbourColours3x3(int x, int y) {
	const sf::Vector2u imageSize = image.getSize();
	const int imageSizeX = imageSize.x;
	const int imageSizeY = imageSize.y;

	// TOP LEFT
	sf::Color topLeft;
	if (x == 0 && y == 0) {
		topLeft = image.getPixel(imageSizeX - 1, imageSizeY - 1);
	}
	else if (x == 0) {
		topLeft = image.getPixel(imageSizeX - 1, y - 1);  
	}
	else if (y == 0) {
		topLeft = image.getPixel(x - 1, imageSizeY - 1);  
	}
	else {
		topLeft = image.getPixel(x-1, y-1);  
	}

	// TOP MIDDLE
	sf::Color topMiddle;
	if (y == 0) {
		topMiddle = image.getPixel(x, imageSizeY - 1);  
	}
	else {
		topMiddle = image.getPixel(x, y - 1);
	}

	// TOP RIGHT
	sf::Color topRight;
	if (x == imageSizeX-1 && y == 0) {
		topRight = image.getPixel(0, imageSizeY - 1);  
	}
	else if (x == imageSizeX - 1) {
		topRight = image.getPixel(0, y - 1);  
	}
	else if (y == 0) {
		topRight = image.getPixel(x + 1, imageSizeY - 1);  
	}
	else {
		topRight = image.getPixel(x+1, y-1);  
	}

	// CENTRE LEFT
	sf::Color centreLeft;
	if (x == 0) {
		centreLeft = image.getPixel(imageSizeX - 1, y);  
	}
	else {
		centreLeft = image.getPixel(x-1, y);  
	}

	// CENTRE MIDDLE
	sf::Color centreMiddle = image.getPixel(x, y);

	// CENTRE RIGHT
	sf::Color centreRight;
	if (x == imageSizeX - 1) {
		centreRight = image.getPixel(0, y);  
	}
	else {
		centreRight = image.getPixel(x+1, y);  
	}

	// BOTTOM LEFT
	sf::Color bottomLeft;
	if (x == 0 && y == imageSizeY - 1) {
		bottomLeft = image.getPixel(imageSizeX-1, 0);  
	}
	else if (x == 0) {
		bottomLeft = image.getPixel(imageSizeX-1, y+1);  
	}
	else if (y == imageSizeY - 1) {
		bottomLeft = image.getPixel(x - 1, 0);  
	}
	else {
		bottomLeft = image.getPixel(x-1, y+1);  
	}

	// BOTTOM MIDDLE
	sf::Color bottomMiddle;
	if (y == imageSizeY - 1) {
		bottomMiddle = image.getPixel(x, 0);  
	}
	else {
		bottomMiddle = image.getPixel(x, y+1);  
	}

	// BOTTOM RIGHT
	sf::Color bottomRight;
	if (x == imageSizeX-1 && y == imageSizeY-1) {
		bottomRight = image.getPixel(0, 0);  
	}
	else if (x == imageSizeX - 1) {
		bottomRight = image.getPixel(0, y+1);  
	}
	else if (y == imageSizeY - 1) {
		bottomRight = image.getPixel(x+1, 0);  
	}
	else {
		bottomRight = image.getPixel(x+1, y+1);
	}

	return std::array<sf::Color, 9>{topLeft, topMiddle, topRight, centreLeft, centreMiddle, centreRight, bottomLeft, bottomMiddle, bottomRight};
}

int ImageProcessor::limitToRange(int input, int max, int min) const {
	if (input < min) {
		return min;
	}
	if (input > max) {
		return max;
	}
}
