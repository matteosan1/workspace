#include "stdlib.h"
#include "time.h"

void Ordina(int n, int* y)
{
    int numero[n];
    srand(time(NULL));    
    
    for(int i=0; i<n; i++)
    {
        numero[i] = i;
        y[i] = rand();     
    }

	for(int i=0; i<n-1; i++)
	{
		for(int k=i+1; k<n; k++)
		{
			if (y[i] > y[k])
			{
				int temp = numero[i];
				numero[i] = numero[k];
				numero[k] = temp;
				temp = y[i];
				y[i] = y[k];
				y[k] = temp;
			}
		}
	} 
}
