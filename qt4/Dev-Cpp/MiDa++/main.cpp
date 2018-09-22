#include <iostream>
#include <iomanip>
#include <vector>
#include "mysql++.h"
#include "custom.h"

using namespace mysqlpp;
using namespace std;

int main()
{
    try
    {
    Connection con("palio","","sani","fisica");
    Query query = con.query();
    query << "select * from vittorie;"; 
    Result res = query.store(); 
    Row r = *(res.begin());
    cout << r[0] << endl;
    
    }
    catch(BadQuery er)
    {
        cerr << "Error: " << er.error << endl;
         system("PAUSE");
        return -1;
    }
    catch(BadConversion er)
    {
        cerr << "Error: tried to convert \"" << er.data;
         system("PAUSE");
        return -1;
    }       
    
    system("PAUSE");	
    return 0;
}
