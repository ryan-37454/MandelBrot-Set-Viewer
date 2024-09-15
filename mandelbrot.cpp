//$ g++ -Llib mandelbrot.cpp -lSDL2 -std=c++20
//$ ./a

#include <iostream>
#include "inc/SDL.h"
#include <numeric>
#include <complex>
#include <windows.h>
#include <thread>
#include <chrono>

float scale = 2.0;
bool running = true;

#undef main

int in_mandel_set(std::complex<double> c);
void keyPress();
int mainCode();

// joining to threads together in main
int main(){
    std::thread keyPressThread(keyPress);
    std::thread mainLogicThread(mainCode);

    keyPressThread.join();
    mainLogicThread.join();

    return 0;
}

// main thread
int mainCode(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Init(SDL_INIT_EVERYTHING);

    const int WIDTH = 1000;
    const int HEIGHT = 1000;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,0, &window, &renderer);
    SDL_RenderSetScale(renderer,1,1);

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // compute mandelbrot set
        for(double x=0.0; x<1.0; x+=0.001) {
            for(double y=0.0; y<1.0; y+=0.001) {
                // lerp, computes the linear interpolation between a and b -> a + t * (b - a), if the parameter t is inside [0, 1]
                // from https://en.cppreference.com/w/cpp/numeric/lerp
                // lerp requires c++20, so using -std=c++20 in my build command
                // gives you every number from -2.0 to 2.0 depending on x (this number 2.0 changes with the scale variable)
                double pointX = std::lerp(-scale, scale, x);
                double pointY = std::lerp(-scale, scale, y);

                int diverge_num = in_mandel_set(std::complex<double>(pointX, pointY));
                if (diverge_num == 0) { // if we are in the mandelbrot set
                    // set to black
                    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
                } else {
                    // set to a colour scaled to diverge_num which is how many iterations it took to diverge
                    /////////////////// using *30 % 255 gives blue effect on the outside and red and yellow as you zoom in
                    SDL_SetRenderDrawColor(renderer, diverge_num*30 % 255, diverge_num*40 % 255, diverge_num*50 % 255, 255);
                    // SDL_SetRenderDrawColor(renderer, diverge_num/500 * 360, diverge_num/500 * 360, diverge_num/500 * 360, 255);
                }
                // draw x, y scaled by 1000, so it fits the screen
                SDL_RenderDrawPointF(renderer, x*1000, y*1000);
            }
        }
        SDL_RenderPresent(renderer);
        // runtime of the program before it is closed
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    }

    // Quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int in_mandel_set(std::complex<double> c) {
    std::complex<double> z(0,0);
    for(int i=0; i < 500; i++) {
        // z = Z^^2 + c
        z = std::pow(z,2) + c;
        // norm returns the squared magnitude of the complex number z
        if(std::norm(z) > 4) {
            // c is not in the mandelbrot set
            return i;
        }
    }
    // c is in the mandelbrot set
    return 0;
}

// keypress thread
void keyPress() {
    while (running) {
        // check o key pressed
        if (GetAsyncKeyState('P') & 0x8000) {
            scale *= 0.99; // zoom in
            std::cout << "Scale\n" << scale; // Debug output
        }
        if (GetAsyncKeyState('O') & 0x8000) {
            scale *= 1.01; // zoom out
            std::cout << "Scale\n" << scale; // Debug output
        }
        // delay between presses
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

// goals -> make the zooming in of the mandelbrot set smoother by dynamically rendering the mandelbrot set and try to remove delay
// and add moving with wasd, although you don't really have to do any of this now