#include <ctime>
#include <map>

#include "utils.h"
#include "../src/space.h"
#include "../src/nbhood_repr.h"

#define MAX_NR_OF_TRIVIALS 10
#define REPEATINGS_FOR_MAKING_AVERAGE 100

using namespace std;

int main()
{   
    srand(time(NULL));

    size_t dim = 3;
    float maxcoord = 100;

    map<int, vector<double> > measuredTimes;

    cerr << "generate " << MAX_NR_OF_TRIVIALS << "x polyhedra of dimension " << dim << ":" << endl;

    for (int i = 0; i < MAX_NR_OF_TRIVIALS; i ++) {
        cerr << "generating polyhedra as union of " << i + 1 << " trivials" << endl;
        Space space(vector<Coord>(dim, maxcoord));
        NbhoodRepr nr(space);
        for (int j = 0; j < i + 1; j ++) {
            NbhoodRepr triv = randomTrivialNbhoodRepr(Coord::ZERO_COORD, maxcoord, space);
            nr = nr.unification(triv);
        }
        int vertexCnt = nr.getVertexesWithNbhood().size();

        measuredTimes[vertexCnt] = vector<double>();

        clock_t begin = clock();
        /////////////////////
        nr.complement();
        /////////////////////
        clock_t end = clock();
        double elapsedSecs = double(end - begin) / CLOCKS_PER_SEC;
    
        measuredTimes[vertexCnt].push_back(elapsedSecs);
    }

    map<int, double> measuredTimesAveraged;

    for (map<int, vector<double> >::iterator it = measuredTimes.begin(); it != measuredTimes.end(); ++ it) {
        double acc = 0;
        for (int i = 0; i < it->second.size(); i ++) {
            acc += it->second[i];
        }
        measuredTimesAveraged[it->first] = acc / it->second.size();
    }

    cerr << "---------------" << endl;

    for (map<int, double>::iterator it = measuredTimesAveraged.begin(); it != measuredTimesAveraged.end(); ++ it) {
        cout << setfill(' ') << setw(4) << std::fixed << it->first << "  " << it->second << endl;
    }

    return 0;
}
