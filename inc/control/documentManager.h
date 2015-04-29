/**
 * Copyright 2015 <michael.r141@gmail.com>
 */

#ifndef DOCUMENT_MANAGER_H
#define DOCUMENT_MANAGER_H

#include <QWidget>
#include <vector>

#include "model/document.h"

class documentManager : public QWidget {
  Q_OBJECT
 private:
  std::vector<document*> m_documents;
 protected:
 public:
  documentManager();
 public slots:
  document* addDocument(const QString& filename
                        , const QString& headgroup
                        , const QString& metadata);
  void removeDocument(document* codeToRemove);
  std::vector<document*> getDocuments(void);
  document* getDocument(const QString& name);
};

#endif  // DOCUMENT_MANAGER_H
