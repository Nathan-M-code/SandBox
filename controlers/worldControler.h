#ifndef WORLDCTL_H
#define WORLDCTL_H

#include <SDL.h>
#include <iostream>

#include "../models/worldModel.h"

class WorldControler{
private:
    WorldModel *_worldModel;
public:
    WorldControler(WorldModel *worldModel);
    ~WorldControler();
    bool event(SDL_Event &event);
};


#endif // WORLDCTL_H
