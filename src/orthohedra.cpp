#include <orthohedra.h>


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
    std::vector<long> origin;
};

static OH_Context CONTEXT;


static inline INTERNAL_REPR & getRepr(const OPP & opp) noexcept
{
    return opp->repr;
}
static inline void setRepr(OPP* opp, INTERNAL_REPR const& repr)
{
    OH_Destroy(*opp);
    *opp = new OPPRepr{repr};
}

static inline void offset_coord(std::vector<Coord> & coords) {
    for (auto & coord : coords) {
        coord = coord.getGridNext();
    }
}

static inline void map_coord(Fixed* from, std::vector<Coord> & to) {
    for (int i = 0; i < CONTEXT.k_dim; i++) {
        to[i] = from[i] - CONTEXT.origin[i];
    }
}

static inline void unmap_coord(std::vector<Coord> const& from, Fixed* to)
{
    for (int i = 0; i < CONTEXT.k_dim; i++) {
        to[i] = (long)from[i] + CONTEXT.origin[i];
    }
}


extern "C"
int OH_Initialize(size_t dim, Fixed* minCoords, Fixed* maxCoords)
{
    if (dim < 1)
        return 1;

    try {
        CONTEXT.origin = std::vector<long>(minCoords, minCoords + dim);
        CONTEXT.k_dim = dim;

        std::vector<Coord> coords(dim);
        map_coord(maxCoords, coords);
        offset_coord(coords);
        CONTEXT.space = Space(coords);

        CONTEXT.initialized = true;
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}


static inline
OPP OH_new_section_internal(std::vector<Coord> const& lowPnt,
                            std::vector<Coord> const& hiPnt)
{
    if (CONTEXT.initialized)
        return new OPPRepr{INTERNAL_REPR(CONTEXT.space, lowPnt, hiPnt)};
    else
        return NULL;
}


extern "C"
OPP OH_New()
{
    OPP opp = NULL;
    try {
        if (CONTEXT.initialized)
            opp = OH_new_section_internal(CONTEXT.space.getZeroPnt(),
                                          CONTEXT.space.limits);
    } catch (...) {
        fprintf(stderr, "OH_New: failed with code %d",
                HandleExceptions());
        opp = NULL;
    }

    return opp;
}

extern "C"
OPP OH_New_Empty()
{
    OPP opp = NULL;
    try {
        if (CONTEXT.initialized)
            opp = new OPPRepr{INTERNAL_REPR(CONTEXT.space)};
    } catch (...) {
        fprintf(stderr, "OH_New_Empty: failed with code %d",
                HandleExceptions());
        opp = NULL;
    }

    return opp;
}

extern "C"
OPP OH_New_Section(Fixed* low, Fixed* high)
{
    try {
        std::vector<Coord> lowPnt(CONTEXT.k_dim);
        std::vector<Coord> hiPnt(CONTEXT.k_dim);

        map_coord(low, lowPnt);
        map_coord(high, hiPnt);
        offset_coord(hiPnt);

        return OH_new_section_internal(lowPnt, hiPnt);
    } catch (...) {
        fprintf(stderr, "OH_New_Section: failed with code %d",
                HandleExceptions());
        return NULL;
    }
}


extern "C"
void OH_Destroy(OPP o)
{
    delete o;
}

extern "C"
int OH_Carve_Section(OPP* in, Fixed* low, Fixed* high, OPP* out)
{
    if (!in)
        return EINVAL;

    try {
        int res;

        *out = OH_New_Section(low, high);

        res = OH_Intersection(out, *in, *out);
        if (res)
            return res;
        return OH_Difference(in, *in, *out);
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}

extern "C"
int OH_Complement(OPP* o, OPP o1)
{
    if (!o1)
        return EINVAL;

    try {
        setRepr(o, getRepr(o1).complement());
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}
extern "C"
int OH_Intersection(OPP* o, OPP o1, OPP o2)
{
    if (!o1 || !o2)
        return EINVAL;

    try {
        setRepr(o, getRepr(o1).intersection(getRepr(o2)));
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}
extern "C"
int OH_Union(OPP* o, OPP o1, OPP o2)
{
    if (!o1 || !o2)
        return EINVAL;

    try {
        setRepr(o, getRepr(o1).unification(getRepr(o2)));
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}
extern "C"
int OH_Difference(OPP* o, OPP o1, OPP o2)
{
    if (!o1 || !o2)
        return EINVAL;

    try {
        setRepr(o, getRepr(o1).difference(getRepr(o2)));
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}


extern "C"
int OH_Get_Point(const OPP o, Fixed* pnt)
{
    if (!o)
        return EINVAL;

    try {
        if (getRepr(o).getVertexesWithNbhood().size() == 0)
            return -1;

        std::vector<Coord> vtx = getRepr(o).getLowestPnt();
        unmap_coord(vtx, pnt);
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}

extern "C"
int OH_Output_Repr(const OPP o, char** buffer, int* size)
{
    if (!o)
        return EINVAL;

    try {
        getRepr(o).printVertexesCoords();
    } catch (...) {
        return HandleExceptions();
    }

    return 0;
}


/* EOF */
