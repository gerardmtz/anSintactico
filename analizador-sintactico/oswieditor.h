#ifndef OSWIEDITOR_H
#define OSWIEDITOR_H

#include <QMainWindow>
#include"editortexto.h"
#include "archivos.h"
#include "lexico.h"
#include "sintactico.h"

QT_BEGIN_NAMESPACE
namespace Ui { class oswiEditor; }
QT_END_NAMESPACE

class oswiEditor : public QMainWindow
{
    Q_OBJECT

public:
    oswiEditor(QWidget *parent = nullptr);
    ~oswiEditor();

private slots:
    void on_actionNuevo_triggered();

    void on_actionAbrir_triggered();

    void on_actionGuardar_triggered();

    void on_actionSalir_triggered();

    void on_actionCambiar_Tema_triggered();

    void on_actionLexico_triggered();

    void on_actionSintactio_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionCambiar_fuente_triggered();

    void showTokensModal(char asTokens[100][100]);

private:
    Ui::oswiEditor *ui;
    CodeEditor *editor;
    void documentWasModified();
    void updateTitle();
    bool changeTheme();
    bool isModified;
    QString currentFile;
    Archivos *File;
    Lexico *lex;
    Sintactico *sin;
    char asTokens[100][100];
};
#endif // OSWIEDITOR_H
