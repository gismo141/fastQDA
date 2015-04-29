/**
 * Copyright 2015, <michael.r141@gmail.com>
 */

#include "view/mainWidget.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QBrush>

#include <poppler-qt5.h>

#include <iostream>

#include "view/fastQDA.h"

mainWidget::mainWidget(QWidget* parent) : QWidget(parent) {
  scrollArea = new QScrollArea(parent);
  scrollArea->setObjectName(QStringLiteral("scrollArea"));
  scrollArea->setWidgetResizable(true);
  scrollArea->setAlignment(Qt::AlignCenter);
  // create document-area
  activeDocument = new DocumentWidget();
  activeDocument->setAlignment(Qt::AlignCenter);
  scrollArea->setWidget(activeDocument);
  // layout for document-area
  QHBoxLayout* labelLayout = new QHBoxLayout();
  documentArea = new QVBoxLayout();
  documentArea->addLayout(labelLayout);
  documentArea->addWidget(scrollArea);

  this->setLayout(documentArea);
}

void mainWidget::openSelectedDocument(const QString& name) {
  if (name.isEmpty()) {
    return;
  }

  if (activeDocument->setDocument(name)) {
    reinterpret_cast<fastQDA*>(parentWidget())->setTitle(name);

  } else {
    QMessageBox::warning(this, tr("PDF Viewer - Failed to Open File"),
                         tr("The specified file could not be opened."));
  }

  // activeDocument->annotate();
}

void mainWidget::setCodeinSelection(QTreeWidgetItem* currentItem) {
  if (!currentItem) {
    return;
  }

  QTextCharFormat code;
  QColor codeColor = currentItem->background(1).color();
  QBrush* codeBrush = new QBrush(codeColor, Qt::SolidPattern);
  code.setBackground(*codeBrush);

  // QTextCursor cursor = activeDocument->textCursor();

  // if (!cursor.hasSelection()) {
  //     cursor.select(QTextCursor::WordUnderCursor);
  // }

  // cursor.mergeCharFormat(code);
  // activeDocument->mergeCurrentCharFormat(code);
}
