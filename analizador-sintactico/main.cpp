#include "oswieditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    oswiEditor w;
    w.show();
    return a.exec();
}
