#include <iostream>
#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
int main(){
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0){
        std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    else{
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            surface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }
    std::string greetings = "Hello SDL2 WOW";
    std::cout << greetings << std::endl;
    std::cout << "WWWWOOO";
    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return EXIT_SUCCESS;
}