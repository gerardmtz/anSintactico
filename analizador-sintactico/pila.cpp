#include "pila.h"

Pila::Pila() {}

void Pila::insertapila(string elem)
{
    if(cima == -1){
        cima = 0;
        strcpy(pilac[cima],elem.c_str());
    }
    else{
        if(cima == MAX - 1)
            puts("Pila LLena");
        else{
            cima++;
            strcpy(pilac[cima],elem.c_str());
        }
    }
}

void Pila::eliminapila()
{
    if(cima == -1)
        puts("Pila Vacia");
    else{
        strcpy(pilac[cima],"");
        cima--;
    }
}
