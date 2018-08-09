#ifndef ORTHOHEDRA_H
#define ORTHOHEDRA_H

#include <stddef.h>
#include <errno.h>

#define ERR_UNHANDLED_EXCEPTION -1

typedef struct OPPRepr
#ifdef __cplusplus
{
    void *repr;
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
int OH_Initialize(size_t dim, int* limitCoords);


/* Initializes an orthogonal pseudo-polyhedron */
OPP OH_New();

void OH_Destroy(OPP o);

int OH_Add_Point(OPP o, int* coords);

int OH_Complement(OPP o, OPP o1);
int OH_Intersection(OPP o, OPP o1, OPP o2);
int OH_Union(OPP o, OPP o1, OPP o2);
int OH_Difference(OPP o, OPP o1, OPP o2);

int OH_Output_Repr(OPP o, char** buffer, int* size);

#ifdef __cplusplus
}
#endif


#endif

/* EOF */
