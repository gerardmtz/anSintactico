#ifndef PILA_H
#define PILA_H

#include <string>
#include <cstring>

using namespace std;

#define MAX 50

class Pila
{
    int cima = -1;
    char pilac[MAX][10];

public:
    Pila();

    void insertapila(string elem);//(char *elem);  //(char elem[]);

    void eliminapila();

    // char* getPilacElement(int index) {
    //     if (index >= 0 && index <= cima) {
    //         return pilac[index];
    //     } else {
    //         return nullptr; // Si el índice está fuera de rango, retorna nullptr
    //     }
    // }

    char* getPilacElement() {
        return pilac[cima];
    }

    int getCima(){
        return cima;
    }

};

#endif // PILA_H
