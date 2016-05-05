#include "../src/space.h"
#include "../src/vertex_repr.h"

using namespace std;

int main()
{
    /* Vytvoreni 4D prostoru o rozmerech 20.454 x 20.454 x 20.454 x 20.454 */

    Space space(vector<Coord>(4, 20.454));

    /* Vytvoreni trivialniho mnohostenu s dolnim levym rohem 'lowPnt' a hornim pravym rohem 'highPnt' */
    
    vector<Coord> lowPnt, highPnt;
    
    lowPnt.push_back(4.45);
    lowPnt.push_back(-6.565);
    lowPnt.push_back(-10.65);
    lowPnt.push_back(12.00122);

    highPnt.push_back(15.523);
    highPnt.push_back(11.4786);
    highPnt.push_back(0.445);
    highPnt.push_back(19.688);

    VertexRepr vr1(space, lowPnt, highPnt);

    cout << endl << endl << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Polyhedron vr1:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl << endl << endl;

    cout << vr1;

    /* Vytvoreni jineho trivialniho mnohostenu */

    lowPnt.clear();
    lowPnt.push_back(5.6598);
    lowPnt.push_back(-0.4548778);
    lowPnt.push_back(-121.56);
    lowPnt.push_back(3.4557);

    highPnt.clear();
    highPnt.push_back(10.546999);
    highPnt.push_back(16.488);
    highPnt.push_back(4.11111);
    highPnt.push_back(17.0045);

    VertexRepr vr2(space, lowPnt, highPnt);

    cout << endl << endl << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Polyhedron vr2:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl << endl << endl;

    cout << vr2;

    /* Prunik vr1, vr2 */

    VertexRepr intersct = vr1.intersection(vr2);
    
    cout << endl << endl << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Intersection of vr1, vr2:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl << endl << endl;

    cout << intersct;

    /* Doplnek vr1 */

    VertexRepr cmpl = vr1.complement();

    cout << endl << endl << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Complement of vr1:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl << endl << endl;

    cout << cmpl;

    return 0;
}
