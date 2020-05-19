QT       += core gui

QT += network
QT += gamepad

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
win32 {

## Link to Xinput
message(Using Win32)

contains(QT_ARCH, i386) {
 BIT_BUILD = x86
}else{
 BIT_BUILD = x64
}

message(Bit build: $$BIT_BUILD)

# Find the lib path
XinputPath = $$(WindowsSdkDir)\\Lib\\$$(WindowsSdkLibVersion)\\um\\$$BIT_BUILD
exists($$XinputPath) {
    message(Found that Lib path: $$XinputPath)
    LIBS += -L$$XinputPath \
            -lxinput \
            -lXinput9_1_0
    message(THE LIBS ARE: $$LIBS)
}else{
    message(Missing XinputPath: $$XinputPath)
}


XinputIncludePath = $$(WindowsSdkDir)\\Include\\$$(WindowsSDKLibVersion)\\um
# Find the include path
exists($$XinputIncludePath) {
    message(Found Xinput Include: $$XinputIncludePath)
    INCLUDEPATH += $$XinputIncludePath
}else{
    message(Missing XInputIncludePath: $$XinputIncludePath)
}

}
SOURCES += \
    gamepadserver.cpp \
    gamepadstate.cpp \
    main.cpp \
    mainwindow.cpp \
    mytcpserver.cpp \
    serialconnection.cpp

HEADERS += \
    gamepadserver.h \
    gamepadstate.h \
    mainwindow.h \
    mytcpserver.h \
    serialconnection.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
