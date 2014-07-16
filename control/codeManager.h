#ifndef CODE_MANAGER_H
#define CODE_MANAGER_H

#include <vector>

#include "../model/code.h"

class codeManager {
private:
	std::vector<code *> m_codes;
protected:

public:
	codeManager();
public slots:
	code* addNewCode(const QString &name, const QString &definition, const QString &anker, QColor color, const QString &headcode);
	void removeCode(const QString &name);
	std::vector<code *> getCodes(void);
	code *getCode(const QString &name);
};

#endif // CODE_MANAGER_H