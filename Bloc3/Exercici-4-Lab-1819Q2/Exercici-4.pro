TEMPLATE = app
QT += opengl

INCLUDEPATH += /usr/include/glm
INCLUDEPATH += ./Model

FORMS += MyForm.ui

HEADERS += MyForm.h MyGLWidget.h myButton.h

SOURCES += main.cpp MyForm.cpp MyGLWidget.cpp ./Model/model.cpp myButton.cpp
