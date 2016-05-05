#ifndef VERTEX_REPR_H
#define VERTEX_REPR_H

#include <stdlib.h>
#include <iomanip>

#include "repr.h"
#include "grid_repr.h"

class GridRepr;
class VertexRepr;

/*static const char *TriboolNDimTableValuesNames[] = {
    "NOT_COMPUTED",
    "BLACK",
    "WHITE"
};*/

class NDimTable {
protected:
    size_t tableSize;
    std::vector<size_t> idxsLimits; /* tyto limits maji typ size_t, narozdil od Space a Repr,
                                      ktere pouzivaji Coord. Neni totiz mozne, abych indexoval
                                      std::vector nejakym typem jako je Coord */
    std::vector<size_t> jumpSizes;
    size_t calcTabIdx(const std::vector<size_t> & idxs) const;
    bool checkLimits(const std::vector<size_t> & idxs) const;

public:
    NDimTable(const std::vector<size_t> & idxsLimits);
    NDimTable(){}
};

class TriboolNDimTable : NDimTable {
public:
    enum Value {
        NOT_COMPUTED,
        BLACK,
        WHITE
    };

private:
    std::vector<bool> tabIsComputed;
    std::vector<bool> tabIsBlack;
    void setValue(const std::vector<size_t> & idxs, enum Value val);

public:
    TriboolNDimTable(const std::vector<size_t> & idxsLimits);
    enum Value getValue(const std::vector<size_t> & idxs) const;
    void setBlack(const std::vector<size_t> & idxs);
    void setWhite(const std::vector<size_t> & idxs);
};

class BoolNDimTable : NDimTable {
public:
    std::vector<bool> table;
public:
    BoolNDimTable(const std::vector<size_t> & idxsLimits);
    BoolNDimTable(){}
    friend std::ostream & operator<<(std::ostream & os, const BoolNDimTable & bdimTab);
    bool operator<(const BoolNDimTable & other) const;
    bool getValue(const std::vector<size_t> & idxs) const;
    void setTrue(const std::vector<size_t> & idxs);
    void setFalse(const std::vector<size_t> & idxs);
    void setValue(const std::vector<size_t> & idxs, bool val);
    void invert();
};

class InducedGrid {
    std::vector<std::vector<Coord> > coords;
public:
    std::vector<size_t> sizes; /* rozmery indukovane mrizky (v poctech bodu)*/

    void update(const VertexRepr & vr);
    friend std::ostream & operator<<(std::ostream & os, const InducedGrid & indGr);
    bool findStartingIdxs(const std::vector<Coord> & pnt, std::vector<size_t> & idxs) const;
    std::vector<Coord> toPnt(const std::vector<size_t> & inducedIdxs) const;
};

/**
 *  Vertex representation of polyhedron.
 */
class VertexRepr : public Repr {

private:
    std::set<std::pair<std::vector<Coord>, bool> > vertexesWithColor;
    TriboolNDimTable *colorMemoizer;
    bool doDeallocMemoizer;
    InducedGrid inducedGrid;
    bool isInducedGridUpdated;

    bool isVertex(const std::vector<Coord> & pnt, bool *color);
    bool colorRec(std::vector<size_t> inducedIdxs);

    /* Spocita barvu bodu na facetu, kdy tento facet se povazuje za samostatny mnohosten.
    Barva se pocita na zaklade definice facetu - pomoci barev v puvodnim mnohostenu, ve kterem facet "zije". */
    /* parametr 'dim': dimenze v puvodnim mnohostenu, ve ktere facet "zije".
       parametr 'pnt': bod, pro ktery chceme zjistit barvu */ 
    bool colorOnFacet(size_t dim, const std::vector<Coord> & pnt);

public:
    /**
     * Constructs polyhedron in a space and initializes the polyhedron with a set of vertices and their colors.
     * Callee is supposed to guarantee that this set is valid polyhedron description.
     * @param space The space.
     * @param vertexesWithColor Set of vertices with their colors.
     */
    VertexRepr(const Space &space, const std::set<std::pair<std::vector<Coord>,bool> > & vertexesWithColor);

    /**
     * Constructs empty polyhedron in a space
     * @param space The space.
     */
    VertexRepr(const Space &space);

    /**
     * Constructs trivial polyhedron using its low point and high point. Callee must guarantee
     * that hight point is higher then low point, meaning coordinatewise (otherwise an assert macro
     * will cause program fail).
     * @param space The space.
     * @param lowPnt The low point.
     * @param highPnt The high point.
     */
    VertexRepr(const Space &space, const std::vector<Coord> & lowPnt, const std::vector<Coord> & highPnt);

    VertexRepr(const VertexRepr & other);
    VertexRepr(const Space &space, const char *filepath);
    VertexRepr(const GridRepr & gr);
    VertexRepr & operator=(const VertexRepr & other);
    ~VertexRepr();
    operator GridRepr(); /* konverze na GridRepr */

    /**
     * Outputs polyhedron as a list of vertices with their colors.
     * Every vertex is output as array of its coordinates.
     * After vertex output there is a newline and on the new line there is ":" symbol
     * followed by either "W" for white or "BLACK" for black.
     */
    friend std::ostream & operator<<(std::ostream & os, const VertexRepr & vr);

    /**
     * Outputs Tikz source code for Tikz picture of the polyhedron. It only works for 2D and 3D polyhedra.
     */
    void outputTikz(std::set<std::pair<std::vector<Coord>, char> > *additional = NULL);

    /**
     * Computes color of a point.
     * @param pnt The point.
     * @returns True for black color; false for white color.
     */
    bool color(const std::vector<Coord> & pnt);

    /**
     * Computes complement of the polyhedron. (The source polyhedra stay untouched.)
     * @returns The complement.
     */
    VertexRepr complement() const;

    /**
     * Computes facet in a chosen coordinate in a chosen dimension.
     * @param dim The dimension.
     * @param fix The coordinate.
     * @returns The facet.
     */
    VertexRepr iFacet(size_t dim, Coord fix);

    /**
     * Computes intersection with other polyhedron.
     * @param other The other polyhedron.
     * @returns The intersection.
     */
    VertexRepr intersection(VertexRepr & other);

    /**
     * Computes union with other polyhedron. (The source polyhedra stay untouched.)
     * @param other The other polyhedron.
     * @returns The union.
     */
    VertexRepr unification(VertexRepr & other);

    /**
     * Computes polyhedron as a result of subtracting other polyhedron from *this polyhedron.
     * (The source polyhedra stay untouched.)
     * @returns The difference polyhedron.
     */
    VertexRepr difference(VertexRepr & other);

    /**
     * Forces the representation to keep the induced grid (which stores some already computed colors)
     * for the whole lifetime of the polyhedron object.
     * (And not only during color() computation.)
     * Default behaviour is to deallocate it immediately. See setDoDeallocMemoizer().
     */
    void unsetDoDeallocMemoizer();

    /**
     * Forces the representation to deallocate induced grid (which stores some already computed colors)
     * immediately after escaping color() computation. This will save memory
     * during the whole polyhedron lifetime but on the other side it will repeatedly
     * lose the already computed colors.
     * Default behaviour is to deallocate it immediately. See unsetDoDeallocMemoizer().
     */
    void setDoDeallocMemoizer();

    /**
     * Computes a boundary as all the facets of the polyhedron.
     * @returns A vector of the facets.
     */
    std::vector<VertexRepr> calcBoundary();

    const std::set<std::pair<std::vector<Coord>, bool> > & getVertexesWithColor() const;
    friend bool testCreationFromGridRepr();
    friend bool testVertexReprMembership();
    friend void testPokusy();
};

#endif
