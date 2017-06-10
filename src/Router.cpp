#include "Router.h"
string Router::_outFileName("");
int Router::_routerNum(0);
vector<Router> Router::_routerList;
bool Router::_systemIsStable(false);
int Router::_time(0);

Router::Router(int ID):_ID(ID), _isStable(false){
    _DV.resize(_routerNum);
    for(int i = 0; i < _routerNum; ++i)
        _DV[i].resize(_routerNum, INT_MAX);
    _shortestPath.resize(_routerNum, ID);
}

void Router::initialize(string inFileName){
    ifstream inFile(inFileName);
    if(!inFile){
        cout << "[Error] Cannot open the file!!\n";
        return;
    }
    //TODO
    _outFileName = "out"+inFileName.substr(2);
    ofstream outFile(_outFileName);
    outFile.close();
    string buf;
    getline(inFile, buf);
    _routerNum = atoi(buf.c_str());
    for(int i = 0; i < _routerNum; ++i)
        _routerList.push_back(i);
    for(int i = 0; i < _routerNum; ++i){
        getline(inFile, buf);
        for(int j = 0; j < _routerNum; ++j){
            int cost = atoi(buf.substr(j*5, 5).c_str());
            if(cost){
                _routerList[i]._neighbor.push_back(j);
                _routerList[i]._DV[j][j] = cost;
            }
        }
    }
    inFile.close();
    for(int i = 0; i < _routerNum; ++i)
        for(int j = 0; j < _routerNum; ++j)
            if(_routerList[i]._DV[j][j] < _routerList[i]._DV[j][i])
                _routerList[i]._shortestPath[j] = j;
    return;
}


void Router::broadcast(){
    if(_isStable)
        return;
    vector<int> shortestPathCost(_routerNum, INT_MAX);
    for(int i = 0; i < _routerNum; ++i)
        shortestPathCost[i] = _DV[i][_shortestPath[i]];
    for(size_t i = 0, s = _neighbor.size(); i < s; ++i){
        Message message(_ID, _neighbor[i], _time, shortestPathCost);
        _routerList[_neighbor[i]].receive(message);
    }
    return;
}

void Router::update(){
    _isStable = true;
    for(size_t i = 0, s = _messageList.size(); i < s; ++i){
        int ID = _messageList[i].getSender();
        for(int j = 0; j < _routerNum; ++j){
            if(j == _ID) 
                continue;
            int cost = _messageList[i].getShortestPathCost(j)+_DV[ID][ID];
            if(cost < 0)
                continue;
            if(cost < _DV[j][_shortestPath[j]]){
                _shortestPath[j] = ID;
                _isStable = false;
                _systemIsStable = false;
            }
            if(cost < _DV[j][ID])
                _DV[j][ID] = cost;
        }
    }
    _messageList.clear();
    return;
}


void Router::receive(Message const& message){
    _messageList.push_back(message);
    return;
}

void Router::run(){
    writeFile();
    if(_systemIsStable)
        return;
    _systemIsStable = true;
    for(int i = 0; i < _routerNum; ++i)
        _routerList[i].broadcast();
    for(int i = 0; i < _routerNum; ++i)
        _routerList[i].update();
    ++_time;
    run();
    return;
}


void Router::writeFile(){
    ofstream outFile(_outFileName, ios::app);
    outFile << "T = " << _time << endl;
    for(int i = 0; i < _routerNum; ++i){
        outFile << "From node " << i << endl;
        outFile << "(";
        for(int j = 0; j < _routerNum; ++j){
        int cost = _routerList[i]._DV[j][_routerList[i]._shortestPath[j]];
        if(i != j)
            if(cost == INT_MAX)
                outFile << "inf";
            else
                outFile << cost;
        else
            outFile << 0;
        if(j == _routerNum-1)
            break;
        outFile << ", ";
        }
        outFile << ")\n";
        for(int j = 0; j < _routerNum; ++j){
            for(int k = 0; k < _routerNum; ++k){
                outFile << setw(6);
                if(_routerList[i]._DV[j][k] == INT_MAX)
                    if(i == j or i == k)
                        outFile << 'x';
                    else
                        outFile << ' ';
                else
                    outFile << _routerList[i]._DV[j][k];
            }
            outFile << endl;
        }
    }
    outFile.close();
    return;
}

