/**
 * Copyright 2015 <michael.r141@gmail.com>
 */

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QColor>

#include <poppler_qt5.h>

class document : public Poppler::Document {
 private:
  QString   m_filename;
  QString   m_metadata;
  document* m_headdocument;
 public:
  document(const QString& filename
           , const QString& metadata
           , document* headdocument);
  void      setName(const QString& filename);
  QString   getName(void);
  void      setHeaddocument(document* headdocument);
  document* getHeaddocument(void);
  void      setMetadata(const QString& metadata);
  QString   getMetadata(void);
};

#endif  // DOCUMENT_H
