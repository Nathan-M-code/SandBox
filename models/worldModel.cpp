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
    _nbThread = 16; //ATTENTION NE PAS CHANGER
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
        _listLawerModel.push_back({});
        for(int col=0;col<_nbCellWidth;col++){
            _listLawerModel[row].push_back(0);
        }
    }

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

    for(int i=0;i<NB_DIFFERENT_CELL_TYPE;i++){
        _listTabRect.push_back({});
        _listCellColor.push_back({});
    }

    //plant
    _listCellColor[0].push_back(0);_listCellColor[0].push_back(255);_listCellColor[0].push_back(0);
    //cloud
    _listCellColor[1].push_back(150);_listCellColor[1].push_back(150);_listCellColor[1].push_back(255);
    //water
    _listCellColor[2].push_back(0);_listCellColor[2].push_back(0);_listCellColor[2].push_back(255);
    //fire
    _listCellColor[3].push_back(0);_listCellColor[3].push_back(0);_listCellColor[3].push_back(0);
    //lead
    _listCellColor[4].push_back(100);_listCellColor[4].push_back(100);_listCellColor[4].push_back(100);
    //c4
    _listCellColor[5].push_back(255);_listCellColor[5].push_back(204);_listCellColor[5].push_back(102);
    //elec
    _listCellColor[6].push_back(255);_listCellColor[6].push_back(255);_listCellColor[6].push_back(0);
}

void WorldModel::changeView(){
    _xray = !_xray;
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
    case 5:
        cout << "c4" << endl;
        break;
    case 6:
        cout << "electricity" << endl;
        break;
    default:
        cout << "nothing" << endl;
    }
}

void WorldModel::deleteCell(unsigned int row, unsigned int col){
    if(row>=0 && row<_listCellModel.size() && col>=0 && col<_listCellModel[row].size()){
        if(_listCellModel[row][col] != 0){
            delete _listCellModel[row][col];
            _listCellModel[row][col] = 0;
        }
    }
    //updateBlockCell();
}

void WorldModel::setCellAtCooByTool(Type type, int mouseX, int mouseY){
    int atRow = mouseY/CELL_HEIGHT;
    int atCol = mouseX/CELL_WIDTH;

    unsigned temp = 0;

    if(type == electricity){
        setCellAt(type, atRow, atCol);
        return;
    }else{
        temp = _radiusTools;
    }

    int midRadiusTool = temp/2;

    for(int row=atRow-midRadiusTool;row<atRow+midRadiusTool;row++){
        for(int col=atCol-midRadiusTool;col<atCol+midRadiusTool;col++){
            setCellAt(type,row,col);
        }
    }

    //updateBlockCell();
}

void WorldModel::setCellAt(Type type, unsigned int row, unsigned int col){
    if(row>=0 && row<_listCellModel.size() && col>=0 && col<_listCellModel[row].size()){
        if(type != electricity && _listCellModel[row][col] != 0){
            deleteCell(row, col);
        }
        if(type == nothing){
            deleteCell(row, col);
        }else if(type == electricity){
            if(_listLawerModel[row][col] == 0){
                _listLawerModel[row][col] = new CellModel(type, row, col);
                if(_listCellModel[row][col] != 0 && _listCellModel[row][col]->getType() == lead){
                    /*BlockCellModel *bcm = getBlockByCell(_listCellModel[row][col]);
                    if(bcm != NULL){
                        _listWave.push_back(new WaveModel(row, col, bcm, _listLawerModel, _listCellModel));
                    }*/
                    _listWave.push_back(new WaveModelV2(row, col, _listLawerModel, _listCellModel));
                }
            }
        }else{
            _listCellModel[row][col] = new CellModel(type, row, col);
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

void WorldModel::generateRectByLine(Type type, int row, std::vector<SDL_Rect> &listRect, std::vector< std::vector<CellModel*> > &listCellModel){
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
            SDL_Rect rect;
            rect.x = minCol * CELL_WIDTH;
            rect.y = row * CELL_HEIGHT;
            rect.h = CELL_HEIGHT;
            rect.w = CELL_WIDTH*((maxCol-minCol)+1);
            listRect.push_back(rect);
            continue;
        }
        col++;
    }
}

void WorldModel::updateAllRectByLine(){
    //clear the list of rect
    clearAllTabRect();
    _listTabRectElec.clear();

    for(int ty=0;ty<NB_DIFFERENT_CELL_TYPE;ty++){
        Type type = static_cast<Type>(ty);
        for(int row=0;row<_nbCellHeight;row++){
            generateRectByLine(type, row, _listTabRect[ty], _listCellModel);
        }
    }

    for(int row=0;row<_nbCellHeight;row++){
        for(int col=0;col<_nbCellWidth;col++){
            if(_listLawerModel[row][col] != 0){
                SDL_Rect rect;
                rect.x = col * CELL_WIDTH;
                rect.y = row * CELL_HEIGHT;
                rect.h = CELL_HEIGHT;
                rect.w = CELL_WIDTH;
                _listTabRectElec.push_back(rect);
            }
        }
    }

}

void WorldModel::updateAllRectByRect(){
    //clear the list of rect
    clearAllTabRect();

    vector<InfoThreadModel *> listPointer;

    //claculate
    _listThread.clear();
    for(int numThread=0;numThread<_nbThread;numThread++){
        //cout << numThread << "minRow: " << (numThread/4)*(_nbCellHeight/4) << "maxRow: " << ((numThread/4)+1)*(_nbCellHeight/4) << "minCol: " << (numThread%4)*(_nbCellWidth/4) << "maxCol: " << ((numThread%4)+1)*(_nbCellWidth/4) << endl;
        InfoThreadModel *i = new InfoThreadModel(numThread, _listCellModel, _listTabRect, (numThread/(int)sqrt(_nbThread))*(_nbCellHeight/(int)sqrt(_nbThread)), ((numThread/(int)sqrt(_nbThread))+1)*(_nbCellHeight/(int)sqrt(_nbThread)), (numThread%(int)sqrt(_nbThread))*(_nbCellWidth/(int)sqrt(_nbThread)), ((numThread%(int)sqrt(_nbThread))+1)*(_nbCellWidth/(int)sqrt(_nbThread)));
        //cout << "adresse de tabRect dans lma creation des threads: " << &_listTabRect << endl;
        //InfoThreadModel *i = new InfoThreadModel(numThread, _listCellModel, _listTabRect, 0, 32, 0, 32);
        listPointer.push_back(i);
        _listThread.push_back(thread(threadCalculateRect, i));
    }

    //synchronization
    for(int i=0;i<_listThread.size();i++){
        _listThread[i].join();
    }

    //cout << "fin de tous les threads" << endl;

    for(int i=0;i<listPointer.size();i++){
        delete listPointer[i];
        listPointer[i] = 0;
    }
}

void WorldModel::update(){
    _listCellLiquid.clear();
    _listCellElec.clear();
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

    for(int row=0;row<_listLawerModel.size();row++){
        for(int col=0;col<_listLawerModel[row].size();col++){
            if(_listLawerModel[row][col] != 0){
                if(_listLawerModel[row][col]->getType() == electricity){
                    _listCellElec.push_back(_listLawerModel[row][col]);
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

    for(unsigned int i=0;i<_listCellElec.size();i++){
        int row = _listCellElec[i]->getRow();
        int col = _listCellElec[i]->getCol();
        if(row+1 < _listCellModel.size() && _listCellModel[row+1][col] != 0 && _listCellModel[row+1][col]->getType() == c4){
            setCellAt(electricity,row+1,col);
            deleteCell(row+1,col);
        }
        if(row-1 >= 0 && _listCellModel[row-1][col] != 0 && _listCellModel[row-1][col]->getType() == c4){
            setCellAt(electricity,row-1,col);
            deleteCell(row-1,col);
        }
        if(col+1 <_listCellModel[row].size() && _listCellModel[row][col+1] != 0 && _listCellModel[row][col+1]->getType() == c4){
            setCellAt(electricity,row,col+1);
            deleteCell(row,col+1);
        }
        if(col-1 >= 0 && _listCellModel[row][col-1] != 0 && _listCellModel[row][col-1]->getType() == c4){
            setCellAt(electricity,row,col-1);
            deleteCell(row,col-1);
        }
        //------------------
        if(_listCellModel[row][col] == 0 ||  _listCellModel[row][col]->getType() != lead){
            delete _listLawerModel[row][col];
            _listLawerModel[row][col] = 0;
        }
    }

    for(int i=0;i<_listWave.size();i++){
        _listWave[i]->update();
        if(_listWave[i]->isFinished()){
            delete _listWave[i];
            _listWave.erase(_listWave.begin()+i);
            i--;
        }
    }

    //updateAllRectByRect();
    updateAllRectByLine();
}

void WorldModel::updateBlockCell(){
    vector<CellModel*> listOfLead;
    for(int i=0;i<_listBlockCell.size();i++){
        delete _listBlockCell[i];
        _listBlockCell[i] = 0;
    }
    _listBlockCell.clear();

    //just LEAD for now
    for(int row=0;row<_listCellModel.size();row++){
        for(int col=0;col<_listCellModel[row].size();col++){
            if(_listCellModel[row][col] != 0 && _listCellModel[row][col]->getType() == lead){
                listOfLead.push_back(_listCellModel[row][col]);
            }
        }
    }


    unsigned currentIndex = -1;
    for(int i=0;i<listOfLead.size();i++){
        int row = listOfLead[i]->getRow();
        int col = listOfLead[i]->getCol();
        if(!isInABlock(_listCellModel[row][col])){
            //add in a new block
            BlockCellModel *bc = new BlockCellModel(lead);
            _listBlockCell.push_back(bc);
            currentIndex++;
            _listBlockCell[currentIndex]->addCellToBLock(_listCellModel[row][col]);

            addNeighbours(listOfLead, _listBlockCell[currentIndex], row, col);
        }
    }
}

void WorldModel::addNeighbours(std::vector<CellModel*> &listOfCell, BlockCellModel *bc, int row, int col){
    if(row-1 >= 0 && _listCellModel[row-1][col] != 0 && _listCellModel[row-1][col]->getType() == lead && !bc->isInBlock(_listCellModel[row-1][col])){
        bc->addCellToBLock(_listCellModel[row-1][col]);
        removeOfList(listOfCell, _listCellModel[row-1][col]);
        addNeighbours(listOfCell, bc, row-1, col);
    }
    if(row+1 < _listCellModel.size() && _listCellModel[row+1][col] != 0 && _listCellModel[row+1][col]->getType() == lead && !bc->isInBlock(_listCellModel[row+1][col])){
        bc->addCellToBLock(_listCellModel[row+1][col]);
        removeOfList(listOfCell, _listCellModel[row+1][col]);
        addNeighbours(listOfCell, bc, row+1, col);
    }
    if(col-1 >= 0 && _listCellModel[row][col-1] != 0 && _listCellModel[row][col-1]->getType() == lead && !bc->isInBlock(_listCellModel[row][col-1])){
        bc->addCellToBLock(_listCellModel[row][col-1]);
        removeOfList(listOfCell, _listCellModel[row][col-1]);
        addNeighbours(listOfCell, bc, row, col-1);
    }
    if(col+1 < _listCellModel[row].size() && _listCellModel[row][col+1] != 0 && _listCellModel[row][col+1]->getType() == lead && !bc->isInBlock(_listCellModel[row][col+1])){
        bc->addCellToBLock(_listCellModel[row][col+1]);
        removeOfList(listOfCell, _listCellModel[row][col+1]);
        addNeighbours(listOfCell, bc, row, col+1);
    }
}

bool WorldModel::isInABlock(CellModel *cm){
    for(int i=0;i<_listBlockCell.size();i++){
        if(_listBlockCell[i]->isInBlock(cm)){
            return true;
        }
    }
    return false;
}

void WorldModel::removeOfList(std::vector<CellModel*> &listOfCell, CellModel * cm){
    for(int i=0;i<listOfCell.size();i++){
        if(listOfCell[i] == cm){
            listOfCell.erase(listOfCell.begin()+i);
            break;
        }
    }
}

BlockCellModel * WorldModel::getBlockByCell(CellModel *cm){
    for(int i=0;i<_listBlockCell.size();i++){
        if(_listBlockCell[i]->isInBlock(cm)){
            return _listBlockCell[i];
        }
    }
    return NULL;
}



void WorldModel::clearAllTabRect(){
    for(int i=0;i<_listTabRect.size();i++){
        _listTabRect[i].clear();
    }
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

//-----------------------------------------------------------------------------------------------------------

std::mutex mtx;

void threadCalculateRect(InfoThreadModel *infoThreadModel){
    //cout << infoThreadModel->_num << " " << infoThreadModel->_minCol << endl;
    vector< vector<CellModel*> > listCellModelCopy;


    vector< vector<CellModel*> > listCell = *(infoThreadModel->getListCell());
    vector< vector<SDL_Rect> > *tabRect = infoThreadModel->getTabRect();
    //cout << "adresse de tabRect dans le calcule des threads: " << tabRect << endl;

//    for(int i=0;i<listCell.size();i++){
//        for(int y=0;y<listCell[i].size();y++){
//            cout << listCell[i][y] << " " ;
//        }
//        cout << endl;
//    }

    for(int row=infoThreadModel->_minRow;row<infoThreadModel->_maxRow;row++){
        listCellModelCopy.push_back({});
        for(int col=infoThreadModel->_minCol;col<infoThreadModel->_maxCol;col++){
            listCellModelCopy[row-infoThreadModel->_minRow].push_back(listCell[row][col]);
        }
    }

    for(int ty=0;ty<NB_DIFFERENT_CELL_TYPE;ty++){

        Type type = static_cast<Type>(ty);

        int minRow = 0;
        int maxRow = 0;
        int minCol = 0;
        int maxCol = 0;

        while(!isEmptyCellType(listCellModelCopy, type)){
            int resultArea = findBiggestRect(listCellModelCopy, type, minRow, maxRow, minCol, maxCol);

            SDL_Rect rect;
            rect.x = (minCol+infoThreadModel->_minCol) * CELL_WIDTH;
            rect.y = (minRow+infoThreadModel->_minRow) * CELL_HEIGHT;
            rect.h = CELL_HEIGHT*((maxRow-minRow)+1);
            rect.w = CELL_WIDTH*((maxCol-minCol)+1);

            mtx.lock();
            tabRect->at(ty).push_back(rect);
            mtx.unlock();

            for(int row=minRow;row<=maxRow;row++){
                for(int col=minCol;col<=maxCol;col++){
                    listCellModelCopy[row][col] = 0;
                }
            }
        }
    }
}

int findBiggestRect(std::vector< std::vector<CellModel*> > &a, Type type, int &minRow, int &maxRow, int &minCol, int &maxCol){
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

bool isEmptyCellType(std::vector< std::vector<CellModel*> > &listCellModel, Type type){
    //return true if the listCellModel dosn't contains the type
    for(int row=0;row<listCellModel.size();row++){
        for(int col=0;col<listCellModel[row].size();col++){
            if(listCellModel[row][col] != 0 && listCellModel[row][col]->getType() == type)
                return false;
        }
    }
    return true;
}
