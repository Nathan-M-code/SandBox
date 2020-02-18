#ifndef WAVEMODEL_H
#define WAVEMODEL_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "cellModel.h"
#include "blockCellModel.h"

class WaveModel{
private:
    int _rowCenter;
    int _colCenter;

    int _radius;

    unsigned _nbAddedCell;

    BlockCellModel *_bcm;

    std::vector<CellModel *> _listActualElec;

    std::vector< std::vector<CellModel*> > & _listLawerModel;
    std::vector< std::vector<CellModel*> > & _listCellModel;

    bool _finished;
public:
    WaveModel(unsigned rowCenter, unsigned colCenter, BlockCellModel *bcm, std::vector< std::vector<CellModel*> > &listLawerModel, std::vector< std::vector<CellModel*> > &listCellModel);
    ~WaveModel();

    inline bool isFinished(){return _finished;};

    void update();

    void circleBres(int xc, int yc, int r);
    void addSymmetric(int xc, int yc, int x, int y);

    bool isAlreadyDisplayed(int row, int col);
};

#endif //WAVEMODEL_H



