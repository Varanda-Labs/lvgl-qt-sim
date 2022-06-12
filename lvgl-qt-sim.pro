QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += debug

FREERTOS_DIR = ../lua_eos/native/FreeRTOS/FreeRTOS

#FREERTOS_PLUS_DIR = ../lua_eos/native/FreeRTOS-Plus


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

DEFINES += LV_CONF_INCLUDE_SIMPLE

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += LUA_EMBEDDED

DEFINES += MOS_DESKTOP

DEFINES += projCOVERAGE_TEST=1

DEFINES += LV_USE_LOG=0
#DEFINES += LV_LOG_LEVEL=LV_LOG_LEVEL_WARN

# lua heap
DEFINES += USE_DL_PREFIX MSPACES=1 USE_DOUG_LEA_MALLOC ONLY_MSPACES=0 NO_MALLINFO=0

mac: DEFINES += MACOS
linux: DEFINES += LINUX

INCLUDEPATH += \
  ./sim \
  ./platform \
  ./lvgl \
  ./lvgl/src/core \
  ./lvgl/src/core \
  ./lvgl/src/draw \
  ./lvgl/src/extra \
  ./lvgl/src/font \
  ./lvgl/src/gpu \
  ./lvgl/src/hal \
  ./lvgl/src/misc \
  ./lvgl/src/widgets



# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./sim/clabel.cpp \
    ./sim/console.cpp \
    ./sim/log.cpp \
    ./sim/main.cpp \
    ./sim/mainwindow.cpp \
    ./sim/termdlg.cpp \
    platform/lvgl_integr.cpp

HEADERS += \
    ./sim/clabel.h \
    ./sim/console.h \
    ./sim/log.h \
    ./sim/mainwindow.h \
    ./sim/termdlg.h \
    lv_conf.h \
    lvgl/lv_conf_template.h \
    platform/eos_config.h \
    platform/eos_init.h \
    platform/lua_eos.h \
    platform/lvgl_integr.h \
    platform/mos.h \
    platform/nat_cmd.h

FORMS += \
    ./sim/mainwindow.ui \
    ./sim/termdlg.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
