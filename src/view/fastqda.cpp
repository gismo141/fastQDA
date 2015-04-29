/**
 * Copyright 2015 <michael.r141@gmail.com>
 */

#include <QApplication>

#include <QStringList>
#include <QHeaderView>

#include "view/fastQDA.h"

fastQDA::fastQDA() : QMainWindow(NULL) {
  setWindowTitle("New Project - fastQDA");

  myMenu = new QMenuBar(this);
  myMenu->addMenu(setupFileMenu());
  myMenu->addMenu(setupEditMenu());
  myMenu->addMenu(setupViewMenu());
  myMenu->addMenu(setupHelpMenu());
  this->setMenuBar(myMenu);

  setupDocumentBrowser();
  myMainWidget = new mainWidget(this);
  setupCodeBrowser();

  this->setCentralWidget(myMainWidget);
}

/*
 *
 * SETUP ALL MENUS
 *
 */

QMenu* fastQDA::setupFileMenu(void) {
  // Install Project Dialog
  myProjectDialog = new QFileDialog(this);
  myProjectDialog->setNameFilter("Project (*.db *.txt *fastqda-project)");
  // Install File Dialog
  myFileDialog = new QFileDialog(this);
  myFileDialog->setNameFilter("Documents (*.pdf *.txt *html)");

  QMenu* myFileMenu  = new QMenu("File", this);

  myFileMenu->addAction("Open Project", myProjectDialog, SLOT(exec())
                        , Qt::CTRL + Qt::Key_O);
  myFileMenu->addAction("Import File", myFileDialog, SLOT(exec())
                        , Qt::CTRL + Qt::Key_I);
  myFileMenu->addAction("Save Project", this, SLOT(saveProject())
                        , Qt::CTRL + Qt::Key_S);
  myFileMenu->addSeparator();
  myFileMenu->addAction("Close", this, SLOT(close()), Qt::CTRL + Qt::Key_Q);

  /* Connect Signals */
  connect(myFileDialog, SIGNAL(fileSelected(const QString&)), this
          , SLOT(importFile(const QString&)));

  return myFileMenu;
}

QMenu* fastQDA::setupEditMenu(void) {
  QMenu* myEditMenu  = new QMenu("Edit", this);
  myEditMenu->addAction("Undo", this, SLOT(showFullScreen())
                        , Qt::CTRL + Qt::Key_Z);
  myEditMenu->addAction("Repeat", this, SLOT(showNormal())
                        , Qt::CTRL + Qt::Key_Y);
  return myEditMenu;
}

QMenu* fastQDA::setupViewMenu(void) {
  QMenu* myViewMenu  = new QMenu("View", this);
  myViewMenu->addAction("Fullscreen", this, SLOT(showFullScreen())
                        , Qt::CTRL + Qt::Key_F);
  myViewMenu->addAction("Windowed", this, SLOT(showNormal())
                        , Qt::CTRL + Qt::Key_N);
  return myViewMenu;
}

QMenu* fastQDA::setupHelpMenu(void) {
  QMenu* myHelpMenu  = new QMenu("Help", this);
  myHelpMenu->addAction("About...", this, SLOT(messageBox())
                        , Qt::CTRL + Qt::Key_H);
  return myHelpMenu;
}

/*
 *
 * SETUP THE DOCUMENT-BROWSER
 *
 */

void fastQDA::setupDocumentBrowser(void) {
  documentBrowser = new QDockWidget(tr("Document-Browser"), this);
  documentBrowser->setAllowedAreas(
    Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  addDockWidget(Qt::LeftDockWidgetArea, documentBrowser);

  documentList* docs = new documentList(this);
  documentBrowser->setWidget(docs);
}

void fastQDA::importFile(const QString& name) {
  myMainWidget->openSelectedDocument(name);
}

/*
 *
 * SETUP THE CODE-BROWSER
 *
 */

void fastQDA::setupCodeBrowser(void) {
  codeBrowser = new QDockWidget(tr("Code-Browser"), this);
  codeBrowser->setAllowedAreas(
    Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  addDockWidget(Qt::RightDockWidgetArea, codeBrowser);

  codeList* codes = new codeList(this);
  codeBrowser->setWidget(codes);
}

void fastQDA::setCodeinSelection(QTreeWidgetItem* currentItem) {
  myMainWidget->setCodeinSelection(currentItem);
}

/*
 *
 * PROJECT INTERACTION
 *
 */

void fastQDA::saveProject(void) {
}

void fastQDA::setTitle(const QString& title) {
  this->setWindowTitle(title + " - New Project - fastQDA");
}
