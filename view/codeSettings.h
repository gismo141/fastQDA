#ifndef CODE_SETTINGS_H
#define CODE_SETTINGS_H

#include <QDialog>
#include <QWidget>
#include <QPlainTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QColor>

#include "mainWidget.h"

class codeSettings : public QDialog {
    Q_OBJECT
private:
    QWidget *thisParent;
	QLabel *l_name;
	QLabel *l_definition;
	QLabel *l_anker;
	QLabel *l_headcode;
	QPlainTextEdit *m_name;
    QPlainTextEdit *m_definition;
    QPlainTextEdit *m_anker;
    QColor m_color;
    QComboBox *m_headcode;
	QPushButton *addCode;
    QPushButton *cancel;
    QPushButton *changeColor;
    void setHeight(QPlainTextEdit* edit, int nRows);
public:
	codeSettings(QWidget *parent = 0);
public slots:
	void setCodeColor(void);
	void addNewCode(void);
	void changeParameters(QTreeWidgetItem*, int);
	void updateSettings(void);
};

#endif // CODE_SETTINGS_H