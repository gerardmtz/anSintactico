#include "archivos.h"

Archivos::Archivos() : Fd(nullptr), tempFile(nullptr) {}

Archivos::~Archivos() {
    cleanup();
}

void Archivos::generararch(QString fileName) {
    if (!editor) {
        QMessageBox::critical(nullptr, "Error", "Editor not initialized");
        return;
    }

    if (fileName.isEmpty()) {
        return;
    }

    // Ensure the file has .dat extension
    if (!fileName.endsWith(".dat")) {
        fileName += ".dat";
    }

    currentFilename = fileName.toStdString();

    // Open file in binary write mode
    Fd = fopen(currentFilename.c_str(), "w+b");
    if(Fd == nullptr) {
        QMessageBox::critical(
            nullptr,
            "Error",
            QString("No se puede abrir el archivo: %1").arg(fileName)
            );
        return;
    }

    // Get content from editor and write to file
    QString content = editor->toPlainText();
    QByteArray data = content.toUtf8();

    // Write the content to file character by character
    for(char c : data) {
        if(c != '\b') {  // Skip backspace characters
            fwrite(&c, sizeof(c), 1, Fd);
        }
    }

    fclose(Fd);
    Fd = nullptr;
}

void Archivos::vabrirarch() {
    QString fileName = QFileDialog::getOpenFileName(
        nullptr,
        "Abrir Archivo",
        "",
        "Archivo de datos (*.dat);;Todos los archivos (*)"
        );

    if (fileName.isEmpty()) {
        return;
    }

    // Ensure the file has .dat extension
    if (!fileName.endsWith(".dat")) {
        fileName += ".dat";
    }

    currentFilename = fileName.toStdString();

    // Open file in binary read mode
    Fd = fopen(currentFilename.c_str(), "r+b");
    if(Fd == nullptr) {
        QMessageBox::critical(
            nullptr,
            "Error",
            QString("No se puede abrir el archivo: %1").arg(fileName)
            );
        return;
    }

    QMessageBox::information(
        nullptr,
        "Éxito",
        "El archivo se ha abierto correctamente"
        );

    if (editor) {
        // Get file size
        fseek(Fd, 0, SEEK_END);
        long fileSize = ftell(Fd);
        fseek(Fd, 0, SEEK_SET);

        // Read file content
        vector<char> buffer(fileSize);
        fread(buffer.data(), 1, fileSize, Fd);

        // Convert to QString and set to editor
        QString content = QString::fromUtf8(buffer.data(), fileSize);
        editor->setPlainText(content);
    }
}

// bool Archivos::processQPlainTextEdit(QPlainTextEdit* editor, const string& filename) {
//     cleanup(); // Clean any existing temporary file

//     // Get text from QPlainTextEdit
//     QString text = editor->toPlainText();

//     if(text.isEmpty()) {
//         cout << "Error: Empty text" << endl;
//         return false;
//     }

//     // Create filename if not provided
//     currentFilename = filename.empty() ? "temp.dat" : filename;
//     if(!currentFilename.ends_with(".dat")) {
//         currentFilename += ".dat";
//     }

//     // Create temporary file
//     tempFile = new QTemporaryFile;
//     if(!tempFile->open()) {
//         cout << "Error: Cannot create temporary file" << endl;
//         delete tempFile;
//         tempFile = nullptr;
//         return false;
//     }

//     // Write content to temporary file
//     QTextStream stream(tempFile);
//     stream << text;
//     stream.flush();
//     tempFile->flush();

//     // Open file with FILE* for compatibility
//     Fd = fopen(tempFile->fileName().toStdString().c_str(), "r+b");
//     if(Fd == nullptr) {
//         cout << "Error: Cannot open temporary file with FILE*" << endl;
//         cleanup();
//         return false;
//     }

//     return true;
// }

// bool Archivos::openExistingFile(const string& filename) {
//     cleanup();

//     currentFilename = filename;
//     if(!currentFilename.ends_with(".dat")) {
//         currentFilename += ".dat";
//     }

//     Fd = fopen(currentFilename.c_str(), "r+b");
//     if(Fd == nullptr) {
//         cout << "Error: Cannot open file: " << currentFilename << endl;
//         return false;
//     }

//     return true;
// }

int Archivos::bytesarch() {
    if(Fd == nullptr) return 0;

    fseek(Fd, 0L, SEEK_END);
    int size = ftell(Fd);
    fseek(Fd, 0L, SEEK_SET);
    return size;
}

FILE* Archivos::getFd() {
    return Fd;
}

void Archivos::cleanup() {
    if(Fd != nullptr) {
        fclose(Fd);
        Fd = nullptr;
    }

    if(tempFile != nullptr) {
        tempFile->close();
        delete tempFile;
        tempFile = nullptr;
    }
}
