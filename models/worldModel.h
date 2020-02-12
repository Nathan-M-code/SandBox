#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <thread>
#include <mutex>
#include <cmath>

#include "infoThreadModel.h"
#include "cellModel.h"
#include "constants.h"


class WorldModel{
private:
    int _nbCellHeight;
    int _nbCellWidth;

    int _mouseX;
    int _mouseY;

    bool _mouseDown;

    unsigned _radiusTools;
    unsigned int _tool;

    std::vector<CellModel*> _listCellLiquid;

    std::vector< std::vector<CellModel*> > _listCellModel;

    std::vector<  std::vector<SDL_Rect> > _listTabRect;

    std::vector< std::vector<int8_t> > _listCellColor;

    bool _xray;

    int _nbThread;
    std::vector<std::thread> _listThread;

public:
    WorldModel();
    ~WorldModel();
    inline std::vector< std::vector<CellModel*> >& getListCellModel(){return _listCellModel;};
    inline int * getMouseX(){return &_mouseX;};
    inline int * getMouseY(){return &_mouseY;};
    inline bool isMouseDown(){return _mouseDown;};
    inline void setMouseDown(bool down){_mouseDown = down;};
    inline int getNbCellHeight(){return _nbCellHeight;};
    inline int getNbCellWidth(){return _nbCellWidth;};
    inline unsigned int getTool(){return _tool;};
    void setTool(int tool);
    inline std::vector<  std::vector<SDL_Rect> >& getTabRect(){return _listTabRect;};
    inline std::vector< std::vector<int8_t> >& getListCellColor(){return _listCellColor;};
    inline bool getXray(){return _xray;};
    void changeView();
    inline int getNbThread(){return _nbThread;};

    void deleteCell(unsigned int row, unsigned int col);
    void setCellAtCooByTool(Type type, int mouseX, int mouseY);
    void setCellAt(Type type, unsigned int row, unsigned int col);
    void moveCellAt(unsigned int originRow, unsigned int originCol, unsigned int targetRow, unsigned int targetCol);
    void moveAndReplaceCellAt(unsigned int originRow, unsigned int originCol, unsigned int targetRow, unsigned int targetCol);

    void growPlantAtCell(unsigned int row, unsigned int col);

    void clearAllTabRect();
    void updateAllRect();

    void init();
    void update();
};

void threadCalculateRect(InfoThreadModel *infoThreadModel);
int findBiggestRect(std::vector< std::vector<CellModel*> > &listCellModelCopy, Type type, int &minRow, int &maxRow, int &minCol, int &maxCol);
bool isEmptyCellType(std::vector< std::vector<CellModel*> > &listCellModel, Type type);

#endif // WORLDMODEL_H
