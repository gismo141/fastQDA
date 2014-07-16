#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QDesktopWidget>
#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QTreeWidget>

#include "../control/codeManager.h"
/**
 * @brief This function represents the working-area for the client.
 * @details The area is divided in 3-horizontal-panes:
 * <ol>
 * <li>The imported documents in the database</li>
 * <li>The opened document in the coding-window</li>
 * <li>The list of all created and activated codes</li>
 * </ol>
 * The left- and right-most pane can be collapsed to provide the client with a larger working area.
 */
class mainWidget : public QWidget {
    Q_OBJECT
private:
    // Code-Manager
    codeManager *myCodeManager;
    // Coding-Window
    QLabel *activeDocumentLabel;
    QTextEdit *activeDocument;
    // Codelist-Area
    QTreeWidget *codeList;
    QLabel *colorLabel;
    QPushButton *addCode;
    QPushButton *setCode;
    QPushButton *removeCode;
public:
    /**
     * @brief std. ctor
     */
    mainWidget(QWidget *parent = 0, QDesktopWidget *dw = 0);
    /**
     * @brief std. dtor
     */
    ~mainWidget() {}
    QTreeWidgetItem *addCodeToList(code *code);
    QTreeWidgetItem *findCodeInList(const QString &name);
    std::vector<QString> getCodeList(void);
public slots:
    /**
     * @brief This function is used to update the coding-window.
     * @details [long description]
     */
    void updateActiveDocument(const QString& name);
    void setCodeinSelection(void);
    void addNewCode(const QString &name, const QString &definition, const QString &anker, QColor color, const QString &headcode);
    void removeThisCode(void);
    code *getCode(QTreeWidgetItem* code);
};

#endif // MAIN_WIDGET_H