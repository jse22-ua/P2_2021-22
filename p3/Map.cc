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
    for(int i=0;i<rows;i++){
        wastes.push_back(waste);
    }
    for(int i=0;i<columns;i++){
        junks.push_back(wastes);
    }
}

bool Map::isInside(const Coordinate &coord) const{
    if(coord.getColumn()<columns&&coord.getRow()<rows){
        return true;
    }
    else{
        return false;
    }
}

void Map::putJunk(const Junk &junk,const Coordinate &coord){
    if(isInside(coord)){
        junks[coord.getColumn()][coord.getRow()]=junk;
    }
    else{
        throw EXCEPTION_OUTSIDE;
    }
}

Junk Map::getJunk(const Coordinate &coord) const{
    if(isInside(coord)){
        return junks[coord.getColumn()][coord.getRow()];
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
        junk=junks[coord.getColumn()][coord.getRow()];
        junks[coord.getColumn()][coord.getRow()]=waste;
        return junk;
    }
}

ostream& operator<<(ostream &os,const Map &map){
    
}