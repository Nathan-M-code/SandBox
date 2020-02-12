#include "cellModel.h"

using namespace std;

CellModel::CellModel(Type type, int row, int col){
    _type = type;
    _row = row;
    _col = col;
}
CellModel::~CellModel(){
}

void CellModel::setCoo(unsigned int newRow, unsigned int newCol) {
    _row = newRow;
    _col = newCol;
};
