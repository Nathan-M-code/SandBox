#include "worldControler.h"

using namespace std;

WorldControler::WorldControler(WorldModel *worldModel){
    _worldModel = worldModel;
}
WorldControler::~WorldControler(){}

bool WorldControler::event(SDL_Event &event){
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        _worldModel->setMouseDown(true);
    }

    if (event.type == SDL_MOUSEBUTTONUP)
    {
        _worldModel->setMouseDown(false);
    }

    if (event.type == SDL_MOUSEMOTION)
    {
        SDL_GetMouseState(_worldModel->getMouseX(), _worldModel->getMouseY());
        //cout << "new mouse coo: " << *_worldModel->getMouseX() << " " << *_worldModel->getMouseY() << endl;
        if(_worldModel->isMouseDown()){
            Type type = static_cast<Type>(_worldModel->getTool());
            _worldModel->setCellAtCooByTool(type, *_worldModel->getMouseX(), *_worldModel->getMouseY());
        }
    }

    if(event.type == SDL_MOUSEWHEEL)
    {
        _worldModel->setTool(_worldModel->getTool()+event.wheel.y);
        /*if(event.wheel.y > 0) // scroll up
        {

        }
        else if(event.wheel.y < 0) // scroll down
        {

        }*/
    }

    return false;
}
