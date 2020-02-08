#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <SDL.h>
#include <iostream>
#include <vector>

#include "../models/worldModel.h"
#include "../models/constants.h"

class WorldView{
private:
    WorldModel *_worldModel;
public:
    WorldView(WorldModel *worldModel);
    ~WorldView();
    void draw(SDL_Renderer *renderer);
};


#endif // WORLDVIEW_H

