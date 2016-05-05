bool testNbhoodReprMembership_datafiles()
{
    cout << "------------------------- ";
    cout << "testNbhoodReprMembership_datafiles:" << endl;

    vector<string> files;
    files.push_back("01");
    files.push_back("02");
    files.push_back("03");
    files.push_back("04");
    files.push_back("06");
    files.push_back("07");
    files.push_back("08");
    files.push_back("09");
    files.push_back("10");
    files.push_back("11");
    files.push_back("12");
    files.push_back("13");
    files.push_back("14");
    files.push_back("15");
    files.push_back("16");
    files.push_back("17");
    files.push_back("18");
    files.push_back("19");
    files.push_back("20");
    files.push_back("21");
    files.push_back("22");

    for (size_t i = 0; i < files.size(); i ++) {
        string datafile, spacefile;
        datafile = "src/test/data/uint/grid_repr/" + files[i] + ".txt";
        spacefile = "src/test/data/uint/grid_repr/" + files[i] + "_space.txt";
        cout << datafile << ": " << endl;

        Space space = createSpaceFromSpacefile(spacefile);

        bool allOk = true;
        vector<vector<Coord> > wrongPnts;
        vector<bool> wrongColors;

        GridRepr gr(space);
        NbhoodRepr nr(space);

        /* Vytvoreni grid reprezentace z souboru */

        gr = GridRepr(space, datafile.c_str());
        nr = gr;
        
        /* Testovani, zda pro vsechny body prostoru vraci color
        na nbhood reprezentaci stejnou hodnotu jako color na referencni
        grid reprezentaci */

        allOk = true;
        Space::Iterator it = space.createIterator(true);
        wrongPnts.clear();
        wrongColors.clear();
        while (!it.atEnd()) {

            bool nrCol = nr.color(*it);
            if (gr.color(*it) != nrCol) {
                allOk = false;
                wrongPnts.push_back(*it);
                wrongColors.push_back(nrCol);
            }
            if (nrCol) {
                // PRINT_POINT(*it)
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

bool testNbhoodReprFacet()
{
    cout << "------------------------- ";
    cout << "testNbhoodReprFacet:" << endl;

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
        Space space = createSpaceFromSpacefile(spacefile);

        GridRepr gr(space, datafile.c_str());
        NbhoodRepr nr(gr);

        for (size_t i = 0; i < gr.dim(); i ++) {
            for (Coord coo = Coord::ZERO_COORD; coo <= space.limits[i]; coo = coo.getGridNext()) {
                GridRepr grFct = gr.iFacet(i, coo);
                NbhoodRepr nrFct = nr.iFacet(i, coo);
                assert(grFct == GridRepr(nrFct));
            }
        }

    }
    return true;
}

bool testNbhoodReprComplement()
{
    cout << "------------------------- ";
    cout << "testNbhoodReprComplement:" << endl;

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
        Space space = createSpaceFromSpacefile(spacefile);

        GridRepr gr(space, datafile.c_str());
        GridRepr grCmpl = gr.complement();
        NbhoodRepr nr(gr);
        NbhoodRepr nrCmpl = nr.complement();
        NbhoodRepr nrCmplCmpl = nrCmpl.complement();
        assert(gr == GridRepr(nr));
        assert(grCmpl == nrCmpl);
        assert(gr == GridRepr(nrCmplCmpl));
    }
    return true;
}

bool testNbhoodReprBooleanOperations()
{

    /* Testovani booleovskych operaci, tj. sjednoceni, pruniku a rozdilu (doplnek je v jinych testech) */
    
    cout << "------------------------- ";
    cout << "testNbhoodReprBooleanOperations:" << endl;

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
            GridRepr gr1(createSpaceFromSpacefile(spacefile), datafile.c_str());
            datafile = "src/test/data/uint/grid_repr/" + fileSet[j] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[j] + "_space.txt";
            GridRepr gr2(createSpaceFromSpacefile(spacefile), datafile.c_str());

            NbhoodRepr nr1(gr1);
            NbhoodRepr nr2(gr2);
            
            NbhoodRepr intersc = nr1.intersection(nr2);
            assert(gr1.intersection(gr2) == GridRepr(intersc));

            NbhoodRepr unif = nr1.unification(nr2);
            assert(gr1.unification(gr2) == GridRepr(unif));

            NbhoodRepr diff = nr1.difference(nr2);
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
            GridRepr gr1(createSpaceFromSpacefile(spacefile), datafile.c_str());
            datafile = "src/test/data/uint/grid_repr/" + fileSet[j] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[j] + "_space.txt";
            GridRepr gr2(createSpaceFromSpacefile(spacefile), datafile.c_str());
        
            NbhoodRepr nr1(gr1);
                        NbhoodRepr nr2(gr2);
            
            NbhoodRepr intersc = nr1.intersection(nr2);
            assert(gr1.intersection(gr2) == GridRepr(intersc));

            NbhoodRepr unif = nr1.unification(nr2);
            assert(gr1.unification(gr2) == GridRepr(unif));

            NbhoodRepr diff = nr1.difference(nr2);
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
            GridRepr gr1(createSpaceFromSpacefile(spacefile), datafile.c_str());
            datafile = "src/test/data/uint/grid_repr/" + fileSet[j] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[j] + "_space.txt";
            GridRepr gr2(createSpaceFromSpacefile(spacefile), datafile.c_str());
        
            NbhoodRepr nr1(gr1);
            NbhoodRepr nr2(gr2);
            
            NbhoodRepr intersc = nr1.intersection(nr2);
            assert(gr1.intersection(gr2) == GridRepr(intersc));

            NbhoodRepr unif = nr1.unification(nr2);
            assert(gr1.unification(gr2) == GridRepr(unif));

            NbhoodRepr diff = nr1.difference(nr2);
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
            GridRepr gr1(createSpaceFromSpacefile(spacefile), datafile.c_str());
            datafile = "src/test/data/uint/grid_repr/" + fileSet[j] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[j] + "_space.txt";
            GridRepr gr2(createSpaceFromSpacefile(spacefile), datafile.c_str());
        
            NbhoodRepr nr1(gr1);
                        NbhoodRepr nr2(gr2);
            
            NbhoodRepr intersc = nr1.intersection(nr2);
            assert(gr1.intersection(gr2) == GridRepr(intersc));

            NbhoodRepr unif = nr1.unification(nr2);
            assert(gr1.unification(gr2) == GridRepr(unif));

            NbhoodRepr diff = nr1.difference(nr2);
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
            GridRepr gr1(createSpaceFromSpacefile(spacefile), datafile.c_str());
            datafile = "src/test/data/uint/grid_repr/" + fileSet[j] + ".txt";
            spacefile = "src/test/data/uint/grid_repr/" + fileSet[j] + "_space.txt";
            GridRepr gr2(createSpaceFromSpacefile(spacefile), datafile.c_str());
        
            NbhoodRepr nr1(gr1);
                        NbhoodRepr nr2(gr2);
            
            NbhoodRepr intersc = nr1.intersection(nr2);
            assert(gr1.intersection(gr2) == GridRepr(intersc));

            NbhoodRepr unif = nr1.unification(nr2);
            assert(gr1.unification(gr2) == GridRepr(unif));

            NbhoodRepr diff = nr1.difference(nr2);
            assert(gr1.difference(gr2) == GridRepr(diff));
        }
    }
#endif

    return true;
}

bool testNbhoodRepr()
{
    if (!testNbhoodReprMembership_datafiles()) {
        return false;
    }
    if (!testNbhoodReprFacet()) {
        return false;
    }
    if (!testNbhoodReprComplement()) {
        return false;
    }
    if (!testNbhoodReprBooleanOperations()) {
        return false;
    }
    return true;
}
