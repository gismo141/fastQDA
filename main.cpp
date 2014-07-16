#include "view/fastQDA.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    fastQDA w;
    w.show();
    
    return a.exec();
}