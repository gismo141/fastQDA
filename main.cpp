#include "view/easycoding.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    easyCoding w;
    w.show();
    
    return a.exec();
}