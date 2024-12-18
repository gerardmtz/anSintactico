#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <cstdio>
#include <string>
#include <iostream>
#include <QPlainTextEdit>
#include <QTemporaryFile>
#include <QFileInfo>
#include <QString>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

using namespace std;

class Archivos {
private:
    FILE* Fd;
    QTemporaryFile* tempFile;
    string currentFilename;
    QPlainTextEdit* editor;
    int numBytesArch;

public:
    Archivos();
    ~Archivos();

    // Original methods
    void generararch(QString fileName);
    void vabrirarch();
    int bytesarch();
    FILE* getFd();


    // New Qt-related methods
    // bool processQPlainTextEdit(QPlainTextEdit* editor, const string& filename = "");
    void cleanup();
    // bool openExistingFile(const string& filename);
    string getCurrentFilename() const { return currentFilename; }

    void setEditor(QPlainTextEdit* e) { editor = e; }
};

#endif // ARCHIVOS_H
