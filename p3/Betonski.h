#ifndef _Betonski_H
#define _Betonski_H
#include <iostream>
#include <vector>
#include "Junk.h"
#include "Util.h"
#include "Coordinate.h"
#include "Map.h"

using namespace std;

class Betonski{
    protected:
        string name;
        int anger;
        bool captured;
        vector<Junk> bag;
        Coordinate position;
    public:
        Betonski(string name);
        string getName() const{return name;}
        int getAnger() const{return anger;}
        bool isCaptured() const{return captured;}
        Coordinate getPosition() const{return position;}
        void capture();
        void setPosition(const Coordinate &coord);
        int calculateValue() const;
        int calculateValue(JunkType type) const;
        int spoliation();
        int spoliation(JunkType type);
        int extract(Map &map);
        bool move(const Map &map);
        friend ostream& operator<<(ostream &os, const Betonski &betonski);

};


#endif