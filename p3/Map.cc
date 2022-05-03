#include <iostream>
#include <vector>
#include "Map.h"

using namespace std;

Map::Map(int rows,int columns){
    Junk waste;
    vector<Junk> wastes;
    if(rows<5||columns<5){
        throw EXCEPTION_SIZE;
    }
    this->rows=rows;
    this->columns=columns;
    for(int i=0;i<columns;i++){
        wastes.push_back(waste);
    }
    for(int i=0;i<rows;i++){
        junks.push_back(wastes);
    }
}

bool Map::isInside(const Coordinate &coord) const{
    if(coord.getColumn()<columns&&coord.getRow()<rows&&coord.getColumn()>=0&&coord.getRow()>=0){
        return true;
    }
    else{
        return false;
    }
}

void Map::putJunk(const Junk &junk,const Coordinate &coord){
    if(isInside(coord)){
        junks[coord.getRow()][coord.getColumn()]=junk;
    }
    else{
        throw EXCEPTION_OUTSIDE;
    }
}

Junk Map::getJunk(const Coordinate &coord) const{
    if(isInside(coord)){
        return junks[coord.getRow()][coord.getColumn()];
    }
    else{
        throw EXCEPTION_OUTSIDE;
    }
}

Junk Map::collectJunk(const Coordinate &coord){
    Junk waste,junk;
    if(!isInside(coord)){
        throw EXCEPTION_OUTSIDE;
    }
    else{
        junk=junks[coord.getRow()][coord.getColumn()];
        junks[coord.getRow()][coord.getColumn()]=waste;
        return junk;
    }
}

ostream& operator<<(ostream &os,const Map &map){
    for(int i=0;i<map.columns;i++){
        if(i<10){
            os << "0";
        }
        os<< i << " ";
    }
    os << endl;
    for(int i=0;i<map.rows;i++){
        if(i<10){
            os << "0";
        }
        os << i << " ";
        for(int j=0;j<map.columns;j++){
            if(map.getJunk(Coordinate(i,j)).getTypeChar()=='W'){
                os << " ";
            }
            else{
                os << map.getJunk(Coordinate(i,j)).getTypeChar();
            }
            os << " ";
        }
        os << endl;
    }
    return os;
}