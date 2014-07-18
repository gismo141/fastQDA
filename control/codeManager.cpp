#include <QMessageBox>

#include <codeManager.h>

codeManager::codeManager() {
}

code* codeManager::addCode(const QString &name, const QString &definition, const QString &anker, QColor color, const QString &headcode) {
	if(headcode == "No Headcode") {
		code* newCode = new code(name, definition, anker, color, 0);
		m_codes.push_back(newCode);
		return newCode;
	}
	else {
		code* newCode = new code(name, definition, anker, color, getCode(headcode));
		m_codes.push_back(newCode);
		return newCode;
	}
}

std::vector<code *> codeManager::getCodes(void) {
	return m_codes;
}

code* codeManager::getCode(const QString &name) {
	for (auto &code : m_codes) {
		if (code->getName() == name)
			return code;
	}
	return 0;
}

void codeManager::removeCode(code *codeToRemove) {
	for (auto &code : m_codes) {
		if (code->getHeadcode() == codeToRemove)
			code->setHeadcode(codeToRemove->getHeadcode());
	}
	// Erase code from code-vector by value
	m_codes.erase(std::remove(m_codes.begin(), m_codes.end(), codeToRemove), m_codes.end());
	delete codeToRemove;
}