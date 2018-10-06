#include <orthohedra.h>

#include "vertex_repr.h"
#include "grid_repr.h"
#include "nbhood_repr.h"

#define INTERNAL_REPR VertexRepr


static int HandleExceptions() noexcept
{
    try { throw; }

    catch (const std::bad_alloc &)
    {
        return ENOMEM;
    }
    catch (...)
    {
        return ERR_UNHANDLED_EXCEPTION;
    }
}


using OH_Context = struct {
    bool initialized = false;
    size_t k_dim;
    Space space;
    std::vector<Coord> origin;
};

static OH_Context CONTEXT;


static inline INTERNAL_REPR *getRepr(const OPP & opp) noexcept
{
    return static_cast<INTERNAL_REPR*>(opp->repr);
}


extern "C"
int OH_Initialize(size_t dim, int* limitCoords)
{
    try {
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
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}

extern "C"
OPP OH_New()
{
    OPP opp = NULL;
    try {
        if (CONTEXT.initialized)
            opp = new OPPRepr{new INTERNAL_REPR(CONTEXT.space)};
    } catch (...) {
        fprintf(stderr, "OH_New: failed with code %d", HandleExceptions());
        opp = NULL;
    }

    return opp;
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
int OH_Add_Point(OPP o, int* coords)
{
    if (!o)
        return EINVAL;

    try {
        std::vector<Coord> pnt(coords, coords + CONTEXT.k_dim);
        getRepr(o)->addPnt(pnt);
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}

extern "C"
int OH_Complement(OPP o, OPP o1)
{
    if (!o || !o1)
        return EINVAL;

    try {
        INTERNAL_REPR result = getRepr(o1)->complement();
        *getRepr(o) = result;
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}
extern "C"
int OH_Intersection(OPP o, OPP o1, OPP o2)
{
    if (!o || !o1 || !o2)
        return EINVAL;

    try {
        INTERNAL_REPR result = getRepr(o1)->intersection(*getRepr(o2));
        *getRepr(o) = result;
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}
extern "C"
int OH_Union(OPP o, OPP o1, OPP o2)
{
    if (!o || !o1 || !o2)
        return EINVAL;

    try {
        INTERNAL_REPR result = getRepr(o1)->unification(*getRepr(o2));
        *getRepr(o) = result;
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}
extern "C"
int OH_Difference(OPP o, OPP o1, OPP o2)
{
    if (!o || !o1 || !o2)
        return EINVAL;

    try {
        INTERNAL_REPR result = getRepr(o1)->difference(*getRepr(o2));
        *getRepr(o) = result;
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}


extern "C"
int OH_Output_Repr(OPP o, char** buffer, int* size)
{
    printf("testing\n");
    return 0;
}


/* EOF */
