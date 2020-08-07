# Kernel-Image-Processing

C++ and SFML implementation of image processing using kernels.

How to use:
 * Place a .png file with the name "input.png" in the location of the executable (or change the code to choose a custom file name/location).
 * When the executable is opened, the input image and a preview of the output image will be shown. These preview images are scaled to fit the screen.
 * You can use the up and down arrows to preview how different kernels affect the input image. The output image is generated based on the current kernel.
 * You can find the "output.png" in the location of the executable (or change the code to choose a custom file name/location).
 * You also need to put a .ttf font file in the executable folder.

Notes:
 * My implementation is based off of the wiki article: https://en.wikipedia.org/wiki/Kernel_(image_processing)#Convolution
 * The #defines are based on the example code from the wiki article: https://en.wikipedia.org/wiki/Kernel_(image_processing)#Concrete_implementation  
