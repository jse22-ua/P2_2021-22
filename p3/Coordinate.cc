#include "Coordinate.h"
#include <iostream>

using namespace std;

Coordinate::Coordinate(){
    row=-1;
    column=-1;
}

Coordinate::Coordinate(int row,int column){
    this->row=row;
    this->column=column;
}

void Coordinate::setRow(int row){
    this->row=row;
}

void Coordinate::setColumn(int column){
    this->column=column;
}

bool Coordinate::compare(const Coordinate &coord){
    if(row==coord.getRow()&&column==getColumn()){
        return true;
    }
    else{
        return false;
    }
}

ostream& operator<<(ostream &os,const Coordinate &coord){
    os << "[" << coord.row << "," << coord.column << "]";
    return os;
}