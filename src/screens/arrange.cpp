#include <iostream>
#include "arrange.h"
#include "fman.h"

using namespace std;

void Arrange::print()
{
    _printList();
    Fman::playAnim("arrange", false, false);
}

void Arrange::inputShips()
{
    _askForShips(_console.input("To position: <a-j><1-10>"));
}

void Arrange::_printList()
{
    cout << "\n\n";
    cout << "4 × single-masted __ __ __ __" << endl;
    cout << "3 × two-masted    __ __ __" << endl;
    cout << "2 × three-masted  __ __" << endl;
    cout << "1 × four-masted   __" << endl;
}

void Arrange::_askForShips(string ans)
{
    cout << ans << endl;
}
