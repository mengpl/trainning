#include "gameoflife.hpp"
#include <cassert>
#include <iostream>

static void example()
{
    charMatrix cMatrix;
    charVector listChar;
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');

    cMatrix.push_back(listChar);

    listChar.clear();
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('*');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');

    cMatrix.push_back(listChar);

    listChar.clear();
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('*');
    listChar.push_back('*');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    cMatrix.push_back(listChar);

    listChar.clear();
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');

    cMatrix.push_back(listChar);

    calculate_next_generation(cMatrix);

    charMatrix cMatrixTmp;
    listChar.clear();
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');

    cMatrixTmp.push_back(listChar);

    listChar.clear();
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('*');
    listChar.push_back('*');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');

    cMatrixTmp.push_back(listChar);

    listChar.clear();
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('*');
    listChar.push_back('*');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    cMatrixTmp.push_back(listChar);

    listChar.clear();
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    listChar.push_back('.');
    cMatrixTmp.push_back(listChar);

    assert( cMatrix == cMatrixTmp);
}

typedef void test();

static test * tests[ ] =
{
    example,

    static_cast<test*>(0),

};

int main()
{

    size_t at = 0;

    while (tests[at])
    {

        tests[at++]();
        std::cout << '.';

    }

    std::cout << std::endl << at << " tests passed" << std::endl;

    return 0;

}