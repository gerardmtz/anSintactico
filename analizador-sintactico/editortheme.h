#ifndef EDITORTHEME_H
#define EDITORTHEME_H

#include <QColor>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMap>
#include <QString>

class EditorTheme {
public:
  struct ThemeColors {
    //Colores de editor
    QColor editor_background;
    QColor editor_foreground;
    QColor editor_lineHighlight;
    QColor editor_selection;
    QColor editor_inactiveSelection;
    QColor editor_cursor;
    QColor editor_whitespace;
    QColor editor_indentGuide;

    //Colores de tokens
    QColor string;
    QColor string_number;
    QColor string_keyword;
    QColor string_comment;
    QColor string_function;
    QColor string_variable;
    QColor string_operators;
    QColor string_className;
  };

  struct Theme {
    QString name;
    QString type;
    ThemeColors colors;
  };

  EditorTheme() { loadThemesFromJson("./themes.json"); }

  const Theme &getTheme(const QString &themeName) const {
    return themes[themeName];
  }

  QStringList getAvailableThemes() const { return themes.keys(); }

private:
  QMap<QString, Theme> themes;

  void loadThemesFromJson(const QString &filename);
};

#endif // EDITORTHEME_H
