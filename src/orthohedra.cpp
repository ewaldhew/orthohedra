#include <orthohedra.h>

#include "vertex_repr.h"
#include "grid_repr.h"
#include "nbhood_repr.h"


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

