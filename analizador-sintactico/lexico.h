#ifndef LEXICO_H
#define LEXICO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cctype>

#define MAXTOKEN 100
#define NUMPALRES 4

using namespace std;

class Lexico
{
    int indice=0, edoAct, edoIni, iniToken=0, k;

    char non[6]="13579", par[6]="24680";

    char sLexema[127];

    char PalRes[5][10]= {"char", "float","int","puts"}; //printf

public:
    Lexico();

    void vanalisislexico(FILE* Fd, int numBytesArch, char asTokens[MAXTOKEN][100]);

    void viniedos();

    int edoActesacept();

    char nextchar(FILE* Fd);

    void falla(FILE* Fd);

    void vretract(FILE *Fd);

    int esId(FILE* Fd);

    void recuperaerror();

    void vmuestra(char asTokens[MAXTOKEN][100]);

};

#endif // LEXICO_H
