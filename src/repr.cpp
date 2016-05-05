#include "repr.h"

using namespace std;

Repr::Repr(const Space &space)
:
tikzOstream(&cout),
space(space)
{
}

size_t Repr::dim() const
{
    return space.limits.size();
}

void Repr::setTikzOstreamToCout()
{
    tikzOstream = &cout;
}

void Repr::setTikzOstreamToCerr()
{
    tikzOstream = &cerr;
}
