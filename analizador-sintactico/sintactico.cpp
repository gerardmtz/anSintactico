#include "sintactico.h"
#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QString>

Sintactico::Sintactico() {}

void Sintactico::vanalisis_sintactico(char asTokens[MAXTOKEN][100])
{
    QDialog dialog;
    dialog.setWindowTitle("Analizador Sintáctico");

    QTextEdit *textEdit = new QTextEdit(&dialog);
    textEdit->setReadOnly(true);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(textEdit);
    dialog.setLayout(layout);

    dialog.show();

    int ip = 0, i, j;
    int renglon, iast;
    char x[10], a[10];

    pila.insertapila("$");

    if (strcmp(asTokens[ip], "puts") == 0)
        pila.insertapila("F");
    else
        pila.insertapila("D");
    QString tokens;
    for (i = 0; strcmp(asTokens[i], "$") != 0; i++) {
        tokens += QString("%1 ").arg(asTokens[i]);
    }
    textEdit->append(tokens);

    // textEdit->append("\n\nProducciones:\n");

    do {
        cima = pila.getCima();
        strcpy(x, pila.getPilacElement());
        strcpy(a, asTokens[ip]);

        if (estoken(x) || (strcmp(x, "$") == 0)) {
            if (strcmp(x, a) == 0) {
                pila.eliminapila();
                ip++;
            } else {
                if (strcmp(asTokens[ip], "puts") == 0)
                    pila.insertapila("F");
                else
                    pila.insertapila("D");

                strcpy(x, pila.getPilacElement());
            }
        } else {
            renglon = buscaTabla(a, x);

            if (renglon != 999) {
                pila.eliminapila();
                iast = 0;
                QString production = QString("%1 -> ").arg(varsint[tablaM[renglon][0]]);
                for (j = 3; iast != 999; j++) {
                    iast = tablaM[renglon][j];
                    if (iast < 0) {
                        iast *= -1;
                        production += QString("%1 ").arg(token[iast]);
                    } else {
                        if (iast != 999)
                            production += QString("%1 ").arg(varsint[iast]);
                    }
                }

                textEdit->append(production);

                for (i = j - 2; i > 2; i--) {
                    iast = tablaM[renglon][i];
                    if (iast < 0) {
                        iast *= -1;
                        pila.insertapila(token[iast]);
                    } else {
                        pila.insertapila(varsint[iast]);
                    }
                }
            } else {
                textEdit->append("\n\nError de Sintaxis");
                dialog.exec();
                return;
            }
        }
        QCoreApplication::processEvents();
    } while (strcmp(x, "$") != 0);

    textEdit->append("\n");
    dialog.exec();
}

int Sintactico::estoken(char x[])
{
    int i;

    for(i=0; i<23; i++)
    {
        if(strcmp(x, token[i]) == 0)
            return 1;
    }

    return 0;
}

int Sintactico::buscaTabla(char a[], char x[])
{
    int indx=0, inda=0, i;

    for(i=0; i<23; i++)
        if(strcmp(a, token[i]) == 0)
            inda = i;//9 int

    for(i=0; i<16; i++)
        if(strcmp(x, varsint[i]) == 0)
            indx=i; //1 D

    for(i=0; i<65; i++)
    {
        if(indx == tablaM[i][0])
            if(inda == tablaM[i][1])
                return i;
    }

    return 999;
}
