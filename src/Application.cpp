#include "Application.h"

Application::Application() {}

Application::Application(sf::String inputImageFile, sf::String imageOutputFile, sf::String inputFontFile, std::vector<std::array<float, 9>>* inputKernelArray, std::vector<std::string>* inputKernelNames)
	: outputFile(imageOutputFile), kernelArray(inputKernelArray), kernelNames(inputKernelNames)
{
	// Window
	sf::VideoMode videoMode(1920, 1080, 1);
	screenWidth = videoMode.width;
	screenHeight = videoMode.height;
	window.create(videoMode, "Kernel Image Processor", sf::Style::Fullscreen);

	// Images
	if (originalImage.loadFromFile(inputImageFile)) {
		originalImageAspectRatio = static_cast<float>(originalImage.getSize().x) / originalImage.getSize().y;
		resizedOriginalTexture = createTexture(originalImage, screenWidth/2, screenHeight/originalImageAspectRatio);
		resizedOriginalSprite.setTexture(resizedOriginalTexture);
		resizedOriginalSprite.setPosition(0, 0);

		ip = ImageProcessor(originalImage, (*kernelArray)[0], imageOutputFile);
		ip.applyConvolution();
		resizedAlteredTexture = createTexture(*ip.getOutputImage(), screenWidth/2, screenHeight/originalImageAspectRatio);
		resizedAlteredSprite.setTexture(resizedAlteredTexture);
		resizedAlteredSprite.setPosition(screenWidth/2, 0);
	}
	
	// Text
	font.loadFromFile(inputFontFile);
	originalText = createText(font, "Input Image Preview", 0, 0);
	alteredText = createText(font, "Output Image Preview", videoMode.width*0.8f, 0);
	processingText = createText(font, "Processing...", screenWidth/2-60, screenHeight-60);
	currentKernel = createText(font, "Current Kernel:\n" + (*kernelNames)[0], screenWidth/2, 0);
}

void Application::render() {
	window.clear(sf::Color::Black);
	window.draw(resizedOriginalSprite);
	window.draw(resizedAlteredSprite);
	window.draw(originalText);
	window.draw(alteredText);
	window.draw(currentKernel);
	window.display();
}

void Application::pollEvents() {
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed: {
				window.close();
				break;
			}
			case sf::Event::KeyPressed: {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					window.close();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					if (selectedKernel < kernelArray->size()-1) {
						selectedKernel++;
						setKernel();
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					if (selectedKernel > 0) {
						selectedKernel--;
						setKernel();
					}
				}
				break;
			}
		}
	}
}

void Application::setKernel() {
	ip.setKernel((*kernelArray)[selectedKernel]);
	window.draw(processingText);
	window.display();
	ip.applyConvolution();
	resizedAlteredTexture = createTexture(*ip.getOutputImage(), screenWidth/2, screenHeight/originalImageAspectRatio);
	resizedAlteredSprite.setTexture(resizedAlteredTexture);
	currentKernel.setString("Current Kernel:\n" + (*kernelNames)[selectedKernel]);
}

bool Application::isOpen() const {
	return window.isOpen();
}

sf::Text Application::createText(const sf::Font& font, const sf::String& string, int x, int y) {
	sf::Text text;
	text.setFont(font);
	text.setString(string);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1);
	text.setPosition(x, y);
	return text;
}

sf::Texture Application::createTexture(const sf::Image& image, int imageWidth, int imageHeight) {
	sf::Image resizedImage;
	resizedImage.create(imageWidth, imageHeight);
	resizeImage(image, resizedImage);
	sf::Texture texture;
	texture.loadFromImage(resizedImage);
	return texture;
}

void Application::resizeImage(const sf::Image& originalImage, sf::Image& resizedImage) {
	const sf::Vector2u originalImageSize = originalImage.getSize();
	const sf::Vector2u resizedImageSize = resizedImage.getSize();
	for (unsigned int y = 0; y < resizedImageSize.y; ++y) {
		for (unsigned int x = 0; x < resizedImageSize.x; ++x) {
			unsigned int origX = static_cast<unsigned int>(static_cast<double>(x) / resizedImageSize.x * originalImageSize.x);
			unsigned int origY = static_cast<unsigned int>(static_cast<double>(y) / resizedImageSize.y * originalImageSize.y);
			resizedImage.setPixel(x, y, originalImage.getPixel(origX, origY));
		}
	}
}
