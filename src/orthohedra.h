#ifndef ORTHOHEDRA_H
#define ORTHOHEDRA_H

#include <stddef.h>
#include <errno.h>

#define ERR_UNHANDLED_EXCEPTION -1

#ifdef __cplusplus
#include "vertex_repr.h"
#include "grid_repr.h"
#include "nbhood_repr.h"

#define INTERNAL_REPR NbhoodRepr
#endif


typedef long Fixed;

typedef struct OPPRepr
#ifdef __cplusplus
{
    INTERNAL_REPR repr;
}
#endif
    *OPP;


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Initializes the space in which all polyhedra shall lie in.
 *
 * Input::
 *   dim
 *     The number of dimensions of the space.
 *
 *   minCoords
 *     The minimum coordinates for each dimension.
 *
 *   maxCoords
 *     The maximum coordinates for each dimension.
 *     Must be in the same order as minCoords.
 *
 * Return::
 *   An error code - 0 if operation was successful, non-zero otherwise.
 */
int OH_Initialize(size_t dim, Fixed* minCoords, Fixed* maxCoords);


/* Initializes an orthogonal pseudo-polyhedron */
OPP OH_New();

void OH_Destroy(OPP o);

int OH_Carve_Section(OPP* in, Fixed* low, Fixed* high, OPP* out);

int OH_Complement(OPP* o, OPP o1);
int OH_Intersection(OPP* o, OPP o1, OPP o2);
int OH_Union(OPP* o, OPP o1, OPP o2);
int OH_Difference(OPP* o, OPP o1, OPP o2);

int OH_Get_Point(const OPP o, Fixed* pnt);
int OH_Output_Repr(const OPP o, char** buffer, int* size);

#ifdef __cplusplus
}
#endif


#endif

/* EOF */
