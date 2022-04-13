#ifndef _Map_H
#define _Map_H
#include <iostream>
#include <vector>
#include "Junk.h"
#include "Coordinate.h"

using namespace std;

class  Map{
    protected:
        int rows;
        int columns;
        vector<vector<Junk> > junks;
    public:
        Map(int rows,int columns);
        bool isInside(const Coordinate &coord) const;
        void putJunk(const Junk &junk,const Coordinate &coord);
        Junk getJunk(const Coordinate &coord) const;
        Junk collectJunk(const Coordinate &coord);
        friend ostream& operator<<(ostream &os, Map &map);
};

#endif