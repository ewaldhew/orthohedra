#ifndef UTILS_H
#define UTILS_H

#include <vector>

#include "../src/space.h"
#include "../src/vertex_repr.h"
#include "../src/nbhood_repr.h"

float randomFloat(float low, float high);
VertexRepr randomTrivialVertexRepr(float low, float high, const Space &space);
NbhoodRepr randomTrivialNbhoodRepr(float low, float high, const Space &space);
std::vector<Coord> randomPoint(float low, float high, const Space &space);

#endif
