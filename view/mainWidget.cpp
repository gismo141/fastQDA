#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSize>
#include <QRect>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QBrush>
#include <QStringList>
#include <QHeaderView>

#include "mainWidget.h"
#include "view/codeSettings.h"

mainWidget::mainWidget(QWidget *parent, QDesktopWidget *dw) : QWidget(parent) {
    // set geometry
    QRect screenGeometry = dw->availableGeometry(-1);
    this->setGeometry(0, 0, screenGeometry.width(),screenGeometry.height()*0.99);

    myCodeManager = new codeManager();
    codeSettings *codeSetup = new codeSettings(this);

    // create coding-area
    activeDocumentLabel = new QLabel("Document-Browser", this);
    activeDocument = new QTextEdit(this);
    activeDocument->setText("Test-Zitat");
    activeDocument->setReadOnly(true);
    activeDocument->setTextInteractionFlags(activeDocument->textInteractionFlags() | Qt::TextSelectableByKeyboard);
    // layout for coding-area
    QVBoxLayout* documentArea = new QVBoxLayout();
	documentArea->addWidget(activeDocumentLabel);
    documentArea->addWidget(activeDocument);

    // create code-list-area
    colorLabel = new QLabel("Code-Browser", this);
    codeList = new QTreeWidget(this);
    codeList->setColumnCount(2);
    QStringList headers;
    headers << tr("Code") << tr("Color");
    codeList->setHeaderLabels(headers);
    codeList->header()->resizeSection(1, codeList->header()->sectionSize(0)*0.25);
    add = new QPushButton("Add New Code", this);
    setCode = new QPushButton("Set Code", this);
    codeList->setSortingEnabled(true);
    // layout for code-settings
    QHBoxLayout *codeSettings = new QHBoxLayout();
    codeSettings->addWidget(codeList);
    // layout for code-list-area
    QHBoxLayout *codeManagment = new QHBoxLayout();
    codeManagment->addWidget(add);
    codeManagment->addWidget(setCode);
    QVBoxLayout *codeArea = new QVBoxLayout();
    codeArea->addWidget(colorLabel);
    codeArea->addLayout(codeSettings);
    codeArea->addLayout(codeManagment);
    // Signals
    QObject::connect(add, SIGNAL(clicked()), codeSetup, SLOT(exec()));
    QObject::connect(setCode, SIGNAL(clicked()), this, SLOT(setCodeinSelection()));
    QObject::connect(codeList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), codeSetup, SLOT(changeParameters(QTreeWidgetItem*, int)));

    // create main-layout
    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addLayout(documentArea);
    mainLayout->addLayout(codeArea);
    QWidget::setLayout(mainLayout);
};

/*
 *
 * CODE MANIUPULATION
 *
 */

void mainWidget::addCode(const QString &name, const QString &definition, const QString &anker, QColor color, const QString &headcode) {
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

void mainWidget::removeCode(const QString &name) {
    code *codeToRemove = myCodeManager->getCode(name);
    myCodeManager->removeCode(codeToRemove);
    updateCodeTree();
}

code *mainWidget::getCode(QTreeWidgetItem* code) {
    return myCodeManager->getCode(code->text(0));
}

std::vector<QString> mainWidget::getCodeList(void) {
    std::vector<QString> codeList;
    for (auto &code : myCodeManager->getCodes())
        codeList.push_back(code->getName());
    return codeList;
}

void mainWidget::updateCodeTree(void) {
    codeList->clear();
    std::vector<code*> codes = myCodeManager->getCodes();
    if(!codes.empty()) {
        for (auto &code : codes) {
            addCodeToList(code);
        }
    }
}

QTreeWidgetItem *mainWidget::addCodeToList(code *code) {
    QTreeWidgetItem *theCodeItem = findCodeInList(code->getName());
    // Check if the code is listed in the tree already
    if(theCodeItem) {
        return theCodeItem;
    // No it's not so ...
    } else {
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
            codeList->addTopLevelItem(theCodeItem);
        codeList->resizeColumnToContents(0);
    }
}

QTreeWidgetItem* mainWidget::findCodeInList(const QString &name) {
    QList<QTreeWidgetItem *> found = codeList->findItems(
        name,  Qt::MatchExactly | Qt::MatchRecursive, 0);
    if(found.isEmpty())
        return NULL;
    return found.first();
}

/*
 *
 * TEXT MANIPULATION
 *
 */

void mainWidget::updateActiveDocument(const QString& name) {
    activeDocumentLabel->setText(name);

    QFile file(name);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox* myDialog = new QMessageBox(QMessageBox::Critical, "Error!", "Can't open the given file!", QMessageBox::Ok);
        myDialog->exec();
    }

    QTextStream in(&file);
    QString allLines;

    while(!in.atEnd()) {
        allLines.append(in.readLine());
    }

    file.close();
    QString textfield = allLines;
    activeDocument->setHtml(textfield);
};

void mainWidget::setCodeinSelection(void) {
    QTreeWidgetItem* currentItem = codeList->currentItem();

    if (!currentItem)
        return;

    QTextCharFormat code;
    QColor codeColor = currentItem->background(1).color();
    QBrush *codeBrush = new QBrush(codeColor, Qt::SolidPattern);
    code.setBackground(*codeBrush);
    
    QTextCursor cursor = activeDocument->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(code);
    activeDocument->mergeCurrentCharFormat(code);
}