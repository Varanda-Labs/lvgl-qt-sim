QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

DEFINES += UNIT_TEST

INCLUDEPATH += ../ ../../ \
  ../../../lvgl \
  ../../lvgl_patch \
  ../../lvgl/src/lv_core \
  ../../lvgl/src/lv_draw \
  ../../lvgl/src/lv_font \
  ../../lvgl/src/lv_hal \
  ../../lvgl/src/lv_mist \
  ../../lvgl/src/lv_themes \
  ../../lvgl/src/lv_widgets \
  ../../lua_eos/native \
  ../../lua/src/ \
  ../../lua_eos/native


TEMPLATE = app

SOURCES +=  tst_testmos.cpp \
  ../../lua_eos/native/mos_desktop.c \
  ../../lua_eos/native/mos_desktop_timer.c \
  ../log.cpp

HEADERS += \
  ../../lua_eos/native/mos_desktop_timer.h
