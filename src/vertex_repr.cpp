#include <algorithm>

#include "vertex_repr.h"

using namespace std;

NDimTable::NDimTable(const std::vector<size_t> & idxsLimits)
:
tableSize(0)
{
    jumpSizes.push_back(1);
    for (size_t i = 0; i < idxsLimits.size(); i ++) {
        jumpSizes.push_back(idxsLimits[i] * jumpSizes[i]);
        this->idxsLimits.push_back(idxsLimits[i]);
    }
    
    tableSize = jumpSizes.back();
    jumpSizes.pop_back();
}

bool NDimTable::checkLimits(const std::vector<size_t> & idxs) const
{
    for (size_t i = 0; i < idxs.size(); i ++) {
        if (idxs[i] > this->idxsLimits[i]) {
            return false;
        }
    }
    return true;
}

size_t NDimTable::calcTabIdx(const std::vector<size_t> & idxs) const
{
    assert(idxsLimits.size() == jumpSizes.size());
    assert(idxsLimits.size() == idxs.size());
    //

    size_t tabIdx = 0;
    for (size_t i = 0; i < idxs.size(); i ++) {
        tabIdx += jumpSizes[i] * idxs[i];
    }
    return tabIdx;
}

TriboolNDimTable::TriboolNDimTable(const std::vector<size_t> & idxsLimits)
:
NDimTable(idxsLimits)
{
    tabIsComputed = std::vector<bool>(tableSize, false);
    tabIsBlack = std::vector<bool>(tableSize, false);
}

void TriboolNDimTable::setValue(const std::vector<size_t> & idxs, enum TriboolNDimTable::Value val)
{
    assert(checkLimits(idxs));
    //
    size_t tabIdx = calcTabIdx(idxs);

    switch (val) {
    case NOT_COMPUTED:
        tabIsComputed[tabIdx] = false;
        break;
    case BLACK:
        tabIsComputed[tabIdx] = true;
        tabIsBlack[tabIdx] = true;
        break;
    case WHITE:
        tabIsComputed[tabIdx] = true;
        tabIsBlack[tabIdx] = false;
        break;
    default:
        assert(!"undef");
    }
}

enum TriboolNDimTable::Value TriboolNDimTable::getValue(const std::vector<size_t> & idxs) const
{
    assert(checkLimits(idxs));
    //
    size_t tabIdx = calcTabIdx(idxs);

    if (tabIsComputed[tabIdx]) {
        if (tabIsBlack[tabIdx]) {
            return BLACK;
        } else {
            return WHITE;
        }
    } else {
        return NOT_COMPUTED;
    }
}

void TriboolNDimTable::setBlack(const std::vector<size_t> & idxs)
{
    setValue(idxs, TriboolNDimTable::BLACK);
}

void TriboolNDimTable::setWhite(const std::vector<size_t> & idxs)
{
    setValue(idxs, TriboolNDimTable::WHITE);
}

BoolNDimTable::BoolNDimTable(const std::vector<size_t> & idxsLimits)
:
NDimTable(idxsLimits)
{
    table = vector<bool>(tableSize, false);
}

std::ostream & operator<<(std::ostream & os, const BoolNDimTable & btab)
{
    BoolvectorIterator bvIt(btab.idxsLimits.size());
    while (!bvIt.atEnd()) {
        vector<size_t> idxs(btab.idxsLimits.size());
        for (size_t i = 0; i < btab.idxsLimits.size(); i ++) {
            idxs[i] = (*bvIt)[i] ? 1 : 0;
            os << idxs[i] << " ";
        }
        os << ": ";
        os << (btab.getValue(idxs) ? "BLACK" : "W") << endl;
        ++ bvIt;
    }
    return os;
}

bool BoolNDimTable::operator<(const BoolNDimTable & other) const
{
    return table < other.table;
}

bool BoolNDimTable::getValue(const std::vector<size_t> & idxs) const
{
    return table[calcTabIdx(idxs)];
}

void BoolNDimTable::setTrue(const std::vector<size_t> & idxs)
{
    table[calcTabIdx(idxs)] = true;
}

void BoolNDimTable::setFalse(const std::vector<size_t> & idxs)
{
    table[calcTabIdx(idxs)] = false;
}

void BoolNDimTable::setValue(const std::vector<size_t> & idxs, bool val)
{
    table[calcTabIdx(idxs)] = val;
}

void BoolNDimTable::invert()
{
    for (size_t i = 0; i < table.size(); i ++) {
        table[i] = ! table[i];
    }
}

void InducedGrid::update(const VertexRepr & vr)
{
    vector<set<Coord> > coordsInSets;
    for (size_t i = 0; i < vr.space.dim(); i ++) {
        coordsInSets.push_back(set<Coord>());
        coords.push_back(vector<Coord>());
    }

    for (set<pair<vector<Coord>, bool> >::iterator it = vr.getVertexesWithColor().begin();
                                                   it != vr.getVertexesWithColor().end();
                                                   ++ it) {
        for (size_t i = 0; i < it->first.size(); i ++) {
            coordsInSets[i].insert(it->first[i]);
        }
    }

    for (size_t i = 0; i < coordsInSets.size(); i ++) {
        for (set<Coord>::iterator it = coordsInSets[i].begin(); it != coordsInSets[i].end(); ++ it) {
            coords[i].push_back(*it);
        }
        sizes.push_back(coords[i].size());
    }
}

std::ostream & operator<<(std::ostream & os, const InducedGrid & indGr)
{
    for (size_t i = 0; i < indGr.coords.size(); i ++) {
        os << setfill(' ') << setw(2) << i << ":  ";
        for (size_t j = 0; j < indGr.coords[i].size(); j ++) {
            os << indGr.coords[i][j];
            if (j != indGr.coords[i].size() - 1) {
                os << ", ";
            }
        }
        os << endl;
    }
    return os;
}

bool InducedGrid::findStartingIdxs(const std::vector<Coord> & pnt, std::vector<size_t> & idxs) const
{
    assert(pnt.size() == coords.size());
    assert(idxs.size() == 0);
    //

    for (size_t i = 0; i < pnt.size(); i ++) {
        vector<Coord>::const_iterator upper = std::upper_bound(coords[i].begin(), coords[i].end(), pnt[i]);
        if (upper == coords[i].begin()) {
            idxs.clear();
            return false;
        } else {
            idxs.push_back((upper - 1) - coords[i].begin());
        }
    }
    return true;
}

std::vector<Coord> InducedGrid::toPnt(const std::vector<size_t> & inducedIdxs) const
{
    assert(inducedIdxs.size() == coords.size());
    for (size_t i = 0; i < inducedIdxs.size(); i ++) {
        assert(inducedIdxs[i] >= 0 && inducedIdxs[i] < coords[i].size());
    }
    //

    vector<Coord> pnt;
    for (size_t i = 0; i < inducedIdxs.size(); i ++) {
        pnt.push_back(coords[i][inducedIdxs[i]]);
    }
    return pnt;
}

VertexRepr::VertexRepr(const Space &space, const std::set<std::pair<std::vector<Coord>, bool> > & vertexesWithColor)
:
Repr(space),
vertexesWithColor(vertexesWithColor),
colorMemoizer(NULL),
doDeallocMemoizer(true),
isInducedGridUpdated(false)
{
}

VertexRepr::VertexRepr(const Space &space)
:
VertexRepr(space, set<pair<vector<Coord>, bool> >())
{
}

VertexRepr::VertexRepr(const GridRepr & gr)
:
VertexRepr(gr.space, set<pair<vector<Coord>, bool> >())
{
    space = gr.space;
    Space::Iterator it = space.createIterator(true);
    while (!it.atEnd()) {
        bool isVertex = true;
        for (size_t i = 0; i < space.dim(); i ++) {
            Space::HalfNbhoodIterator nbIt = space.createHalfNbhoodIterator(&(*it), i, false);
            bool colorDiff = false;
            while (!nbIt.atEnd()) {
                if (gr.color(*nbIt) != gr.color(space.iPredecessor(*nbIt, i))) {
                    colorDiff = true;
                    break;
                }
                ++ nbIt;
            }
            if (!colorDiff) {
                isVertex = false;
                break;
            }
        }
        if (isVertex) {
            vertexesWithColor.insert(std::pair<std::vector<Coord>, bool>(*it, gr.color(*it)));
            assert(!(space.hasAllZeroCoords(*it) && !gr.color(*it)));
        }
        ++ it;
    }
}

VertexRepr::VertexRepr(const Space &space, const char *filepath)
:
VertexRepr(space, set<pair<vector<Coord>, bool> >())
{
    std::ifstream ifs;
    ifs.open(filepath);
    if (!ifs.is_open()) {
        cout << "Can't open file " << filepath << endl;
        exit(1);
    }
    string line;

    /* TODO: nutne prepsat nejak obecne pro obe moznosti int a float */

    while (getline(ifs, line)) {
        istringstream iss(line);
        vector<Coord> pnt;
        int n;
        bool emptyLine = false;
        for (size_t i = 0; i < space.dim(); i ++) {
            if (!(iss >> n)) {
                if (i == 0) {
                    emptyLine = true;
                    break;
                } else {
                    assert(!"bad count of coordinates");
                }
            }
            pnt.push_back(n);
        }
        if (emptyLine) {
            continue;
        }
        assert(pnt.size() == dim());
        string dummy;
        if (!(iss >> dummy) || dummy != "-") {
            assert(!"missing symbol '-'");
        }
        char cColor;
        if (!(iss >> cColor)) {
            assert(!"missing color value");
        }
        assert(cColor == 'b' || cColor == 'w');
        assert(!(iss >> dummy));
        assert(space.checkLimitsAllowLimits(pnt));

        vertexesWithColor.insert(pair<vector<Coord>,bool>(pnt, (cColor == 'b') ? true : false));
    }
}

VertexRepr::VertexRepr(const Space &space, const std::vector<Coord> & lowPnt, const std::vector<Coord> & highPnt)
:
VertexRepr(space, set<pair<vector<Coord>, bool> >())
{
    assert(space.checkLimitsAllowLimits(lowPnt) && space.checkLimitsAllowLimits(highPnt));
    assert(lower(lowPnt, highPnt));
    //
    
    BoolvectorIterator bvIt(space.dim());
    vertexesWithColor.insert(pair<vector<Coord>,bool>(lowPnt, true));
    ++ bvIt;
    while(!bvIt.atEnd()) {
        vector<Coord> coords;
        for (size_t i = 0; i < space.dim(); i ++) {
            coords.push_back((*bvIt)[i] ? highPnt[i] : lowPnt[i]);
        }
        vertexesWithColor.insert(pair<vector<Coord>,bool>(coords, false));
        ++ bvIt;
    }
}

VertexRepr::VertexRepr(const VertexRepr & other)
:
Repr(other.space),
vertexesWithColor(other.vertexesWithColor),
colorMemoizer(NULL),
doDeallocMemoizer(other.doDeallocMemoizer),
inducedGrid(other.inducedGrid),
isInducedGridUpdated(other.isInducedGridUpdated)
{
    if (other.colorMemoizer) {
        colorMemoizer = new TriboolNDimTable(*(other.colorMemoizer));
    }
}

VertexRepr & VertexRepr::operator=(const VertexRepr & other)
{
    space = other.space;
    vertexesWithColor = other.vertexesWithColor;
    doDeallocMemoizer = other.doDeallocMemoizer;
    inducedGrid = other.inducedGrid;
    isInducedGridUpdated = other.isInducedGridUpdated;
    if (colorMemoizer) {
        delete colorMemoizer;
        colorMemoizer = NULL;
        if (other.colorMemoizer) {
            colorMemoizer = new TriboolNDimTable(*(other.colorMemoizer));
        }
    }
    return *this;
}

VertexRepr::~VertexRepr()
{
    if (colorMemoizer) {
        delete colorMemoizer;
    }
}

VertexRepr :: operator GridRepr()
{
    GridRepr gr(space);
    Space::Iterator it = space.createIterator(true);
    while (!it.atEnd()) {
        if (color(*it)) {
            gr.addPnt(*it);
        }
        ++ it;
    }
    return gr;
}

void VertexRepr::addPnt(const std::vector<Coord> & pnt)
{
    assert(pnt.size() == dim());
    assert(space.checkLimitsAllowLimits(pnt));

    vertexesWithColor.insert(pair<vector<Coord>,bool>(pnt, true));
}

std::ostream & operator<<(std::ostream & os, const VertexRepr & vr)
{
    for (std::set<std::pair<std::vector<Coord>, bool> >::iterator it = vr.vertexesWithColor.begin();
                                                                  it != vr.vertexesWithColor.end();
                                                                  ++ it) {
        PRINT_POINT(it->first)
        os << " : " << (it->second ? "BLACK" : "W") << endl;
    }
    return os;
}

void VertexRepr::outputTikz(std::set<std::pair<std::vector<Coord>, char> > *additional)
{
    Space::Iterator it = space.createIterator(true);
    GridRepr gr(space);
    if ((*tikzOstream).rdbuf() == std::cerr.rdbuf()) {
        gr.setTikzOstreamToCerr();
    }
    while (!it.atEnd()) {
        if (color(*it)) {
            gr.addPnt(*it);
        }
        ++ it;
    }

    set<pair<vector<Coord>, char> > additionalAll;

    for (set<pair<vector<Coord>, bool> >::iterator it = vertexesWithColor.begin();
                                                   it != vertexesWithColor.end();
                                                   ++ it) {
        additionalAll.insert(pair<vector<Coord>, bool>(it->first, it->second ? 1 : 0));
    }
    if (additional) {
        additionalAll.insert(additional->begin(), additional->end());
    }
    gr.outputTikz(& additionalAll);
}

bool VertexRepr::isVertex(const std::vector<Coord> & pnt, bool *color)
{
    if (vertexesWithColor.find(pair<vector<Coord>, bool>(pnt, true)) != vertexesWithColor.end()) {
        *color = true;
        return true;
    } else if (vertexesWithColor.find(pair<vector<Coord>, bool>(pnt, false)) != vertexesWithColor.end()) {
        *color = false;
        return true;
    } else {
        return false;
    }
}

bool VertexRepr::colorRec(vector<size_t> inducedIdxs)
{
    /* Pokud jsme pod induced mrizkou, barva je bila */
    for (size_t i = 0; i < inducedIdxs.size(); i ++) {
        if (inducedIdxs[i] == (size_t)-1) {
            return false;
        }
    }

    TriboolNDimTable::Value lookup = colorMemoizer->getValue(inducedIdxs);
    if (lookup != TriboolNDimTable::NOT_COMPUTED) {
        return (lookup == TriboolNDimTable::BLACK) ? true : false;
    }
    
    bool col;

    if (isVertex(inducedGrid.toPnt(inducedIdxs), &col)) {
        /* nop */

    } else {
        bool wasSuchIndexFound = false;
        int suchIndex = -1;
        for (size_t i = 0; i < space.dim(); i ++) {
            bool allEqual = true;

            BoolvectorIterator bvIt(space.dim());
            ++ bvIt; /* preskoceni base pointu */
            while (!bvIt.atEnd()) {
                if (!(*bvIt)[i]) { /* iterujeme jen jednu polovinu nbhoodu */
                    vector<size_t> nbIdxs = inducedIdxs;
                    for (size_t j = 0; j < space.dim(); j ++) {
                        if ((*bvIt)[j]) {
                            nbIdxs[j] --;
                        }
                    }
                    vector<size_t> brotherIdxs = nbIdxs;
                    brotherIdxs[i] --;
                    if (colorRec(nbIdxs) != colorRec(brotherIdxs)) {
                        allEqual = false;
                        break;
                    }
                }
                ++ bvIt;
            }
            if (allEqual) {
                wasSuchIndexFound = true;
                suchIndex = i;
                break;
            }
        }

        if (wasSuchIndexFound) {
            vector<size_t> brotherIdxs = inducedIdxs;
            brotherIdxs[suchIndex] --;
            col = colorRec(brotherIdxs);

        } else {
            assert(!"At least one such 'i' must exist");
        }
    }

    if (col) {
        colorMemoizer->setBlack(inducedIdxs);
    } else {
        colorMemoizer->setWhite(inducedIdxs);
    }

    return col;
}

bool VertexRepr::color(const std::vector<Coord> & pnt)
{
    assert(space.checkLimitsAllowLimits(pnt, true));
    //

    bool col;

/*    if (isVertex(pnt, &col)) {
        return col;
    }
*/
    if (!isInducedGridUpdated) {
        inducedGrid.update(*this);
        isInducedGridUpdated = true;
        /* TODO: dealokovat memoizer a nastavit jej na NULL*/
    }

    if (!colorMemoizer) {
        colorMemoizer = new TriboolNDimTable(inducedGrid.sizes);
    }

    vector<size_t> inducedIdxs;
    if (!inducedGrid.findStartingIdxs(pnt, inducedIdxs)) {
        col = false;
    } else {
        col = colorRec(inducedIdxs);
    }

    if (doDeallocMemoizer) {
        delete colorMemoizer;
        colorMemoizer = NULL;
    }
    return col;
}

VertexRepr VertexRepr::complement() const
{
    set<pair<vector<Coord>, bool> > newVtxWithCol;

    /* Pokud je ve vertexesWithColor pocatek souradnic, pak jedine s cernou barvou */
    assert(vertexesWithColor.find(pair<vector<Coord>,bool>(space.getZeroPnt(), false)) == vertexesWithColor.end());

    /* V doplnku je pocatek souradnic prave tehdy, pokud puvodne nebyl */
    if (vertexesWithColor.find(pair<vector<Coord>,bool>(space.getZeroPnt(), true)) == vertexesWithColor.end()) {
        newVtxWithCol.insert(pair<vector<Coord>,bool>(space.getZeroPnt(), true));
    }

    /* Iteruji vsechny rohy z prostoru krome pocatku souradnic.
    V doplnku roh bude prave tehdy kdyz v puvodnim mnohostenu nebyl. */

    Space::SpaceCornerIterator spCorner = space.createSpaceCornerIterator();
    while(!spCorner.atEnd()) {
        if (!space.hasAllZeroCoords(*spCorner)) {

            /* Pokud je ve vertexesWithColor roh, pak jedine s bilou barvou */
            assert(vertexesWithColor.find(pair<vector<Coord>,bool>(*spCorner, true)) == vertexesWithColor.end());

            if (vertexesWithColor.find(pair<vector<Coord>,bool>(*spCorner, false)) == vertexesWithColor.end()) {
                newVtxWithCol.insert(pair<vector<Coord>,bool>(*spCorner, false));
            }
        }
        ++ spCorner;
    }

    /* Vrcholy z puvodniho mnohostenu budou v doplnku s opacnou barvou */

    for (set<pair<vector<Coord>, bool> >::iterator it = vertexesWithColor.begin();
                                                 it != vertexesWithColor.end();
                                                 ++ it) {
        if (space.isCorner(it->first)) {
            /* nop */
        } else if (space.isOnFrontBoundary(it->first)) {

            /* Pokud je v puvodnim mnohostenu bod z front boundary, pak jedine s bilou barvou */
            assert(vertexesWithColor.find(pair<vector<Coord>,bool>(it->first, true)) == vertexesWithColor.end());

            newVtxWithCol.insert(pair<vector<Coord>,bool>(it->first, false));

        } else {
            newVtxWithCol.insert(pair<vector<Coord>,bool>(it->first, !it->second));
        }
    }

    VertexRepr cmpl(space, newVtxWithCol);
    if (!doDeallocMemoizer) {
        cmpl.unsetDoDeallocMemoizer();
    }
    return cmpl;
}

bool VertexRepr::colorOnFacet(size_t dim, const std::vector<Coord> & pnt)
{
    return color(pnt) != color(space.iPredecessor(pnt, dim));
}

VertexRepr VertexRepr::iFacet(size_t dim, Coord fix)
{
    if (space.dim() == 1) {
        cout << "For 1D space there are no facets defined!" << endl;
        exit(1);
    }
    
    assert(dim >= 0 && dim < space.dim());
    assert(fix >= Coord::ZERO_COORD && fix <= space.limits[dim]);
    //

    set<pair<vector<Coord>, bool> > facetVertWithCol;

    for (set<pair<vector<Coord>, bool> >::iterator it = vertexesWithColor.begin();
                                                   it != vertexesWithColor.end();
                                                   ++ it) {
        if (it->first[dim] == fix) {
            bool isFctVertex = true;
            for (size_t i = 0; i < space.dim(); i ++) {
                if (i == dim) {
                    continue;
                }
                bool allSame = true;
                for (Space::HalfNbhoodIterator hnbIt = space.createHalfNbhoodIterator(&it->first, i, false);
                                               !hnbIt.atEnd();
                                               ++ hnbIt) {
                    if ((*hnbIt)[dim] == fix) {
                        if (colorOnFacet(dim, space.iPredecessor(*hnbIt, i)) != colorOnFacet(dim, *hnbIt)) {
                            allSame = false;
                            break;
                        }
                    }
                }

                if (allSame) {
                    isFctVertex = false;
                    break;
                }
            }
            if (isFctVertex) {
                vector<Coord> pntNew = it->first;
                pntNew.erase(pntNew.begin() + dim);
                facetVertWithCol.insert(pair<vector<Coord>, bool>(pntNew, colorOnFacet(dim, it->first)));
            }
        }
    }

    Space fctSpace(space);
    fctSpace.cutDimension(dim);
    return VertexRepr(fctSpace, facetVertWithCol);
}

VertexRepr VertexRepr::intersection(VertexRepr & other)
{
    assert(space == other.space);
    //

    set<pair<vector<Coord>, bool> > intersVertWithCol;
    set<vector<Coord> > alreadyChecked;

    for (set<pair<vector<Coord>, bool> >::iterator it1 = vertexesWithColor.begin(); it1 != vertexesWithColor.end(); ++ it1) {
        for (set<pair<vector<Coord>, bool> >::iterator it2 = other.vertexesWithColor.begin(); it2 != other.vertexesWithColor.end(); ++ it2) {

            vector<Coord> candidate = coordWiseMax(it1->first, it2->first);

            if (alreadyChecked.find(candidate) != alreadyChecked.end()) {
                continue;
            }

            alreadyChecked.insert(candidate);

            bool isVertex = true;
            for (size_t i = 0; i < space.dim(); i ++) {

                Space::HalfNbhoodIterator hnbIt = space.createHalfNbhoodIterator(& candidate, i, false);

                bool allSame = true;
                while (!hnbIt.atEnd()) {

                    bool hnbitColorInFirst = color(*hnbIt);
                    bool hnbitColorInSecond = other.color(*hnbIt);
                    bool predecColorInFirst = color(space.iPredecessor(*hnbIt, i));
                    bool predecColorInSecond = other.color(space.iPredecessor(*hnbIt, i));

                    if ((hnbitColorInFirst && hnbitColorInSecond) != (predecColorInFirst && predecColorInSecond)) {
                        allSame = false;
                        break;
                    }

                    ++ hnbIt;
                }

                if (allSame) {
                    isVertex = false;
                    break;
                }
            }
            if (isVertex) {
                bool candidColor = color(candidate) && other.color(candidate);
                intersVertWithCol.insert(pair<vector<Coord>,bool>(candidate, candidColor));
            }
        }
    }

    VertexRepr inters(space, intersVertWithCol);
    if (!doDeallocMemoizer) {
        inters.unsetDoDeallocMemoizer();
    }
    return inters;
}

VertexRepr VertexRepr::unification(VertexRepr & other)
{
    assert(space == other.space);
    //

    VertexRepr complOfOther = other.complement();
    return (complement().intersection(complOfOther)).complement();
}

VertexRepr VertexRepr::difference(VertexRepr & other)
{
    assert(space == other.space);
    //

    VertexRepr complOfOther = other.complement();
    return intersection(complOfOther);
}

void VertexRepr::unsetDoDeallocMemoizer()
{
    doDeallocMemoizer = false;
}

void VertexRepr::setDoDeallocMemoizer()
{
    doDeallocMemoizer = true;
}

const std::set<std::pair<std::vector<Coord>, bool> > & VertexRepr::getVertexesWithColor() const
{
    return vertexesWithColor;
}

std::vector<VertexRepr> VertexRepr::calcBoundary()
{
    if (space.dim() == 1) {
        cout << "Boundary can't be calculated for 1D polyhedron!" << endl;
        exit(1);
    }

    std::vector<VertexRepr> bndary;
    for (size_t i = 0; i < space.dim(); i ++) {
        Coord fix = Coord::ZERO_COORD;
        while (fix <= space.limits[i]) {
            VertexRepr fct = iFacet(i, fix);
            if (fct.getVertexesWithColor().size() > 0) { /* vkladame pouze neprazdne facety */
                bndary.push_back(fct);
            }
            fix = fix.getGridNext();
        }
    }

    return bndary;
}
