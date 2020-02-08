#include "worldModel.h"

using namespace std;

WorldModel::WorldModel(){
    _nbCellHeight = SCREEN_HEIGHT / CELL_HEIGHT;
    _nbCellWidth = SCREEN_WIDTH / CELL_WIDTH;
    _mouseDown = false;
    _radiusTools = 5;
    _tool = 0;
    _xray = false;
    //cout << _nbCellHeight << " " << _nbCellWidth << endl;
}
WorldModel::~WorldModel(){
    for(int row=0;row<_nbCellHeight;row++){
        for(int col=0;col<_nbCellWidth;col++){
            if(_listCellModel[row][col]){
                delete _listCellModel[row][col];
                _listCellModel[row][col] = 0;
            }
        }
    }
}

void WorldModel::init(){
    for(int row=0;row<_nbCellHeight;row++){
        _listCellModel.push_back({});
        for(int col=0;col<_nbCellWidth;col++){
            _listCellModel[row].push_back(0);
        }
    }

    //setCellAt(plant, 0,0);

    /*for(int row=0;row<_listCellModel.size();row++){
        for(int col=0;col<_listCellModel[row].size();col++){
            if(_listCellModel[row][col] == 0){
                cout << "0 ";
            }else{
                cout << "1 ";
            }
        }
        cout << endl;
    }*/
}

void WorldModel::changeView(){
    _xray = !_xray;
}

void WorldModel::generateRectByLine(Type type, int row, std::vector<SDL_Rect*> &listRect, std::vector< std::vector<CellModel*> > &listCellModel){
    int col = 0;
    unsigned int minCol;
    unsigned int maxCol;
    while(col < _nbCellWidth){
        if(listCellModel[row][col] != 0 && listCellModel[row][col]->getType() == type){
            minCol = col;
            maxCol = col;
            col++;
            while(col < listCellModel[row].size() && listCellModel[row][col] != 0 && listCellModel[row][col]->getType() == type){
                maxCol = col;
                col++;
            }
            SDL_Rect *rect = new SDL_Rect;
            rect->x = minCol * CELL_WIDTH;
            rect->y = row * CELL_HEIGHT;
            rect->h = CELL_HEIGHT;
            rect->w = CELL_WIDTH*((maxCol-minCol)+1);
            listRect.push_back(rect);
            continue;
        }
        col++;
    }
}

void WorldModel::updateTabAllType(){
    for(int i=0;i<_tabPlantVec.size();i++){
        delete _tabPlantVec[i];
    }
    _tabPlantVec.clear();
    for(int i=0;i<_tabCloudVec.size();i++){
        delete _tabCloudVec[i];
    }
    _tabCloudVec.clear();
    for(int i=0;i<_tabWaterVec.size();i++){
        delete _tabWaterVec[i];
    }
    _tabWaterVec.clear();
    for(int i=0;i<_tabFireVec.size();i++){
        delete _tabFireVec[i];
    }
    _tabFireVec.clear();
    for(int i=0;i<_tabLeadVec.size();i++){
        delete _tabLeadVec[i];
    }
    _tabLeadVec.clear();


    for(int row=0;row<_nbCellHeight;row++){
        this->generateRectByLine(plant, row, _tabPlantVec, _listCellModel);
        this->generateRectByLine(cloud, row, _tabCloudVec, _listCellModel);
        this->generateRectByLine(water, row, _tabWaterVec, _listCellModel);
        this->generateRectByLine(fire, row, _tabFireVec, _listCellModel);
        this->generateRectByLine(lead, row, _tabLeadVec, _listCellModel);
    }
    /*for(int i=0;i<_tabPlantVec.size();i++){
        cout << "i: " << i <<  "x: "<< _tabPlantVec[i]->x << " y: " << _tabPlantVec[i]->y << " w: " << _tabPlantVec[i]->w << " h: " << _tabPlantVec[i]->h << endl;
    }*/
}

void WorldModel::updateTabRectByType(Type type){
    vector< vector<CellModel*> > listCellModelCopy(_listCellModel);

    if(type == plant){
        _tabPlantVec.clear();
    }else if(type == cloud){
        _tabCloudVec.clear();
    }else if(type == water){
        _tabWaterVec.clear();
    }else if(type == fire){
        _tabFireVec.clear();
        for(int row=0;row<listCellModelCopy.size();row++){
            for(int col=0;col<listCellModelCopy[row].size();col++){
                if(listCellModelCopy[row][col] != 0 && listCellModelCopy[row][col]->getType() == fire){
                    _tabFireVec.push_back(listCellModelCopy[row][col]->getRect());
                }
            }
        }
        return;
    }else if(type == lead){
        _tabLeadVec.clear();
    }

    int minRow = 0;
    int maxRow = 0;
    int minCol = 0;
    int maxCol = 0;

    while(!isEmptyCellType(listCellModelCopy, type)){
        int resultArea = findBiggestRect(listCellModelCopy, type, minRow, maxRow, minCol, maxCol);

        SDL_Rect *rect = new SDL_Rect;
        rect->x = minCol * CELL_WIDTH;
        rect->y = minRow * CELL_HEIGHT;
        rect->h = CELL_HEIGHT*((maxRow-minRow)+1);
        rect->w = CELL_WIDTH*((maxCol-minCol)+1);

        if(type == plant)
            _tabPlantVec.push_back(rect);
        else if(type == cloud)
            _tabCloudVec.push_back(rect);
        else if(type == water)
            _tabWaterVec.push_back(rect);
        else if(type == fire)
            _tabFireVec.push_back(rect);
        else if(type == lead)
            _tabLeadVec.push_back(rect);

        for(int row=minRow;row<=maxRow;row++){
            for(int col=minCol;col<=maxCol;col++){
                listCellModelCopy[row][col] = 0;
            }
        }
    }
}

int WorldModel::findBiggestRect(std::vector< std::vector<CellModel*> > &a, Type type, int &minRow, int &maxRow, int &minCol, int &maxCol){
    int w[a.size()][a[0].size()];
    for(int row=0;row<a.size();row++){
        for(int col=0;col<a[0].size();col++){
            w[row][col] = 0;
        }
    }

    int h[a.size()][a[0].size()];
    for(int row=0;row<a.size();row++){
        for(int col=0;col<a[0].size();col++){
            h[row][col] = 0;
        }
    }

    int resultMax = 0;
    int result = 0;
    int minw;

    for(int row=0;row<a.size();row++){
        for(int col=0;col<a[row].size();col++){
            if(a[row][col] == 0 || a[row][col]->getType() != type){
                continue;
            }
            if(row == 0){
                h[row][col] = 1;
            }else{
                h[row][col] = h[row-1][col]+1;
            }
            if(col == 0){
                w[row][col] = 1;
            }else{
                w[row][col] = w[row][col-1]+1;
            }
            minw = w[row][col];
            //cout << "minw: " << minw << endl;
            for(int dh=0;dh<h[row][col];dh++){
                //cout << "dh: " << dh << endl;
                minw = min(minw, w[row-dh][col]);
                result = (dh+1)*minw;
                if(result > resultMax){
                    resultMax = result;
                    minRow = row-dh;
                    minCol = col-minw+1;
                    maxRow = row;
                    maxCol = col;
                }
            }
        }
    }

    return resultMax;
}

bool WorldModel::isEmptyCellType(std::vector< std::vector<CellModel*> > &listCellModel, Type type){
    for(int row=0;row<listCellModel.size();row++){
        for(int col=0;col<listCellModel[row].size();col++){
            if(listCellModel[row][col] != 0 && listCellModel[row][col]->getType() == type)
                return false;
        }
    }
    return true;
}

void WorldModel::setTool(int tool){
    _tool = tool;
    if(tool<0){
        _tool=0;
    }
    cout << "new tools: ";
    switch (_tool){
    case 0:
        cout << "plant" << endl;
        break;
    case 1:
        cout << "cloud" << endl;
        break;
    case 2:
        cout << "water" << endl;
        break;
    case 3:
        cout << "fire" << endl;
        break;
    case 4:
        cout << "lead" << endl;
        break;
    default:
        cout << "nothing" << endl;
    }
}

void WorldModel::deleteCell(unsigned int row, unsigned int col){
    if(row>=0 && row<_listCellModel.size() && col>=0 && col<_listCellModel[row].size()){
        if(_listCellModel[row][col] != 0){
            /*Type type = _listCellModel[row][col]->getType();
            SDL_Rect *rect = _listCellModel[row][col]->getRect();
            if(type == plant){
                deleteToList(rect, _tabPlantVec);
            }else if(type == cloud){
                deleteToList(rect, _tabCloudVec);
            }else if(type == water){
                deleteToList(rect, _tabWaterVec);
            }else if(type == fire){
                deleteToList(rect, _tabFireVec);
            }else if(type == lead){
                deleteToList(rect, _tabLeadVec);
            }*/
            delete _listCellModel[row][col];
            _listCellModel[row][col] = 0;
        }
    }
}

void WorldModel::setCellAtCooByTool(Type type, int mouseX, int mouseY){
    int atRow = mouseY/CELL_HEIGHT;
    int atCol = mouseX/CELL_WIDTH;

    int midRadiusTool = _radiusTools/2;

    for(int row=atRow-midRadiusTool;row<atRow+midRadiusTool;row++){
        for(int col=atCol-midRadiusTool;col<atCol+midRadiusTool;col++){
            if(row>=0 && row<_listCellModel.size() && col>=0 && col<_listCellModel[row].size()){
                if(_listCellModel[row][col] != 0){
                    deleteCell(row, col);
                }
                if(type == nothing){
                    deleteCell(row, col);
                }else{
                    _listCellModel[row][col] = new CellModel(type, row, col);
                    //addRectToList(_listCellModel[row][col]);
                }
            }
        }
    }
}

void WorldModel::setCellAt(Type type, unsigned int row, unsigned int col){
    if(row>=0 && row<_listCellModel.size() && col>=0 && col<_listCellModel[row].size()){
        if(_listCellModel[row][col] != 0){
            deleteCell(row, col);
        }
        if(type == nothing){
            deleteCell(row, col);
        }else{
            _listCellModel[row][col] = new CellModel(type, row, col);
            //addRectToList(_listCellModel[row][col]);
        }

    }
}

void WorldModel::moveCellAt(unsigned int originRow, unsigned int originCol, unsigned int targetRow, unsigned int targetCol){
    if(_listCellModel[originRow][originCol] != 0){
            if(_listCellModel[targetRow][targetCol] == 0){
                //swap pointers
                _listCellModel[targetRow][targetCol] = _listCellModel[originRow][originCol];
                _listCellModel[targetRow][targetCol]->setCoo(targetRow, targetCol);

                //remove the cell in the origin box
                _listCellModel[originRow][originCol] = 0;
            }
        }
}

void WorldModel::moveAndReplaceCellAt(unsigned int originRow, unsigned int originCol, unsigned int targetRow, unsigned int targetCol){
    if(_listCellModel[originRow][originCol] != 0){
            if(_listCellModel[targetRow][targetCol] != 0){
                deleteCell(targetRow, targetCol);
            }
            //swap pointers
            _listCellModel[targetRow][targetCol] = _listCellModel[originRow][originCol];
            _listCellModel[targetRow][targetCol]->setCoo(targetRow, targetCol);

            //remove the cell in the origin box
            _listCellModel[originRow][originCol] = 0;
        }
}

bool WorldModel::contains(SDL_Rect *rect, std::vector<SDL_Rect*> &listRect){
    for(int i=0;i<listRect.size();i++){
        if(listRect[i] == rect){
            return true;
        }
    }
    return false;
}

void WorldModel::addRectToList(CellModel* cellmodel){
    Type type = cellmodel->getType();
    SDL_Rect *rect = cellmodel->getRect();
    //cout << "rect qui va etre ajouter: " << rect->x << " " << rect->y << " " << rect->h << " " << rect->w << endl;

    if(type == plant){
        if(!contains(rect, _tabPlantVec)){
            _tabPlantVec.push_back(rect);
        }
    }else if(type == cloud){
        if(!contains(rect, _tabCloudVec)){
            _tabCloudVec.push_back(rect);
        }
    }else if(type == water){
        if(!contains(rect, _tabWaterVec)){
            _tabWaterVec.push_back(rect);
        }
    }else if(type == fire){
        if(!contains(rect, _tabFireVec)){
            _tabFireVec.push_back(rect);
        }
    }else if(type == lead){
        if(!contains(rect, _tabLeadVec)){
            _tabLeadVec.push_back(rect);
        }
    }

    /*cout << "list :" << endl;
    for(int i=0;i<_tabPlantVec.size();i++){
        cout << "i: " << i << "ptr: " << _tabPlantVec[i] <<  " x: "<< _tabPlantVec[i]->x << " y: " << _tabPlantVec[i]->y << " w: " << _tabPlantVec[i]->w << " h: " << _tabPlantVec[i]->h << endl;
    }*/
}

void WorldModel::deleteToList(SDL_Rect *rect, std::vector<SDL_Rect*> &listRect){
    for(int i=0;i<listRect.size();i++){
        if(listRect[i] == rect){
            listRect.erase(listRect.begin()+i);
        }
    }
}

void WorldModel::update(){
    _listCellLiquid.clear();
    for(int row=0;row<_listCellModel.size();row++){
        for(int col=0;col<_listCellModel[row].size();col++){
            if(_listCellModel[row][col] != 0){
                if(_listCellModel[row][col]->getType() == fire){
                    int r = rand() % 100 +1;
                    if(r <= 10){
                        if(row+1 < _listCellModel.size() && _listCellModel[row+1][col] != 0 && _listCellModel[row+1][col]->getType() == plant){
                            setCellAt(fire,row+1,col);
                        }
                        if(row-1 >= 0 && _listCellModel[row-1][col] != 0 && _listCellModel[row-1][col]->getType() == plant){
                            setCellAt(fire,row-1,col);
                        }
                        if(col+1 <_listCellModel[row].size() && _listCellModel[row][col+1] != 0 && _listCellModel[row][col+1]->getType() == plant){
                            setCellAt(fire,row,col+1);
                        }
                        if(col-1 >= 0 && _listCellModel[row][col-1] != 0 && _listCellModel[row][col-1]->getType() == plant){
                            setCellAt(fire,row,col-1);
                        }
                        deleteCell(row, col);
                        continue;
                    }
                }
                if(_listCellModel[row][col]->getType() == cloud){
                    if(_listCellModel[row+1][col] == 0){
                        int r = rand() % 100 + 1;
                        if(r<=1){
                            setCellAt(water, row+1, col);
                        }
                    }
                }
                if(_listCellModel[row][col]->getType() == water){
                    _listCellLiquid.push_back(_listCellModel[row][col]);
                }
            }
        }
    }
    for(unsigned int i=0;i<_listCellLiquid.size();i++){
        //cout << i << " / " << _listCellLiquid.size()-1 << endl;
        if(_listCellLiquid[i]->getType() == water){
            unsigned int row = _listCellLiquid[i]->getRow();
            unsigned int col = _listCellLiquid[i]->getCol();
            if(row+1 < _listCellModel.size()){
                if(_listCellModel[row+1][col] == 0){
                    moveCellAt(row, col, row+1, col);
                }else if(_listCellModel[row+1][col]->getType() == plant){
                    deleteCell(row, col);
                    growPlantAtCell(row+1, col);
                }else if(_listCellModel[row+1][col]->getType() == fire){
                    moveAndReplaceCellAt(row, col, row+1,col);
                }else if((col-1 >= 0 && _listCellModel[row][col-1] == 0) || (col+1 < _listCellModel[row].size() && _listCellModel[row][col+1] == 0)){
                    int r = rand() % 100 +1;
                    if(r <= 50){
                        moveCellAt(row, col, row, col+1);
                    }else{
                        moveCellAt(row, col, row, col-1);
                    }
                }
            }else{
                deleteCell(row, col);
            }
        }
    }

    updateTabAllType();
}

void WorldModel::growPlantAtCell(unsigned int row, unsigned int col){
    if(_listCellModel[row][col] != 0 && _listCellModel[row][col]->getType() == plant){
        int r = rand() % 100 + 1;
        if(r>=10){
            if(row-1 >= 0 && _listCellModel[row-1][col] == 0){
                setCellAt(plant, row-1, col);
            }
        }else if(r>=5){
            if(col-1 >= 0 && _listCellModel[row][col-1] == 0){
                setCellAt(plant, row, col-1);
            }
        }else if(r>=0){
            if(col+1 < _listCellModel[row].size() && _listCellModel[row][col+1] == 0){
                setCellAt(plant, row, col+1);
            }
        }
    }
}
