/**
 * Copyright 2015 <michael.r141@gmail.com>
 */

#include "model/code.h"

code::code(const QString& name, const QString& definition
           , const QString& anchor, QColor color, code* headcode) {
  m_name = name;
  m_definition = definition;
  m_anchor = anchor;
  m_color = color;
  m_headcode = headcode;
}

void code::setName(const QString& name) {
  m_name = name;
}

QString code::getName(void) {
  return m_name;
}

void code::setDefinition(const QString& definition) {
  m_definition = definition;
}

QString code::getDefinition(void) {
  return m_definition;
}

void code::setAnchor(const QString& anchor) {
  m_anchor = anchor;
}

QString code::getAnchor(void) {
  return m_anchor;
}

void code::setColor(QColor color) {
  m_color = color;
}

QColor code::getColor(void) {
  return m_color;
}

void code::setHeadcode(code* headcode) {
  m_headcode = headcode;
}

code* code::getHeadcode(void) {
  return m_headcode;
}
