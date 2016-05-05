#include <cmath>
#include <limits>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <assert.h>

#include "utils.h"

using namespace std;

float randomFloat(float low, float high)
{
    float randBetweenZeroAndOne = float(rand()) / float(RAND_MAX);
    return (randBetweenZeroAndOne * (high - low)) + low;
}

std::vector<Coord> randomPoint(float low, float high, const Space &space)
{
    vector<Coord> pnt;
    for (size_t k = 0; k < space.dim(); k ++) {
        pnt.push_back(randomFloat(low, high));
    }
    return pnt;
}

VertexRepr randomTrivialVertexRepr(float low, float high, const Space &space)
{
    vector<Coord> lowPnt, highPnt;
    for (size_t k = 0; k < space.dim(); k ++) {
        lowPnt.push_back(randomFloat(low, high));
        while (1) {
            float r = randomFloat(lowPnt.back().co, lowPnt.back().co + ((high - lowPnt.back().co) / 1000));
            if (r > lowPnt.back().co) {
                highPnt.push_back(r);
                break;
            }
        }
    }
    return VertexRepr(space, lowPnt, highPnt);
}

NbhoodRepr randomTrivialNbhoodRepr(float low, float high, const Space &space)
{
    vector<Coord> lowPnt, highPnt;
    for (size_t k = 0; k < space.dim(); k ++) {
        lowPnt.push_back(randomFloat(low, high));
        while (1) {
            float r = randomFloat(lowPnt.back().co, lowPnt.back().co + ((high - lowPnt.back().co) / 1000));
            if (r > lowPnt.back().co) {
                highPnt.push_back(r);
                break;
            }
        }
    }
    return NbhoodRepr(space, lowPnt, highPnt);
}
