#include <code.h>

code::code(const QString &name, const QString &definition, const QString &anker, QColor color, code *headcode) {
	this->m_name = name;
	this->m_definition = definition;
	this->m_anker = anker;
	this->m_color = color;
	this->m_headcode = headcode;
};

void code::setName(const QString &name) {
	this->m_name = name;
}

QString code::getName(void) {
	return m_name;
}

void code::setDefinition(const QString &definition) {
	this->m_definition = definition;
}

QString code::getDefinition(void) {
	return m_definition;
}

void code::setAnker(const QString &anker) {
	this->m_anker = anker;
}

QString code::getAnker(void) {
	return m_anker;
}

void code::setColor(QColor color) {
	this->m_color = color;
}

QColor code::getColor(void) {
	return m_color;
}

void code::setHeadcode(code *headcode) {
	this->m_headcode = headcode;
}

code *code::getHeadcode(void) {
	return m_headcode;
}