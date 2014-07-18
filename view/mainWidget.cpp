#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QBrush>

#include "mainWidget.h"

mainWidget::mainWidget(QWidget *parent) : QWidget(parent) {
    // create document-area
    activeDocumentLabel = new QLabel("Active Document", this);
    activeDocumentLabel->setAlignment(Qt::AlignCenter);
    activeDocument = new QTextEdit(this);
    activeDocument->setReadOnly(true);
    activeDocument->setTextInteractionFlags(activeDocument->textInteractionFlags() | Qt::TextSelectableByKeyboard);
    // layout for document-area
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addWidget(activeDocumentLabel);
    documentArea = new QVBoxLayout();
	documentArea->addLayout(labelLayout);
    documentArea->addWidget(activeDocument);

    this->setLayout(documentArea);
};

void mainWidget::openSelectedDocument(const QString& name) {
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

void mainWidget::setCodeinSelection(QTreeWidgetItem* currentItem) {
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