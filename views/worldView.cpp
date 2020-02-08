#include "worldView.h"

using namespace std;

WorldView::WorldView(WorldModel *worldModel){
    _worldModel = worldModel;
}
WorldView::~WorldView(){
    _worldModel = 0;
}
void WorldView::draw(SDL_Renderer *renderer){
    vector<SDL_Rect*> tabPlantVec = _worldModel->getTabRectPlant();
    vector<SDL_Rect*> tabCloudVec = _worldModel->getTabRectCloud();
    vector<SDL_Rect*> tabWaterVec = _worldModel->getTabRectWater();
    vector<SDL_Rect*> tabFireVec = _worldModel->getTabRectFire();
    vector<SDL_Rect*> tabLeadVec = _worldModel->getTabRectLead();

    int nbCellPlant = tabPlantVec.size();
    SDL_Rect tabPlant[nbCellPlant];
    for(int i=0;i<nbCellPlant;i++){
        tabPlant[i] = *tabPlantVec[i];
    }

//    cout << "nbCellPlant: " << nbCellPlant << endl;
//    for(int i=0;i<nbCellPlant;i++){
//        cout << "i: " << i <<  "x: "<< tabPlant[i].x << " y: " << tabPlant[i].y << " w: " << tabPlant[i].w << " h: " << tabPlant[i].h << endl;
//    }

    int nbCellCloud = tabCloudVec.size();
    SDL_Rect tabCloud[nbCellCloud];
    for(int i=0;i<nbCellCloud;i++){
        tabCloud[i] = *tabCloudVec[i];
    }

    int nbCellWater = tabWaterVec.size();
    SDL_Rect tabWater[nbCellWater];
    for(int i=0;i<nbCellWater;i++){
        tabWater[i] = *tabWaterVec[i];
    }

    int nbCellFire = tabFireVec.size();
    SDL_Rect tabFire[nbCellFire];
    for(int i=0;i<nbCellFire;i++){
        tabFire[i] = *tabFireVec[i];
    }

    int nbCellLead = tabLeadVec.size();
    SDL_Rect tabLead[nbCellLead];
    for(int i=0;i<nbCellLead;i++){
        tabLead[i] = *tabLeadVec[i];
    }

    if(_worldModel->getXray()){
        SDL_SetRenderDrawColor(renderer, 0,255,0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRects(renderer,tabPlant,nbCellPlant);

        SDL_SetRenderDrawColor(renderer, 150,150,255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRects(renderer,tabCloud,nbCellCloud);

        SDL_SetRenderDrawColor(renderer, 0,0,255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRects(renderer,tabWater,nbCellWater);

        int r = rand() % 156 +100;
        SDL_SetRenderDrawColor(renderer, r,0,0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRects(renderer,tabFire,nbCellFire);

        SDL_SetRenderDrawColor(renderer, 100,100,100, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRects(renderer,tabLead,nbCellLead);
    }else{
        SDL_SetRenderDrawColor(renderer, 0,255,0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRects(renderer,tabPlant,nbCellPlant);

        SDL_SetRenderDrawColor(renderer, 150,150,255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRects(renderer,tabCloud,nbCellCloud);

        SDL_SetRenderDrawColor(renderer, 0,0,255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRects(renderer,tabWater,nbCellWater);

        int r = rand() % 156 +100;
        SDL_SetRenderDrawColor(renderer, r,0,0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRects(renderer,tabFire,nbCellFire);

        SDL_SetRenderDrawColor(renderer, 100,100,100, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRects(renderer,tabLead,nbCellLead);
    }
}


