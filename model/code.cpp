#include <code.h>

code::code(const QString &name, const QString &definition, const QString &anker, QColor color, code *headcode) {
	m_name = name;
	m_definition = definition;
	m_anker = anker;
	m_color = color;
	m_headcode = headcode;
};

void code::setName(const QString &name) {
	m_name = name;
}

QString code::getName(void) {
	return m_name;
}

void code::setDefinition(const QString &definition) {
	m_definition = definition;
}

QString code::getDefinition(void) {
	return m_definition;
}

void code::setAnker(const QString &anker) {
	m_anker = anker;
}

QString code::getAnker(void) {
	return m_anker;
}

void code::setColor(QColor color) {
	m_color = color;
}

QColor code::getColor(void) {
	return m_color;
}

void code::setHeadcode(code *headcode) {
	m_headcode = headcode;
}

code *code::getHeadcode(void) {
	return m_headcode;
}