#ifndef WAVEMODELV2_H
#define WAVEMODELV2_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "cellModel.h"

class WaveModelV2{
private:
    unsigned _nbAddedCell;

    std::vector<CellModel *> _listActualElec;
    std::vector<CellModel *> _listAlreadyVisited;

    std::vector< std::vector<CellModel*> > & _listLawerModel;
    std::vector< std::vector<CellModel*> > & _listCellModel;

    bool _finished;
public:
    WaveModelV2(unsigned rowCenter, unsigned colCenter, std::vector< std::vector<CellModel*> > &listLawerModel, std::vector< std::vector<CellModel*> > &listCellModel);
    ~WaveModelV2();

    inline bool isFinished(){return _finished;};

    void update();

    bool isAlreadyVisited(CellModel *cm);
};

#endif //WAVEMODELV2_H



