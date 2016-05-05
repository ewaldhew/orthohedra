#include "space.h"

using namespace std;

#if INTEGER_VERSION
const int Coord::ZERO_COORD = 0;
const int Coord::UNDER_ZERO_COORD = -1;
#else
const float Coord::UNDER_ZERO_COORD = - std::numeric_limits<float>::max();
const float Coord::ZERO_COORD = nextafterf(UNDER_ZERO_COORD, std::numeric_limits<float>::max());
#endif

const int Space::DEFAULT_LIMIT = 100;

std::vector<size_t> boolVectorToSizetVector(const std::vector<bool> & pnt)
{
    std::vector<size_t> sizetVctr(pnt.size());
    for (size_t i = 0; i < pnt.size(); i ++) {
        sizetVctr[i] = pnt[i] ? 1 : 0;
    }
    return sizetVctr;
}

bool pntsEqualDontCareLastCoord(const std::vector<Coord> & pnt1, const std::vector<Coord> & pnt2)
{
    assert(pnt1.size() == pnt2.size());
    //
    
    for (size_t i = 0; i < pnt1.size() - 1; i ++) {
        if (pnt1[i] != pnt2[i]) {
            return false;
        }
    }
    return true;
}

std::vector<Coord> coordWiseMax(const std::vector<Coord> & pnt1, const std::vector<Coord> & pnt2)
{
    assert(pnt1.size() == pnt2.size());
    //

    vector<Coord> res;
    for (size_t i = 0; i < pnt1.size(); i ++) {
        res.push_back((pnt1[i] > pnt2[i]) ? pnt1[i] : pnt2[i]);
    }
    return res;
}

bool lowerOrEqual(const std::vector<Coord> & leftPnt, const std::vector<Coord> &rightPnt)
{
    assert(leftPnt.size() == rightPnt.size());
    //
    
    for (size_t i = 0; i < leftPnt.size(); i ++) {
        if (leftPnt[i] > rightPnt[i]) {
            return false;
        }
    }
    return true;
}

bool lower(const std::vector<Coord> & leftPnt, const std::vector<Coord> &rightPnt)
{
    assert(leftPnt.size() == rightPnt.size());
    //
    
    for (size_t i = 0; i < leftPnt.size(); i ++) {
        if (leftPnt[i] >= rightPnt[i]) {
            return false;
        }
    }
    return true;
}

float nthFloat(size_t n)
{
    float actualFl = Coord::ZERO_COORD;
    for (size_t i = 0; i < n; i ++) {
        actualFl = nextafterf(actualFl, std::numeric_limits<float>::max());
    }
    return actualFl;
}

BoolvectorIterator::BoolvectorIterator(size_t size)
:
isEnd(false)
{
    for (size_t i = 0; i < size; i ++) {
        vctr.push_back(false);
    }
}

BoolvectorIterator & BoolvectorIterator::operator++()
{
    if (isEnd) {
        return *this;
    }
    
    /* Overeni, zda vektor jiz dosahl maximalni hodnoty */

    bool allAtLimit = true;
    for (size_t i = 0; i < vctr.size(); i ++) {
        if (!vctr[i]) {
            allAtLimit = false;
            break;
        }
    }
    if (allAtLimit) {
        isEnd = true;
        return *this;
    }

    /* Vektor je inkrementovan jako scitacka */

    size_t i = 0;
    while (i < vctr.size()) {
        if (!vctr[i]) {
            vctr[i] = true;
            break;
        } else {
            vctr[i] = false;
        }
        i ++;
    }

    return *this;
}

bool BoolvectorIterator::atEnd() const
{
    return isEnd;
}

const std::vector<bool> & BoolvectorIterator::operator*() const
{
    return vctr;
}


Space::Space(size_t dim)
{
    assert(dim >= 1);
    //
    for (size_t i = 0; i < dim; i ++) {
        limits.push_back(DEFAULT_LIMIT);
    }
    for (size_t i = 0; i < this->dim(); i ++) {
        zeroPnt.push_back(Coord::ZERO_COORD);
    }
}

Space::Space(const std::vector<Coord> & limits)
{
    assert(limits.size() >= 1);
    //
    for (size_t i = 0; i < limits.size(); i ++) {
        assert(limits[i] > Coord::ZERO_COORD);
    }
    this->limits = limits;
    for (size_t i = 0; i < this->dim(); i ++) {
        zeroPnt.push_back(Coord::ZERO_COORD);
    }
}

std::ostream & operator<<(std::ostream & os, const Space & space)
{
    for (size_t i = 0; i < space.limits.size(); i ++) {
        if (i != 0) {
            os << " x ";
        }
        os << space.limits[i];
    }
    return os;
}

bool Space::operator==(const Space & other) const
{
    return limits == other.limits;
}

size_t Space::dim() const
{
    return limits.size();
}

bool Space::checkLimits(const std::vector<Coord> & pnt, bool allowUnderFirstCoord) const
{
    assert(pnt.size() == limits.size());
    //
    for (size_t i = 0; i < pnt.size(); i ++) {
        bool cond = allowUnderFirstCoord ?
                    ((pnt[i] >= Coord::ZERO_COORD && pnt[i] < limits[i]) || pnt[i] == Coord::UNDER_ZERO_COORD) :
                    ((pnt[i] >= Coord::ZERO_COORD && pnt[i] < limits[i]));

        if (!cond) {
            cout << "This point is out of range:" << endl;
            cout << "Point:" << endl;
            PRINT_POINT(pnt)
            cout << "Range:" << endl;
            cout << *this << endl;
            return false;
        }
    }
    return true;
}

bool Space::checkLimitsAllowLimits(const std::vector<Coord> & pnt, bool allowUnderFirstCoord) const
{
    assert(pnt.size() == limits.size());
    //
    for (size_t i = 0; i < pnt.size(); i ++) {
        bool cond = allowUnderFirstCoord ?
                    ((pnt[i] >= Coord::ZERO_COORD && pnt[i] <= limits[i]) || pnt[i] == Coord::UNDER_ZERO_COORD) :
                    ((pnt[i] >= Coord::ZERO_COORD && pnt[i] <= limits[i]));

        if (!cond) {
            cout << "point (";
            for (size_t j = 0; j < pnt.size(); j ++) {
                if (j != 0) {
                    cout << ", ";
                }
                cout << pnt[j];
            }
            cout << ") is out of the range " << *this << endl;
            return false;
        }
    }
    return true;
}

bool Space::hasAtLeastOneZeroCoord(const std::vector<Coord> &pnt) const
{
    assert(pnt.size() == limits.size());
    //
    for (size_t i = 0; i < pnt.size(); i ++) {
        if (pnt[i] == Coord::ZERO_COORD) {
            return true;
        }
    }
    return false;
}

bool Space::hasAtLeastOneUnderZeroCoord(const std::vector<Coord> &pnt) const
{
    assert(pnt.size() == limits.size());
    //
    for (size_t i = 0; i < pnt.size(); i ++) {
        if (pnt[i] == Coord::UNDER_ZERO_COORD) {
            return true;
        }
    }
    return false;
}

bool Space::hasAllZeroCoords(const std::vector<Coord> &pnt) const
{
    assert(pnt.size() == limits.size());
    //
    for (size_t i = 0; i < pnt.size(); i ++) {
        if (pnt[i] != Coord::ZERO_COORD) {
            return false;
        }
    }
    return true;
}

bool Space::isOnFrontBoundary(const std::vector<Coord> &pnt) const
{
    assert(pnt.size() == limits.size());
    //
    /* Bod je prvkem predni hranice prostoru, pokud alespon jedna souradnice je limitni */
    for (size_t i = 0; i < pnt.size(); i ++) {
        if (pnt[i] == limits[i]) {
            return true;
        }
    }
    return false;
}

bool Space::isCorner(const std::vector<Coord> &pnt) const
{
    assert(pnt.size() == limits.size());
    //
    /* Bod je rohem prostoru, pokud pro kazdou souradnici plati,
    ze je bud limitni, nebo nulova */
    for (size_t i = 0; i < pnt.size(); i ++) {
        if (pnt[i] != limits[i] && pnt[i] != Coord::ZERO_COORD) {
            return false;
        }
    }
    return true;
}

Space::Iterator::Iterator(const Space *space, bool includeLimits)
:
space(space),
isEnd(false),
includeLimits(includeLimits)
{
    for (size_t i = 0; i < space->dim(); i ++) {
        pnt.push_back(Coord::ZERO_COORD);
    }
}

Space::Iterator & Space::Iterator::operator++()
{
    if (isEnd) {
        return *this;
    }

    /* Overeni, zda vektor jiz dosahl maximalni hodnoty */

    bool allAtLimit = true;
    for (size_t i = 0; i < pnt.size(); i ++) {
        if (pnt[i] < (includeLimits ? space->limits[i] : space->limits[i].getGridPrev())) {
            allAtLimit = false;
            break;
        }
    }
    if (allAtLimit) {
        isEnd = true;
        return *this;
    }

    /* Vektor je inkrementovan jako scitacka */

    size_t i = 0;
    while (i < pnt.size()) {
        if (pnt[i] < (includeLimits ? space->limits[i] : space->limits[i].getGridPrev())) {
            pnt[i] = pnt[i].getGridNext();
            break;
        } else {
            pnt[i] = Coord::ZERO_COORD;
        }
        i ++;
    }

    return *this;
}

const vector<Coord> & Space::Iterator::operator*() const
{
    return pnt;
}

bool Space::Iterator::atEnd() const
{
    return isEnd;
}

Space::Iterator Space::createIterator(bool includeLimits) const
{
    return Iterator(this, includeLimits);
}

void Space::cutDimension(size_t i)
{
    assert(i >= 0 && i < limits.size());
    //
    limits.erase(limits.begin() + i);
}

Space::NbhoodIterator::NbhoodIterator(const Space *space, const std::vector<Coord> *basePnt)
:
space(space),
basePnt(basePnt),
corner(space->dim())
{
}

Space::NbhoodIterator & Space::NbhoodIterator::operator++()
{
    ++ corner;
    return *this;
}

std::vector<Coord> Space::NbhoodIterator::operator*() const
{
    vector<Coord> nbr = *basePnt;
    for (size_t i = 0; i < nbr.size(); i ++) {
        if ((*corner)[i]) {
            nbr[i] = nbr[i].getGridPrev(); /* Muze vzniknout i hodnota Coord::UNDER_ZERO_COORD */
        }
    }
    return nbr;
}

bool Space::NbhoodIterator::atEnd() const
{
    return corner.atEnd();
}

Space::NbhoodIterator Space::createNbhoodIterator(const std::vector<Coord> *basePnt) const
{
    return NbhoodIterator(this, basePnt);
}

Space::HalfNbhoodIterator::HalfNbhoodIterator(const Space *space, const std::vector<Coord> *basePnt,
        size_t dim, bool leftPart)
:
space(space),
basePnt(basePnt),
corner(space->dim() - 1),
dim(dim),
leftPart(leftPart)
{
    assert(dim >= 0 && dim < space->dim());
    //
}

Space::HalfNbhoodIterator & Space::HalfNbhoodIterator::operator++()
{
    ++ corner;
    return *this;
}

std::vector<Coord> Space::HalfNbhoodIterator::operator*() const
{
    vector<Coord> nbr = *basePnt;
    size_t i = 0;
    while (i < dim) {
        if ((*corner)[i]) {
            nbr[i] = nbr[i].getGridPrev(); /* Muze vzniknout i hodnota Coord::UNDER_ZERO_COORD */
        }
        i ++;
    }
    if (leftPart) {
       nbr[i] = nbr[i].getGridPrev();
    }
    i ++;
    while (i < nbr.size()) {
        if ((*corner)[i - 1]) {
            nbr[i] = nbr[i].getGridPrev(); /* Muze vzniknout i hodnota Coord::UNDER_ZERO_COORD */
        }
        i ++;
    }
    return nbr;
}

bool Space::HalfNbhoodIterator::atEnd() const
{
    return corner.atEnd();
}

Space::HalfNbhoodIterator Space::createHalfNbhoodIterator(const std::vector<Coord> *basePnt, size_t dim, bool leftPart) const
{
    return HalfNbhoodIterator(this, basePnt, dim, leftPart);
}

Space::SpaceBoundaryIterator::SpaceBoundaryIterator(const Space *space)
:
space(space),
isEnd(false),
facet(createFacet(0)),
facetDim(0),
isFacetLeft(true),
facetIt(facet, true)
{}

Space * Space::SpaceBoundaryIterator::createFacet(size_t dim)
{
    assert(space->dim() >= 1);
    assert(dim < space->dim() && dim >= 0);
    //

    vector<Coord> facetLimits;
    for (size_t i = 0; i < space->dim(); i ++) {
        if (i != dim) {
            facetLimits.push_back(space->limits[i]);
        }
    }
    Space *facet = new Space(facetLimits);
    return facet;
}

Space::SpaceBoundaryIterator & Space::SpaceBoundaryIterator::operator++()
{
    if (isEnd) {
        return *this;
    }

    if (facetIt.atEnd()) {

        if (isFacetLeft) {
            isFacetLeft = false;
            facetIt = facet->createIterator(true);

        } else {

            if (facetDim < space->dim() - 1) {
                facetDim ++;
                facet = createFacet(facetDim);
                facetIt = facet->createIterator(true);
                isFacetLeft = true;
                
            } else {
                isEnd = true;
                return *this;
            }
        }

    } else {
        ++ facetIt;
    }

    return *this;
}

bool Space::SpaceBoundaryIterator::atEnd() const
{
    return isEnd;
}

std::vector<Coord> Space::SpaceBoundaryIterator::operator*() const
{
    vector<Coord> pnt = *facetIt;
    pnt.insert(pnt.begin() + facetDim, isFacetLeft ? 0 : space->limits[facetDim]);
    return pnt;
}

Space::SpaceBoundaryIterator Space::createSpaceBoundaryIterator() const
{
    return SpaceBoundaryIterator(this);
}

Space::SpaceCornerIterator::SpaceCornerIterator(const Space *space)
:
space(space),
corner(space->dim())
{

}

Space::SpaceCornerIterator & Space::SpaceCornerIterator::operator++()
{
    ++ corner;
    return *this;
}

bool Space::SpaceCornerIterator::atEnd() const
{
    return corner.atEnd();
}

std::vector<Coord> Space::SpaceCornerIterator::operator*() const
{
    vector<Coord> crnr = space->limits;
    for (size_t i = 0; i < crnr.size(); i ++) {
        if ((*corner)[i]) {
            crnr[i] = Coord::ZERO_COORD;
        }
    }
    return crnr;
}

Space::SpaceCornerIterator Space::createSpaceCornerIterator() const
{
    return SpaceCornerIterator(this);
}

std::vector<Coord> Space::iPredecessor(const std::vector<Coord> & pnt, size_t dim) const
{
    assert(dim >= 0 && dim < this->dim());
    //
    std::vector<Coord> iPredec = pnt;
    iPredec[dim] = iPredec[dim].getGridPrev();
    return iPredec;
}

std::vector<Coord> Space::iSuccessor(const std::vector<Coord> & pnt, size_t dim) const
{
    assert(dim >= 0 && dim < this->dim());
    //
    std::vector<Coord> iPredec = pnt;
    iPredec[dim] = iPredec[dim].getGridNext();
    return iPredec;
}

const std::vector<Coord> & Space::getZeroPnt() const
{
    return zeroPnt;
}

