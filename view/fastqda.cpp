#include <QApplication>

#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QRect>

#include "fastQDA.h"

fastQDA::fastQDA() : QMainWindow(NULL) {
    createMenuBar();
    QDesktopWidget dw;
    QRect screenGeometry = dw.availableGeometry(-1);
    this->setFixedSize(screenGeometry.width(),screenGeometry.height());
    myMainWidget = new mainWidget(this, &dw);
};

void fastQDA::createMenuBar(void) {
    /* Install File Dialog */
    myFileDialog = new QFileDialog(this);
    myFileDialog->setNameFilter("Documents (*.pdf *.txt *html)");

    /* Create Main Menu */
    QMenuBar* myMenu    = new QMenuBar(this);
    QMenu*  myFileMenu  = new QMenu("File", this);
    QMenu*  myViewMenu  = new QMenu("View", this);
    QMenu*  myHelpMenu  = new QMenu("Help", this);

    myFileMenu->addAction("Import File", myFileDialog, SLOT(exec()),
                            Qt::CTRL + Qt::Key_O);
    myFileMenu->addAction("Close", this, SLOT(close()),
                            Qt::CTRL + Qt::Key_Q);
    myViewMenu->addAction("Fullscreen", this, SLOT(showFullScreen()),
                            Qt::CTRL + Qt::Key_F);
    myViewMenu->addAction("Windowed", this, SLOT(showNormal()),
                            Qt::CTRL + Qt::Key_N);
    myHelpMenu->addAction("About...", this, SLOT(messageBox()),
                            Qt::CTRL + Qt::Key_H);
    myMenu->addMenu(myFileMenu);
    myMenu->addMenu(myViewMenu);
    myMenu->addMenu(myHelpMenu);
    this->setMenuBar(myMenu);

    /* Connect Signals */
    connect (myFileDialog, SIGNAL(fileSelected(const QString&)), this,
                        SLOT(importFile(const QString&)));
}

void fastQDA::importFile(const QString& name) {
    myMainWidget->updateActiveDocument(name);
}