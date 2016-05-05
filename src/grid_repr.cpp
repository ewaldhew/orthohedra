#include <iomanip>
#include <algorithm>

#include "grid_repr.h"

using namespace std;

GridRepr::GridRepr(const Space &space)
:
Repr(space),
doTikzPrintGridPnts(false)
{}

GridRepr::GridRepr(const Space &space, const char *filepath, bool considerAsNthFloat)
:
Repr(space),
doTikzPrintGridPnts(false)
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
        int n;
        vector<Coord> pnt;
        while (iss >> n) {
            if (considerAsNthFloat) {
                pnt.push_back(nthFloat(n));
            } else {
                pnt.push_back(n);
            }
        }

        if (pnt.size() == 0) {
            continue;
        } else {
            assert(pnt.size() == dim());
            assert(space.checkLimits(pnt));
        }
        addPnt(pnt);
    }
}

GridRepr::GridRepr(const Space &space, const std::vector<Coord> & lowPnt, const std::vector<Coord> & highPnt)
:
Repr(space),
doTikzPrintGridPnts(false)
{
    assert(space.checkLimitsAllowLimits(lowPnt) && space.checkLimitsAllowLimits(highPnt));
    assert(lower(lowPnt, highPnt));
    //

    vector<Coord> subHighPnt = highPnt;
    for (size_t i = 0; i < subHighPnt.size(); i ++) {
        subHighPnt[i] = subHighPnt[i].getGridPrev();
    }

    Space::Iterator it = space.createIterator();
    while (!it.atEnd()) {
        if (lowerOrEqual(lowPnt, *it) && lowerOrEqual(*it, subHighPnt)) {
            addPnt(*it);
        }
        ++ it;
    }
}

std::ostream & operator<<(std::ostream & os, const GridRepr & gridRepr)
{
    for (set<std::vector<Coord> >::iterator it = gridRepr.points.begin(); it != gridRepr.points.end(); ++ it) {
        PRINT_POINT(*it)
    }
    return os;
}

bool GridRepr::operator==(const GridRepr & other) const
{
    return space == other.space && points == other.points;
}

void GridRepr::outputTikzBoxFacet3D(const vector<Coord> & pnt, size_t dim) const
{
    /* Box-facet ve 3D je ctverecek */

    vector<Coord> pntRmost = pnt;
    for (size_t i = 0; i < pntRmost.size(); i ++) {
        pntRmost[i] = pntRmost[i].getGridNext();
    }
    Space::HalfNbhoodIterator hnbIt = space.createHalfNbhoodIterator(&pntRmost, dim, true);
    vector<vector<Coord> > facet;
    while(!hnbIt.atEnd()) {
        facet.push_back(*hnbIt);
        ++ hnbIt;
    }
    iter_swap(facet.begin() + 2, facet.begin() + 3);
    *tikzOstream << "\\draw[cube, fill=gray, fill opacity=0.6] ";
    for (size_t i = 0; i < facet.size(); i ++) {
        *tikzOstream << "(";
        for (size_t j = 0; j < space.dim(); j ++) {
            *tikzOstream << facet[i][j];
            if (j < space.dim() - 1) {
                *tikzOstream << ", ";
            }
        }
        *tikzOstream << ")";
        if (i < facet.size() - 1) {
            *tikzOstream << " -- ";
        }
    }
    *tikzOstream << " -- cycle;" << endl;
}

void GridRepr::outputTikzBoxFacet2D(const vector<Coord> & pnt, size_t dim) const
{
    /* Box-facet ve 2D je usecka */
    assert(!"not yet impl");
}

void GridRepr::outputTikzBox3D(const vector<Coord> & pnt) const
{
    for (size_t i = 0; i < space.dim(); i ++) {
        outputTikzBoxFacet3D(pnt, i);
        outputTikzBoxFacet3D(space.iSuccessor(pnt, i), i);
    }
}

void GridRepr::outputTikzBox2D(const vector<Coord> & pnt) const
{
    vector<Coord> pntRmost = pnt;
    for (size_t i = 0; i < pntRmost.size(); i ++) {
        pntRmost[i] = pntRmost[i].getGridNext();
    }
    Space::NbhoodIterator hnbIt = space.createNbhoodIterator(&pntRmost);
    vector<vector<Coord> > facet;
    while(!hnbIt.atEnd()) {
        facet.push_back(*hnbIt);
        ++ hnbIt;
    }
    iter_swap(facet.begin() + 2, facet.begin() + 3);
    *tikzOstream << "\\draw[cube, fill=gray, fill opacity=0.6] ";
    for (size_t i = 0; i < facet.size(); i ++) {
        *tikzOstream << "(";
        for (size_t j = 0; j < space.dim(); j ++) {
            *tikzOstream << facet[i][j];
            if (j < space.dim() - 1) {
                *tikzOstream << ", ";
            }
        }
        *tikzOstream << ")";
        if (i < facet.size() - 1) {
            *tikzOstream << " -- ";
        }
    }
    *tikzOstream << " -- cycle;" << endl;
}

void GridRepr::outputTikzAdditional(const std::set<std::pair<std::vector<Coord>, char> > *additional) const
{
    for (std::set<std::pair<std::vector<Coord>, char> >::iterator it = additional->begin();
                                                                  it != additional->end();
                                                                  ++ it) {
        *tikzOstream << "\\node[circle, draw=black";
        switch (it->second) {
        case 0:
            *tikzOstream << ", fill=white";
            break;
        case 1:
            *tikzOstream << ", fill=black";
            break;
        case 2:
            *tikzOstream << ", fill=red";
            break;
        default:
            assert(!"undef");
        }
        
        *tikzOstream << ", thick, inner sep=0pt, minimum size=5pt] at (";
        for (size_t i = 0; i < it->first.size(); i ++) {
            *tikzOstream << it->first[i];
            if (i < it->first.size() - 1) {
                *tikzOstream << ",";
            }
        }
        *tikzOstream << ") {};" << endl;
    }
}

void GridRepr::outputTikz3D(const std::set<std::pair<std::vector<Coord>, char> > *additional) const
{
    assert(space.limits[0] >= 2 && space.limits[1] >= 2 && space.limits[2] >= 2);
    //
    int xLmt = space.limits[0].co,
        yLmt = space.limits[1].co,
        zLmt = space.limits[2].co;
    string xRange, yRange, zRange;
    stringstream sstm;

    sstm << "0,1,...," << xLmt;
    xRange = sstm.str();
    sstm.str("");

    sstm << "0,1,...," << yLmt;
    yRange = sstm.str();
    sstm.str("");

    sstm << "0,1,...," << zLmt;
    zRange = sstm.str();
    sstm.str("");

    *tikzOstream <<
        "\\foreach \\x in {" << xRange << "}" << endl <<
        "{" << endl <<
            "\\draw[grid] (\\x,0,0) -- (\\x," << yLmt << ",0);" << endl <<
        "}" << endl <<
        "\\foreach \\y in {" << yRange << "}" << endl <<
        "{" << endl <<
            "\\draw[grid] (0,\\y,0) -- (" << xLmt << ",\\y,0);" << endl <<
        "}" << endl <<
        "\\foreach \\y in {" << yRange << "}" << endl <<
        "{" << endl <<
            "\\draw[grid] (0,\\y,0) -- (0,\\y," << zLmt << ");" << endl <<
        "}" << endl <<
        "\\foreach \\z in {" << zRange << "}" << endl <<
        "{" << endl <<
            "\\draw[grid] (0,0,\\z) -- (0," << yLmt << ",\\z);" << endl <<
        "}" << endl <<
        "\\foreach \\x in {" << xRange << "}" << endl <<
        "{" << endl <<
            "\\draw[grid] (\\x,0,0) -- (\\x,0," << zLmt << ");" << endl <<
        "}" << endl <<
        "\\foreach \\z in {" << zRange << "}" << endl <<
        "{" << endl <<
            "\\draw[grid] (0,0,\\z) -- (" << xLmt << ",0,\\z);" << endl <<
        "}" << endl <<

        "\\draw[axis] (0,0,0) -- (" << xLmt << ",0,0) node[anchor=west]{$dim 1$};" << endl <<
        "\\draw[axis] (0,0,0) -- (0," << yLmt << ",0) node[anchor=west]{$dim 2$};" << endl <<
        "\\draw[axis] (0,0,0) -- (0,0," << zLmt << ") node[anchor=west]{$dim 3$};" << endl <<

        "\\foreach \\coo in {1,...," << xLmt << "}" << endl <<
        "{" << endl <<
        "\\draw[thick] (\\coo,-3pt) -- (\\coo,3pt) node[below=4pt,scale=0.7] {\\coo};" << endl <<
        "}" << endl <<

        "\\foreach \\coo in {1,...," << yLmt << "}" << endl <<
        "{" << endl <<
        "\\draw[thick] (0,\\coo) -- (0,\\coo) node[above=5pt,left=1pt,scale=0.7] {\\coo};" << endl <<
        "}" << endl <<

        "\\foreach \\coo in {1,...," << zLmt << "}" << endl <<
        "{" << endl <<
        "\\draw[thick] (0,0,\\coo) -- (0,0,\\coo) node[above=2pt,scale=0.7] {\\coo};" << endl <<
        "}" << endl;

    vector<Coord> coords;

    for (set<vector<Coord> >::iterator it = points.begin(); it != points.end(); ++ it) {
        outputTikzBox3D(*it);
    }

    if (additional) {
        outputTikzAdditional(additional);
    }
}

void GridRepr::outputTikz2D(const std::set<std::pair<std::vector<Coord>, char> > *additional) const
{
    assert(space.limits[0] >= 2 && space.limits[1] >= 2);
    //
    int xLmt = space.limits[0].co,
        yLmt = space.limits[1].co;
    string xRange, yRange;
    stringstream sstm;

    sstm << "0,1,...," << xLmt;
    xRange = sstm.str();
    sstm.str("");

    sstm << "0,1,...," << yLmt;
    yRange = sstm.str();
    sstm.str("");

    *tikzOstream <<
        "\\foreach \\x in {" << xRange << "}" << endl <<
        "{" << endl <<
            "\\draw[grid] (\\x,0,0) -- (\\x," << yLmt << ",0);" << endl <<
        "}" << endl <<
        "\\foreach \\y in {" << yRange << "}" << endl <<
        "{" << endl <<
            "\\draw[grid] (0,\\y,0) -- (" << xLmt << ",\\y,0);" << endl <<
        "}" << endl <<

        "\\draw[axis] (0,0,0) -- (" << xLmt << ",0,0) node[anchor=west]{$dim 1$};" << endl <<
        "\\draw[axis] (0,0,0) -- (0," << yLmt << ",0) node[anchor=west,rotate=90]{$dim 2$};" << endl <<

        "\\foreach \\coo in {1,...," << xLmt << "}" << endl <<
        "{" << endl <<
        "\\draw[thick] (\\coo,-3pt) -- (\\coo,3pt) node[below=4pt,scale=0.7] {\\coo};" << endl <<
        "}" << endl <<

        "\\foreach \\coo in {1,...," << yLmt << "}" << endl <<
        "{" << endl <<
        "\\draw[thick] (0,\\coo) -- (0,\\coo) node[above=5pt,left=1pt,scale=0.7] {\\coo};" << endl <<
        "}" << endl;

    vector<Coord> coords;
    for (set<vector<Coord> >::iterator it = points.begin(); it != points.end(); ++ it) {
        outputTikzBox2D(*it);
    }

    if (additional) {
        outputTikzAdditional(additional);
    }
}

void GridRepr::outputTikz(const std::set<std::pair<std::vector<Coord>, char> > *additional) const
{
    assert(space.dim() == 2 || space.dim() == 3);
    //

    *tikzOstream <<
        "\\documentclass{standalone}" << endl <<
        "\\usepackage{tikz}" << endl <<

        "\\begin{document}" << endl;

    if (space.dim() == 2) {
        *tikzOstream <<
        "\\begin{tikzpicture}" << endl <<
        "        [cube/.style={very thin,black}," << endl <<
        "            grid/.style={very thin,gray}," << endl <<
        "            axis/.style={blue,thick}]" << endl;
    } else {
        *tikzOstream <<
        "\\begin{tikzpicture}" << endl <<
        "        [cube/.style={very thin,black}," << endl <<
        "            grid/.style={very thin,gray}," << endl <<
        "            axis/.style={blue,thick}]" << endl;
    }


    if (space.dim() == 2) {
        outputTikz2D(additional);
    } else {
        outputTikz3D(additional);
    }

    if (doTikzPrintGridPnts && additional == NULL) {
        outputGridPnts();
    }

    *tikzOstream <<
        endl <<
        "\\end{tikzpicture}" << endl <<
        "\\end{document}" << endl;
}

void GridRepr::setTikzPrintGridPnts()
{
    doTikzPrintGridPnts = true;
}

void GridRepr::outputGridPnts() const
{
    Space::Iterator it = space.createIterator(true);

    while(!it.atEnd()) {
        *tikzOstream << "\\node[circle, draw=black";
        if (color(*it)) {
            *tikzOstream << ", fill=black";
        } else {
            *tikzOstream << ", fill=white";
        }
        
        *tikzOstream << ", thick, inner sep=0pt, minimum size=5pt] at (";
        for (size_t i = 0; i < (*it).size(); i ++) {
            *tikzOstream << (*it)[i];
            if (i < (*it).size() - 1) {
                *tikzOstream << ",";
            }
        }
        *tikzOstream << ") {};" << endl;
        ++ it;
    }
}

void GridRepr::addPnt(const std::vector<Coord> & pnt)
{
    assert(pnt.size() == dim());
    assert(space.checkLimits(pnt));
    //
    points.insert(pnt);
}

void GridRepr::addPntCutDim(const std::vector<Coord> & pnt, size_t dim)
{
    assert(dim >= 0 && dim < space.dim() + 1);
    //
    std::vector<Coord> pntNew = pnt;
    pntNew.erase(pntNew.begin() + dim);
    addPnt(pntNew);
}

bool GridRepr::color(const std::vector<Coord> & pnt) const
{
    assert(pnt.size() == dim());
    //
    return points.find(pnt) != points.end();
}

GridRepr GridRepr::intersection(GridRepr & other) const
{
    assert(space == other.space);
    //
    GridRepr insc(other.space);
    set_intersection(this->points.begin(), this->points.end(),
        other.points.begin(), other.points.end(), std::inserter(insc.points,insc.points.begin()));
    return insc;
}

GridRepr GridRepr::unification(GridRepr & other) const
{
    assert(space == other.space);
    //
    GridRepr unif(other.space);
    set_union(this->points.begin(), this->points.end(),
        other.points.begin(), other.points.end(), std::inserter(unif.points,unif.points.begin()));
    return unif;
}

GridRepr GridRepr::difference(GridRepr & other) const
{
    assert(space == other.space);
    //
    GridRepr unif(other.space);
    set_difference(this->points.begin(), this->points.end(),
        other.points.begin(), other.points.end(), std::inserter(unif.points,unif.points.begin()));
    return unif;
}

GridRepr GridRepr::complement() const
{
    GridRepr cmpl(space);
    Space::Iterator it = space.createIterator();
    while (!it.atEnd()) {
        if (points.find(*it) == points.end()) {
            cmpl.addPnt(*it);
        }
        ++ it;
    }
    return cmpl;
}

GridRepr GridRepr::iFacet(size_t dim, Coord fix) const
{
    if (space.dim() == 1) {
        cout << "For 1D space there are no facets defined!" << endl;
        exit(1);
    }
    
    assert(dim >= 0 && dim < space.dim());
    assert(fix >= Coord::ZERO_COORD && fix <= space.limits[dim]);
    //

    Space fctSpace(space);
    fctSpace.cutDimension(dim);

    GridRepr iFct(fctSpace);

    Space::Iterator it = space.createIterator(true);

    while (!it.atEnd()) {
        if ((*it)[dim] == fix) {

            vector<Coord> brother = *it;
            brother[dim] = fix.getGridPrev();

            if (color(*it) != color(brother)) {
                iFct.addPntCutDim(*it, dim);
            }
        }
        ++ it;
    }

    return iFct;
}
