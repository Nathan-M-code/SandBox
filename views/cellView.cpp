#include "cellView.h"

CellView::CellView(CellModel *cellModel){
    _cellModel = cellModel;
}
CellView::~CellView(){
    _cellModel = 0;
}
void CellView::draw(SDL_Renderer *renderer, int row, int col) const{
    if(_cellModel->getType() == plant){
        SDL_SetRenderDrawColor(renderer, 0,255,0, SDL_ALPHA_OPAQUE);
    }else if(_cellModel->getType() == cloud){
        SDL_SetRenderDrawColor(renderer, 150,150,255, SDL_ALPHA_OPAQUE);
    }else if(_cellModel->getType() == water){
        SDL_SetRenderDrawColor(renderer, 0,0,255, SDL_ALPHA_OPAQUE);
    }else if(_cellModel->getType() == fire){
        int r = rand() % 156 +100;
        SDL_SetRenderDrawColor(renderer, r,0,0, SDL_ALPHA_OPAQUE);
    }

    SDL_Rect *rect = new SDL_Rect;
    rect->x = col * CELL_WIDTH;
    rect->y = row * CELL_HEIGHT;
    rect->h = CELL_HEIGHT;
    rect->w = CELL_WIDTH;
    SDL_RenderFillRect(renderer, rect);
    delete rect;
}
