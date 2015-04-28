include_directories("model")
include_directories("control")
include_directories("view")

add_library(fastqdaLib
	./model/code.cpp
	./control/codeManager.cpp
	./view/codeList.cpp
	./view/codeSettings.cpp
	./view/documentList.cpp
	./view/mainWidget.cpp
	./view/fastqda.cpp)

qt5_use_modules(fastqdaLib Widgets)