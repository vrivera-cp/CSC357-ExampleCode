#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480

#define RECTANGLE_WIDTH     128
#define RECTANGLE_HEIGHT    128
#define RECTANGLE_X         ((WINDOW_WIDTH / 2) - (RECTANGLE_WIDTH / 2))
#define RECTANGLE_Y         ((WINDOW_HEIGHT / 2) - (RECTANGLE_HEIGHT / 2))

bool initialize()
{
    bool success = SDL_Init(SDL_INIT_VIDEO);
    if (!success)
    {
        SDL_Log("Error initializing SDL. %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return success;
}

SDL_Window *initialize_window()
{
    SDL_Window *window = SDL_CreateWindow("My Window", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL)
    {
        SDL_Log("Error creating window. %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    return window;
} 

SDL_Surface *get_window_surface(SDL_Window *window)
{
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    if (surface == NULL)
    {
        SDL_Log("Error obtaining window surface. %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    return surface;
}

int main(int arg, char *argv[])
{
    // Initialization
    initialize();

    SDL_Window *window = initialize_window();
    SDL_Surface *window_surface = get_window_surface(window);

    // Main Program
    bool running = true;
    while (running)
    {
        // Event Handling
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type)
            {
                case SDL_EVENT_QUIT:
                    running = false;
                break;
            }
        }

        // Quit if requested
        if (!running)
        {
            break;
        }

        // Rendering
        SDL_Rect rectangle = {RECTANGLE_X, RECTANGLE_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT};
        SDL_FillSurfaceRect(window_surface, NULL, 0x0000FF); // Fill screen with blue
        SDL_FillSurfaceRect(window_surface, &rectangle, 0x00FF00); // Draw a green rectangle
        SDL_UpdateWindowSurface(window);
    }
    
    // Cleanup
    SDL_DestroyWindow(window);
    window = NULL;
    window_surface = NULL;

    SDL_Quit();

    return 0;
}