#include "editortheme.h"

void EditorTheme::loadThemesFromJson(const QString &filename) {
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("No se pudo abrir el archivo JSON.");
    return;
  }

  QByteArray jsonData = file.readAll();
  QJsonDocument doc = QJsonDocument::fromJson(jsonData);

  if (doc.isNull()) {
    qWarning("Fallo el parse del JSON.");
    return;
  }

  QJsonObject root = doc.object();
  QJsonObject themesObj = root["themes"].toObject();

  for (auto it = themesObj.begin(); it != themesObj.end(); ++it) {
    QString themeKey = it.key();
    QJsonObject themeObj = it.value().toObject();

    Theme theme;
    theme.name = themeObj["name"].toString();
    theme.type = themeObj["type"].toString();

    // Parsear los colores del editor
    QJsonObject colors = themeObj["colors"].toObject();
    theme.colors.editor_background =
        QColor(colors["editor.background"].toString());
    theme.colors.editor_foreground =
        QColor(colors["editor.foreground"].toString());
    theme.colors.editor_lineHighlight =
        QColor(colors["editor.lineHighlightBackground"].toString());
    theme.colors.editor_selection =
        QColor(colors["editor.selectionBackground"].toString());
    theme.colors.editor_inactiveSelection =
        QColor(colors["editor.inactiveSelectionBackground"].toString());
    theme.colors.editor_cursor =
        QColor(colors["editorCursor.foreground"].toString());
    theme.colors.editor_whitespace =
        QColor(colors["editorWhitespace.foreground"].toString());
    theme.colors.editor_indentGuide =
        QColor(colors["editorIndentGuide.background"].toString());

    // Parsear los colores de los tokens
    QJsonObject tokenColors = themeObj["tokenColors"].toObject();
    theme.colors.string = QColor(tokenColors["string"].toString());
    theme.colors.string_number = QColor(tokenColors["number"].toString());
    theme.colors.string_keyword = QColor(tokenColors["keyword"].toString());
    theme.colors.string_comment = QColor(tokenColors["comment"].toString());
    theme.colors.string_function = QColor(tokenColors["function"].toString());
    theme.colors.string_variable = QColor(tokenColors["variable"].toString());
    theme.colors.string_operators = QColor(tokenColors["operator"].toString());
    theme.colors.string_className = QColor(tokenColors["class"].toString());

    themes[themeKey] = theme;
  }
}
