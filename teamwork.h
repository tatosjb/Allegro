#ifndef TEAMWORK_H_INCLUDED
#define	TEAMWORK_H_INCLUDED
#include "menu.h"
#include <time.h>
#include "ini.h"
#include "teamwork.h"
#include <iostream>

using namespace std;
#include "objetos.h"

void teamwork(){
	//"Sem comentários pra essa.. Kkk"
	srand(time(NULL));
	//Roda menu
	if(inicializa()){
		menu();
	}
}


#endif // !TEAMWORK_H_INCLUDED
