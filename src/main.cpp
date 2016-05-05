#include <iostream>
#include "test/test.h"

using namespace std;

int main()
{
    if (!test()) {
        cout << "tests failed" << endl;
        return 1;
    }

    return 0;
}
