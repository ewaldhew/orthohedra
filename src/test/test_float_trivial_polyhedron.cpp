bool testFloatTrivialPolyhedronCreation_1()
{
    cout << "------------------------- ";
    cout << "testFloatTrivialPolyhedronCreation_1:" << endl;

    vector<Coord> lowPnt, highPnt;
    vector<Coord> pnt;

    cout << "2D polyhedra" << endl;

    Space space(vector<Coord>(2, nthFloat(10)));
    
    lowPnt.clear();
    lowPnt.push_back(nthFloat(3));
    lowPnt.push_back(nthFloat(4));

    highPnt.clear();
    highPnt.push_back(nthFloat(5));
    highPnt.push_back(nthFloat(6));

    VertexRepr vr(space, lowPnt, highPnt);
    NbhoodRepr nr(space, lowPnt, highPnt);

    /* cerne body */

    pnt.clear();
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(4));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(5));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(4));
    pnt.push_back(nthFloat(4));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(4));
    pnt.push_back(nthFloat(5));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    /* bile body */

    pnt.clear();
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(4));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(3));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(0));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    cout << "3D polyhedra" << endl;

    space = Space(vector<Coord>(3, 7));

    lowPnt.clear();
    lowPnt.push_back(nthFloat(2));
    lowPnt.push_back(nthFloat(0));
    lowPnt.push_back(nthFloat(1));

    highPnt.clear();
    highPnt.push_back(nthFloat(4));
    highPnt.push_back(nthFloat(3));
    highPnt.push_back(nthFloat(5));

    vr = VertexRepr(space, lowPnt, highPnt);
    nr = NbhoodRepr(space, lowPnt, highPnt);


    /* cerne body */

    pnt.clear();
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(1));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(1));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(2));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(2));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(4));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    /* bile body */

    pnt.clear();
    pnt.push_back(nthFloat(4));
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(4));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(4));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(5));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(4));
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(6));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(6));
    pnt.push_back(nthFloat(6));
    pnt.push_back(nthFloat(0));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(1));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(0));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(0));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));


    cout << "4D polyhedra" << endl;

    space = Space(vector<Coord>(4, 7));

    lowPnt.clear();
    lowPnt.push_back(nthFloat(4));
    lowPnt.push_back(nthFloat(1));
    lowPnt.push_back(nthFloat(3));
    lowPnt.push_back(nthFloat(2));

    highPnt.clear();
    highPnt.push_back(nthFloat(5));
    highPnt.push_back(nthFloat(5));
    highPnt.push_back(nthFloat(4));
    highPnt.push_back(nthFloat(4));

    vr = VertexRepr(space, lowPnt, highPnt);
    nr = NbhoodRepr(space, lowPnt, highPnt);


    /* cerne body */

    pnt.clear();
    pnt.push_back(nthFloat(4));
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(2));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(4));
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(3));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(4));
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(3));
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    /* bile body */

    pnt.clear();
    pnt.push_back(nthFloat(5));
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(2));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(5));
    pnt.push_back(nthFloat(5));
    pnt.push_back(nthFloat(4));
    pnt.push_back(nthFloat(4));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(4));
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(2));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(2));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(0));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(0));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(nthFloat(6));
    pnt.push_back(nthFloat(6));
    pnt.push_back(nthFloat(6));
    pnt.push_back(nthFloat(6));
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));
    return true;
}

bool testFloatTrivialPolyhedronCreation_2()
{
    cout << "------------------------- ";
    cout << "testFloatTrivialPolyhedronCreation_2:" << endl;

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

    VertexRepr vr(space, lowPnt, highPnt);
    NbhoodRepr nr(space, lowPnt, highPnt);

    /* cerne body */

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(4);
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(5);
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(4);
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(5);
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    /* bile body */

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(4);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(3);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(0);
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

    vr = VertexRepr(space, lowPnt, highPnt);
    nr = NbhoodRepr(space, lowPnt, highPnt);


    /* cerne body */

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(0);
    pnt.push_back(1);
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(1);
    pnt.push_back(1);
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(0);
    pnt.push_back(2);
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(1);
    pnt.push_back(2);
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(2);
    pnt.push_back(4);
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    /* bile body */

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(2);
    pnt.push_back(4);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(3);
    pnt.push_back(4);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(2);
    pnt.push_back(5);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(2);
    pnt.push_back(6);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(6);
    pnt.push_back(6);
    pnt.push_back(0);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(0);
    pnt.push_back(1);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(0);
    pnt.push_back(0);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(0);
    pnt.push_back(0);
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

    vr = VertexRepr(space, lowPnt, highPnt);
    nr = NbhoodRepr(space, lowPnt, highPnt);


    /* cerne body */

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(1);
    pnt.push_back(3);
    pnt.push_back(2);
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(1);
    pnt.push_back(3);
    pnt.push_back(3);
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(3);
    pnt.push_back(3);
    pnt.push_back(3);
    assert(vr.color(pnt));
    assert(nr.color(pnt));

    /* bile body */

    pnt.clear();
    pnt.push_back(5);
    pnt.push_back(1);
    pnt.push_back(3);
    pnt.push_back(2);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(5);
    pnt.push_back(5);
    pnt.push_back(4);
    pnt.push_back(4);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(0);
    pnt.push_back(3);
    pnt.push_back(2);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(1);
    pnt.push_back(3);
    pnt.push_back(2);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(1);
    pnt.push_back(0);
    pnt.push_back(0);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(0);
    pnt.push_back(0);
    pnt.push_back(0);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    pnt.clear();
    pnt.push_back(6);
    pnt.push_back(6);
    pnt.push_back(6);
    pnt.push_back(6);
    assert(!vr.color(pnt));
    assert(!nr.color(pnt));

    return true;
}

bool testFloatTrivialPolyhedronCreation()
{
    if (!testFloatTrivialPolyhedronCreation_1()) {
        return false;
    }
    if (!testFloatTrivialPolyhedronCreation_2()) {
        return false;
    }
    return true;
}
