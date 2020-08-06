#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <string>
#include "ImageProcessor.h"

class Application {
public:

private:
    const std::vector<std::array<float, 9>>* kernelArray;
    const std::vector<std::string>* kernelNames;
    int selectedKernel = 0;

    int screenWidth;
    int screenHeight;
    sf::RenderWindow window;
    sf::Event event;

    sf::Image originalImage;
    sf::Image resizedOriginalImage;
    sf::Image resizedAlteredImage;
    ImageProcessor ip;
    float originalImageAspectRatio = 1;
    sf::String outputFile;

    sf::Texture resizedOriginalTexture;
    sf::Texture resizedAlteredTexture;
    sf::Sprite resizedOriginalSprite;
    sf::Sprite resizedAlteredSprite;

    sf::Font font;
    sf::Text originalText;
    sf::Text alteredText;
    sf::Text processingText;
    sf::Text currentKernel;

public:
    Application();
    Application(sf::String inputImageFile, sf::String imageOutputFile, sf::String inputFontFile, std::vector<std::array<float, 9>>* inputKernelArray, std::vector<std::string>* inputKernelNames);
    void render();
    void pollEvents();
    bool isOpen() const;

private:
    void setKernel();
    sf::Text createText(const sf::Font& font, const sf::String& string, int x, int y);
    sf::Texture createTexture(const sf::Image& image, int imageWidth, int imageHeight);
    void resizeImage(const sf::Image& originalImage, sf::Image& resizedImage);
};