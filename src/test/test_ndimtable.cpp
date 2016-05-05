bool testTriboolNDimTable()
{
    cout << "------------------------- ";
    cout << "testTriboolNDimTable:" << endl;

    vector<size_t>idxsLimits;
    idxsLimits.push_back(5);
    idxsLimits.push_back(4);
    idxsLimits.push_back(4);

    /* Vytvoreni TriboolNDimTable o danych mezich */

    TriboolNDimTable tribTab(idxsLimits);

    /* Vlozeni nejakych hodnot do TriboolNDimTable */
    vector<size_t> idxs;

    idxs.clear();
    idxs.push_back(0);
    idxs.push_back(2);
    idxs.push_back(1);
    tribTab.setBlack(idxs);

    idxs.clear();
    idxs.push_back(5);
    idxs.push_back(1);
    idxs.push_back(4);
    tribTab.setWhite(idxs);

    /* Testovani, zda jsou v TriboolNDimTable spravne hodnoty */

    idxs.clear();
    idxs.push_back(0);
    idxs.push_back(0);
    idxs.push_back(0);

    assert(tribTab.getValue(idxs) == TriboolNDimTable::NOT_COMPUTED);

    idxs.clear();
    idxs.push_back(0);
    idxs.push_back(0);
    idxs.push_back(1);

    assert(tribTab.getValue(idxs) == TriboolNDimTable::NOT_COMPUTED);

    idxs.clear();
    idxs.push_back(0);
    idxs.push_back(0);
    idxs.push_back(0);

    assert(tribTab.getValue(idxs) == TriboolNDimTable::NOT_COMPUTED);

    idxs.clear();
    idxs.push_back(0);
    idxs.push_back(4);
    idxs.push_back(1);

    assert(tribTab.getValue(idxs) == TriboolNDimTable::NOT_COMPUTED);

    idxs.clear();
    idxs.push_back(5);
    idxs.push_back(4);
    idxs.push_back(0);

    assert(tribTab.getValue(idxs) == TriboolNDimTable::NOT_COMPUTED);

    idxs.clear();
    idxs.push_back(5);
    idxs.push_back(4);
    idxs.push_back(3);

    assert(tribTab.getValue(idxs) == TriboolNDimTable::NOT_COMPUTED);

    idxs.clear();
    idxs.push_back(5);
    idxs.push_back(4);
    idxs.push_back(4);

    assert(tribTab.getValue(idxs) == TriboolNDimTable::NOT_COMPUTED);

    idxs.clear();
    idxs.push_back(0);
    idxs.push_back(2);
    idxs.push_back(1);

    assert(tribTab.getValue(idxs) == TriboolNDimTable::BLACK);

    idxs.clear();
    idxs.push_back(5);
    idxs.push_back(1);
    idxs.push_back(4);

    assert(tribTab.getValue(idxs) == TriboolNDimTable::WHITE);

    /* Dalsi zmena hodnot */

    idxs.clear();
    idxs.push_back(5);
    idxs.push_back(1);
    idxs.push_back(4);
    tribTab.setWhite(idxs);

    idxs.clear();
    idxs.push_back(0);
    idxs.push_back(0);
    idxs.push_back(0);
    tribTab.setBlack(idxs);

    /* Testovani, zda jsou v TriboolNDimTable spravne hodnoty */

    idxs.clear();
    idxs.push_back(5);
    idxs.push_back(1);
    idxs.push_back(4);

    assert(tribTab.getValue(idxs) == TriboolNDimTable::WHITE);

    idxs.clear();
    idxs.push_back(0);
    idxs.push_back(0);
    idxs.push_back(0);
    
    assert(tribTab.getValue(idxs) == TriboolNDimTable::BLACK);

    return true;
}

bool testNDimTable()
{
    if (!testTriboolNDimTable()) {
        return false;
    }
    return true;
}
