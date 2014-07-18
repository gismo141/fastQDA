#include "view/fastQDA.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    fastQDA mainWindow;
    mainWindow.show();
    
    return app.exec();
}