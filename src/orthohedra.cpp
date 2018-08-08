#include <orthohedra.h>

#include "vertex_repr.h"
#include "grid_repr.h"
#include "nbhood_repr.h"

#define INTERNAL_REPR VertexRepr


using OH_Context = struct {
    bool initialized = false;
    size_t k_dim;
    Space space;
    std::vector<Coord> origin;
};

static OH_Context CONTEXT;


static inline INTERNAL_REPR *getRepr(const OPP & opp)
{
    return static_cast<INTERNAL_REPR*>(opp->repr);
}


extern "C"
int OH_Initialize(size_t dim, int* limitCoords)
{
    std::vector<Coord> coords(dim);
    CONTEXT.origin = std::vector<Coord>(dim);

    if (dim < 1)
        return 1;

    for (size_t i = 0; i < dim; i ++) {
        CONTEXT.origin[i] = -limitCoords[2*i];
        coords[i] = limitCoords[2*i + 1] - limitCoords[2*i];
    }

    CONTEXT.space = Space(coords);
    CONTEXT.k_dim = dim;
    CONTEXT.initialized = true;

    return 0;
}

extern "C"
OPP OH_New()
{
    if (!CONTEXT.initialized)
        return NULL;
    else
        return new OPPRepr{new INTERNAL_REPR(CONTEXT.space)};
}

extern "C"
void OH_Destroy(OPP o)
{
    if (!o)
        return;

    delete getRepr(o);
    delete o;
}

extern "C"
OPP OH_Complement(OPP o)
{
    if (!o)
        return NULL;

    OPP result = OH_New();
    *getRepr(result) = getRepr(o)->complement();
    return result;
}
extern "C"
OPP OH_Intersection(OPP o1, OPP o2)
{
    if (!o1 || !o2)
        return NULL;

    OPP result = OH_New();
    *getRepr(result) = getRepr(o1)->intersection(*getRepr(o2));
    return result;
}
extern "C"
OPP OH_Union(OPP o1, OPP o2)
{
    if (!o1 || !o2)
        return NULL;

    OPP result = OH_New();
    *getRepr(result) = getRepr(o1)->unification(*getRepr(o2));
    return result;
}
extern "C"
OPP OH_Difference(OPP o1, OPP o2)
{
    if (!o1 || !o2)
        return NULL;

    OPP result = OH_New();
    *getRepr(result) = getRepr(o1)->difference(*getRepr(o2));
    return result;
}


extern "C"
int OH_Output_Repr(OPP o, char** buffer, int* size)
{
    printf("testing\n");
    return 0;
}


/* EOF */
