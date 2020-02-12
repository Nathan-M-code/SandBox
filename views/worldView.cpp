#include "worldView.h"

using namespace std;

WorldView::WorldView(WorldModel *worldModel){
    _worldModel = worldModel;
}
WorldView::~WorldView(){
    _worldModel = 0;
}
void WorldView::draw(SDL_Renderer *renderer){

    std::vector<  std::vector<SDL_Rect> > tabRect = _worldModel->getTabRect();

    int count = 0;
    for(int i=0;i<tabRect.size();i++){
        for(int y=0;y<tabRect[i].size();y++){
            count++;
        }
    }

//    cout << "nombre de rect: " << count << endl;

    std::vector< std::vector<int8_t> > listColor = _worldModel->getListCellColor();

    /*for(int i=0;i<tabRect.size();i++){
        for(int y=0;y<tabRect[i].size();y++){
            cout << tabRect[i][y] << endl;
        }
    }*/

    for(int ty=0;ty<NB_DIFFERENT_CELL_TYPE;ty++){

        Type type = static_cast<Type>(ty);
        int nbCell = tabRect[ty].size();
        SDL_Rect tabCell[nbCell];
        for(int i=0;i<nbCell;i++){
            tabCell[i] = tabRect[ty][i];
        }

        if(_worldModel->getXray()){
            if(type == fire){
                int r = rand() % 156 +100;
                SDL_SetRenderDrawColor(renderer, r,listColor[ty][1],listColor[ty][2], SDL_ALPHA_OPAQUE);
                SDL_RenderDrawRects(renderer,tabCell,nbCell);
            }else{
                SDL_SetRenderDrawColor(renderer, listColor[ty][0],listColor[ty][1],listColor[ty][2], SDL_ALPHA_OPAQUE);
                SDL_RenderDrawRects(renderer,tabCell,nbCell);
            }
            int nbThread = _worldModel->getNbThread();
            for(int i=0;i<(int)sqrt(nbThread);i++){
                SDL_RenderDrawLine(renderer, (i+1)*(_worldModel->getNbCellWidth()/sqrt(nbThread))*5,0,(i+1)*(_worldModel->getNbCellWidth()/sqrt(nbThread))*5,SCREEN_HEIGHT);
                SDL_RenderDrawLine(renderer, 0, (i+1)*(_worldModel->getNbCellHeight()/sqrt(nbThread))*5, SCREEN_WIDTH, (i+1)*(_worldModel->getNbCellHeight()/sqrt(nbThread))*5);
            }
        }else{
            if(type == fire){
                int r = rand() % 156 +100;
                SDL_SetRenderDrawColor(renderer, r,listColor[ty][1],listColor[ty][2], SDL_ALPHA_OPAQUE);
                SDL_RenderFillRects(renderer,tabCell,nbCell);
            }else{
                SDL_SetRenderDrawColor(renderer, listColor[ty][0],listColor[ty][1],listColor[ty][2], SDL_ALPHA_OPAQUE);
                SDL_RenderFillRects(renderer,tabCell,nbCell);
            }
        }
    }

    /*int nbCellPlant = tabPlantVec.size();
    SDL_Rect tabPlant[nbCellPlant];
    for(int i=0;i<nbCellPlant;i++){
        tabPlant[i] = *tabPlantVec[i];
    }*/

//    cout << "nbCellPlant: " << nbCellPlant << endl;
//    for(int i=0;i<nbCellPlant;i++){
//        cout << "i: " << i <<  "x: "<< tabPlant[i].x << " y: " << tabPlant[i].y << " w: " << tabPlant[i].w << " h: " << tabPlant[i].h << endl;
//    }

    /*int nbCellCloud = tabCloudVec.size();
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
    }*/

    /*if(_worldModel->getXray()){
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
    }*/
}


