//#include "menu.h"
#include <time.h>
//#include "ini.h"
#include "teamwork.h"
#include <iostream>

using namespace std;


int main(void)
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow( hWnd, SW_HIDE );
	teamwork();
	return 0;
}