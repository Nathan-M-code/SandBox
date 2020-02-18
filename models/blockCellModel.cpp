#include "blockCellModel.h"

using namespace std;

BlockCellModel::BlockCellModel(Type type){
    _type = type;
}
BlockCellModel::~BlockCellModel(){}
void BlockCellModel::addCellToBLock(CellModel *cm){
    if(cm->getType() == _type){
        _listCellModelOfTheBlock.push_back(cm);
        //cout << "Le block possede maintenant: " << _listCellModelOfTheBlock.size() << endl;
    }
}
bool BlockCellModel::isInBlock(CellModel *cm){
    for(int i=0;i<_listCellModelOfTheBlock.size();i++){
        if(_listCellModelOfTheBlock[i] == cm){
            return true;
        }
    }
    return false;
}
