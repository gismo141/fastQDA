/**
 * Copyright 2015 <michael.r141@gmail.com>
 */

#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QScrollArea>
#include <QTreeWidgetItem>

#include "view/documentwidget.h"

class mainWidget : public QWidget {
  Q_OBJECT
 private:
  QVBoxLayout* documentArea;
  QLabel* activeDocumentLabel;
  QScrollArea* scrollArea;
  DocumentWidget* activeDocument;
 public:
  /**
   * @brief std. ctor
   */
  explicit mainWidget(QWidget* parent = 0);
  /**
   * @brief std. dtor
   */
  ~mainWidget() {}
 public slots:
  /**
   * @brief This function is used to update the coding-window.
   * @details [long description]
   */
  void openSelectedDocument(const QString& name);
  void setCodeinSelection(QTreeWidgetItem* currentItem);
};

#endif  // MAIN_WIDGET_H
