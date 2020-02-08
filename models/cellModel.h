#ifndef CellModel_H
#define CellModel_H

#include <SDL.h>
#include <iostream>
#include <vector>

#include "constants.h"

enum Type {nothing, plant, cloud, water, fire, lead};

class CellModel{
private:
    Type _type;
    unsigned int _row;
    unsigned int _col;
    SDL_Rect *_rect;
public:
    CellModel(Type type, int row, int col);
    ~CellModel();
    inline Type getType() const{return _type;};
    inline unsigned int getRow() const{return _row;};
    inline unsigned int getCol() const{return _col;};
    inline void setRow(unsigned int newRow) {_row = newRow;};
    inline void setCol(unsigned int newCol) {_col = newCol;};
    void setCoo(unsigned int newRow, unsigned int newCol);
    inline SDL_Rect* getRect() {return _rect;};
};

#endif


