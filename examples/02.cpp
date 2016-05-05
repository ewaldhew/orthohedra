#include "../src/space.h"
#include "../src/nbhood_repr.h"

using namespace std;

int main()
{
    /* Vytvoreni 2D prostoru o rozmerech 16.454 x 16.454 */

    Space space(vector<Coord>(2, 16.454));

    /* Vytvoreni trivialniho mnohostenu s dolnim levym rohem 'lowPnt' a hornim pravym rohem 'highPnt' */
    
    vector<Coord> lowPnt, highPnt;
    
    lowPnt.push_back(4.45);
    lowPnt.push_back(-6.565);

    highPnt.push_back(15.523);
    highPnt.push_back(11.4786);

    NbhoodRepr nr1(space, lowPnt, highPnt);

    cout << endl << endl << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Polyhedron nr1:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl << endl << endl;

    cout << nr1;

    /* Vytvoreni jineho trivialniho mnohostenu */

    lowPnt.clear();
    lowPnt.push_back(8.6598);
    lowPnt.push_back(-0.4548778);

    highPnt.clear();
    highPnt.push_back(10.546999);
    highPnt.push_back(6.488);

    NbhoodRepr nr2(space, lowPnt, highPnt);

    cout << endl << endl << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Polyhedron nr2:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl << endl << endl;

    cout << nr2;

    /* Sjednoceni nr1, nr2 */

    NbhoodRepr uni = nr1.unification(nr2);
    
    cout << endl << endl << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Union of nr1, nr2:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl << endl << endl;

    cout << uni;

    /* Rozdil (nr1 - nr2) */

    NbhoodRepr diff = nr1.difference(nr2);

    cout << endl << endl << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Difference (nr1 - nr2):" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl << endl << endl;

    cout << diff;

    return 0;
}
