#include "documentList.h"

documentList::documentList(QMainWindow *parent) {
	thisParent = parent;

	// create document-browser
    documentTree = new QTreeWidget(thisParent);
    documentTree->setColumnCount(2);
    QStringList documentHeaders;
    documentHeaders << tr("Documents") << tr("active");
    documentTree->setHeaderLabels(documentHeaders);
    // layout for document-browser
    documentLayout = new QVBoxLayout();
    documentLayout->addWidget(documentTree);

    this->setLayout(documentLayout);
}