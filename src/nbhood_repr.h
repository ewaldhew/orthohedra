#ifndef NBHOOD_REPR_H
#define NBHOOD_REPR_H

#include "vertex_repr.h"

class GridRepr;
class VertexRepr;

struct VertexWithNbhood {
    std::vector<Coord> vertex;
    BoolNDimTable nbhood;
    VertexWithNbhood(const std::vector<Coord> & vertex, const BoolNDimTable & nbhood);
    friend std::ostream & operator<<(std::ostream & os, const VertexWithNbhood & vertWithNbh);
    bool operator<(const VertexWithNbhood & other) const;
    bool operator==(const VertexWithNbhood & other) const;
};

class NbhoodRepr : public Repr {

    std::vector<VertexWithNbhood> vertexesWithNbhood;
    BoolNDimTable zeroPntNbhood; /* nbhood pocatku souradnic - je konstantni */

    VertexWithNbhood calcNbhoodFromVertexRepr(const std::vector<Coord> & pnt, VertexRepr & vr) const;
    BoolNDimTable calcNbhoodFromNbhoodRepr(const std::vector<Coord> & pnt) const;
    std::vector<size_t> iSectionVertexCandidates(size_t dim, const Coord & fix) const;
    bool isISectionVertex(size_t vertexId, size_t dim) const;
    NbhoodRepr iSection(size_t dim, const Coord & fix) const;
    void vertexesWithColorFromVertexesWithNbhood(std::vector<VertexWithNbhood> vWithNbhood, std::set<std::pair<std::vector<Coord>, bool> > & vWithColor) const;
    bool getVertexColor(const struct VertexWithNbhood & vtxWithNbh) const;
    BoolNDimTable calcIntersectionOfNbhoods(const BoolNDimTable & nbh1, const BoolNDimTable & nbh2) const;
    bool colorOfSingleVertex() const;
    size_t vertexCnt() const;
    bool isInVertexList(const std::vector<Coord> & pnt) const; /* funkcnost zavisla na VertexWithNbhood::operator== */
    bool isInVertexList(const std::vector<Coord> & pnt, BoolNDimTable & nbhood) const; /* funkcnost zavisla na VertexWithNbhood::operator== */
    bool isVertex(const BoolNDimTable & nbhood) const; /* zjisteni, zda bod je vertex, na zaklade jeho nbhoodu */
    const BoolNDimTable & getZeroPntNbhood() const;
    void correctNbhoodLimitPntsToWhite(const std::vector<Coord> & pnt, BoolNDimTable & nbh) const;
    bool colorOnFacet(size_t dim, const BoolNDimTable & nbhood, const std::vector<bool> & nbhPnt) const;

public:
    /**
     * Constructs polyhedron in a space and initializes the polyhedron with a set of vertices and their
     * neighbourhood colors.
     * Callee is supposed to guarantee that this set is valid polyhedron description.
     * @param space The space.
     * @param vertexesWithNbhood Set of vertices with their neighbourhood colors.
     */
    NbhoodRepr(const Space &space, const std::vector<VertexWithNbhood> & vertexesWithNbhood);

    /**
     * Constructs empty polyhedron in a space.
     * @param space The space.
     */
    NbhoodRepr(const Space &space);

    /**
     * Constructs trivial polyhedron using its low point and high point. Callee must guarantee
     * that hight point is higher then low point, meaning coordinatewise (otherwise an assert macro
     * will cause program fail).
     * @param space The space.
     * @param lowPnt The low point.
     * @param highPnt The high point.
     */
    NbhoodRepr(const Space &space, const std::vector<Coord> & lowPnt, const std::vector<Coord> & highPnt);

    NbhoodRepr(const GridRepr & gr);
    operator GridRepr(); /* konverze na GridRepr */

    /**
     * Outputs polyhedron as a list of vertices and their neighbourhood colors.
     */
    friend std::ostream & operator<<(std::ostream & os, const NbhoodRepr & nbhoodRepr);

    /**
     * Outputs Tikz source code for Tikz picture of the polyhedron. It only works for 2D and 3D polyhedra.
     */
    void outputTikz(std::set<std::pair<std::vector<Coord>, char> > *additional = NULL);

    /**
     * Computes color of a point.
     * @param pnt The point.
     * @returns True for black color; false for white color.
     */
    bool color(const std::vector<Coord> & pnt) const;

    /**
     * Computes complement of the polyhedron. (The source polyhedra stay untouched.)
     * @returns The complement.
     */
    NbhoodRepr complement() const;

    /**
     * Computes intersection with other polyhedron.
     * @param other The other polyhedron.
     * @returns The intersection.
     */
    NbhoodRepr intersection(NbhoodRepr & other) const;

    /**
     * Computes union with other polyhedron. (The source polyhedra stay untouched.)
     * @param other The other polyhedron.
     * @returns The union.
     */
    NbhoodRepr unification(NbhoodRepr & other) const;

    /** Computes polyhedron as a result of subtracting other polyhedron from *this polyhedron.
     * (The source polyhedra stay untouched.)
     * @returns The difference polyhedron.
     */
    NbhoodRepr difference(NbhoodRepr & other) const;

    /**
     * Computes facet in a chosen coordinate in a chosen dimension.
     * @param dim The dimension.
     * @param fix The coordinate.
     * @returns The facet.
     */
    NbhoodRepr iFacet(size_t dim, Coord fix) const;

    /**
     * Computes a boundary as all the facets of the polyhedron.
     * @returns A vector of the facets.
     */
    std::vector<NbhoodRepr> calcBoundary();

    
    const std::vector<VertexWithNbhood> & getVertexesWithNbhood() const;
    void printVertexesCoords(); /* pro debugging */
    void readCoordsFromFile(const char * filepath); /* pro debugging */
};

#endif
