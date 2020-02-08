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
            switch(_worldModel->getTool()){
            case 0:
                _worldModel->setCellAtCooByTool(plant, *_worldModel->getMouseX(), *_worldModel->getMouseY());
                //_worldModel->updateTabRectByType(plant);
                break;
            case 1:
                _worldModel->setCellAtCooByTool(cloud, *_worldModel->getMouseX(), *_worldModel->getMouseY());
                //_worldModel->updateTabRectByType(cloud);
                break;
            case 2:
                _worldModel->setCellAtCooByTool(water, *_worldModel->getMouseX(), *_worldModel->getMouseY());
                //_worldModel->updateTabRectByType(water);
                break;
            case 3:
                _worldModel->setCellAtCooByTool(fire, *_worldModel->getMouseX(), *_worldModel->getMouseY());
                //_worldModel->updateTabRectByType(fire);
                break;
            case 4:
                _worldModel->setCellAtCooByTool(lead, *_worldModel->getMouseX(), *_worldModel->getMouseY());
                //_worldModel->updateTabRectByType(lead);
                break;
            default:
                _worldModel->setCellAtCooByTool(nothing, *_worldModel->getMouseX(), *_worldModel->getMouseY());
                break;
            }
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
