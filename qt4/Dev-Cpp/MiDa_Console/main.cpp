#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s = "Sòkajfgò aòsdfaò asdfpguioò afògoh";
    string temp;
    for(int i=0; i<s.length(); i++)
    {
        temp = s.substr(i, 1);
        if (temp == " ")
            s.replace(i, 1, "_");
    }
    
    cout << s << endl;
    system("PAUSE");
    return 0;
}  


