#include "codeList.h"
#include "codeSettings.h"
#include "fastqda.h"

codeList::codeList(QMainWindow *parent) {
	thisParent = parent;

	myCodeManager = new codeManager();
    codeSettings *codeSetup = new codeSettings(this);

    // create code-tree-area
    codeTree = new QTreeWidget(thisParent);
    codeTree->setColumnCount(2);
    QStringList codeHeaders;
    codeHeaders << tr("Code") << tr("Color");
    codeTree->setHeaderLabels(codeHeaders);
    add = new QPushButton("Add New Code", thisParent);
    setCode = new QPushButton("Set Code", thisParent);
    codeTree->setSortingEnabled(true);
    // layout for code-list-area
    QHBoxLayout *codeManagment = new QHBoxLayout();
    codeManagment->addWidget(add);
    codeManagment->addWidget(setCode);
    codeLayout = new QVBoxLayout();
    codeLayout->addWidget(codeTree);
    codeLayout->addLayout(codeManagment);

    this->setLayout(codeLayout);

    // Signals
    QObject::connect(add, SIGNAL(clicked()), codeSetup, SLOT(exec()));
    QObject::connect(setCode, SIGNAL(clicked()), thisParent, SLOT(setCodeinSelection()));
    QObject::connect(codeTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), codeSetup, SLOT(changeParameters(QTreeWidgetItem*, int)));
}

void codeList::setCodeinSelection(void) {
    ((fastQDA *) thisParent)->setCodeinSelection(codeTree->currentItem());
}

void codeList::addCode(const QString &name, const QString &definition, const QString &anker, QColor color, const QString &headcode) {
    code *newCode = myCodeManager->getCode(name);
    // Check if code is already in the database
    if(newCode) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "WARNING!", "Overwrite existing code?", QMessageBox::No|QMessageBox::Yes);
        if (reply == QMessageBox::Yes)
            removeCode(newCode->getName());
        else
            return;
    }
    // No it's not so add it
    if(myCodeManager->addCode(name, definition, anker, color, headcode))
        updateCodeTree();
}

void codeList::removeCode(const QString &name) {
    code *codeToRemove = myCodeManager->getCode(name);
    myCodeManager->removeCode(codeToRemove);
    updateCodeTree();
}

code *codeList::getCode(QTreeWidgetItem* code) {
    return myCodeManager->getCode(code->text(0));
}

std::vector<QString> codeList::getCodeList(void) {
    std::vector<QString> codeTree;
    for (auto &code : myCodeManager->getCodes())
        codeTree.push_back(code->getName());
    return codeTree;
}

void codeList::updateCodeTree(void) {
    codeTree->clear();
    std::vector<code*> codes = myCodeManager->getCodes();
    if(!codes.empty()) {
        for (auto &code : codes) {
            addCodeToList(code);
        }
    }
}

QTreeWidgetItem *codeList::addCodeToList(code *code) {
    QTreeWidgetItem *theCodeItem = findCodeInList(code->getName());
    // Check if the code is NOT listed in the tree already
    if(!theCodeItem) {
        theCodeItem = new QTreeWidgetItem();
        theCodeItem->setBackground(1, code->getColor());
        theCodeItem->setText(0, code->getName());
        // ... check if code has a headcode
        if(code->getHeadcode()) {
            QTreeWidgetItem *theHeadcodeItem = addCodeToList(code->getHeadcode());
            theHeadcodeItem->setExpanded(true);
            theHeadcodeItem->addChild(theCodeItem);
        }
        // The code has no headcode so it is a headcode itself
        else
            codeTree->addTopLevelItem(theCodeItem);
        codeTree->resizeColumnToContents(0);
    }
    // Otherwise return it directly
    return theCodeItem;
}

QTreeWidgetItem* codeList::findCodeInList(const QString &name) {
    QList<QTreeWidgetItem *> found = codeTree->findItems(
        name,  Qt::MatchExactly | Qt::MatchRecursive, 0);
    if(found.isEmpty())
        return NULL;
    return found.first();
}