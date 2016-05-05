bool testFloatVertexReprMembership()
{
    cout << "------------------------- ";
    cout << "testFloatVertexReprMembership:" << endl;

    /* Vytvoreni mnohostenu v grid reprezentaci*/

    vector<Coord>limits;
    limits.push_back(nthFloat(5));
    limits.push_back(nthFloat(4));
    limits.push_back(nthFloat(4));
    Space space(limits);

    GridRepr gr(space);
    vector<Coord> pnt;

    pnt.clear();
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(1));
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(1));
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(2));
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(2));
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(3));
    pnt.push_back(nthFloat(2));
    gr.addPnt(pnt);

    /* Vytvoreni vertex reprezentace z grid reprezentace */

    VertexRepr vr(gr);
    vr.unsetDoDeallocMemoizer();

    /* Testovani, zda pro vsechny body prostoru vraci color
    na vertex reprezentaci stejnou hodnotu jako color na referencni
    grid reprezentaci */


    bool allOk = true;
    Space::Iterator it = space.createIterator(true);
    vector<vector<Coord> > wrongPnts;
    vector<bool> wrongColors;

#if 1
    allOk = true;
    it = space.createIterator(true);
    wrongPnts.clear();
    wrongColors.clear();
    while (!it.atEnd()) {
        bool vrCol = vr.color(*it);
        if (gr.color(*it) != vrCol) {
            allOk = false;
            wrongPnts.push_back(*it);
            wrongColors.push_back(vrCol);
        }
        ++ it;
    }
    if (!allOk) {
        cout << "----------------------------------------------------------" << endl;
        cout << "WRONG POINTS:" << endl;
        for (size_t i = 0; i < wrongPnts.size(); i ++) {
            PRINT_POINT(wrongPnts[i])
            cout << "wrong color: " << wrongColors[i] << endl;
        }
    }
    assert(allOk);
#endif

    /* Vytvoreni mnohostenu v grid reprezentaci*/

    gr = GridRepr(space);

    pnt.clear();
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(1));
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(1));
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(1));
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(nthFloat(0));
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(1));
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(1));
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(1));
    gr.addPnt(pnt);

    pnt.clear();
    pnt.push_back(nthFloat(2));
    pnt.push_back(nthFloat(1));
    pnt.push_back(nthFloat(0));
    gr.addPnt(pnt);

    /* Vytvoreni vertex reprezentace z grid reprezentace */

    vr = gr;
    vr.unsetDoDeallocMemoizer();

    /* Testovani, zda pro vsechny body prostoru vraci color
    na vertex reprezentaci stejnou hodnotu jako color na referencni
    grid reprezentaci */

#if 1
    allOk = true;
    it = space.createIterator(true);
    wrongPnts.clear();
    wrongColors.clear();
    while (!it.atEnd()) {
        bool vrCol = vr.color(*it);
        if (gr.color(*it) != vrCol) {
            allOk = false;
            wrongPnts.push_back(*it);
            wrongColors.push_back(vrCol);
        }
        ++ it;
    }
    if (!allOk) {
        cout << "----------------------------------------------------------" << endl;
        cout << "WRONG POINTS:" << endl;
        for (size_t i = 0; i < wrongPnts.size(); i ++) {
            PRINT_POINT(wrongPnts[i])
            cout << "wrong color: " << wrongColors[i] << endl;
        }
    }
    assert(allOk);
#endif

    return true;
}

bool testFloatVertexReprMembership_datafiles()
{
    cout << "------------------------- ";
    cout << "testFloatVertexReprMembership_datafiles:" << endl;

    vector<string> files;
    files.push_back("01");
    files.push_back("02");
    files.push_back("03");
    files.push_back("04");
    files.push_back("05");

    for (size_t i = 0; i < files.size(); i ++) {
        string datafile, spacefile;
        datafile = "src/test/data/uint/grid_repr/" + files[i] + ".txt";
        spacefile = "src/test/data/uint/grid_repr/" + files[i] + "_space.txt";
        cout << datafile << ": " << endl;
        
        Space space = createSpaceFromSpacefile(spacefile, true);

        bool allOk = true;
        vector<vector<Coord> > wrongPnts;
        vector<bool> wrongColors;

        GridRepr gr(space);
        VertexRepr vr(space);

        /* Vytvoreni grid reprezentace z souboru */

        gr = GridRepr(space, datafile.c_str(), true);

        cout << "----- grid repr -----" << endl;
        cout << gr;
        cout << "---- vertex repr ----" << endl;

        /* Vytvoreni vertex reprezentace z dane grid reprezentace */

        vr = gr;
        vr.unsetDoDeallocMemoizer();

        /* Testovani, zda pro vsechny body prostoru vraci color
        na vertex reprezentaci stejnou hodnotu jako color na referencni
        grid reprezentaci */

        allOk = true;
        Space::Iterator it = space.createIterator(true);
        wrongPnts.clear();
        wrongColors.clear();
        while (!it.atEnd()) {
            bool vrCol = vr.color(*it);
            if (gr.color(*it) != vrCol) {
                allOk = false;
                wrongPnts.push_back(*it);
                wrongColors.push_back(vrCol);
            }
            if (vrCol) {
                PRINT_POINT(*it)
            }
            ++ it;
        }
        if (!allOk) {
            cout << "----------------------------------------------------------" << endl;
            cout << "WRONG POINTS:" << endl;
            for (size_t i = 0; i < wrongPnts.size(); i ++) {
                PRINT_POINT(wrongPnts[i])
                cout << "wrong color: " << wrongColors[i] << endl;
            }
        }
        assert(allOk);
    }

    return true;
}

bool testFloatVertexReprComplement()
{
    cout << "------------------------- ";
    cout << "testFloatVertexReprComplement:" << endl;

    vector<string> files;
    files.push_back("01");
    files.push_back("02");
    files.push_back("03");
    files.push_back("04");
    files.push_back("05");
    files.push_back("06");
    files.push_back("07");
    files.push_back("08");
    files.push_back("09");
    files.push_back("10");
    files.push_back("11");
    files.push_back("12");

    for (size_t i = 0; i < files.size(); i ++) {
        string datafile, spacefile;
        datafile = "src/test/data/uint/grid_repr/" + files[i] + ".txt";
        spacefile = "src/test/data/uint/grid_repr/" + files[i] + "_space.txt";
        cout << datafile << ": " << endl;
        Space space = createSpaceFromSpacefile(spacefile, true);

        GridRepr gr(space, datafile.c_str(), true);
        GridRepr grCmpl = gr.complement();
        VertexRepr vr(gr);

        vr.unsetDoDeallocMemoizer();
        VertexRepr vrCmpl = vr.complement();
        vrCmpl.unsetDoDeallocMemoizer();

        VertexRepr vrCmplCmpl = vrCmpl.complement();
        vrCmplCmpl.unsetDoDeallocMemoizer();


        assert(gr == GridRepr(vr));
        assert(grCmpl == vrCmpl);
        assert(gr == GridRepr(vrCmplCmpl));
    }

    return true;
}

bool testFloatVertexReprFacet()
{
    cout << "------------------------- ";
    cout << "testFloatVertexReprFacet:" << endl;

    vector<string> files;
    files.push_back("01");
    files.push_back("02");
    files.push_back("04");
    files.push_back("05");
    files.push_back("06");
    files.push_back("07");
    files.push_back("08");
    files.push_back("09");
    files.push_back("10");
    files.push_back("11");
    files.push_back("12");

    for (size_t i = 0; i < files.size(); i ++) {
        string datafile, spacefile;
        datafile = "src/test/data/uint/grid_repr/" + files[i] + ".txt";
        spacefile = "src/test/data/uint/grid_repr/" + files[i] + "_space.txt";
        cout << datafile << ": " << endl;
        Space space = createSpaceFromSpacefile(spacefile, true);

        GridRepr gr(space, datafile.c_str(), true);
        VertexRepr vr(gr);
        vr.unsetDoDeallocMemoizer();

        for (size_t i = 0; i < gr.dim(); i ++) {
            for (Coord coo = Coord::ZERO_COORD; coo <= space.limits[i]; coo = coo.getGridNext()) {
                GridRepr grFct = gr.iFacet(i, coo);
                VertexRepr vrFct = vr.iFacet(i, coo);
                vrFct.unsetDoDeallocMemoizer();
                assert(grFct == GridRepr(vrFct));
            }
        }
    }
    return true;
}

bool testFloatVertexReprBooleanOperations()
{

    /* Testovani booleovskych operaci, tj. sjednoceni, pruniku a rozdilu (doplnek je v jinych testech) */
    
    cout << "------------------------- ";
    cout << "testFloatVertexReprBooleanOperations:" << endl;

    vector<string> fileSet;
    string file1, file2;
    string datafile, spacefile;

    /* Kazda sada mnohostenu (kazda sada objahuje mnohosteny se stejnym Space) bude testovana tak, ze
    pro kazdou dvojici teto sady spocitame prunik (resp. sjednoceni, rozdil) ve vertex reprezentaci a otestujeme,
    zda je tento prunik (resp. sjednoceni, rozdil) stejny jako prunik (resp. sjednoceni, rozdil)
    v grid reprezentaci (tu povazujeme za referencni). */

    /* Sada pro 2D prostor o rozmerech 4 x 4 */

    cout << "test 2D polyhedra" << endl;

    fileSet.clear();
    fileSet.push_back("06");
    fileSet.push_back("07");
    fileSet.push_back("08");
    fileSet.push_back("09");
    fileSet.push_back("10");
    fileSet.push_back("11");
    fileSet.push_back("12");

    for (size_t i = 0; i < fileSet.size(); i ++) {
        for (size_t j = 0; j < fileSet.size(); j ++) {

            datafile = "src/test/data/uint/grid_repr/" + fileSet[i] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[i] + "_space.txt";
            GridRepr gr1(createSpaceFromSpacefile(spacefile, true), datafile.c_str(), true);
            datafile = "src/test/data/uint/grid_repr/" + fileSet[j] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[j] + "_space.txt";
            GridRepr gr2(createSpaceFromSpacefile(spacefile, true), datafile.c_str(), true);

            VertexRepr vr1(gr1);
            vr1.unsetDoDeallocMemoizer();
            VertexRepr vr2(gr2);
            vr2.unsetDoDeallocMemoizer();

            VertexRepr intersc = vr1.intersection(vr2);
            intersc.unsetDoDeallocMemoizer();
            assert(gr1.intersection(gr2) == GridRepr(intersc));

            VertexRepr unif = vr1.unification(vr2);
            unif.unsetDoDeallocMemoizer();
            assert(gr1.unification(gr2) == GridRepr(unif));

            VertexRepr diff = vr1.difference(vr2);
            diff.unsetDoDeallocMemoizer();
            assert(gr1.difference(gr2) == GridRepr(diff));

        }
    }

    /* Sada pro 3D prostor o rozmerech 6 x 6 x 6 */

    cout << "test 3D polyhedra" << endl;

    fileSet.clear();
    fileSet.push_back("13");
    fileSet.push_back("14");
    fileSet.push_back("15");
    fileSet.push_back("16");
    fileSet.push_back("17");

    for (size_t i = 0; i < fileSet.size(); i ++) {
        for (size_t j = 0; j < fileSet.size(); j ++) {

            datafile = "src/test/data/uint/grid_repr/" + fileSet[i] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[i] + "_space.txt";
            GridRepr gr1(createSpaceFromSpacefile(spacefile, true), datafile.c_str(), true);
            datafile = "src/test/data/uint/grid_repr/" + fileSet[j] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[j] + "_space.txt";
            GridRepr gr2(createSpaceFromSpacefile(spacefile, true), datafile.c_str(), true);
        
            VertexRepr vr1(gr1);
            vr1.unsetDoDeallocMemoizer();
            VertexRepr vr2(gr2);
            vr2.unsetDoDeallocMemoizer();

            VertexRepr intersc = vr1.intersection(vr2);
            intersc.unsetDoDeallocMemoizer();
            assert(gr1.intersection(gr2) == GridRepr(intersc));

            VertexRepr unif = vr1.unification(vr2);
            unif.unsetDoDeallocMemoizer();
            assert(gr1.unification(gr2) == GridRepr(unif));

            VertexRepr diff = vr1.difference(vr2);
            diff.unsetDoDeallocMemoizer();
            assert(gr1.difference(gr2) == GridRepr(diff));
        }
    }

    /* Sada pro 1D prostor o rozmerech 20 */

    cout << "test 1D polyhedra" << endl;

    fileSet.clear();
    fileSet.push_back("18");
    fileSet.push_back("19");
    fileSet.push_back("20");
    fileSet.push_back("21");

    for (size_t i = 0; i < fileSet.size(); i ++) {
        for (size_t j = 0; j < fileSet.size(); j ++) {

            datafile = "src/test/data/uint/grid_repr/" + fileSet[i] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[i] + "_space.txt";
            GridRepr gr1(createSpaceFromSpacefile(spacefile, true), datafile.c_str(), true);
            datafile = "src/test/data/uint/grid_repr/" + fileSet[j] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[j] + "_space.txt";
            GridRepr gr2(createSpaceFromSpacefile(spacefile, true), datafile.c_str(), true);
        
            VertexRepr vr1(gr1);
            vr1.unsetDoDeallocMemoizer();
            VertexRepr vr2(gr2);
            vr2.unsetDoDeallocMemoizer();

            VertexRepr intersc = vr1.intersection(vr2);
            intersc.unsetDoDeallocMemoizer();
            assert(gr1.intersection(gr2) == GridRepr(intersc));

            VertexRepr unif = vr1.unification(vr2);
            unif.unsetDoDeallocMemoizer();
            assert(gr1.unification(gr2) == GridRepr(unif));

            VertexRepr diff = vr1.difference(vr2);
            diff.unsetDoDeallocMemoizer();
            assert(gr1.difference(gr2) == GridRepr(diff));
        }
    }

#if 1
    /* Sada pro 4D prostor o rozmerech 6 x 6 x 6 x 6 */

    cout << "test 4D polyhedra" << endl;

    fileSet.clear();
    fileSet.push_back("22");
    fileSet.push_back("23");
    fileSet.push_back("24");

    for (size_t i = 0; i < fileSet.size(); i ++) {
        for (size_t j = 0; j < fileSet.size(); j ++) {

            datafile = "src/test/data/uint/grid_repr/" + fileSet[i] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[i] + "_space.txt";
            GridRepr gr1(createSpaceFromSpacefile(spacefile, true), datafile.c_str(), true);
            datafile = "src/test/data/uint/grid_repr/" + fileSet[j] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[j] + "_space.txt";
            GridRepr gr2(createSpaceFromSpacefile(spacefile, true), datafile.c_str(), true);
        
            VertexRepr vr1(gr1);
            vr1.unsetDoDeallocMemoizer();
            VertexRepr vr2(gr2);
            vr2.unsetDoDeallocMemoizer();

            VertexRepr intersc = vr1.intersection(vr2);
            intersc.unsetDoDeallocMemoizer();
            assert(gr1.intersection(gr2) == GridRepr(intersc));

            VertexRepr unif = vr1.unification(vr2);
            unif.unsetDoDeallocMemoizer();
            assert(gr1.unification(gr2) == GridRepr(unif));

            VertexRepr diff = vr1.difference(vr2);
            diff.unsetDoDeallocMemoizer();
            assert(gr1.difference(gr2) == GridRepr(diff));
        }
    }
#endif

#if 1
    /* Sada pro 5D prostor o rozmerech 5 x 5 x 5 x 4 x 3 */

    cout << "test 5D polyhedra" << endl;

    fileSet.clear();
    fileSet.push_back("25");
    fileSet.push_back("26");

    for (size_t i = 0; i < fileSet.size(); i ++) {
        for (size_t j = 0; j < fileSet.size(); j ++) {

            datafile = "src/test/data/uint/grid_repr/" + fileSet[i] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[i] + "_space.txt";
            GridRepr gr1(createSpaceFromSpacefile(spacefile, true), datafile.c_str(), true);
            datafile = "src/test/data/uint/grid_repr/" + fileSet[j] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[j] + "_space.txt";
            GridRepr gr2(createSpaceFromSpacefile(spacefile, true), datafile.c_str(), true);
        
            VertexRepr vr1(gr1);
            vr1.unsetDoDeallocMemoizer();
            VertexRepr vr2(gr2);
            vr2.unsetDoDeallocMemoizer();

            VertexRepr intersc = vr1.intersection(vr2);
            intersc.unsetDoDeallocMemoizer();
            assert(gr1.intersection(gr2) == GridRepr(intersc));

            VertexRepr unif = vr1.unification(vr2);
            unif.unsetDoDeallocMemoizer();
            assert(gr1.unification(gr2) == GridRepr(unif));

            VertexRepr diff = vr1.difference(vr2);
            diff.unsetDoDeallocMemoizer();
            assert(gr1.difference(gr2) == GridRepr(diff));
        }
    }
#endif

    return true;
}

bool testFloatVertexRepr()
{
    if (!testFloatVertexReprMembership()) {
        return false;
    }
    if (!testFloatVertexReprMembership_datafiles()) {
        return false;
    }
    if (!testFloatVertexReprComplement()) {
        return false;
    }
    if (!testFloatVertexReprFacet()) {
        return false;
    }
    if (!testFloatVertexReprBooleanOperations()) {
        return false;
    }
    return true;
}
