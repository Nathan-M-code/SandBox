#include "waveModelV2.h"

using namespace std;

WaveModelV2::WaveModelV2(unsigned rowCenter, unsigned colCenter, std::vector< std::vector<CellModel*> > &listLawerModel, std::vector< std::vector<CellModel*> > &listCellModel): _listLawerModel(listLawerModel), _listCellModel(listCellModel){
    _nbAddedCell = 0;

    //the cell center
    CellModel *cm = new CellModel(electricity, rowCenter, colCenter);
    _listActualElec.push_back(cm);
    _listLawerModel[rowCenter][colCenter] = cm;

    _finished = false;
}

WaveModelV2::~WaveModelV2(){

}

void WaveModelV2::update(){
    _nbAddedCell = 0;
    vector<CellModel *> listNewElec;
    for(int i=0;i<_listActualElec.size();i++){
        int row = _listActualElec[i]->getRow();
        int col = _listActualElec[i]->getCol();
        if(row+1 < _listCellModel.size() && _listCellModel[row+1][col] != 0 && _listCellModel[row+1][col]->getType() == lead && !isAlreadyVisited(_listCellModel[row+1][col])){
            _listAlreadyVisited.push_back(_listCellModel[row+1][col]);
            _nbAddedCell++;
            CellModel *cm = new CellModel(electricity, row+1, col);
            listNewElec.push_back(cm);
        }
        if(row-1 >= 0 && _listCellModel[row-1][col] != 0 && _listCellModel[row-1][col]->getType() == lead && !isAlreadyVisited(_listCellModel[row-1][col])){
            _listAlreadyVisited.push_back(_listCellModel[row-1][col]);
            _nbAddedCell++;
            CellModel *cm = new CellModel(electricity, row-1, col);
            listNewElec.push_back(cm);
        }
        if(col+1 <_listCellModel[row].size() && _listCellModel[row][col+1] != 0 && _listCellModel[row][col+1]->getType() == lead && !isAlreadyVisited(_listCellModel[row][col+1])){
            _listAlreadyVisited.push_back(_listCellModel[row][col+1]);
            _nbAddedCell++;
            CellModel *cm = new CellModel(electricity, row, col+1);
            listNewElec.push_back(cm);
        }
        if(col-1 >= 0 && _listCellModel[row][col-1] != 0 && _listCellModel[row][col-1]->getType() == lead && !isAlreadyVisited(_listCellModel[row][col-1])){
            _listAlreadyVisited.push_back(_listCellModel[row][col-1]);
            _nbAddedCell++;
            CellModel *cm = new CellModel(electricity, row, col-1);
            listNewElec.push_back(cm);
        }
    }

    for(int i=0;i<_listActualElec.size();i++){
        int row = _listActualElec[i]->getRow();
        int col = _listActualElec[i]->getCol();
        _listLawerModel[row][col] = 0;
        delete _listActualElec[i];
    }
    _listActualElec.clear();

    for(int i=0;i<listNewElec.size();i++){
        int row = listNewElec[i]->getRow();
        int col = listNewElec[i]->getCol();
        _listActualElec.push_back(listNewElec[i]);
        _listLawerModel[row][col] = listNewElec[i];
    }

    if(_nbAddedCell == 0){
        _finished = true;
        //cout << "END" << endl;
    }
}

bool WaveModelV2::isAlreadyVisited(CellModel *cm){
    for(int i=0;i<_listAlreadyVisited.size();i++){
        if(_listAlreadyVisited[i] == cm){
            return true;
        }
    }
    return false;
}
