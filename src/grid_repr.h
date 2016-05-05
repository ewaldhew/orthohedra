#ifndef GRID_REPR_H
#define GRID_REPR_H

#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <fstream>
#include "repr.h"

class GridRepr : public Repr {

    std::set<std::vector<Coord> > points;
    bool doTikzPrintGridPnts;
    
    void outputTikz3D(const std::set<std::pair<std::vector<Coord>, char> > *additional = NULL) const;
    void outputTikz2D(const std::set<std::pair<std::vector<Coord>, char> > *additional = NULL) const;
    void outputTikzBox3D(const std::vector<Coord> & pnt) const;
    void outputTikzBox2D(const std::vector<Coord> & pnt) const;
    void outputTikzAdditional(const std::set<std::pair<std::vector<Coord>, char> > * additional) const;
    void outputTikzBoxFacet3D(const std::vector<Coord> & pnt, size_t dim) const;
    void outputTikzBoxFacet2D(const std::vector<Coord> & pnt, size_t dim) const;
    void outputGridPnts() const;

public:

    GridRepr(const Space &space);
    GridRepr(const Space &space, const char *filepath, bool considerAsNthFloat = false);
    GridRepr(const Space &space, const std::vector<Coord> & lowPnt, const std::vector<Coord> & highPnt);
    friend std::ostream & operator<<(std::ostream & os, const GridRepr & gridRepr);
    bool operator==(const GridRepr & other) const;
    void outputTikz(const std::set<std::pair<std::vector<Coord>, char> > *additional = NULL) const;
    void setTikzPrintGridPnts();
    virtual void addPnt(const std::vector<Coord> & pnt);
    void addPntCutDim(const std::vector<Coord> & pnt, size_t dim);
    virtual bool color(const std::vector<Coord> & pnt) const;
    GridRepr intersection(GridRepr & other) const;
    GridRepr unification(GridRepr & other) const;
    GridRepr difference(GridRepr & other) const;
    GridRepr complement() const;
    GridRepr iFacet(size_t dim, Coord fix) const;

    friend bool testGridReprBasicOperations();
    friend bool testGridReprFacet();
    friend bool testTrivialPolyhedronCreation();
};

#endif
