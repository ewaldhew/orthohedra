bool testGridReprBasicOperations()
{
    cout << "------------------------- ";
    cout << "testGridReprBasicOperations:" << endl;

    Space space(3);

    /* Vytvoreni mnohostenu */

    GridRepr gr(space);
    vector<Coord> pnt;

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(12);
    pnt.push_back(7);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(10);
    pnt.push_back(1);
    pnt.push_back(2);
    gr.addPnt(pnt);

    /* zamerne vlozeni jiz existujiciho bodu */
    pnt.clear();
    pnt.push_back(10);
    pnt.push_back(1);
    pnt.push_back(2);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(6);
    pnt.push_back(4);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(5);
    pnt.push_back(0);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(12);
    pnt.push_back(3);
    gr.addPnt(pnt);

    /* zamerne vlozeni jiz existujiciho bodu */
    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(5);
    pnt.push_back(0);
    gr.addPnt(pnt);

    assert(gr.points.size() == 5);

    /* Testovani membershipu pro obsazene body */

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(12);
    pnt.push_back(3);
    assert(gr.color(pnt));

    pnt.clear();
    pnt.push_back(10);
    pnt.push_back(1);
    pnt.push_back(2);
    assert(gr.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(6);
    pnt.push_back(4);
    assert(gr.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(12);
    pnt.push_back(3);
    assert(gr.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(5);
    pnt.push_back(0);
    assert(gr.color(pnt));

    /* Testovani membershipu pro neobsazene body */

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(13);
    pnt.push_back(3);
    assert(!gr.color(pnt));

    pnt.clear();
    pnt.push_back(400);
    pnt.push_back(300);
    pnt.push_back(200);
    assert(!gr.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(0);
    pnt.push_back(0);
    assert(!gr.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(0);
    pnt.push_back(0);
    assert(!gr.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(5);
    pnt.push_back(1);
    assert(!gr.color(pnt));

    /* Vytvoreni druheho mnohostenu */

    GridRepr gr2(space);

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(6);
    pnt.push_back(4);
    gr2.addPnt(pnt);

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(0);
    pnt.push_back(0);
    gr2.addPnt(pnt);

    assert(gr2.points.size() == 2);

    /* Prunik mnohostenu */

    GridRepr grInsc(gr.intersection(gr2));

    /* Testovani, zda prunik obsahuje spravne body */

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(6);
    pnt.push_back(4);
    assert(grInsc.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(12);
    pnt.push_back(7);
    assert(!grInsc.color(pnt));

    pnt.clear();
    pnt.push_back(10);
    pnt.push_back(1);
    pnt.push_back(2);
    assert(!grInsc.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(0);
    pnt.push_back(0);
    assert(!grInsc.color(pnt));

    assert(grInsc.points.size() == 1);

    /* Sjednoceni mnohostenu */

    GridRepr grUnif(gr.unification(gr2));

    /* Testovani, zda sjednoceni obsahuje spravne body */

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(12);
    pnt.push_back(7);
    assert(grUnif.color(pnt));

    pnt.clear();
    pnt.push_back(10);
    pnt.push_back(1);
    pnt.push_back(2);
    assert(grUnif.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(6);
    pnt.push_back(4);
    assert(grUnif.color(pnt));

    pnt.clear();
    pnt.push_back(4);
    pnt.push_back(12);
    pnt.push_back(3);
    assert(grUnif.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(5);
    pnt.push_back(0);
    assert(grUnif.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(6);
    pnt.push_back(4);
    assert(grUnif.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(0);
    pnt.push_back(0);
    assert(grUnif.color(pnt));

    pnt.clear();
    pnt.push_back(123);
    pnt.push_back(123);
    pnt.push_back(123);
    assert(!grUnif.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(1);
    pnt.push_back(2);
    assert(!grUnif.color(pnt));

    assert(grUnif.points.size() == 6);

    /* Rozdil mnohostenu */

    GridRepr gr3(space);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(1);
    pnt.push_back(2);
    gr3.addPnt(pnt);

    pnt.clear();
    pnt.push_back(45);
    pnt.push_back(6);
    pnt.push_back(7);
    gr3.addPnt(pnt);

    pnt.clear();
    pnt.push_back(9);
    pnt.push_back(0);
    pnt.push_back(14);
    gr3.addPnt(pnt);

    GridRepr gr4(space);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(1);
    pnt.push_back(2);
    gr4.addPnt(pnt);

    pnt.clear();
    pnt.push_back(45);
    pnt.push_back(6);
    pnt.push_back(7);
    gr4.addPnt(pnt);

    pnt.clear();
    pnt.push_back(56);
    pnt.push_back(63);
    pnt.push_back(24);
    gr4.addPnt(pnt);

    pnt.clear();
    pnt.push_back(99);
    pnt.push_back(69);
    pnt.push_back(3);
    gr4.addPnt(pnt);

    GridRepr grDiff(gr3.difference(gr4));

    /* Testovani, zda rozdil obsahuje spravne body */

    assert(grDiff.points.size() == 1);

    pnt.clear();
    pnt.push_back(9);
    pnt.push_back(0);
    pnt.push_back(14);
    assert(grDiff.color(pnt));

    /* Vytvoreni prostoru o rozmerech 2x5 a v nem vytvoreni mnohostenu */

    vector<Coord>limits;
    limits.push_back(2);
    limits.push_back(5);
    Space space2(limits);

    GridRepr gr5(space2);

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(1);
    gr5.addPnt(pnt);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(2);
    gr5.addPnt(pnt);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(3);
    gr5.addPnt(pnt);

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(3);
    gr5.addPnt(pnt);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(4);
    gr5.addPnt(pnt);

    /* Doplnek mnohostenu do jeho prostoru */

    GridRepr grCmpl = gr5.complement();

    /* Testovani, zda doplnek obsahuje spravne body */

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(1);
    assert(!grCmpl.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(2);
    assert(!grCmpl.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(3);
    assert(!grCmpl.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(3);
    assert(!grCmpl.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(4);
    assert(!grCmpl.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(0);
    assert(grCmpl.color(pnt));

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(1);
    assert(grCmpl.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(0);
    assert(grCmpl.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(2);
    assert(grCmpl.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(4);
    assert(grCmpl.color(pnt));

    assert(grCmpl.points.size() == 5);

    /* Dalsi testovani doplnku */

    limits.clear();
    limits.push_back(1);
    limits.push_back(1);
    Space space3(limits); 
    GridRepr gr6(space3);

    GridRepr grCmpl2 = gr6.complement();

    assert(grCmpl2.points.size() == 1);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(0);

    assert(grCmpl2.color(pnt));

    return true;
}

bool testGridReprFacet()
{
    cout << "------------------------- ";
    cout << "testGridReprFacet:" << endl;

    /* Vytvoreni 3D mnohostenu */

    vector<Coord>limits;
    limits.push_back(5);
    limits.push_back(4);
    limits.push_back(4);
    Space space(limits);

    GridRepr gr(space);
    vector<Coord> pnt;

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(2);
    pnt.push_back(1);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(2);
    pnt.push_back(1);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(2);
    pnt.push_back(2);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(2);
    pnt.push_back(2);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(3);
    pnt.push_back(2);
    gr.addPnt(pnt);

    /* Vytvareni 2D facetů z puvodniho mnohostenu */

    int dim3d;
    int fix3d;

    dim3d = 0;
    fix3d = 0;
    GridRepr fct2d = gr.iFacet(dim3d, fix3d);
    
    assert(fct2d.points.size() == 1);

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(1);
    assert(fct2d.color(pnt));

    fix3d = 1;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 1);

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    fix3d = 2;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 2);

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(1);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    fix3d = 3;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 2);

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    fix3d = 4;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 0);

    fix3d = 5;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 0);

    dim3d = 1;
    fix3d = 0;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 0);

    fix3d = 1;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 0);

    fix3d = 2;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 4);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(1);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(1);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    fix3d = 3;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 3);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(1);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(1);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    fix3d = 4;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 1);

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    dim3d = 2;
    fix3d = 0;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 0);

    fix3d = 1;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 2);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    fix3d = 2;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 3);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(3);
    assert(fct2d.color(pnt));

    fix3d = 3;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 3);

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(2);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(3);
    assert(fct2d.color(pnt));

    fix3d = 4;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 0);

    /* Nektere 1D facety */

    /* 1D facety pro 2D facet s dim3d = 0, fix3d = 0 */

    dim3d = 0;
    fix3d = 0;
    fct2d = gr.iFacet(dim3d, fix3d);

    int dim2d = 0;
    int fix2d = 1;
    GridRepr fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 0);

    dim2d = 0;
    fix2d = 2;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 1);

    pnt.clear();
    pnt.push_back(1);
    assert(fct1d.color(pnt));

    fix2d = 3;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 1);

    pnt.clear();
    pnt.push_back(1);
    assert(fct1d.color(pnt));

    fix2d = 4;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 0);

    /* 1D facety pro 2D facet s dim3d = 2, fix3d = 2 */

    dim3d = 2;
    fix3d = 2;
    fct2d = gr.iFacet(dim3d, fix3d);

    dim2d = 0;
    fix2d = 0;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 1);

    pnt.clear();
    pnt.push_back(2);
    assert(fct1d.color(pnt));

    fix2d = 1;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 1);

    pnt.clear();
    pnt.push_back(2);
    assert(fct1d.color(pnt));

    fix2d = 2;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 2);

    pnt.clear();
    pnt.push_back(2);
    assert(fct1d.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    assert(fct1d.color(pnt));

    fix2d = 3;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 2);

    pnt.clear();
    pnt.push_back(2);
    assert(fct1d.color(pnt));

    pnt.clear();
    pnt.push_back(3);
    assert(fct1d.color(pnt));

    fix2d = 4;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 0);

    fix2d = 5;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 0);

    dim2d = 1;
    fix2d = 0;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 0);

    fix2d = 1;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 0);

    fix2d = 2;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 2);

    pnt.clear();
    pnt.push_back(0);
    assert(fct1d.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    assert(fct1d.color(pnt));

    fix2d = 3;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 1);

    pnt.clear();
    pnt.push_back(0);
    assert(fct1d.color(pnt));


    fix2d = 4;
    fct1d = fct2d.iFacet(dim2d, fix2d);

    assert(fct1d.points.size() == 1);

    pnt.clear();
    pnt.push_back(2);
    assert(fct1d.color(pnt));

    /* Vytvoreni 3D mnohostenu */

    gr = GridRepr(space);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(0);
    pnt.push_back(1);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(0);
    pnt.push_back(1);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(1);
    pnt.push_back(1);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(2);
    pnt.push_back(1);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(2);
    pnt.push_back(1);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(1);
    pnt.push_back(1);
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(1);
    pnt.push_back(0);
    gr.addPnt(pnt);

    /* Vytvareni 2D facetů z puvodniho mnohostenu */

    dim3d = 0;
    fix3d = 1;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 1);

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(1);
    assert(fct2d.color(pnt));

    fix3d = 2;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 4);

    pnt.clear();
    pnt.push_back(0);
    pnt.push_back(1);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(0);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(1);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(1);
    assert(fct2d.color(pnt));

    dim3d = 1;
    fix3d = 2;
    fct2d = gr.iFacet(dim3d, fix3d);

    assert(fct2d.points.size() == 3);

    pnt.clear();
    pnt.push_back(1);
    pnt.push_back(1);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(0);
    assert(fct2d.color(pnt));

    pnt.clear();
    pnt.push_back(2);
    pnt.push_back(1);
    assert(fct2d.color(pnt));
    return true;
}

bool testGridRepr()
{   
    if (!testGridReprBasicOperations()) {
        return false;
    }
    if (!testGridReprFacet()) {
        return false;
    }
    return true;
}
