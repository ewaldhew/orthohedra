#ifndef REPR_H
#define REPR_H

#include <assert.h>
#include <vector>
#include <ostream>
#include "space.h"

class Repr {

protected:
    std::ostream *tikzOstream;

public:
    Space space;
    
    Repr(const Space &space);
    size_t dim() const;
    void addPntCutDim(const std::vector<Coord> & pnt, size_t dim);
    void setTikzOstreamToCout();
    void setTikzOstreamToCerr();
};

#endif
