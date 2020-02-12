#include <SDL.h>
#include <iostream>
#include <vector>
#include <windows.h>

#include "models/worldModel.h"
#include "views/worldView.h"
#include "controlers/worldControler.h"

#include "models/constants.h"

using namespace std;

int main(int argc, char* args[]) {

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "could not initiate sdl: " << SDL_GetError() << endl;
        return 1;
    }

    window = SDL_CreateWindow("EcoSim",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

    if (window == NULL) {
        cout << "could not create window: " << SDL_GetError() << endl;
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    WorldModel worldModel;
    WorldControler worldControler(&worldModel);
    WorldView worldView(&worldModel);

    worldModel.init();

    SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

    while (1)
	{

	    if(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT)
            {
                break;
            }

            if(worldControler.event(event)){
                break;
            }
            //TEST
            if (event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_t){
                    worldModel.changeView();
                }
                if(event.key.keysym.sym == SDLK_RIGHT){
                    worldModel.update();
                }
            }
        }
//        Uint32 timeA = SDL_GetTicks();
		worldModel.update();
//		Uint32 timeB = SDL_GetTicks();
//        cout << "time to update: " << timeB - timeA << endl;
        worldView.draw(renderer);
//        Uint32 timeC = SDL_GetTicks();
//        cout << "time to draw: " << timeC - timeB << endl;
        SDL_RenderPresent(renderer); //draw now

//        Uint32 timeD = SDL_GetTicks();
//        Uint32 timePresent = timeD - timeC;
//        cout << "time to present: " << timePresent << endl;
        /*if(timePresent>20){
            worldModel.updateTabRectByType(plant);
            worldModel.updateTabRectByType(cloud);
            worldModel.updateTabRectByType(lead);
            worldModel.updateTabRectByType(water);
            //worldModel.updateTabRectByType(fire);
        }*/

        //clear
        SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

//        Uint32 timeE = SDL_GetTicks();
//        cout << "time to clear: " << timeE - timeD << endl;


	}

	if (renderer)
		SDL_DestroyRenderer(renderer);

	if (window)
		SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
