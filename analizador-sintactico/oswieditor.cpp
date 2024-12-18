#include "oswieditor.h"
#include "ui_oswieditor.h"
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFont>
#include <QFontDialog>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include <QDialog>
#include <QListWidget>
#include <QVBoxLayout>
#include <iostream>

using namespace std;

oswiEditor::oswiEditor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::oswiEditor) {
  ui->setupUi(this);
  editor = new CodeEditor(this);
  File = new Archivos();
  lex = new Lexico();
  sin = new Sintactico();

  this->setCentralWidget(editor);
  File->setEditor(editor);

  isModified = false;
  editor->setPlainText("");
  editor->setFont(QFont("Monospace", 12));

  connect(editor, &CodeEditor::textChanged, this,
          &oswiEditor::documentWasModified);
  updateTitle();
}

oswiEditor::~oswiEditor() { delete ui; }

void oswiEditor::documentWasModified() {
  isModified = true;
  updateTitle();
}

void oswiEditor::updateTitle() {
  QString title = "Oswi Editor";
  if (!currentFile.isEmpty() && isModified)
    title = title + " - " + QFileInfo(currentFile).fileName() + '*';
  if (!currentFile.isEmpty() && !isModified)
    title = title + " - " + QFileInfo(currentFile).fileName();
  if (currentFile.isEmpty() && isModified)
    title = title + '*';
  if (!isModified)
    title = "Oswi Editor";

  setWindowTitle(title);
}

bool oswiEditor::changeTheme() {}

void oswiEditor::on_actionNuevo_triggered() {
  if (!editor->toPlainText().isEmpty()) {
    QMessageBox::StandardButton response;
    response = QMessageBox::question(
        this, tr("Nuevo Archivo"),
        tr("¿Desea guardar los cambios antes de crear un nuevo archivo?"),
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (response == QMessageBox::Yes) {
      on_actionGuardar_triggered();
      if (!editor->toPlainText().isEmpty()) {
        editor->clear();
        isModified = false;
        updateTitle();
      }
    } else if (response == QMessageBox::No) {
      editor->clear();
      isModified = false;
      updateTitle();
    }
  } else {
    editor->clear();
  }
}

void oswiEditor::on_actionAbrir_triggered() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Abrir Archivo"), "",
      tr("Codigo de C (*.c);;Codigo de C++(*.cpp);;Archivo de Texto "
         "(*.txt);;All Files (*)"));
  if (!fileName.isEmpty()) {
    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
      QTextStream in(&file);
      editor->setPlainText(in.readAll());
      file.close();

      currentFile = fileName;
      isModified = false;
      updateTitle();
    }
  }
}

//OG
void oswiEditor::on_actionGuardar_triggered() {
    QString fileName = QFileDialog::getSaveFileName(
        nullptr,
        "Guardar Archivo",
        "",
        "Archivo de datos (*.dat);;Todos los archivos (*)"
        );
    File->generararch(fileName);
}

// void oswiEditor::on_actionGuardar_triggered() {

// }


void oswiEditor::on_actionSalir_triggered() {
  if (!editor->toPlainText().isEmpty()) {
    QMessageBox::StandardButton response;
    response = QMessageBox::question(
        this, tr("Salir"),
        tr("¿Desea guardar los cambios antes de cerrar el programa?"),
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (response == QMessageBox::Yes) {
      on_actionGuardar_triggered();
      if (!editor->toPlainText().isEmpty()) {
        close();
      }
    } else if (response == QMessageBox::No) {
      close();
    }
  } else {
    close();
  }
}

void oswiEditor::on_actionCambiar_Tema_triggered() {}

void oswiEditor::on_actionLexico_triggered() {
    File->vabrirarch();
    lex->vanalisislexico(File->getFd(),File->bytesarch(), this->asTokens);
    oswiEditor::showTokensModal(this->asTokens);
}

void oswiEditor::showTokensModal(char asTokens[100][100]) {
    QDialog dialog;
    dialog.setWindowTitle("ANALIZADOR LÉXICO");

    QListWidget *listWidget = new QListWidget(&dialog);
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(listWidget);
    dialog.setLayout(layout);
    for (int i = 0; i < 100; ++i) {
        if(asTokens[i][0] == '$'){
            break;
        }
        if (asTokens[i][0] != '\0') { // Check if the token is not empty
            listWidget->addItem(asTokens[i]);
        }
    }
    dialog.exec();
}


void oswiEditor::on_actionSintactio_triggered() {
    File->vabrirarch();
    lex->vanalisislexico(File->getFd(),File->bytesarch(), this->asTokens);
    sin->vanalisis_sintactico(this->asTokens);

}

void oswiEditor::on_actionZoom_In_triggered() { editor->zoomIn(); }

void oswiEditor::on_actionZoom_Out_triggered() { editor->zoomOut(); }

void oswiEditor::on_actionCambiar_fuente_triggered() {
  editor->setFont(QFontDialog::getFont(0, editor->font()));
}
