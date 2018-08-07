#include <orthohedra.h>

#include "vertex_repr.h"
#include "grid_repr.h"
#include "nbhood_repr.h"


using OH_Context = struct {
    size_t k_dim;
    Space space;
    std::vector<Coord> origin;
};

static OH_Context CONTEXT;


int OH_Initialize(size_t dim, int* limitCoords, int* fakeOrigin)
{
    std::vector<Coord> coords(dim);
    CONTEXT.origin = std::vector<Coord>(dim);

    if (dim < 1)
        return 1;

    for (size_t i = 0; i < dim; i ++) {
        coords[i] = limitCoords[2*i + 1] - limitCoords[2*i];
        CONTEXT.origin[i] = fakeOrigin[i] - limitCoords[2*i];
    }

    CONTEXT.space = Space(coords);
    CONTEXT.k_dim = dim;

    return 0;
}

OPP* OH_New(){ return NULL; }

void OH_Destroy(OPP* o){}

OPP* OH_Complement(OPP* o){ return NULL; }
OPP* OH_Intersection(OPP* o1, OPP* o2){ return NULL; }
OPP* OH_Union(OPP* o1, OPP* o2){ return NULL; }
OPP* OH_Difference(OPP* o1, OPP* o2){ return NULL; }

int OH_Output_Repr(OPP* o, char** buffer, int* size)
{
  printf("testing\n");
  return 0;
}


/* EOF */
