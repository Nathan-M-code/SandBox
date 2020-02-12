#include "infoThreadModel.h"

using namespace std;

InfoThreadModel::InfoThreadModel(int num, std::vector< std::vector<CellModel*> > &listCell, std::vector< std::vector<SDL_Rect> > &tabRect, int minRow, int maxRow, int minCol, int maxCol): _listCell(listCell), _tabRect(tabRect){
    /*_listCell = listCell;
    _tabRect = tabRect;*/
    //cout << "adresse de tabRect dans le constructeurs des infosThread: " << &_tabRect << endl;
    _minRow = minRow;
    _maxRow = maxRow;
    _minCol = minCol;
    _maxCol = maxCol;
    _num = num;
}

InfoThreadModel::~InfoThreadModel(){}
