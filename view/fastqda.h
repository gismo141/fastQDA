#ifndef FASTQDA_H
#define FASTQDA_H

#include <QMainWindow>

#include <QFileDialog>
#include <QMessageBox>
#include <QString>

#include "mainWidget.h"

class QFileDialog;
class QString;

/**
 * @brief This class represents the main-window and its menubar.
 * @details Every action triggered via the menubar is processed here. Also it is responsible for all the systemcalls like quit.
 */
class fastQDA : public QMainWindow {
    Q_OBJECT
private:
    /**
     * @brief This function creates the menubar and its entries.
     * @details All global functions of the program should be accessable from here. 
     */
    void createMenuBar(void);
protected:
    QFileDialog *myFileDialog;
    mainWidget *myMainWidget;
public:
    /**
     * @brief std. ctor
     */
    fastQDA();
    /**
     * @brief std. dtor
     */
    ~fastQDA() {}

public slots:
    /**
     * @brief This function imports a file into the local database.
     * @details If the selected file is a *.pdf its text is extracted with `pdftotext`, after that the file is saved in the local database and its content will be sent to the mainWidget's coding-pane.
     * 
     * @param name The pointer to the selected file to import.
     */
    void importFile(const QString& name);
    /**
     * @brief This function shows the program in fullscreen-mode.
     * @details No explicit information atm.
     */
    void showFullScreen(void) {
        this->showFullScreen();
    }
    /**
     * @brief This function shows the program in the standard-size-window.
     * @details No explicit information atm.
     */
    void showNormal(void) {
        this->showNormal();
    }
    /**
     * @brief This function shows a messagebox.
     * @details At the moment there is only a `about`-box implemented.
     */
    void messageBox(void) {
        QMessageBox* myDialog = new QMessageBox(QMessageBox::Information,
        "fastQDA", "fastQDA\n a fast and simple alternative to MaxQDA", QMessageBox::Ok);
        myDialog->exec();
    }
};

#endif // FASTQDA_H