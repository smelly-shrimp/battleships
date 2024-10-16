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
    string ans = _console.input("To position: <a-j><1-10>");

    if (ans.length() == 2) {
        cout << ans;
    }
    else {
        inputShips();
    }
}

void Arrange::_printList()
{
    cout << "\n\n";
    cout << "4 × single-masted __ __ __ __" << endl;
    cout << "3 × two-masted    __ __ __" << endl;
    cout << "2 × three-masted  __ __" << endl;
    cout << "1 × four-masted   __" << endl;
}
