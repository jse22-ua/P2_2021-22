#include <iostream>
#include "Betonski.h"
#include "Util.h"

using namespace std;

Betonski::Betonski(string name){
    if(name.length()==0){
        throw EXCEPTION_NAME;
    }
    this->name=name;
    captured=false;
    anger=0;
}

void Betonski::capture(){
    captured=true;
}

void Betonski::setPosition(const Coordinate &coord){
    position=coord;
}

int Betonski::calculateValue() const{
    int total=0;  

    if(bag.size()!=0){
        for(int i=0; i<(int)bag.size();i++){
            total+=bag[i].getValue();
        }
    }

    return total;
}

int Betonski::calculateValue(JunkType type) const{
    int total=0;

    if(bag.size()!=0){
        for(int i=0;i<(int)bag.size();i++){
            if(type==bag[i].getType()){
                total+=bag[i].getValue();
            }
        }
    }

    return total;
}

int Betonski::spoliation(){
    int value = calculateValue();
    if(!captured){
        throw BETONSKI_NOT_CAPTURED;
    }
    else if(value>=5000){
        captured=false;
        anger=0;
        throw EXCEPTION_REBELION;
    }
    else{
        anger+= value;
        bag.clear();
        return value;
    }
}

int Betonski::spoliation(JunkType type){
    int value=calculateValue(type);
    vector <Junk> junks;

    if(!captured){
        throw BETONSKI_NOT_CAPTURED;
    }
    else if(value>=5000){
        captured=false;
        anger=0;
        throw EXCEPTION_REBELION;
    }
    else{
        anger+= value;
        for(int i=0;i<(int)bag.size();i++){
            if(type!=bag[i].getType()){
                junks.push_back(bag[i]);
            }
        }
        bag.clear();
        bag=junks;
        return value;
    }
}

int Betonski::extract(Map &map){
    int value=0;
    Junk item;

    if(map.isInside(position)){
        if(map.getJunk(position).getType()!=WASTELAND){
            item = map.collectJunk(position);
            bag.push_back(item);
            value = item.getValue();
        }
    }
    return value;
}

bool Betonski::move(const Map &map){
    bool moved=false;

    if(!map.isInside(position)){
       throw EXCEPTION_OUTSIDE;
    }

    else{
        int direction= Util::getRandomNumber(8);
        int row = position.getRow();
        int column = position.getColumn();

        if(direction==0||direction==7||direction==1){
            row--;
        }
        else if(direction==5||direction==4||direction==3){
            row++;
        }

        if(direction==7||direction==6||direction==5){
            column--;
        }
        else if(direction==1||direction==2||direction==3){
            column++;
        }

        if(map.isInside(Coordinate(row,column))){
            moved=true;
            position.setColumn(column);
            position.setRow(row);
        }

        return moved;
    }
}

ostream& operator<<(ostream &os,const Betonski &betonski){
    os << "Betonski \"" << betonski.name << "\" ";

    if(betonski.captured){
        os << " Captured ";
    }
    else{
        os << " Free ";
    }

    os << betonski.anger << " " << betonski.position << endl;
    if(betonski.bag.size()!=0){
        for(int i=0; i<(int)betonski.bag.size();i++){
            os << betonski.bag[i];
        }
        os << endl;
    }
    return os;
}