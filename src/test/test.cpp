#include "test.h"

using namespace std;

Space createSpaceFromSpacefile(const string & spacefile, bool considerAsNthFloat = false)
{
    std::ifstream spaceIfs;
    spaceIfs.open(spacefile.c_str());
    if (!spaceIfs.is_open()) {
        cout << "Can't open spacefile " << spacefile << endl;
        exit(1);
    }
    string line;
    if (!getline(spaceIfs, line)) {
        cout << "Bad spacefile content" << endl;
        exit(1);
    }
    istringstream iss(line);
    int lim;
    vector<Coord>limits;
    while (iss >> lim) {
        if (considerAsNthFloat) {
            limits.push_back(nthFloat(lim));
        } else {
            limits.push_back(lim);
        }
    }

    return Space(limits);
}

#include "test_trivial_polyhedron.cpp"
#include "test_grid_repr.cpp"
#include "test_vertex_repr.cpp"
#include "test_ndimtable.cpp"
#include "test_nbhood_repr.cpp"

#include "test_float_trivial_polyhedron.cpp"
#include "test_float_vertex_repr.cpp"
#include "test_float_nbhood_repr.cpp"

void testPokusy()
{
#if 0
    string file = "01";
    string datafile, spacefile;
    datafile = "pom/" + file + ".txt";
    spacefile = "pom/" + file + "_space.txt";
#else
    string file = "07";
    string datafile, spacefile;
    datafile = "src/test/data/uint/grid_repr/" + file + ".txt";
    spacefile = "src/test/data/uint/grid_repr/" + file + "_space.txt";

    /*string file = "01";
    string datafile, spacefile;
    datafile = "src/test/data/uint/vertex_repr/" + file + ".txt";
    spacefile = "src/test/data/uint/vertex_repr/" + file + "_space.txt";*/
#endif
    GridRepr gr(createSpaceFromSpacefile(spacefile), datafile.c_str());
    VertexRepr vr = gr;
    // VertexRepr vr(createSpaceFromSpacefile(spacefile), datafile.c_str());
    // GridRepr gr = vr;
    
/*    gr.setTikzOstreamToCerr();
    gr.outputTikz();
*/    

    // vr = vr.complement();

    /*vr.setTikzOstreamToCerr();
    vr.outputTikz();*/
    
/*    GridRepr emptyGr(createSpaceFromSpacefile(spacefile));
    emptyGr.setTikzOstreamToCerr();
    emptyGr.outputTikz();*/


    vector<Coord> pnt;
    pnt.push_back(6);
    pnt.push_back(3);

}

bool test()
{   
    
#if 1
    /* testy spolecne pro integer a float verzi */

    if (!testTriboolNDimTable()) {
        return false;
    }

#if INTEGER_VERSION
    /* testy integer verze */

    if (!testTrivialPolyhedronCreation()) {
        return false;
    }
    if (!testTriboolNDimTable()) {
        return false;
    }
    if (!testGridRepr()) {
        return false;
    }
    if (!testVertexRepr()) {
        return false;
    }
    if (!testNbhoodRepr()) {
        return false;
    }

#else
    /* testy float verze */

    if (!testFloatTrivialPolyhedronCreation()) {
        return false;
    }
    if (!testFloatVertexRepr()) {
        return false;
    }
    if (!testFloatNbhoodRepr()) {
        return false;
    }

#endif
    cout << "-------------------------" << endl;
    cout << "All tests passed" << endl;

#else
    testPokusy();
#endif
    
    return true;
}

