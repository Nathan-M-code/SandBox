#include "cellModel.h"

using namespace std;

CellModel::CellModel(Type type, int row, int col){
    _type = type;
    _row = row;
    _col = col;

    _rect = new SDL_Rect;
    _rect->x = col * CELL_WIDTH;
    _rect->y = row * CELL_HEIGHT;
    _rect->h = CELL_HEIGHT;
    _rect->w = CELL_WIDTH;
}
CellModel::~CellModel(){
    delete _rect;
    _rect = 0;
}

void CellModel::setCoo(unsigned int newRow, unsigned int newCol) {
    _row = newRow;
    _col = newCol;
    _rect->x = _col * CELL_WIDTH;
    _rect->y = _row * CELL_HEIGHT;
};
