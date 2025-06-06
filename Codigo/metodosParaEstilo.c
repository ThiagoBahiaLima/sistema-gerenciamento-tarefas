#include <stdio.h>
#include <windows.h>
#include "MPT.h"
#include "MPV.h"
#include "MPE.h"

void mudarCor(int cor){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}