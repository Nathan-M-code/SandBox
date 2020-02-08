#ifndef CellView_H
#define CellView_H

#include <SDL.h>
#include <iostream>
#include "../models/cellModel.h"
#include "../models/constants.h"

class CellView{
private:
    CellModel *_cellModel;
public:
    CellView(CellModel *cellModel);
    ~CellView();
    inline CellModel * getCellModel(){return _cellModel;};
    void draw(SDL_Renderer *renderer, int row, int col) const;
};

#endif // CellView_H


