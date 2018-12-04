#include <algorithm>

#include "nbhood_repr.h"

using namespace std;

VertexWithNbhood::VertexWithNbhood(const std::vector<Coord> & vertex, const BoolNDimTable & nbhood)
:
vertex(vertex),
nbhood(nbhood)
{}

std::ostream & operator<<(std::ostream & os, const VertexWithNbhood & vertWithNbh)
{
    os << "--------- vertex:" << endl;
    PRINT_POINT(vertWithNbh.vertex)
    os << "--------- nbhood:" << endl;
    os << vertWithNbh.nbhood;
    return os;
}

bool VertexWithNbhood::operator<(const VertexWithNbhood & other) const
{
    return vertex < other.vertex;
}

bool VertexWithNbhood::operator==(const VertexWithNbhood & other) const
{
    return vertex == other.vertex;
}

VertexWithNbhood NbhoodRepr::calcNbhoodFromVertexRepr(const std::vector<Coord> & pnt, VertexRepr & vr) const
{
    BoolvectorIterator bvctIt(space.dim());
    vector<size_t> bndimTableLimits(space.dim(), 2);
    BoolNDimTable bndimTable(bndimTableLimits);
    Space::NbhoodIterator nbIt = space.createNbhoodIterator(&pnt);
    while (!nbIt.atEnd()) {
        vector<size_t> nbhoodIdxs(space.dim());
        for (size_t i = 0; i < space.dim(); i ++) {
            nbhoodIdxs[i] = (*bvctIt)[i] ? 1 : 0;
        }
        vr.unsetDoDeallocMemoizer();
        bool col = vr.color(*nbIt); /* pouzije se VertexRepr::color */
        if (col) {
            bndimTable.setTrue(nbhoodIdxs);
        } else {
            bndimTable.setFalse(nbhoodIdxs);
        }
        ++ nbIt;
        ++ bvctIt;
    }
    return VertexWithNbhood(pnt, bndimTable);
}

BoolNDimTable NbhoodRepr::calcNbhoodFromNbhoodRepr(const std::vector<Coord> & pnt) const
{
    BoolvectorIterator bvctIt(space.dim());
    vector<size_t> bndimTableLimits(space.dim(), 2);
    BoolNDimTable bndimTable(bndimTableLimits);
    Space::NbhoodIterator nbIt = space.createNbhoodIterator(&pnt);
    while (!nbIt.atEnd()) {
        vector<size_t> nbhoodIdxs(space.dim());
        for (size_t i = 0; i < space.dim(); i ++) {
            nbhoodIdxs[i] = (*bvctIt)[i] ? 1 : 0;
        }
        bool col;
        if (space.hasAtLeastOneUnderZeroCoord(*nbIt)) {
            col = false;
        } else {
            col = color(*nbIt); /* pouzije se NbhoodRepr::color */
        }
        bndimTable.setValue(nbhoodIdxs, col);
        ++ nbIt;
        ++ bvctIt;
    }
    return bndimTable;
}

NbhoodRepr::NbhoodRepr(const Space &space, const std::vector<VertexWithNbhood> & vertexesWithNbhood)
:
Repr(space),
vertexesWithNbhood(vertexesWithNbhood),
zeroPntNbhood(BoolNDimTable(vector<size_t>(space.dim(), 2)))
{
    zeroPntNbhood.setTrue(vector<size_t>(space.dim(), 0)); /* pokud je pocatek souradnic vertex, pak je vzdy cerny */
}

NbhoodRepr::NbhoodRepr(const Space &space)
:
NbhoodRepr(space, vector<VertexWithNbhood>())
{
}

NbhoodRepr::NbhoodRepr(const GridRepr & gr)
:
NbhoodRepr(gr.space, vector<VertexWithNbhood>())
{   
    VertexRepr vr(gr);
    vr.unsetDoDeallocMemoizer();
    for (set<pair<vector<Coord>, bool> >::iterator it = vr.getVertexesWithColor().begin();
                                                   it != vr.getVertexesWithColor().end();
                                                   ++ it) {
        vertexesWithNbhood.push_back(calcNbhoodFromVertexRepr(it->first, vr));
    }
}

NbhoodRepr::NbhoodRepr(const Space &space, const std::vector<Coord> & lowPnt, const std::vector<Coord> & highPnt)
:
NbhoodRepr(space, vector<VertexWithNbhood>())
{
    assert(space.checkLimitsAllowLimits(lowPnt) && space.checkLimitsAllowLimits(highPnt));
    assert(lower(lowPnt, highPnt));
    //

    set<VertexWithNbhood> newVtxsWithNbh;

    BoolvectorIterator bvIt(space.dim());
    newVtxsWithNbh.insert(VertexWithNbhood(lowPnt, getZeroPntNbhood()));
    ++ bvIt;

    while(!bvIt.atEnd()) {
        vector<Coord> coords;
        for (size_t i = 0; i < space.dim(); i ++) {
            coords.push_back((*bvIt)[i] ? highPnt[i] : lowPnt[i]);
        }
        
        BoolNDimTable bndim(vector<size_t>(space.dim(), 2));
        BoolvectorIterator bndimIt(space.dim());
        Space::NbhoodIterator nbIt = space.createNbhoodIterator(& coords);

        while (!nbIt.atEnd()) {
            if (lowerOrEqual(lowPnt, *nbIt) && lower(*nbIt, highPnt)) {
                bndim.setTrue(boolVectorToSizetVector(*bndimIt));
            }

            ++ nbIt;
            ++ bndimIt;
        }

        newVtxsWithNbh.insert(VertexWithNbhood(coords, bndim));

        ++ bvIt;
    }

    for (set<VertexWithNbhood>::iterator it = newVtxsWithNbh.begin(); it != newVtxsWithNbh.end(); ++ it) {
        vertexesWithNbhood.push_back(*it);
    }
}

NbhoodRepr :: operator GridRepr()
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

std::ostream & operator<<(std::ostream & os, const NbhoodRepr & nbhoodRepr)
{
    for (size_t i = 0; i < nbhoodRepr.vertexesWithNbhood.size(); i ++) {
        os << nbhoodRepr.vertexesWithNbhood[i];
        if (i != nbhoodRepr.vertexesWithNbhood.size() - 1) {
            os << endl;
        }
    }
    return os;
}

void NbhoodRepr::outputTikz(std::set<std::pair<std::vector<Coord>, char> > *additional)
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

    for (size_t i = 0; i < vertexesWithNbhood.size(); i ++) {

        additionalAll.insert(pair<vector<Coord>, bool>(vertexesWithNbhood[i].vertex, getVertexColor(vertexesWithNbhood[i])));
    }
    
    if (additional) {
        additionalAll.insert(additional->begin(), additional->end());
    }
    gr.outputTikz(& additionalAll);
}

size_t NbhoodRepr::vertexCnt() const
{
    return vertexesWithNbhood.size();
}

bool NbhoodRepr::colorOfSingleVertex() const
{
    assert(vertexesWithNbhood.size() == 1);
    //

    vector<size_t> nbhoodIdxs;
    return vertexesWithNbhood[0].nbhood.getValue(nbhoodIdxs);
}

void NbhoodRepr::printVertexesCoords()
{
    for (size_t i = 0; i < vertexesWithNbhood.size(); i ++) {
        PRINT_POINT(vertexesWithNbhood[i].vertex)
    }
}

bool NbhoodRepr::isInVertexList(const std::vector<Coord> & pnt, BoolNDimTable & nbhood) const
{
    BoolNDimTable dummyBdimt;
    VertexWithNbhood vrtxWithNbh(pnt, dummyBdimt);
    vector<VertexWithNbhood>::const_iterator it = std::find(vertexesWithNbhood.begin(), vertexesWithNbhood.end(), vrtxWithNbh);
    if (it != vertexesWithNbhood.end()) {
        nbhood = it->nbhood;
        return true;
    }
    return false;
}

bool NbhoodRepr::isInVertexList(const std::vector<Coord> & pnt) const
{
    BoolNDimTable dummyBdimt;
    VertexWithNbhood vrtxWithNbh(pnt, dummyBdimt);
    return std::find(vertexesWithNbhood.begin(), vertexesWithNbhood.end(), vrtxWithNbh) != vertexesWithNbhood.end();
}

void NbhoodRepr::readCoordsFromFile(const char * filepath)
{
    vector<VertexWithNbhood> vertWithNbh;
    std::ifstream ifs;
    ifs.open(filepath);
    if (!ifs.is_open()) {
        cout << "Can't open file " << filepath << endl;
        exit(1);
    }
    string line;
    int pntDim;
    ifs >> pntDim;
    while (getline(ifs, line)) {
        istringstream iss(line);
        vector<Coord> pnt;
        int n;
        bool emptyLine = false;
        for (int i = 0; i < pntDim; i ++) {
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
        vector<size_t> dummyLimits;
        BoolNDimTable dummyBtab(dummyLimits);
        vertWithNbh.push_back(VertexWithNbhood(pnt, dummyBtab));
    }
    vertexesWithNbhood = vertWithNbh;
}

vector<size_t> NbhoodRepr::iSectionVertexCandidates(size_t dim, const Coord & fix) const
{
    assert(dim >= 0 && dim < space.dim());
    assert(fix >= Coord::ZERO_COORD && fix <= space.limits[dim]);
    //

    vector<size_t> candidates;

    if (vertexesWithNbhood.size() == 0) {
        return candidates;

    } else if (vertexesWithNbhood.size() == 1) {
        /* pokud existuje jediny vrchol, pak nema zadneho vrcholoveho naslednika ve smeru 'dim',
        proto je kandidatem */
        candidates.push_back(0);
        return candidates;
    }

    vector<Coord> fixPnt = vertexesWithNbhood[0].vertex;
    size_t cand = 0;
    for (size_t i = 1; i < vertexesWithNbhood.size(); i ++) {
        const vector<Coord> & current = vertexesWithNbhood[i].vertex;
        // PRINT_POINT(current)
        if (!pntsEqualDontCareLastCoord(fixPnt, current)) {

            //////////////////
            if (vertexesWithNbhood[cand].vertex[dim] <= fix) {
                candidates.push_back(cand);
            }            
            //////////////////

            fixPnt = current;
            cand = i;
        } else {
            // cout << "--------------------" << endl;
            // cout << current[dim] << "__" << vertexesWithNbhood[cand].vertex[dim] << endl;
            if (current[dim] > vertexesWithNbhood[cand].vertex[dim] && current[dim] <= fix) {
                cand = i;
                // cout << "updated" << endl;
            }
            if (i == vertexesWithNbhood.size() - 1) {
                //////////////////
                if (vertexesWithNbhood[cand].vertex[dim] <= fix) {
                    candidates.push_back(cand);
                }            
                //////////////////
            }
        }
    }
    return candidates;
}

bool NbhoodRepr::isISectionVertex(size_t vertexId, size_t dim) const
{
    assert(dim >= 0 && dim < space.dim());
    //

    for (size_t i = 0; i < space.dim(); i ++) {
        if (i == dim) {
            continue;
        }

        bool allSame = true;

        BoolvectorIterator bvIt(space.dim());
        while (!bvIt.atEnd()) {
            if ((*bvIt)[dim] == false) { /* viz podminka v dukazu: body se berou pouze z pruseku s nbhood^dim */
                                        /* pozor: false odpovida vetsi souradnici, true odpovida te mensi */
                if ((*bvIt)[i] == false) { /* iteruji jen half neighbourhood: nbhood^(i-) */
                                            /* pozor: false odpovida vetsi souradnici, true odpovida te mensi */

                    /* do BoolNDimTable se da pristupovat pouze pres indexy typu size_t */
                    vector<size_t> nbIdxs = boolVectorToSizetVector(*bvIt);
                    
                    vector<bool> brother = *bvIt; /* bratr aktualniho bodu sousedstvi ve smeru 'i' */
                    brother[i] = !brother[i];     /* bratr se od aktualniho bodu lisi v 'i'-te souradnici */

                    /* do BoolNDimTable se da pristupovat pouze pres indexy typu size_t */
                    vector<size_t> brotherIdxs = boolVectorToSizetVector(brother);

                    const BoolNDimTable & vertexNbhood = vertexesWithNbhood[vertexId].nbhood;

                    if (vertexNbhood.getValue(nbIdxs) != vertexNbhood.getValue(brotherIdxs)) {
                        allSame = false;
                        break;
                    }
                }
            }
            ++ bvIt;
        }

        if (allSame) {
            return false;
        }
    }
    return true;
}

NbhoodRepr NbhoodRepr::iSection(size_t dim, const Coord & fix) const
{
    assert(dim >= 0 && dim < space.dim());
    assert(fix >= Coord::ZERO_COORD && fix <= space.limits[dim]);
    //

    vector<VertexWithNbhood> vtxsWithNbh;

    vector<size_t> vrtxCandidates = iSectionVertexCandidates(dim, fix);
    
    for (size_t i = 0; i < vrtxCandidates.size(); i ++) {
        if (isISectionVertex(vrtxCandidates[i], dim)) {

            /* Vertex v i-sekci ma o dimenzi mene nez v puvodnim mnohostenu - nebude mit
            souradnici v dimenzi 'dim' */
            vector<Coord> trimmedCoords(vertexesWithNbhood[vrtxCandidates[i]].vertex.begin(),
                                        vertexesWithNbhood[vrtxCandidates[i]].vertex.end() - 1);
            /* Nbhood v i-sekci ma o dimenzi mene nez v puvodnim mnohostenu - nebude mit
            souradnice v dimenzi 'dim' */
            vector<size_t> bndimTableLimits(space.dim() - 1, 2);
            BoolNDimTable trimmedNbhood(bndimTableLimits);



            BoolvectorIterator bvIt(space.dim());
            while (!bvIt.atEnd()) {
                if ((*bvIt)[dim] == false) { /* nbhood v i-sekci ztrati druhou polovinu puvodniho nbhoodu */
                    
                    vector<bool> trimmedNbhoodBv = *bvIt;
                    trimmedNbhoodBv.erase(trimmedNbhoodBv.begin() + dim);

                    /* do BoolNDimTable se da pristupovat pouze pres indexy typu size_t */
                    vector<size_t> oldNbhoodIdxs = boolVectorToSizetVector(*bvIt);

                    /* do BoolNDimTable se da pristupovat pouze pres indexy typu size_t */
                    vector<size_t> trimmedNbhoodIdxs = boolVectorToSizetVector(trimmedNbhoodBv);

                    /* Vyplneni nbhoodu pro sekci */

                    if (vertexesWithNbhood[vrtxCandidates[i]].nbhood.getValue(oldNbhoodIdxs) == true) {
                        trimmedNbhood.setTrue(trimmedNbhoodIdxs);
                    } else {
                        trimmedNbhood.setFalse(trimmedNbhoodIdxs);
                    }
                }
                ++ bvIt;
            }
            vtxsWithNbh.push_back(VertexWithNbhood(trimmedCoords, trimmedNbhood));
        }
    }
    Space isectSpace(space);
    isectSpace.cutDimension(dim);
    return NbhoodRepr(isectSpace, vtxsWithNbh);
}

bool NbhoodRepr::color(const std::vector<Coord> & pnt) const
{
    /*BoolNDimTable vrtNbh;
    if (isInVertexList(pnt, vrtNbh)) {
        return getVertexColor(VertexWithNbhood(pnt, vrtNbh));
    }*/

    NbhoodRepr isect = iSection(space.dim() - 1, pnt[space.dim() - 1]);
    for (int i = space.dim() - 2; i != -1; i --) {
        isect = isect.iSection(i, pnt[i]);
    }
    assert(isect.vertexCnt() <= 1);

    if (isect.vertexCnt() == 0) {
        return false;
    } else {
        return isect.colorOfSingleVertex();
    }
}

void NbhoodRepr::vertexesWithColorFromVertexesWithNbhood(std::vector<VertexWithNbhood> vWithNbhood, std::set<std::pair<std::vector<Coord>, bool> > & vWithColor) const
{
    vector<size_t> idxsOfBasePnt(space.dim(), 0);
    for (size_t i = 0; i < vWithNbhood.size(); i ++) {
        vWithColor.insert(pair<vector<Coord>, bool>(vWithNbhood[i].vertex, vWithNbhood[i].nbhood.getValue(idxsOfBasePnt)));
    }
}

bool NbhoodRepr::getVertexColor(const struct VertexWithNbhood & vtxWithNbh) const
{
    return vtxWithNbh.nbhood.getValue(vector<size_t>(space.dim(), 0));
}

BoolNDimTable NbhoodRepr::calcIntersectionOfNbhoods(const BoolNDimTable & nbh1, const BoolNDimTable & nbh2) const
{
    BoolNDimTable intersNbh(vector<size_t>(space.dim(), 2));
    BoolvectorIterator bvIt(space.dim());
    while(!bvIt.atEnd()) {
        bool intersColor = nbh1.getValue(boolVectorToSizetVector(*bvIt)) && nbh2.getValue(boolVectorToSizetVector(*bvIt));
        intersNbh.setValue(boolVectorToSizetVector(*bvIt), intersColor);
        ++ bvIt;
    }
    return intersNbh;
}

bool NbhoodRepr::isVertex(const BoolNDimTable & nbhood) const
{
    for (size_t i = 0; i < space.dim(); i ++) {
        bool allSame = true;
        BoolvectorIterator bvIt(space.dim());
        while (!bvIt.atEnd()) {
            if ((*bvIt)[i] == false) { /* iteruji jednu polovinu nbhoodu a dotazuji se na bratry v druhe polovine */
                vector<bool> brother = *bvIt;
                brother[i] = true;
                if (nbhood.getValue(boolVectorToSizetVector(*bvIt)) != nbhood.getValue(boolVectorToSizetVector(brother))) {
                    allSame = false;
                    break;
                }
            }
            ++ bvIt;
        }
        if (allSame) {
            return false;
        }
    }
    return true;
}

const BoolNDimTable & NbhoodRepr::getZeroPntNbhood() const
{
    return zeroPntNbhood;
}

NbhoodRepr NbhoodRepr::intersection(NbhoodRepr & other) const
{
    assert(space == other.space);
    //

    set<VertexWithNbhood> newVtxsWithNbh;
    set<vector<Coord> > alreadyChecked;

    for (vector<VertexWithNbhood>::const_iterator it1 = vertexesWithNbhood.begin(); it1 != vertexesWithNbhood.end(); ++ it1) {
        for (vector<VertexWithNbhood>::const_iterator it2 = other.vertexesWithNbhood.begin(); it2 != other.vertexesWithNbhood.end(); ++ it2) {

            vector<Coord> candidate = coordWiseMax((*it1).vertex, (*it2).vertex);

            if (alreadyChecked.find(candidate) != alreadyChecked.end()) {
                continue;
            }

            alreadyChecked.insert(candidate);

            BoolNDimTable nbhInFirst, nbhInSecond;

            if (!isInVertexList(candidate, nbhInFirst)) {
                    nbhInFirst = calcNbhoodFromNbhoodRepr(candidate);
            }
            if (!other.isInVertexList(candidate, nbhInSecond)) {
                nbhInSecond = other.calcNbhoodFromNbhoodRepr(candidate);
            }

            BoolNDimTable intersNbh = calcIntersectionOfNbhoods(nbhInFirst, nbhInSecond);

            if (isVertex(intersNbh)) {
                newVtxsWithNbh.insert(VertexWithNbhood(candidate, intersNbh));
            }
        }
    }

    vector<VertexWithNbhood> vectorNewVtxsWithNbh;
    for (set<VertexWithNbhood>::iterator it = newVtxsWithNbh.begin(); it != newVtxsWithNbh.end(); ++ it) {
        vectorNewVtxsWithNbh.push_back(*it);
    }
    return NbhoodRepr(space, vectorNewVtxsWithNbh);
}

void NbhoodRepr::correctNbhoodLimitPntsToWhite(const std::vector<Coord> & pnt, BoolNDimTable & nbh) const
{
    BoolvectorIterator bvctIt(space.dim());
    BoolNDimTable bndimTable(vector<size_t>(space.dim(), 2));
    Space::NbhoodIterator nbIt = space.createNbhoodIterator(& pnt);
    while (!nbIt.atEnd()) {
        if (space.isOnFrontBoundary(*nbIt) || space.hasAtLeastOneUnderZeroCoord(*nbIt)) {
            nbh.setFalse(boolVectorToSizetVector(*bvctIt));
        }
        ++ nbIt;
        ++ bvctIt;
    }
}

NbhoodRepr NbhoodRepr::complement() const
{
    set<VertexWithNbhood> newVtxsWithNbh;

    for (size_t i = 0; i < vertexesWithNbhood.size(); i ++) {
        BoolNDimTable newNbh = vertexesWithNbhood[i].nbhood;
        newNbh.invert();

        /* Nastav bilou barvu bodum, ktere jsou na front boundary ci pod nulou
        (protoze jim se invertovanim barva otocila na cernou, a to je spatne) */
        correctNbhoodLimitPntsToWhite(vertexesWithNbhood[i].vertex, newNbh);

        newVtxsWithNbh.insert(VertexWithNbhood(vertexesWithNbhood[i].vertex, newNbh));
    }

    Space::SpaceCornerIterator spCorner = space.createSpaceCornerIterator();
    while(!spCorner.atEnd()) {
        if (!space.hasAllZeroCoords(*spCorner)) {
            if (!isInVertexList(*spCorner)) {
                vector<Coord> crnrCoords = *spCorner;
                BoolNDimTable newNbh = calcNbhoodFromNbhoodRepr(crnrCoords);
                newNbh.invert();

                /* Nastav bilou barvu bodum, ktere jsou na front boundary ci pod nulou
                (protoze jim se invertovanim barva otocila na cernou, a to je spatne) */
                correctNbhoodLimitPntsToWhite(crnrCoords, newNbh);

                newVtxsWithNbh.insert(VertexWithNbhood(crnrCoords, newNbh));
            }
        }
        ++ spCorner;
    }

    if (!isInVertexList(space.getZeroPnt())) {
        newVtxsWithNbh.insert(VertexWithNbhood(space.getZeroPnt(), getZeroPntNbhood()));
    }

    vector<VertexWithNbhood> vectorNewVtxsWithNbh;
    for (set<VertexWithNbhood>::iterator it = newVtxsWithNbh.begin(); it != newVtxsWithNbh.end(); ++ it) {
        vectorNewVtxsWithNbh.push_back(*it);
    }
    return NbhoodRepr(space, vectorNewVtxsWithNbh);
}

NbhoodRepr NbhoodRepr::unification(NbhoodRepr & other) const
{
    assert(space == other.space);
    //

    NbhoodRepr complOfOther = other.complement();
    return (complement().intersection(complOfOther)).complement();
}

NbhoodRepr NbhoodRepr::difference(NbhoodRepr & other) const
{
    assert(space == other.space);
    //

    NbhoodRepr complOfOther = other.complement();
    return intersection(complOfOther);
}

bool NbhoodRepr::colorOnFacet(size_t dim, const BoolNDimTable & nbhood, const vector<bool> & nbhPnt) const
{
    assert(nbhPnt.size() == space.dim());
    assert(nbhPnt[dim] == false); /* je mozne se dotazat pouze na body, ktere jsou na facetu */
    //

    vector<bool> outerBrother = nbhPnt;
    outerBrother[dim] = true;

    return nbhood.getValue(boolVectorToSizetVector(nbhPnt)) != nbhood.getValue(boolVectorToSizetVector(outerBrother));

}

NbhoodRepr NbhoodRepr::iFacet(size_t dim, Coord fix) const
{
    if (space.dim() == 1) {
        cout << "For 1D space there are no facets defined!" << endl;
        exit(1);
    }
    
    assert(dim >= 0 && dim < space.dim());
    assert(fix >= Coord::ZERO_COORD && fix <= space.limits[dim]);
    //

    vector<VertexWithNbhood> facetVertWithNbh;;

    for (size_t i = 0; i < vertexesWithNbhood.size(); i ++) {
        if (vertexesWithNbhood[i].vertex[dim] == fix) {
            // cout << vertexesWithNbhood[i];
            bool isFctVertex = true;
            for (size_t j = 0; j < space.dim(); j ++) {
                if (j == dim) {
                    continue;
                }

                bool allSame = true;

                BoolvectorIterator bvIt(space.dim());
                while (!bvIt.atEnd()) {
                    if ((*bvIt)[dim] == false) { /* viz Maleruv clanek: x' se bere z pruniku mnozin N^{j}(x), N^{dim}(x) */
                        if ((*bvIt)[j] == false) { /* iterujeme half nbhood a dotazujeme se na bratra z druhe poloviny */
                            vector<bool> brother = *bvIt;
                            brother[j] = ! brother[j];
                            if (colorOnFacet(dim, vertexesWithNbhood[i].nbhood, *bvIt) !=
                                colorOnFacet(dim, vertexesWithNbhood[i].nbhood, brother)) {
                                allSame = false;
                            }
                        }
                    }
                    ++ bvIt;
                }

                if (allSame) {
                    isFctVertex = false;
                    break;
                }
            }
            if (isFctVertex) {

                /* Vertex ve facetu ztrati dimenzi 'dim' */

                vector<Coord> trimmedPnt = vertexesWithNbhood[i].vertex;
                trimmedPnt.erase(trimmedPnt.begin() + dim);

                /* Vytvoreni nbhoodu daneho vertexu platneho ve facetu,
                nbhood je o dimenzi mensi nez prislusny nbhood v puvodnim mnohostenu */

                BoolNDimTable facetNbh(vector<size_t>(space.dim() - 1, 2));
                BoolvectorIterator bvIt(space.dim());
                BoolvectorIterator fctBvIt(space.dim() - 1);

                while (!bvIt.atEnd()) {
                    if ((*bvIt)[dim] == false) { /* iterujeme pouze body, ktere jsou ve facetu */
                        facetNbh.setValue(boolVectorToSizetVector(*fctBvIt),
                                            colorOnFacet(dim, vertexesWithNbhood[i].nbhood, *bvIt));
                        ++ fctBvIt;
                    }
                    ++ bvIt;
                }

                /*cout << vertexesWithNbhood[i];
                cout << "####################" << endl;
                cout << facetNbh;
                cout << "####################" << endl;*/

                facetVertWithNbh.push_back(VertexWithNbhood(trimmedPnt, facetNbh));
            }
        }
    }

    Space fctSpace(space);
    fctSpace.cutDimension(dim);
    return NbhoodRepr(fctSpace, facetVertWithNbh);
}

const std::vector<VertexWithNbhood> & NbhoodRepr::getVertexesWithNbhood() const
{
    return vertexesWithNbhood;  
}

const std::vector<Coord> & NbhoodRepr::getLowestPnt() const
{
    return vertexesWithNbhood[0].vertex;
}

std::vector<NbhoodRepr> NbhoodRepr::calcBoundary()
{
    if (space.dim() == 1) {
        cout << "Boundary can't be calculated for 1D polyhedron!" << endl;
        exit(1);
    }

    std::vector<NbhoodRepr> bndary;
    for (size_t i = 0; i < space.dim(); i ++) {
        Coord fix = Coord::ZERO_COORD;
        while (fix <= space.limits[i]) {
            NbhoodRepr fct = iFacet(i, fix);
            if (fct.getVertexesWithNbhood().size() > 0) { /* vkladame pouze neprazdne facety */
                bndary.push_back(fct);
            }
            fix = fix.getGridNext();
        }
    }

    return bndary;
}
