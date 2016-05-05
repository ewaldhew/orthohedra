/* Testuje konstruktor pro vznik trivialniho mnohostenu */

bool testTrivialPolyhedronCreation()
{
    cout << "------------------------- ";
    cout << "testTrivialPolyhedronCreation:" << endl;

    vector<Coord> lowPnt, highPnt;
    vector<Coord> pnt;

    cout << "2D polyhedra" << endl;

    Space space(vector<Coord>(2, 10));

    lowPnt.clear();
    lowPnt.push_back(3);
    lowPnt.push_back(4);

    highPnt.clear();
    highPnt.push_back(5);
    highPnt.push_back(6);

    GridRepr gr(space, lowPnt, highPnt);
    VertexRepr vr(space, lowPnt, highPnt);
    NbhoodRepr nr(space, lowPnt, highPnt);

    assert(gr.points.size() == 4);

    /* cerne body */

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(4);
    assert(gr.color(pnt));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(5);
    assert(gr.color(pnt));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(4);
    assert(gr.color(pnt));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(5);
    assert(gr.color(pnt));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    /* bile body */

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(4);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(3);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(0);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));


    cout << "3D polyhedra" << endl;

    space = Space(vector<Coord>(3, 7));

    lowPnt.clear();
    lowPnt.push_back(2);
    lowPnt.push_back(0);
    lowPnt.push_back(1);

    highPnt.clear();
    highPnt.push_back(4);
    highPnt.push_back(3);
    highPnt.push_back(5);

    gr = GridRepr(space, lowPnt, highPnt);
    vr = VertexRepr(space, lowPnt, highPnt);
    nr = NbhoodRepr(space, lowPnt, highPnt);

    assert(gr.points.size() == 24);

    /* cerne body */

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(0);
    pnt.push_back(1);
    assert(gr.color(pnt));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(1);
    pnt.push_back(1);
    assert(gr.color(pnt));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(0);
    pnt.push_back(2);
    assert(gr.color(pnt));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(1);
    pnt.push_back(2);
    assert(gr.color(pnt));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(2);
    pnt.push_back(4);
    assert(gr.color(pnt));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    /* bile body */

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(2);
    pnt.push_back(4);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(3);
    pnt.push_back(4);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(2);
    pnt.push_back(5);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(2);
    pnt.push_back(6);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(6);
    pnt.push_back(6);
    pnt.push_back(0);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(0);
    pnt.push_back(1);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(0);
    pnt.push_back(0);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(0);
    pnt.push_back(0);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));


    cout << "4D polyhedra" << endl;

    space = Space(vector<Coord>(4, 7));

    lowPnt.clear();
    lowPnt.push_back(4);
    lowPnt.push_back(1);
    lowPnt.push_back(3);
    lowPnt.push_back(2);

    highPnt.clear();
    highPnt.push_back(5);
    highPnt.push_back(5);
    highPnt.push_back(4);
    highPnt.push_back(4);

    gr = GridRepr(space, lowPnt, highPnt);
    vr = VertexRepr(space, lowPnt, highPnt);
    nr = NbhoodRepr(space, lowPnt, highPnt);

    assert(gr.points.size() == 8);

    /* cerne body */

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(1);
    pnt.push_back(3);
    pnt.push_back(2);
    assert(gr.color(pnt));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(1);
    pnt.push_back(3);
    pnt.push_back(3);
    assert(gr.color(pnt));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(3);
    pnt.push_back(3);
    pnt.push_back(3);
    assert(gr.color(pnt));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    /* bile body */

    pnt.clear();
    pnt.push_back(5);
    pnt.push_back(1);
    pnt.push_back(3);
    pnt.push_back(2);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(5);
    pnt.push_back(5);
    pnt.push_back(4);
    pnt.push_back(4);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(0);
    pnt.push_back(3);
    pnt.push_back(2);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(1);
    pnt.push_back(3);
    pnt.push_back(2);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(1);
    pnt.push_back(0);
    pnt.push_back(0);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(0);
    pnt.push_back(0);
    pnt.push_back(0);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(6);
    pnt.push_back(6);
    pnt.push_back(6);
    pnt.push_back(6);
    assert(!gr.color(pnt));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    return true;
}
