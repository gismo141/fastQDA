/**
 * Copyright 2015, <michael.r141@gmail.com>
 */

#include "view/mainWidget.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QBrush>

#include <poppler-qt5.h>

#include <iostream>

mainWidget::mainWidget(QWidget* parent) : QWidget(parent) {
    // create document-area
    activeDocumentLabel = new QLabel("Active Document", this);
    activeDocumentLabel->setAlignment(Qt::AlignCenter);
    activeDocument = new QLabel("no document loaded", this);
    activeDocument->setAlignment(Qt::AlignCenter);
    // layout for document-area
    QHBoxLayout* labelLayout = new QHBoxLayout();
    labelLayout->addWidget(activeDocumentLabel);
    documentArea = new QVBoxLayout();
    documentArea->addLayout(labelLayout);
    documentArea->addWidget(activeDocument);

    this->setLayout(documentArea);
}

void mainWidget::openSelectedDocument(const QString& name) {
    activeDocumentLabel->setText(name);

    Poppler::Document* document = Poppler::Document::load(name);

    if (!document || document->isLocked()) {
        QMessageBox* myDialog = new QMessageBox(QMessageBox::Critical
                                                , "Error!"
                                                , "Can't open: " + name
                                                , QMessageBox::Ok);
        myDialog->exec();
    }

    // Paranoid safety check
    if (document == 0) {
        std::cout << "Document not available!" << std::endl;
        return;
    }

    // Access page of the PDF file
    // Document starts at page 0
    uint32_t pageNumber = 1;
    Poppler::Page* pdfPage
        = document->page(pageNumber);

    if (pdfPage == 0) {
        std::cout << "Page not available!" << std::endl;
        return;
    }

    // Generate a QImage of the rendered page
    QImage image = pdfPage->renderToImage(0.75 * physicalDpiX()
                                          , 0.75 * physicalDpiY());

    // if (image.isNull()) {
    //     std::cout << "Image not available!" << std::endl;
    //     return;
    // }

    // // ... use image ...
    // activeDocument->setPixmap(QPixmap::fromImage(image));
}

void mainWidget::setCodeinSelection(QTreeWidgetItem* currentItem) {
    if (!currentItem) {
        return;
    }

    QTextCharFormat code;
    QColor codeColor = currentItem->background(1).color();
    QBrush* codeBrush = new QBrush(codeColor, Qt::SolidPattern);
    code.setBackground(*codeBrush);

    // QTextCursor cursor = activeDocument->textCursor();

    // if (!cursor.hasSelection()) {
    //     cursor.select(QTextCursor::WordUnderCursor);
    // }

    // cursor.mergeCharFormat(code);
    // activeDocument->mergeCurrentCharFormat(code);
}
