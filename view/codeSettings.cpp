#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QFontMetrics>
#include <QTreeWidgetItem>

#include "codeSettings.h"

codeSettings::codeSettings(QWidget *parent) : QDialog(parent) {
	thisParent = parent;
    // set-up all labels
    int fixedWidth = 100;
    l_name = new QLabel("Code:", this);
    l_name->setFixedWidth(fixedWidth);
	l_definition = new QLabel("Definition:", this);
	l_definition->setFixedWidth(fixedWidth);
	l_anker = new QLabel("Anker:", this);
	l_anker->setFixedWidth(fixedWidth);
	l_headcode = new QLabel("Headcode:", this);
	l_headcode->setFixedWidth(fixedWidth);

	// set-up all input-areas
	m_name = new QPlainTextEdit(this);
    m_name->setPlainText("The name of the code");
	setHeight(m_name, 2);
    m_definition = new QPlainTextEdit(this);
    m_definition->setPlainText("The definition of that code");
    setHeight(m_definition, 3);
    m_anker = new QPlainTextEdit(this);
    m_anker->setPlainText("The citation that represents the code");
    setHeight(m_anker, 3);
    m_headcode = new QComboBox(this);
    m_headcode->setEditable(false);

    // set-up all buttons
    cancel = new QPushButton("Cancel", this);
    changeColor = new QPushButton("Change Color", this);
    addCode = new QPushButton("Save", this);

    // Horizontal layouts
    QHBoxLayout *name = new QHBoxLayout();
    name->addWidget(l_name);
    name->addWidget(m_name);
    QHBoxLayout *definition = new QHBoxLayout();
    definition->addWidget(l_definition);
    definition->addWidget(m_definition);
    QHBoxLayout *anker = new QHBoxLayout();
    anker->addWidget(l_anker);
    anker->addWidget(m_anker);
    QHBoxLayout *headcode = new QHBoxLayout();
    headcode->addWidget(l_headcode);
    headcode->addWidget(m_headcode);
	QHBoxLayout *buttons = new QHBoxLayout();
	buttons->addWidget(cancel);
    buttons->addWidget(changeColor);
    buttons->addWidget(addCode);

    // Signals
    QObject::connect(changeColor, SIGNAL(clicked()), this, SLOT(setCodeColor()));
    QObject::connect(addCode, SIGNAL(clicked()), this, SLOT(addNewCode()));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(close()));

    // create main-layout
    QVBoxLayout* settingsLayout = new QVBoxLayout();
    settingsLayout->addLayout(name);
    settingsLayout->addLayout(definition);
    settingsLayout->addLayout(anker);
    settingsLayout->addLayout(headcode);
    settingsLayout->addLayout(buttons);
    QWidget::setLayout(settingsLayout);
}

void codeSettings::updateSettings(void) {
	m_headcode->clear();
	m_headcode->addItem("No Headcode", "No Headcode");
	for (auto headcode : ((mainWidget *) thisParent)->getCodeList())
		m_headcode->addItem(headcode, headcode);
	exec();
}

void codeSettings::setHeight(QPlainTextEdit* edit, int nRows) {
	QFontMetrics m(edit->font());
	int rowHeight = m.lineSpacing();
	edit -> setFixedHeight(nRows * rowHeight);
}

void codeSettings::setCodeColor(void) {
	QColor color = QColorDialog::getColor(Qt::green, this);
    if (color.isValid())
    {
   		m_color = color;
        l_name->setPalette(QPalette(color));
        l_name->setAutoFillBackground(true);
    }
}

void codeSettings::addNewCode(void) {
	((mainWidget *) thisParent)->addNewCode(m_name->toPlainText()
											, m_definition->toPlainText()
											, m_anker->toPlainText()
											, m_color
											, m_headcode->currentText());
	m_headcode->addItem(m_name->toPlainText(), m_name->toPlainText());
}

void codeSettings::changeParameters(QTreeWidgetItem* oldCodeItem, int column) {
	code *newCode = ((mainWidget *) thisParent)->getCode(oldCodeItem);

	m_name->setPlainText(newCode->getName());
	m_definition->setPlainText(newCode->getDefinition());
	m_anker->setPlainText(newCode->getAnker());
	if(newCode->getHeadcode())
		m_headcode->setCurrentIndex(m_headcode->findData(newCode->getHeadcode()->getName()));
	else
		m_headcode->setCurrentIndex(m_headcode->findData("No Headcode"));

    m_color = newCode->getColor();
 	l_name->setPalette(QPalette(m_color));
 	l_name->setAutoFillBackground(true);
	exec();
}