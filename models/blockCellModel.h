#ifndef BLOCKCELLMODEL_H
#define BLOCKCELLMODEL_H

#include <iostream>
#include <vector>

#include "cellModel.h"

class BlockCellModel{
private:
    Type _type;
    std::vector<CellModel*> _listCellModelOfTheBlock;
public:
    BlockCellModel(Type type);
    ~BlockCellModel();
    void addCellToBLock(CellModel *cm);
    bool isInBlock(CellModel *cm);
};

#endif //BLOCKCELLMODEL_H




