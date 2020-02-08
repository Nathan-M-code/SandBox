#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>

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

    std::vector<SDL_Rect*> _tabPlantVec;
    std::vector<SDL_Rect*> _tabCloudVec;
    std::vector<SDL_Rect*> _tabWaterVec;
    std::vector<SDL_Rect*> _tabFireVec;
    std::vector<SDL_Rect*> _tabLeadVec;

    bool _xray;

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
    inline std::vector<SDL_Rect*>& getTabRectPlant(){return _tabPlantVec;};
    inline std::vector<SDL_Rect*>& getTabRectCloud(){return _tabCloudVec;};
    inline std::vector<SDL_Rect*>& getTabRectWater(){return _tabWaterVec;};
    inline std::vector<SDL_Rect*>& getTabRectFire(){return _tabFireVec;};
    inline std::vector<SDL_Rect*>& getTabRectLead(){return _tabLeadVec;};
    inline bool getXray(){return _xray;};
    void changeView();

    void addRectToList(CellModel* cellmodel);
    void deleteToList(SDL_Rect *rect, std::vector<SDL_Rect*> &listRect);
    bool contains(SDL_Rect *rect, std::vector<SDL_Rect*> &listRect);

    void deleteCell(unsigned int row, unsigned int col);
    void setCellAtCooByTool(Type type, int mouseX, int mouseY);
    void setCellAt(Type type, unsigned int row, unsigned int col);
    void moveCellAt(unsigned int originRow, unsigned int originCol, unsigned int targetRow, unsigned int targetCol);
    void moveAndReplaceCellAt(unsigned int originRow, unsigned int originCol, unsigned int targetRow, unsigned int targetCol);

    void growPlantAtCell(unsigned int row, unsigned int col);

    void generateRectByLine(Type type, int row, std::vector<SDL_Rect*> &listRect, std::vector< std::vector<CellModel*> > &listCellModel);
    void updateTabAllType();
    void updateTabRectByType(Type type);
    bool isEmptyCellType(std::vector< std::vector<CellModel*> > &listCellModel, Type type);
    int findBiggestRect(std::vector< std::vector<CellModel*> > &listCellModelCopy, Type type, int &minRow, int &maxRow, int &minCol, int &maxCol);

    void init();
    void update();
};


#endif // WORLDMODEL_H
