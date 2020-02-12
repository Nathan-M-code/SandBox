#ifndef INFOTHREADMODEL_H
#define INFOTHREADMODEL_H

#include <SDL.h>
#include <iostream>

#include "cellModel.h"

class InfoThreadModel{
private:
    std::vector< std::vector<CellModel*> > & _listCell;
    std::vector< std::vector<SDL_Rect> > & _tabRect;
public:
    InfoThreadModel(int num, std::vector< std::vector<CellModel*> > &listCell, std::vector< std::vector<SDL_Rect> > &tabRect, int minRow, int maxRow, int minCol, int maxCol);
    ~InfoThreadModel();
    int _minRow;
    int _maxRow;
    int _minCol;
    int _maxCol;
    int _num;

    inline std::vector< std::vector<CellModel*> > * getListCell(){return &_listCell;};
    inline std::vector< std::vector<SDL_Rect> > * getTabRect(){return &_tabRect;};
};


#endif // INFOTHREADMODEL_H

