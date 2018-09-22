#include <windows.h>
#include "resource.h"
#include <string>

BOOL CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);

class CppWnd
{
public:
	void Add();
	void Change(int i);
	void FillCombos();                          //fills combo boxes with data 
	CppWnd();	       
	CppWnd(HWND hApp, int n, std::string* nom, std::string* val);
	virtual ~CppWnd();
	BOOL CALLBACK PippoProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
	HWND        hwndCh;
	int         indice;
	std::string nome[100];
	std::string valutazione[100];
	int         giocatori;
};

