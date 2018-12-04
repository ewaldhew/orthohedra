#ifndef SPACE_H
#define SPACE_H

#include <assert.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>

#define INTEGER_VERSION 1

#define PRINT_POINT(PNT) { \
            for (size_t _iii_ = 0; _iii_ < (PNT).size(); _iii_ ++) { \
                cout << setfill(' ') << setw(2) << setprecision(10) << (PNT)[_iii_] << " "; \
            } \
            cout << endl; \
        }

#define PRINT_POINTS_SELFTEST(PNT_SET) { \
            cout << "    assert(" << #PNT_SET << ".size() == " << (PNT_SET).size() << ");" << endl << endl; \
            for (set<vector<Coord> >::iterator _it_ = (PNT_SET).begin(); _it_ != (PNT_SET).end(); ++ _it_) { \
                cout << "    pnt.clear();" << endl; \
                for (size_t _iii_ = 0; _iii_ < (pnt).size(); _iii_ ++) { \
                    cout << "    pnt.push_back(" << (*_it_)[_iii_] << ");" << endl; \
                } \
                cout << "    assert(" << #PNT_SET << ".find(pnt) != " << #PNT_SET << ".end());" << endl << endl; \
            } \
        }
#define PRINT_VERTEXES_WITH_COLOR_SELFTEST(VERTWITHCOLOR_SET) { \
            cout << "    assert(" << #VERTWITHCOLOR_SET << ".size() == " << (VERTWITHCOLOR_SET).size() << ");" << endl << endl; \
            for (set<std::pair<std::vector<Coord>, bool> >::iterator _it_ = (VERTWITHCOLOR_SET).begin(); _it_ != (VERTWITHCOLOR_SET).end(); ++ _it_) { \
                cout << "    pnt.clear();" << endl; \
                for (size_t _iii_ = 0; _iii_ < (pnt).size(); _iii_ ++) { \
                    cout << "    pnt.push_back(" << (_it_->first)[_iii_] << ");" << endl; \
                } \
                cout << "    vertWithColor = std::pair<std::vector<Coord>, bool>(pnt, " << (_it_->second ? "true" : "false") << ");" << endl; \
                cout << "    assert(" << #VERTWITHCOLOR_SET << ".find(vertWithColor) != " << #VERTWITHCOLOR_SET << ".end());" << endl << endl; \
            } \
        }
#define PRINT_ARRAY(ARRAY) { \
            for (size_t _iii_ = 0; _iii_ < (ARRAY).size(); _iii_ ++ ) { \
                cout << (ARRAY)[_iii_] << endl; \
            } \
        }
#define PRINT_CHAR_ARRAY(ARRAY) { \
            for (size_t _iii_ = 0; _iii_ < (ARRAY).size(); _iii_ ++ ) { \
                cout << (int)(ARRAY)[_iii_] << endl; \
            } \
        }
#define ASSERT_WITH_CRASH(CONDITION) { \
            if (!(CONDITION)) { \
                std::cout << "Zavolano makro ASSERT_WITH_CRASH" << std::endl; \
                std::vector<bool> __dummyCrashVector__; \
                __dummyCrashVector__[0] = 777; \
            } \
        }

struct Coord;

std::vector<size_t> boolVectorToSizetVector(const std::vector<bool> & pnt);
bool pntsEqualDontCareLastCoord(const std::vector<Coord> & pnt1, const std::vector<Coord> & pnt2);
std::vector<Coord> coordWiseMax(const std::vector<Coord> & pnt1, const std::vector<Coord> & pnt2);

/* vraci true prave kdyz leftPnt <= rightPnt, kde se porovnava tak, ze kazda souradnice je <= */
bool lowerOrEqual(const std::vector<Coord> & leftPnt, const std::vector<Coord> &rightPnt);

/* vraci true prave kdyz leftPnt < rightPnt, kde se porovnava tak, ze kazda souradnice je < */
bool lower(const std::vector<Coord> & leftPnt, const std::vector<Coord> &rightPnt);

float nthFloat(size_t n);

class BoolvectorIterator {
    std::vector<bool> vctr;
    bool isEnd;
public:
    BoolvectorIterator(size_t size);
    BoolvectorIterator & operator++();
    bool atEnd() const;
    const std::vector<bool> & operator*() const;
};

#if INTEGER_VERSION
struct Coord {
    static const int ZERO_COORD;
    static const int UNDER_ZERO_COORD;
    int co;

    Coord() : Coord(0) {}
    Coord(int co) : co(co) {}
    Coord & operator=(const Coord & other)
    {
        this->co = other.co;
        return *this;
    }
    Coord & operator=(int n)
    {
        this->co = n;
        return *this;
    }
    bool operator==(const Coord & other) const
    {
        return co == other.co;
    }
    bool operator!=(const Coord & other) const
    {
        return co != other.co;
    }
    bool operator>(const Coord & other) const
    {
        return co > other.co;
    }
    bool operator<(const Coord & other) const
    {
        return co < other.co;
    }
    bool operator>=(const Coord & other) const
    {
        return co >= other.co;
    }
    bool operator<=(const Coord & other) const
    {
        return co <= other.co;
    }
    friend std::ostream & operator<<(std::ostream & os, const Coord & coord)
    {
        os << coord.co;
        return os;
    }
    Coord getGridPrev() const
    {
        assert(co != UNDER_ZERO_COORD);
        //
        return Coord(co - 1);
    }
    Coord getGridNext() const
    {
        return Coord(co + 1);
    }
    explicit operator int() const
    {
        return co;
    }
};
#else

/**
 * Represents a coordinate. Objects of this class are linearly ordered.
 */
struct Coord {
    static const float ZERO_COORD;
    static const float UNDER_ZERO_COORD;
    float co;
    
    Coord() : Coord(0) {}
    Coord(float co) : co(co) {}
    Coord & operator=(const Coord & other)
    {
        this->co = other.co;
        return *this;
    }
    Coord & operator=(float n)
    {
        this->co = n;
        return *this;
    }

    bool operator==(const Coord & other) const
    {
        return co == other.co;
    }
    bool operator!=(const Coord & other) const
    {
        return co != other.co;
    }
    bool operator>(const Coord & other) const
    {
        return co > other.co;
    }
    bool operator<(const Coord & other) const
    {
        return co < other.co;
    }
    bool operator>=(const Coord & other) const
    {
        return co >= other.co;
    }
    bool operator<=(const Coord & other) const
    {
        return co <= other.co;
    }
    friend std::ostream & operator<<(std::ostream & os, const Coord & coord)
    {
        os << coord.co;
        return os;
    }

    /**
     * Returns Coord on space grid closest to *this Coord and lower or equal to *this.
     * Actually by this method and the getGridNext() method the space grid is well defined.
     * @return The closest grid coord.
     */
    Coord getGridPrev() const
    {
        assert(co != UNDER_ZERO_COORD);
        //
        return Coord(nextafterf(co, - std::numeric_limits<float>::max()));
    }

    /**
     * Returns Coord on space grid closest to *this Coord and higher or equal to *this.
     * Actually by this method and the getGridPrev() method the space grid is well defined.
     * @return The closest grid coord.
     */
    Coord getGridNext() const
    {
        return Coord(nextafterf(co, std::numeric_limits<float>::max()));
    }
};
#endif

/**
 *  Encapsulates information about space the polyhedra are living in.
 *  For each dimension, it stores the limit coordinate in that dimension
 *  (so that the space extent is defined).
 */
class Space {
public:
    class Iterator {
        const Space *space;
        std::vector<Coord> pnt;
        bool isEnd;
        bool includeLimits;
    public:
        Iterator(const Space *space, bool includeLimits);
        Iterator & operator++();
        const std::vector<Coord> & operator*() const;
        bool atEnd() const;
    };

    class NbhoodIterator {
        const Space *space;
        const std::vector<Coord> *basePnt;
        BoolvectorIterator corner;
    public:
        NbhoodIterator(const Space *space, const std::vector<Coord> *basePnt);
        NbhoodIterator & operator++();
        bool atEnd() const;
        std::vector<Coord> operator*() const;
    };

    class HalfNbhoodIterator {
        const Space *space;
        const std::vector<Coord> *basePnt;
        BoolvectorIterator corner;
        size_t dim;
        bool leftPart;
    public:
        HalfNbhoodIterator(const Space *space, const std::vector<Coord> *basePnt, size_t dim, bool leftPart);
        HalfNbhoodIterator & operator++();
        bool atEnd() const;
        std::vector<Coord> operator*() const;
    };

    class SpaceBoundaryIterator {
    
    /* Iteruje body, ktere ohranicuji Space */

        const Space *space;
        bool isEnd;
        Space *facet; /* aktualne zpracovanany facet */
        size_t facetDim; /* dimenze z puvodniho Space, ve ktere facet lezi
                        (napr. pro 3D space znamena "facetDim == 2", ze je to facet v rovine 'z') */
        bool isFacetLeft; /* napr. pro facet v rovine 'x' to znamena, zda je to ten facet nalevo, ci napravo */
        Space::Iterator facetIt; /* iterator aktualniho facetu */

        Space *createFacet(size_t dim); /* vytvori space pro hranicni facet; tento space se bude iterovat */

    public:
        SpaceBoundaryIterator(const Space *space);
        SpaceBoundaryIterator & operator++();
        bool atEnd() const;
        std::vector<Coord> operator*() const;
    };

    class SpaceCornerIterator {

    /* Iteruje rohy ohranicujici Space */

        const Space *space;
        BoolvectorIterator corner;

    public:
        SpaceCornerIterator(const Space *space);
        SpaceCornerIterator & operator++();
        bool atEnd() const;
        std::vector<Coord> operator*() const;
    };

private:
    static const int DEFAULT_LIMIT;
    std::vector<Coord> zeroPnt;

public:
    std::vector<Coord> limits;

    Space() = default;
    /**
     * Constructs Space using the count of dimensions.
     * @param dim Count of dimensions. In each dimension the default limit coordinate is to be set to Space::DEFAULT_LIMIT.
     */
    Space(size_t dim);

    /**
     * Constructs Space using vector which holds limit coordinate for each dimension.
     * @param limits Vector of limit coordinates for each dimension.
     */
    Space(const std::vector<Coord> & limits);

    friend std::ostream & operator<<(std::ostream & os, const Space & space);

    /**
     * Considers two spaces equal iff they have the same vector of limit coordinates.
     * @param other The other Space to compare with.
     */
    bool operator==(const Space & other) const;

    /**
     * Returns a count of space dimensions.
     * @return The count of dimensions.
     */
    size_t dim() const;

    bool checkLimits(const std::vector<Coord> &pnt, bool allowUnderFirstCoord = false) const;
    bool checkLimitsAllowLimits(const std::vector<Coord> &pnt, bool allowUnderFirstCoord = false) const;
    void cutDimension(size_t i);
    bool hasAtLeastOneZeroCoord(const std::vector<Coord> &pnt) const;
    bool hasAtLeastOneUnderZeroCoord(const std::vector<Coord> &pnt) const;
    bool hasAllZeroCoords(const std::vector<Coord> &pnt) const;
    bool isOnFrontBoundary(const std::vector<Coord> &pnt) const;
    bool isCorner(const std::vector<Coord> &pnt) const;
    const std::vector<Coord> & getZeroPnt() const;
    

    /* iterator vsech bodu prostoru */
    Iterator createIterator(bool includeLimits = false) const;

    /* neighbourhood iterator */
    NbhoodIterator createNbhoodIterator(const std::vector<Coord> *basePnt) const;

    /* half-neighbourhood iterator */
    HalfNbhoodIterator createHalfNbhoodIterator(const std::vector<Coord> *basePnt, size_t dim, bool leftPart) const;

    /* space boundary iterator */
    SpaceBoundaryIterator createSpaceBoundaryIterator() const;

    /* iterator rohu prostoru */
    SpaceCornerIterator createSpaceCornerIterator() const;

    std::vector<Coord> iPredecessor(const std::vector<Coord> & pnt, size_t dim) const;
    std::vector<Coord> iSuccessor(const std::vector<Coord> & pnt, size_t dim) const;
};


    

#endif
