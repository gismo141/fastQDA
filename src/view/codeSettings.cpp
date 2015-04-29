/**
 * Copyright 2015 <michael.r141@gmail.com>
 */

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QFontMetrics>

#include <vector>

#include "view/codeSettings.h"
#include "view/codeList.h"

codeSettings::codeSettings(QWidget* parent) : QDialog(parent) {
  thisParent = parent;
  // set-up all labels
  int fixedWidth = 100;
  l_name = new QLabel("Code:", this);
  l_name->setFixedWidth(fixedWidth);
  l_definition = new QLabel("Definition:", this);
  l_definition->setFixedWidth(fixedWidth);
  l_anchor = new QLabel("Anchor:", this);
  l_anchor->setFixedWidth(fixedWidth);
  l_headcode = new QLabel("Headcode:", this);
  l_headcode->setFixedWidth(fixedWidth);

  // set-up all input-areas
  m_name = new QPlainTextEdit(this);
  m_name->setPlainText("The name of the code");
  setHeight(m_name, 2);
  m_definition = new QPlainTextEdit(this);
  m_definition->setPlainText("The definition of that code");
  setHeight(m_definition, 3);
  m_anchor = new QPlainTextEdit(this);
  m_anchor->setPlainText("The citation that represents the code");
  setHeight(m_anchor, 3);
  m_headcode = new QComboBox(this);
  m_headcode->setEditable(false);
  updateCodeList();

  // set-up all buttons
  b_cancel = new QPushButton("Cancel", this);
  b_remove = new QPushButton("Remove", this);
  b_changeColor = new QPushButton("Change Color", this);
  b_save = new QPushButton("Save", this);

  // Horizontal layouts
  QHBoxLayout* name = new QHBoxLayout();
  name->addWidget(l_name);
  name->addWidget(m_name);
  QHBoxLayout* definition = new QHBoxLayout();
  definition->addWidget(l_definition);
  definition->addWidget(m_definition);
  QHBoxLayout* anker = new QHBoxLayout();
  anker->addWidget(l_anchor);
  anker->addWidget(m_anchor);
  QHBoxLayout* headcode = new QHBoxLayout();
  headcode->addWidget(l_headcode);
  headcode->addWidget(m_headcode);
  QHBoxLayout* buttons = new QHBoxLayout();
  buttons->addWidget(b_save);
  buttons->addWidget(b_changeColor);
  buttons->addWidget(b_remove);
  buttons->addWidget(b_cancel);

  // Signals
  QObject::connect(b_changeColor, SIGNAL(clicked()), this
                   , SLOT(setCodeColor()));
  QObject::connect(b_save, SIGNAL(clicked()), this, SLOT(saveCode()));
  QObject::connect(b_remove, SIGNAL(clicked()), this, SLOT(removeCode()));
  QObject::connect(b_cancel, SIGNAL(clicked()), this, SLOT(close()));

  // create main-layout
  QVBoxLayout* settingsLayout = new QVBoxLayout();
  settingsLayout->addLayout(name);
  settingsLayout->addLayout(definition);
  settingsLayout->addLayout(anker);
  settingsLayout->addLayout(headcode);
  settingsLayout->addLayout(buttons);
  QWidget::setLayout(settingsLayout);
}

/*
 *
 * WIDGET-SETTINGS
 *
 */

void codeSettings::setHeight(QPlainTextEdit* edit, int nRows) {
  QFontMetrics m(edit->font());
  int rowHeight = m.lineSpacing();
  edit -> setFixedHeight(nRows * rowHeight);
}

void codeSettings::updateCodeList(void) {
  m_headcode->clear();
  m_headcode->addItem("No Headcode", "No Headcode");
  std::vector<QString> codelist
    = reinterpret_cast<codeList*>(thisParent)->getCodeList();

  for (auto& code : codelist) {
    m_headcode->addItem(code, code);
  }
}

void codeSettings::changeParameters(QTreeWidgetItem* oldCodeItem, int column) {
  code* newCode
    = reinterpret_cast<codeList*>(thisParent)->getCode(oldCodeItem);

  m_name->setPlainText(newCode->getName());
  m_definition->setPlainText(newCode->getDefinition());
  m_anchor->setPlainText(newCode->getAnchor());

  if (newCode->getHeadcode()) {
    m_headcode->setCurrentIndex(m_headcode->findData(
                                  newCode->getHeadcode()->getName()));

  } else {
    m_headcode->setCurrentIndex(m_headcode->findData("No Headcode"));
  }

  m_color = newCode->getColor();
  l_name->setPalette(QPalette(m_color));
  l_name->setAutoFillBackground(true);
  exec();
}

/*
 *
 * CODE-MANIPULATION
 *
 */

void codeSettings::setCodeColor(void) {
  QColor color = QColorDialog::getColor(Qt::green, this);

  if (color.isValid()) {
    m_color = color;
    l_name->setPalette(QPalette(color));
    l_name->setAutoFillBackground(true);
  }
}

void codeSettings::saveCode(void) {
  reinterpret_cast<codeList*>(thisParent)->addCode(m_name->toPlainText()
      , m_definition->toPlainText()
      , m_anchor->toPlainText()
      , m_color
      , m_headcode->currentText());
  updateCodeList();
}

void codeSettings::removeCode(void) {
  reinterpret_cast<codeList*>(thisParent)->removeCode(m_name->toPlainText());
  close();
}
