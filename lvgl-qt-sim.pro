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

INCLUDEPATH += ../lvgl \
  ../lvgl_patch \
  ../lvgl/src/lv_core \
  ../lvgl/src/lv_draw \
  ../lvgl/src/lv_font \
  ../lvgl/src/lv_hal \
  ../lvgl/src/lv_mist \
  ../lvgl/src/lv_themes \
  ../lvgl/src/lv_widgets \
  ../lua_eos/native \
  ../lua/src/ \
  ../. \
  ../lua_eos/native

INCLUDEPATH += $${FREERTOS_DIR}/Source/include
INCLUDEPATH += $${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix
INCLUDEPATH += $${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix/utils
INCLUDEPATH += $${FREERTOS_DIR}/Demo/Common/include
INCLUDEPATH += $${FREERTOS_DIR}/Demo/Posix_GCC

#INCLUDEPATH += ../lua_eos/native/FreeRTOS/FreeRTOS/Source/include
#INCLUDEPATH += ../lua_eos/native/FreeRTOS/FreeRTOS/Source/portable/ThirdParty/GCC/Posix
#INCLUDEPATH += ../lua_eos/native/FreeRTOS/FreeRTOS/Source/portable/ThirdParty/GCC/Posix/utils
#INCLUDEPATH += ../lua_eos/native/FreeRTOS/FreeRTOS/Demo/Common/include


#INCLUDEPATH += $${FREERTOS_PLUS_DIR}/Source/FreeRTOS-Plus-Trace/Include


# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../lua/src/lapi.c \
    ../lua/src/lauxlib.c \
    ../lua/src/lbaselib.c \
    ../lua/src/lcode.c \
    ../lua/src/lcorolib.c \
    ../lua/src/lctype.c \
    ../lua/src/ldblib.c \
    ../lua/src/ldebug.c \
    ../lua/src/ldo.c \
    ../lua/src/ldump.c \
    ../lua/src/lfunc.c \
    ../lua/src/lgc.c \
    ../lua/src/linit.c \
    ../lua/src/liolib.c \
    ../lua/src/llex.c \
    ../lua/src/lmathlib.c \
    ../lua/src/lmem.c \
    ../lua/src/loadlib.c \
    ../lua/src/lobject.c \
    ../lua/src/lopcodes.c \
    ../lua/src/loslib.c \
    ../lua/src/lparser.c \
    ../lua/src/lstate.c \
    ../lua/src/lstring.c \
    ../lua/src/lstrlib.c \
    ../lua/src/ltable.c \
    ../lua/src/ltablib.c \
    ../lua/src/ltm.c \
    ../lua/src/lua.c \
    ../lua/src/lundump.c \
    ../lua/src/lutf8lib.c \
    ../lua/src/lvm.c \
    ../lua/src/lzio.c \
    ../lua_eos/native/bidings.c \
    ../lua_eos/native/eos_init.cpp \
    ../lua_eos/native/lua_eos.c \
    ../lua_eos/native/lvgl_lua.c \
    ../lua_eos/native/mos_desktop.c \
    ../lua_eos/native/mos_desktop_timer.c \
    ../lua_eos/native/nat_cmd.c \
    ../lua_eos/native/splash.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0002.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0006.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0010.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0014.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0018.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0022.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0026.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0030.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0034.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0038.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0042.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0046.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0050.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0054.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0058.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0062.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0066.c \
    ../lua_eos/native/splash_logo/c_arrays/logo_0070.c \
    ../lvgl/src/lv_core/lv_disp.c \
    ../lvgl/src/lv_core/lv_group.c \
    ../lvgl/src/lv_core/lv_indev.c \
    ../lvgl/src/lv_core/lv_obj.c \
    ../lvgl/src/lv_core/lv_refr.c \
    ../lvgl/src/lv_core/lv_style.c \
    ../lvgl/src/lv_draw/lv_draw_arc.c \
    ../lvgl/src/lv_draw/lv_draw_blend.c \
    ../lvgl/src/lv_draw/lv_draw_img.c \
    ../lvgl/src/lv_draw/lv_draw_label.c \
    ../lvgl/src/lv_draw/lv_draw_line.c \
    ../lvgl/src/lv_draw/lv_draw_mask.c \
    ../lvgl/src/lv_draw/lv_draw_rect.c \
    ../lvgl/src/lv_draw/lv_draw_triangle.c \
    ../lvgl/src/lv_draw/lv_img_buf.c \
    ../lvgl/src/lv_draw/lv_img_cache.c \
    ../lvgl/src/lv_draw/lv_img_decoder.c \
    ../lvgl/src/lv_font/lv_font.c \
    ../lvgl/src/lv_font/lv_font_dejavu_16_persian_hebrew.c \
    ../lvgl/src/lv_font/lv_font_fmt_txt.c \
    ../lvgl/src/lv_font/lv_font_loader.c \
    ../lvgl/src/lv_font/lv_font_montserrat_10.c \
    ../lvgl/src/lv_font/lv_font_montserrat_12.c \
    ../lvgl/src/lv_font/lv_font_montserrat_12_subpx.c \
    ../lvgl/src/lv_font/lv_font_montserrat_14.c \
    ../lvgl/src/lv_font/lv_font_montserrat_16.c \
    ../lvgl/src/lv_font/lv_font_montserrat_18.c \
    ../lvgl/src/lv_font/lv_font_montserrat_20.c \
    ../lvgl/src/lv_font/lv_font_montserrat_22.c \
    ../lvgl/src/lv_font/lv_font_montserrat_24.c \
    ../lvgl/src/lv_font/lv_font_montserrat_26.c \
    ../lvgl/src/lv_font/lv_font_montserrat_28.c \
    ../lvgl/src/lv_font/lv_font_montserrat_28_compressed.c \
    ../lvgl/src/lv_font/lv_font_montserrat_30.c \
    ../lvgl/src/lv_font/lv_font_montserrat_32.c \
    ../lvgl/src/lv_font/lv_font_montserrat_34.c \
    ../lvgl/src/lv_font/lv_font_montserrat_36.c \
    ../lvgl/src/lv_font/lv_font_montserrat_38.c \
    ../lvgl/src/lv_font/lv_font_montserrat_40.c \
    ../lvgl/src/lv_font/lv_font_montserrat_42.c \
    ../lvgl/src/lv_font/lv_font_montserrat_44.c \
    ../lvgl/src/lv_font/lv_font_montserrat_46.c \
    ../lvgl/src/lv_font/lv_font_montserrat_48.c \
    ../lvgl/src/lv_font/lv_font_montserrat_8.c \
    ../lvgl/src/lv_font/lv_font_simsun_16_cjk.c \
    ../lvgl/src/lv_font/lv_font_unscii_16.c \
    ../lvgl/src/lv_font/lv_font_unscii_8.c \
    ../lvgl/src/lv_hal/lv_hal_disp.c \
    ../lvgl/src/lv_hal/lv_hal_indev.c \
    ../lvgl/src/lv_hal/lv_hal_tick.c \
    ../lvgl/src/lv_misc/lv_anim.c \
    ../lvgl/src/lv_misc/lv_area.c \
    ../lvgl/src/lv_misc/lv_async.c \
    ../lvgl/src/lv_misc/lv_bidi.c \
    ../lvgl/src/lv_misc/lv_color.c \
    ../lvgl/src/lv_misc/lv_debug.c \
    ../lvgl/src/lv_misc/lv_fs.c \
    ../lvgl/src/lv_misc/lv_gc.c \
    ../lvgl/src/lv_misc/lv_ll.c \
    ../lvgl/src/lv_misc/lv_log.c \
    ../lvgl/src/lv_misc/lv_math.c \
    ../lvgl/src/lv_misc/lv_mem.c \
    ../lvgl/src/lv_misc/lv_printf.c \
    ../lvgl/src/lv_misc/lv_task.c \
    ../lvgl/src/lv_misc/lv_templ.c \
    ../lvgl/src/lv_misc/lv_txt.c \
    ../lvgl/src/lv_misc/lv_txt_ap.c \
    ../lvgl/src/lv_misc/lv_utils.c \
    ../lvgl/src/lv_themes/lv_theme.c \
    ../lvgl/src/lv_themes/lv_theme_empty.c \
    ../lvgl/src/lv_themes/lv_theme_material.c \
    ../lvgl/src/lv_themes/lv_theme_mono.c \
    ../lvgl/src/lv_themes/lv_theme_template.c \
    ../lvgl/src/lv_widgets/lv_arc.c \
    ../lvgl/src/lv_widgets/lv_bar.c \
    ../lvgl/src/lv_widgets/lv_btn.c \
    ../lvgl/src/lv_widgets/lv_btnmatrix.c \
    ../lvgl/src/lv_widgets/lv_calendar.c \
    ../lvgl/src/lv_widgets/lv_canvas.c \
    ../lvgl/src/lv_widgets/lv_chart.c \
    ../lvgl/src/lv_widgets/lv_checkbox.c \
    ../lvgl/src/lv_widgets/lv_cont.c \
    ../lvgl/src/lv_widgets/lv_cpicker.c \
    ../lvgl/src/lv_widgets/lv_dropdown.c \
    ../lvgl/src/lv_widgets/lv_gauge.c \
    ../lvgl/src/lv_widgets/lv_img.c \
    ../lvgl/src/lv_widgets/lv_imgbtn.c \
    ../lvgl/src/lv_widgets/lv_keyboard.c \
    ../lvgl/src/lv_widgets/lv_label.c \
    ../lvgl/src/lv_widgets/lv_led.c \
    ../lvgl/src/lv_widgets/lv_line.c \
    ../lvgl/src/lv_widgets/lv_linemeter.c \
    ../lvgl/src/lv_widgets/lv_list.c \
    ../lvgl/src/lv_widgets/lv_msgbox.c \
    ../lvgl/src/lv_widgets/lv_objmask.c \
    ../lvgl/src/lv_widgets/lv_objx_templ.c \
    ../lvgl/src/lv_widgets/lv_page.c \
    ../lvgl/src/lv_widgets/lv_roller.c \
    ../lvgl/src/lv_widgets/lv_slider.c \
    ../lvgl/src/lv_widgets/lv_spinbox.c \
    ../lvgl/src/lv_widgets/lv_spinner.c \
    ../lvgl/src/lv_widgets/lv_switch.c \
    ../lvgl/src/lv_widgets/lv_table.c \
    ../lvgl/src/lv_widgets/lv_tabview.c \
    ../lvgl/src/lv_widgets/lv_textarea.c \
    ../lvgl/src/lv_widgets/lv_tileview.c \
    ../lvgl/src/lv_widgets/lv_win.c \
    ../lvgl_patch/bind_lv_arc.c \
    ../lvgl_patch/bind_lv_bar.c \
    ../lvgl_patch/bind_lv_btn.c \
    ../lvgl_patch/bind_lv_btnmatrix.c \
    ../lvgl_patch/bind_lv_calendar.c \
    ../lvgl_patch/bind_lv_checkbox.c \
    ../lvgl_patch/bind_lv_disp.c \
    ../lvgl_patch/bind_lv_keyboard.c \
    ../lvgl_patch/bind_lv_label.c \
    ../lvgl_patch/bind_lv_linemeter.c \
    ../lvgl_patch/bind_lv_obj.c \
    ../lvgl_patch/bind_lv_slider.c \
    ../lvgl_patch/bind_lv_style.c \
    ../lvgl_patch/bind_lv_switch.c \
    ../lvgl_patch/bind_lv_textarea.c \
    ../lvgl_patch/lvgl_init_modules.c \
    ../lvgl_patch/lvgl_integr.cpp \
    ../utils/malloc.c \
    clabel.cpp \
    console.cpp \
    log.cpp \
    main.cpp \
    mainwindow.cpp \
    termdlg.cpp

HEADERS += \
    ../lua/src/lapi.h \
    ../lua/src/lauxlib.h \
    ../lua/src/lcode.h \
    ../lua/src/lctype.h \
    ../lua/src/ldebug.h \
    ../lua/src/ldo.h \
    ../lua/src/lfunc.h \
    ../lua/src/lgc.h \
    ../lua/src/ljumptab.h \
    ../lua/src/llex.h \
    ../lua/src/llimits.h \
    ../lua/src/lmem.h \
    ../lua/src/lobject.h \
    ../lua/src/lopcodes.h \
    ../lua/src/lopnames.h \
    ../lua/src/lparser.h \
    ../lua/src/lprefix.h \
    ../lua/src/lstate.h \
    ../lua/src/lstring.h \
    ../lua/src/ltable.h \
    ../lua/src/ltm.h \
    ../lua/src/lua.h \
    ../lua/src/lua.hpp \
    ../lua/src/luaconf.h \
    ../lua/src/lualib.h \
    ../lua/src/lundump.h \
    ../lua/src/lvm.h \
    ../lua/src/lzio.h \
    ../lua_eos/native/eos_config.h \
    ../lua_eos/native/eos_init.h \
    ../lua_eos/native/eos_lua.h \
    ../lua_eos/native/lua_eos.h \
    ../lua_eos/native/lvgl_lua.h \
    ../lua_eos/native/mos.h \
    ../lua_eos/native/mos_desktop_timer.h \
    ../lua_eos/native/nat_cmd.h \
    ../lua_eos/native/splash.h \
    ../lvgl/src/lv_api_map.h \
    ../lvgl/src/lv_conf_internal.h \
    ../lvgl/src/lv_conf_kconfig.h \
    ../lvgl/src/lv_core/lv_disp.h \
    ../lvgl/src/lv_core/lv_group.h \
    ../lvgl/src/lv_core/lv_indev.h \
    ../lvgl/src/lv_core/lv_obj.h \
    ../lvgl/src/lv_core/lv_obj_style_dec.h \
    ../lvgl/src/lv_core/lv_refr.h \
    ../lvgl/src/lv_core/lv_style.h \
    ../lvgl/src/lv_draw/lv_draw.h \
    ../lvgl/src/lv_draw/lv_draw_arc.h \
    ../lvgl/src/lv_draw/lv_draw_blend.h \
    ../lvgl/src/lv_draw/lv_draw_img.h \
    ../lvgl/src/lv_draw/lv_draw_label.h \
    ../lvgl/src/lv_draw/lv_draw_line.h \
    ../lvgl/src/lv_draw/lv_draw_mask.h \
    ../lvgl/src/lv_draw/lv_draw_rect.h \
    ../lvgl/src/lv_draw/lv_draw_triangle.h \
    ../lvgl/src/lv_draw/lv_img_buf.h \
    ../lvgl/src/lv_draw/lv_img_cache.h \
    ../lvgl/src/lv_draw/lv_img_decoder.h \
    ../lvgl/src/lv_font/lv_font.h \
    ../lvgl/src/lv_font/lv_font_fmt_txt.h \
    ../lvgl/src/lv_font/lv_font_loader.h \
    ../lvgl/src/lv_font/lv_symbol_def.h \
    ../lvgl/src/lv_hal/lv_hal.h \
    ../lvgl/src/lv_hal/lv_hal_disp.h \
    ../lvgl/src/lv_hal/lv_hal_indev.h \
    ../lvgl/src/lv_hal/lv_hal_tick.h \
    ../lvgl/src/lv_misc/lv_anim.h \
    ../lvgl/src/lv_misc/lv_area.h \
    ../lvgl/src/lv_misc/lv_async.h \
    ../lvgl/src/lv_misc/lv_bidi.h \
    ../lvgl/src/lv_misc/lv_color.h \
    ../lvgl/src/lv_misc/lv_debug.h \
    ../lvgl/src/lv_misc/lv_fs.h \
    ../lvgl/src/lv_misc/lv_gc.h \
    ../lvgl/src/lv_misc/lv_ll.h \
    ../lvgl/src/lv_misc/lv_log.h \
    ../lvgl/src/lv_misc/lv_math.h \
    ../lvgl/src/lv_misc/lv_mem.h \
    ../lvgl/src/lv_misc/lv_printf.h \
    ../lvgl/src/lv_misc/lv_task.h \
    ../lvgl/src/lv_misc/lv_templ.h \
    ../lvgl/src/lv_misc/lv_txt.h \
    ../lvgl/src/lv_misc/lv_txt_ap.h \
    ../lvgl/src/lv_misc/lv_types.h \
    ../lvgl/src/lv_misc/lv_utils.h \
    ../lvgl/src/lv_themes/lv_theme.h \
    ../lvgl/src/lv_themes/lv_theme_empty.h \
    ../lvgl/src/lv_themes/lv_theme_material.h \
    ../lvgl/src/lv_themes/lv_theme_mono.h \
    ../lvgl/src/lv_themes/lv_theme_template.h \
    ../lvgl/src/lv_widgets/lv_arc.h \
    ../lvgl/src/lv_widgets/lv_bar.h \
    ../lvgl/src/lv_widgets/lv_btn.h \
    ../lvgl/src/lv_widgets/lv_btnmatrix.h \
    ../lvgl/src/lv_widgets/lv_calendar.h \
    ../lvgl/src/lv_widgets/lv_canvas.h \
    ../lvgl/src/lv_widgets/lv_chart.h \
    ../lvgl/src/lv_widgets/lv_checkbox.h \
    ../lvgl/src/lv_widgets/lv_cont.h \
    ../lvgl/src/lv_widgets/lv_cpicker.h \
    ../lvgl/src/lv_widgets/lv_dropdown.h \
    ../lvgl/src/lv_widgets/lv_gauge.h \
    ../lvgl/src/lv_widgets/lv_img.h \
    ../lvgl/src/lv_widgets/lv_imgbtn.h \
    ../lvgl/src/lv_widgets/lv_keyboard.h \
    ../lvgl/src/lv_widgets/lv_label.h \
    ../lvgl/src/lv_widgets/lv_led.h \
    ../lvgl/src/lv_widgets/lv_line.h \
    ../lvgl/src/lv_widgets/lv_linemeter.h \
    ../lvgl/src/lv_widgets/lv_list.h \
    ../lvgl/src/lv_widgets/lv_msgbox.h \
    ../lvgl/src/lv_widgets/lv_objmask.h \
    ../lvgl/src/lv_widgets/lv_objx_templ.h \
    ../lvgl/src/lv_widgets/lv_page.h \
    ../lvgl/src/lv_widgets/lv_roller.h \
    ../lvgl/src/lv_widgets/lv_slider.h \
    ../lvgl/src/lv_widgets/lv_spinbox.h \
    ../lvgl/src/lv_widgets/lv_spinner.h \
    ../lvgl/src/lv_widgets/lv_switch.h \
    ../lvgl/src/lv_widgets/lv_table.h \
    ../lvgl/src/lv_widgets/lv_tabview.h \
    ../lvgl/src/lv_widgets/lv_textarea.h \
    ../lvgl/src/lv_widgets/lv_tileview.h \
    ../lvgl/src/lv_widgets/lv_win.h \
    ../lvgl/src/lvgl.h \
    ../lvgl_patch/bind_lv_btn.h \
    ../lvgl_patch/bind_lv_disp.h \
    ../lvgl_patch/bind_lv_label.h \
    ../lvgl_patch/bind_lv_linemeter.h \
    ../lvgl_patch/bind_lv_obj.h \
    ../lvgl_patch/bind_lv_slider.h \
    ../lvgl_patch/bind_lv_style.h \
    ../lvgl_patch/lv_conf.h \
    ../lvgl_patch/lvgl_integr.h \
    ../utils/malloc.h \
    clabel.h \
    console.h \
    log.h \
    mainwindow.h \
    termdlg.h

FORMS += \
    mainwindow.ui \
    termdlg.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
