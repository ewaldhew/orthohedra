#ifndef ORTHOHEDRA_H
#define ORTHOHEDRA_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    void *repr;
} OPP;

/* Initializes an orthogonal pseudo-polyhedron */
OPP* OH_New();

void OH_Destroy(OPP* o);

OPP* OH_Complement(OPP* o);
OPP* OH_Intersection(OPP* o1, OPP* o2);
OPP* OH_Union(OPP* o1, OPP* o2);
OPP* OH_Difference(OPP* o1, OPP* o2);

int OH_Output_Repr(OPP* o, char** buffer, int* size);

#ifdef __cplusplus
}
#endif


#endif

/* EOF */
