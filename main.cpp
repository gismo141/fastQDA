/**
 * Copyright 2015 <michael.r141@gmail.com>
 */

#include <QApplication>

#include "view/fastQDA.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  fastQDA mainWindow;
  mainWindow.show();

  return app.exec();
}
