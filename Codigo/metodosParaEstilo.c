#include <stdio.h>
#include <windows.h>
#include "MPT.h"
#include "MPE.h"
#include "MPS.h"

void mudarCor(int cor){

    //Ponteiro para o console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Altera a cor do texto do console
    SetConsoleTextAttribute(hConsole, cor);
}