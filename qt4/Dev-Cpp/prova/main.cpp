#include <cstdlib>
#include <iostream>
#include "math.h"

using namespace std;

int main(int argc, char *argv[])
{
    double s = 16.8;
    cout << s << endl;
    s = s / 1.2;
    cout << s << endl;
    s = (s * 100.);
    cout << s << endl;
    s = floorf(s);
    cout << s << endl;
    s = s / 100;
    cout << s << endl;
    cout << floorf(16.8) << endl;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
