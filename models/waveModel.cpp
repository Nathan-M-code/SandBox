#include "waveModel.h"

using namespace std;

WaveModel::WaveModel(unsigned rowCenter, unsigned colCenter, BlockCellModel *bcm, std::vector< std::vector<CellModel*> > &listLawerModel, std::vector< std::vector<CellModel*> > &listCellModel): _listLawerModel(listLawerModel), _listCellModel(listCellModel){
    _bcm = bcm;
    _rowCenter = rowCenter;
    _colCenter = colCenter;
    _radius = 0;
    _nbAddedCell = 0;

    //the cell center
    CellModel *cm = new CellModel(electricity, rowCenter, colCenter);
    _listActualElec.push_back(cm);

    _finished = false;
}

WaveModel::~WaveModel(){}

void WaveModel::update(){
    for(int i=0;i<_listActualElec.size();i++){
        int row = _listActualElec[i]->getRow();
        int col = _listActualElec[i]->getCol();
        if(_listLawerModel[row][col] != 0){
            _listLawerModel[row][col] = 0;
        }
        delete _listActualElec[i];
        _listActualElec[i] = 0;
    }
    _listActualElec.clear();

    _radius++;
    _nbAddedCell = 0;
    //cout << "radius: " << _radius << " ";
    circleBres(_colCenter, _rowCenter, _radius);
    //cout << "Size: " << _listActualElec.size() << endl;
    if(_nbAddedCell == 0){
        _finished = true;
        //cout << "END" << endl;
    }
}

// using Bresenham's algorithm
void WaveModel::circleBres(int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;
    addSymmetric(xc, yc, x, y);
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels

        x++;

        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        addSymmetric(xc, yc, x, y);
    }
}

void WaveModel::addSymmetric(int xc, int yc, int x, int y)
{
    //cout << "(" << xc+x << ";" << yc+y << ")" << " ";
    if(yc+y < _listCellModel.size() && xc+x < _listCellModel[yc+y].size() && _bcm->isInBlock(_listCellModel[yc+y][xc+x]) && !isAlreadyDisplayed(yc+y, xc+x) && _listLawerModel[yc+y][xc+x] == 0){
        CellModel *cm = new CellModel(electricity, yc+y, xc+x);
        _listActualElec.push_back(cm);
        _listLawerModel[yc+y][xc+x] = cm;
        _nbAddedCell++;
    }
    //cout << "(" << xc-x << ";" << yc+y << ")" << " ";
    if(yc+y < _listCellModel.size() && xc-x >= 0 && _bcm->isInBlock(_listCellModel[yc+y][xc-x]) && !isAlreadyDisplayed(yc+y, xc-x) && _listLawerModel[yc+y][xc-x] == 0){
        CellModel *cm = new CellModel(electricity, yc+y, xc-x);
        _listActualElec.push_back(cm);
        _listLawerModel[yc+y][xc-x] = cm;
        _nbAddedCell++;
    }
    //cout << "(" << xc+x << ";" << yc-y << ")" << " ";
    if(yc-y >= 0 && xc+x < _listCellModel[yc-y].size() && _bcm->isInBlock(_listCellModel[yc-y][xc+x]) && !isAlreadyDisplayed(yc-y, xc+x) && _listLawerModel[yc-y][xc+x] == 0){
        CellModel *cm = new CellModel(electricity, yc-y, xc+x);
        _listActualElec.push_back(cm);
        _listLawerModel[yc-y][xc+x] = cm;
        _nbAddedCell++;
    }
    //cout << "(" << xc-x << ";" << yc-y << ")" << " ";
    if(yc-y >= 0 && xc-x >= 0 && _bcm->isInBlock(_listCellModel[yc-y][xc-x]) && !isAlreadyDisplayed(yc-y, xc-x) && _listLawerModel[yc-y][xc-x] == 0){
        CellModel *cm = new CellModel(electricity, yc-y, xc-x);
        _listActualElec.push_back(cm);
        _listLawerModel[yc-y][xc-x] = cm;
        _nbAddedCell++;
    }
    //cout << "(" << xc+y << ";" << yc+x << ")" << " ";
    if(yc+x < _listCellModel.size() && xc+y < _listCellModel[yc+x].size() && _bcm->isInBlock(_listCellModel[yc+x][xc+y]) && !isAlreadyDisplayed(yc+x, xc+y) && _listLawerModel[yc+x][xc+y] == 0){
        CellModel *cm = new CellModel(electricity, yc+x, xc+y);
        _listActualElec.push_back(cm);
        _listLawerModel[yc+x][xc+y] = cm;
        _nbAddedCell++;
    }
    //cout << "(" << xc-y << ";" << yc+x << ")" << " ";
    if(yc+x < _listCellModel.size() && xc-y >= 0 && _bcm->isInBlock(_listCellModel[yc+x][xc-y]) && !isAlreadyDisplayed(yc+x, xc-y) && _listLawerModel[yc+x][xc-y] == 0){
        CellModel *cm = new CellModel(electricity, yc+x, xc-y);
        _listActualElec.push_back(cm);
        _listLawerModel[yc+x][xc-y] = cm;
        _nbAddedCell++;
    }
    //cout << "(" << xc+y << ";" << yc-x << ")" << " ";
    if(yc-x >= 0 && xc+y < _listCellModel[yc-x].size() && _bcm->isInBlock(_listCellModel[yc-x][xc+y]) && !isAlreadyDisplayed(yc-x, xc+y) && _listLawerModel[yc-x][xc+y] == 0){
        CellModel *cm = new CellModel(electricity, yc-x, xc+y);
        _listActualElec.push_back(cm);
        _listLawerModel[yc-x][xc+y] = cm;
        _nbAddedCell++;
    }
    //cout << "(" << xc-y << ";" << yc-x << ")" << " ";
    if(yc-x >= 0 && xc-y >= 0 && _bcm->isInBlock(_listCellModel[yc-x][xc-y]) && !isAlreadyDisplayed(yc-x, xc-y) && _listLawerModel[yc-x][xc-y] == 0){
        CellModel *cm = new CellModel(electricity, yc-x, xc-y);
        _listActualElec.push_back(cm);
        _listLawerModel[yc-x][xc-y] = cm;
        _nbAddedCell++;
    }
}

bool WaveModel::isAlreadyDisplayed(int row, int col){
    for(int i=0;i<_listActualElec.size();i++){
        int trow = _listActualElec[i]->getRow();
        int tcol = _listActualElec[i]->getCol();
        if(trow == row && tcol == col){
            return true;
        }
    }
    return false;
}
