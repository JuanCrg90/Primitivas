QT+=core gui opengl
LIBS+= -lm -lglut -lGLU

HEADERS += \
    glvisual.h \
    mainwindow.h \
    primitives.h \
    MyTree/mytree.h

SOURCES += \
    glvisual.cpp \
    main.cpp \
    mainwindow.cpp \
    primitives.cpp

FORMS += \
    mainwindow.ui

OTHER_FILES += \
    README


