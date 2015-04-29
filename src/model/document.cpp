/**
 * Copyright 2015 <michael.r141@gmail.com>
 */

#include "model/document.h"

document::document(const QString& filename
                   , const QString& metadata
                   , document* headdocument) {
  m_filename = filename;
  m_metadata = metadata;
  m_headdocument = headdocument;
}

void document::setName(const QString& filename) {
  m_filename = filename;
}

QString document::getName(void) {
  return m_filename;
}

void document::setMetadata(const QString& metadata) {
  m_metadata = metadata;
}

QString document::getMetadata(void) {
  return m_metadata;
}

void document::setHeaddocument(document* headdocument) {
  m_headdocument = headdocument;
}

document* document::getHeaddocument(void) {
  return m_headdocument;
}
