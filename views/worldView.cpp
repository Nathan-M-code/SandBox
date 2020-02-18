#include "worldView.h"

using namespace std;

WorldView::WorldView(WorldModel *worldModel){
    _worldModel = worldModel;
}
WorldView::~WorldView(){
    _worldModel = 0;
}
void WorldView::draw(SDL_Renderer *renderer){

    std::vector< std::vector<SDL_Rect> > tabRect = _worldModel->getTabRect();
    std::vector<SDL_Rect> tabElec = _worldModel->getTabElec();

    /*int count = 0;
    for(int i=0;i<tabRect.size();i++){
        for(int y=0;y<tabRect[i].size();y++){
            count++;
        }
    }*/

//    cout << "nombre de rect: " << count << endl;

    std::vector< std::vector<int8_t> > listColor = _worldModel->getListCellColor();

    /*for(int i=0;i<tabRect.size();i++){
        for(int y=0;y<tabRect[i].size();y++){
            cout << tabRect[i][y] << endl;
        }
    }*/

    for(int ty=0;ty<NB_DIFFERENT_CELL_TYPE;ty++){

        Type type = static_cast<Type>(ty);

        if(type == electricity){
            int nbCell = tabElec.size();
            SDL_Rect tabCell[nbCell];
            for(int i=0;i<nbCell;i++){
                tabCell[i] = tabElec[i];
            }
            if(_worldModel->getXray()){
                int b = rand() % 156 +100;
                SDL_SetRenderDrawColor(renderer, listColor[ty][0],listColor[ty][1],b, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawRects(renderer,tabCell,nbCell);
            }else{
                int b = rand() % 156 +100;
                SDL_SetRenderDrawColor(renderer, listColor[ty][0],listColor[ty][1],b, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRects(renderer,tabCell,nbCell);
            }
        }else{
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
                //ROWS
                /*int nbThread = _worldModel->getNbThread();
                for(int i=0;i<(int)sqrt(nbThread);i++){
                    SDL_RenderDrawLine(renderer, (i+1)*(_worldModel->getNbCellWidth()/sqrt(nbThread))*5,0,(i+1)*(_worldModel->getNbCellWidth()/sqrt(nbThread))*5,SCREEN_HEIGHT);
                    SDL_RenderDrawLine(renderer, 0, (i+1)*(_worldModel->getNbCellHeight()/sqrt(nbThread))*5, SCREEN_WIDTH, (i+1)*(_worldModel->getNbCellHeight()/sqrt(nbThread))*5);
                }*/
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
    }
}


