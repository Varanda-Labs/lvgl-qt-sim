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

DEFINES += LV_USE_DEMO_MUSIC
DEFINES += USE_DEMO_MUSIC

DEFINES += LV_USE_LOG=LV_LOG_LEVEL_WARN
#DEFINES += LV_LOG_LEVEL=LV_LOG_LEVEL_WARN


# lua heap
DEFINES += USE_DL_PREFIX MSPACES=1 USE_DOUG_LEA_MALLOC ONLY_MSPACES=0 NO_MALLINFO=0

mac: DEFINES += MACOS
linux: DEFINES += LINUX

INCLUDEPATH += \
  ./app \
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
  ./lvgl/src/widgets \
  ./lvgl/demos/music \
  ./lvgl/demos/music/assets



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
    app/app.c \
    lvgl/src/core/lv_disp.c \
    lvgl/src/core/lv_event.c \
    lvgl/src/core/lv_group.c \
    lvgl/src/core/lv_indev.c \
    lvgl/src/core/lv_indev_scroll.c \
    lvgl/src/core/lv_obj.c \
    lvgl/src/core/lv_obj_class.c \
    lvgl/src/core/lv_obj_draw.c \
    lvgl/src/core/lv_obj_pos.c \
    lvgl/src/core/lv_obj_scroll.c \
    lvgl/src/core/lv_obj_style.c \
    lvgl/src/core/lv_obj_style_gen.c \
    lvgl/src/core/lv_obj_tree.c \
    lvgl/src/core/lv_refr.c \
    lvgl/src/core/lv_theme.c \
    lvgl/src/draw/lv_draw.c \
    lvgl/src/draw/lv_draw_arc.c \
    lvgl/src/draw/lv_draw_img.c \
    lvgl/src/draw/lv_draw_label.c \
    lvgl/src/draw/lv_draw_line.c \
    lvgl/src/draw/lv_draw_mask.c \
    lvgl/src/draw/lv_draw_rect.c \
    lvgl/src/draw/lv_draw_triangle.c \
    lvgl/src/draw/lv_img_buf.c \
    lvgl/src/draw/lv_img_cache.c \
    lvgl/src/draw/lv_img_decoder.c \
    lvgl/src/draw/sw/lv_draw_sw.c \
    lvgl/src/draw/sw/lv_draw_sw_arc.c \
    lvgl/src/draw/sw/lv_draw_sw_blend.c \
    lvgl/src/draw/sw/lv_draw_sw_dither.c \
    lvgl/src/draw/sw/lv_draw_sw_gradient.c \
    lvgl/src/draw/sw/lv_draw_sw_img.c \
    lvgl/src/draw/sw/lv_draw_sw_letter.c \
    lvgl/src/draw/sw/lv_draw_sw_line.c \
    lvgl/src/draw/sw/lv_draw_sw_polygon.c \
    lvgl/src/draw/sw/lv_draw_sw_rect.c \
    lvgl/src/extra/layouts/flex/lv_flex.c \
    lvgl/src/extra/layouts/grid/lv_grid.c \
    lvgl/src/extra/lv_extra.c \
    lvgl/src/extra/themes/basic/lv_theme_basic.c \
    lvgl/src/extra/themes/default/lv_theme_default.c \
    lvgl/src/extra/themes/mono/lv_theme_mono.c \
    lvgl/src/font/lv_font.c \
    lvgl/src/font/lv_font_dejavu_16_persian_hebrew.c \
    lvgl/src/font/lv_font_fmt_txt.c \
    lvgl/src/font/lv_font_loader.c \
    lvgl/src/font/lv_font_montserrat_10.c \
    lvgl/src/font/lv_font_montserrat_12.c \
    lvgl/src/font/lv_font_montserrat_12_subpx.c \
    lvgl/src/font/lv_font_montserrat_14.c \
    lvgl/src/font/lv_font_montserrat_16.c \
    lvgl/src/font/lv_font_montserrat_18.c \
    lvgl/src/font/lv_font_montserrat_20.c \
    lvgl/src/font/lv_font_montserrat_22.c \
    lvgl/src/font/lv_font_montserrat_24.c \
    lvgl/src/font/lv_font_montserrat_26.c \
    lvgl/src/font/lv_font_montserrat_28.c \
    lvgl/src/font/lv_font_montserrat_28_compressed.c \
    lvgl/src/font/lv_font_montserrat_30.c \
    lvgl/src/font/lv_font_montserrat_32.c \
    lvgl/src/font/lv_font_montserrat_34.c \
    lvgl/src/font/lv_font_montserrat_36.c \
    lvgl/src/font/lv_font_montserrat_38.c \
    lvgl/src/font/lv_font_montserrat_40.c \
    lvgl/src/font/lv_font_montserrat_42.c \
    lvgl/src/font/lv_font_montserrat_44.c \
    lvgl/src/font/lv_font_montserrat_46.c \
    lvgl/src/font/lv_font_montserrat_48.c \
    lvgl/src/font/lv_font_montserrat_8.c \
    lvgl/src/font/lv_font_simsun_16_cjk.c \
    lvgl/src/font/lv_font_unscii_16.c \
    lvgl/src/font/lv_font_unscii_8.c \
    lvgl/src/hal/lv_hal_disp.c \
    lvgl/src/hal/lv_hal_indev.c \
    lvgl/src/hal/lv_hal_tick.c \
    lvgl/src/misc/lv_anim.c \
    lvgl/src/misc/lv_anim_timeline.c \
    lvgl/src/misc/lv_area.c \
    lvgl/src/misc/lv_async.c \
    lvgl/src/misc/lv_bidi.c \
    lvgl/src/misc/lv_color.c \
    lvgl/src/misc/lv_fs.c \
    lvgl/src/misc/lv_gc.c \
    lvgl/src/misc/lv_ll.c \
    lvgl/src/misc/lv_log.c \
    lvgl/src/misc/lv_lru.c \
    lvgl/src/misc/lv_math.c \
    lvgl/src/misc/lv_mem.c \
    lvgl/src/misc/lv_printf.c \
    lvgl/src/misc/lv_style.c \
    lvgl/src/misc/lv_style_gen.c \
    lvgl/src/misc/lv_templ.c \
    lvgl/src/misc/lv_timer.c \
    lvgl/src/misc/lv_tlsf.c \
    lvgl/src/misc/lv_txt.c \
    lvgl/src/misc/lv_txt_ap.c \
    lvgl/src/misc/lv_utils.c \
    lvgl/src/widgets/lv_arc.c \
    lvgl/src/widgets/lv_bar.c \
    lvgl/src/widgets/lv_btn.c \
    lvgl/src/widgets/lv_btnmatrix.c \
    lvgl/src/widgets/lv_canvas.c \
    lvgl/src/widgets/lv_checkbox.c \
    lvgl/src/widgets/lv_dropdown.c \
    lvgl/src/widgets/lv_img.c \
    lvgl/src/widgets/lv_label.c \
    lvgl/src/widgets/lv_line.c \
    lvgl/src/widgets/lv_objx_templ.c \
    lvgl/src/widgets/lv_roller.c \
    lvgl/src/widgets/lv_slider.c \
    lvgl/src/widgets/lv_switch.c \
    lvgl/src/widgets/lv_table.c \
    lvgl/src/widgets/lv_textarea.c \
    platform/eos_init.cpp \
    platform/lvgl_integr.cpp \
    platform/mos_desktop.c \
    platform/mos_desktop_timer.c \
    lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.c \
    lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.c \
    lvgl/src/extra/widgets/calendar/lv_calendar.c \
    lvgl/src/extra/widgets/led/lv_led.c \
    lvgl/src/extra/widgets/win/lv_win.c \
    lvgl/src/extra/widgets/chart/lv_chart.c \
    lvgl/src/extra/widgets/spinbox/lv_spinbox.c \
    lvgl/src/extra/widgets/imgbtn/lv_imgbtn.c \
    lvgl/src/extra/widgets/spinner/lv_spinner.c \
    lvgl/src/extra/widgets/tabview/lv_tabview.c \
    lvgl/src/extra/widgets/msgbox/lv_msgbox.c \
    lvgl/src/extra/widgets/span/lv_span.c \
    lvgl/src/extra/widgets/colorwheel/lv_colorwheel.c \
    lvgl/src/extra/widgets/list/lv_list.c \
    lvgl/src/extra/widgets/menu/lv_menu.c \
    lvgl/src/extra/widgets/animimg/lv_animimg.c \
    lvgl/src/extra/widgets/meter/lv_meter.c \
    lvgl/src/extra/widgets/tileview/lv_tileview.c \
    lvgl/src/extra/widgets/keyboard/lv_keyboard.c \
    lvgl/src/extra/others/snapshot/lv_snapshot.c \
    lvgl/src/extra/others/gridnav/lv_gridnav.c \
    lvgl/src/extra/others/monkey/lv_monkey.c \
    lvgl/src/extra/libs/ffmpeg/lv_ffmpeg.c \
    lvgl/src/extra/libs/sjpg/tjpgd.c \
    lvgl/src/extra/libs/sjpg/lv_sjpg.c \
    lvgl/src/extra/libs/freetype/lv_freetype.c \
    lvgl/src/extra/libs/png/lv_png.c \
    lvgl/src/extra/libs/png/lodepng.c \
    lvgl/src/extra/libs/qrcode/lv_qrcode.c \
    lvgl/src/extra/libs/qrcode/qrcodegen.c \
    lvgl/src/extra/libs/rlottie/lv_rlottie.c \
    lvgl/src/extra/libs/fsdrv/lv_fs_stdio.c \
    lvgl/src/extra/libs/fsdrv/lv_fs_posix.c \
    lvgl/src/extra/libs/fsdrv/lv_fs_fatfs.c \
    lvgl/src/extra/libs/fsdrv/lv_fs_win32.c \
    lvgl/src/extra/libs/bmp/lv_bmp.c \
    lvgl/src/extra/libs/gif/lv_gif.c \
    lvgl/src/extra/libs/gif/gifdec.c \
    platform/nat_cmd.c \
    lvgl/demos/music/lv_demo_music_list.c \
    lvgl/demos/music/lv_demo_music_main.c \
    lvgl/demos/music/assets/img_lv_demo_music_slider_knob_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_list_border_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_icon_1.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_list_play_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_next.c \
    lvgl/demos/music/assets/img_lv_demo_music_cover_1.c \
    lvgl/demos/music/assets/img_lv_demo_music_logo.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_corner_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_list_border.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_loop_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_prev_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_icon_4_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_next_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_wave_top.c \
    lvgl/demos/music/assets/img_lv_demo_music_icon_2.c \
    lvgl/demos/music/assets/img_lv_demo_music_corner_right_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_cover_2.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_list_play.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_play_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_pause_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_loop.c \
    lvgl/demos/music/assets/img_lv_demo_music_corner_right.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_pause.c \
    lvgl/demos/music/assets/img_lv_demo_music_cover_2_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_list_pause.c \
    lvgl/demos/music/assets/img_lv_demo_music_icon_2_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_rnd_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_cover_3.c \
    lvgl/demos/music/assets/img_lv_demo_music_icon_3.c \
    lvgl/demos/music/assets/img_lv_demo_music_icon_3_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_rnd.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_list_pause_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_corner_left.c \
    lvgl/demos/music/assets/img_lv_demo_music_cover_3_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_corner_left_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_prev.c \
    lvgl/demos/music/assets/img_lv_demo_music_icon_1_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_icon_4.c \
    lvgl/demos/music/assets/img_lv_demo_music_btn_play.c \
    lvgl/demos/music/assets/img_lv_demo_music_cover_1_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_wave_bottom.c \
    lvgl/demos/music/assets/img_lv_demo_music_wave_bottom_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_wave_top_large.c \
    lvgl/demos/music/assets/img_lv_demo_music_slider_knob.c \
    lvgl/demos/music/lv_demo_music.c

#    lvgl/demos/keypad_encoder/lv_demo_keypad_encoder.c
#    lvgl/demos/widgets/lv_demo_widgets.c
#    lvgl/demos/widgets/assets/img_clothes.c
#    lvgl/demos/widgets/assets/img_lvgl_logo.c
#    lvgl/demos/widgets/assets/img_demo_widgets_avatar.c
#    lvgl/demos/stress/lv_demo_stress.c
#    lvgl/demos/stress/assets/lv_font_montserrat_12_compr_az.c
#    lvgl/demos/stress/assets/lv_font_montserrat_28_compr_az.c
#    lvgl/demos/stress/assets/lv_font_montserrat_16_compr_az.c

#lvgl/demos/benchmark/lv_demo_benchmark.c
#lvgl/demos/benchmark/assets/img_benchmark_cogwheel_chroma_keyed.c
#lvgl/demos/benchmark/assets/img_benchmark_cogwheel_alpha16.c
#lvgl/demos/benchmark/assets/img_benchmark_cogwheel_indexed16.c
#lvgl/demos/benchmark/assets/lv_font_bechmark_montserrat_16_compr_az.c.c
#lvgl/demos/benchmark/assets/lv_font_bechmark_montserrat_12_compr_az.c.c
#lvgl/demos/benchmark/assets/img_benchmark_cogwheel_rgb.c
#lvgl/demos/benchmark/assets/img_benchmark_cogwheel_argb.c
#lvgl/demos/benchmark/assets/lv_font_bechmark_montserrat_28_compr_az.c.c

HEADERS += \
    ./sim/clabel.h \
    ./sim/console.h \
    ./sim/log.h \
    ./sim/mainwindow.h \
    ./sim/termdlg.h \
    lv_conf.h \
    lvgl/demos/music/lv_demo_music.h \
    lvgl/demos/music/lv_demo_music_list.h \
    lvgl/demos/music/lv_demo_music_main.h \
    lvgl/lv_conf_template.h \
    lvgl/src/core/lv_disp.h \
    lvgl/src/core/lv_event.h \
    lvgl/src/core/lv_group.h \
    lvgl/src/core/lv_indev.h \
    lvgl/src/core/lv_indev_scroll.h \
    lvgl/src/core/lv_obj.h \
    lvgl/src/core/lv_obj_class.h \
    lvgl/src/core/lv_obj_draw.h \
    lvgl/src/core/lv_obj_pos.h \
    lvgl/src/core/lv_obj_scroll.h \
    lvgl/src/core/lv_obj_style.h \
    lvgl/src/core/lv_obj_style_gen.h \
    lvgl/src/core/lv_obj_tree.h \
    lvgl/src/core/lv_refr.h \
    lvgl/src/core/lv_theme.h \
    lvgl/src/draw/lv_draw.h \
    lvgl/src/draw/lv_draw_arc.h \
    lvgl/src/draw/lv_draw_img.h \
    lvgl/src/draw/lv_draw_label.h \
    lvgl/src/draw/lv_draw_line.h \
    lvgl/src/draw/lv_draw_mask.h \
    lvgl/src/draw/lv_draw_rect.h \
    lvgl/src/draw/lv_draw_triangle.h \
    lvgl/src/draw/lv_img_buf.h \
    lvgl/src/draw/lv_img_cache.h \
    lvgl/src/draw/lv_img_decoder.h \
    lvgl/src/draw/sw/lv_draw_sw.h \
    lvgl/src/draw/sw/lv_draw_sw_blend.h \
    lvgl/src/draw/sw/lv_draw_sw_dither.h \
    lvgl/src/draw/sw/lv_draw_sw_gradient.h \
    lvgl/src/extra/layouts/flex/lv_flex.h \
    lvgl/src/extra/layouts/grid/lv_grid.h \
    lvgl/src/extra/layouts/lv_layouts.h \
    lvgl/src/extra/lv_extra.h \
    lvgl/src/extra/themes/basic/lv_theme_basic.h \
    lvgl/src/extra/themes/default/lv_theme_default.h \
    lvgl/src/extra/themes/lv_themes.h \
    lvgl/src/extra/themes/mono/lv_theme_mono.h \
    lvgl/src/font/lv_font.h \
    lvgl/src/font/lv_font_fmt_txt.h \
    lvgl/src/font/lv_font_loader.h \
    lvgl/src/font/lv_symbol_def.h \
    lvgl/src/hal/lv_hal.h \
    lvgl/src/hal/lv_hal_disp.h \
    lvgl/src/hal/lv_hal_indev.h \
    lvgl/src/hal/lv_hal_tick.h \
    lvgl/src/misc/lv_anim.h \
    lvgl/src/misc/lv_anim_timeline.h \
    lvgl/src/misc/lv_area.h \
    lvgl/src/misc/lv_assert.h \
    lvgl/src/misc/lv_async.h \
    lvgl/src/misc/lv_bidi.h \
    lvgl/src/misc/lv_color.h \
    lvgl/src/misc/lv_fs.h \
    lvgl/src/misc/lv_gc.h \
    lvgl/src/misc/lv_ll.h \
    lvgl/src/misc/lv_log.h \
    lvgl/src/misc/lv_lru.h \
    lvgl/src/misc/lv_math.h \
    lvgl/src/misc/lv_mem.h \
    lvgl/src/misc/lv_printf.h \
    lvgl/src/misc/lv_style.h \
    lvgl/src/misc/lv_style_gen.h \
    lvgl/src/misc/lv_templ.h \
    lvgl/src/misc/lv_timer.h \
    lvgl/src/misc/lv_tlsf.h \
    lvgl/src/misc/lv_txt.h \
    lvgl/src/misc/lv_txt_ap.h \
    lvgl/src/misc/lv_types.h \
    lvgl/src/misc/lv_utils.h \
    lvgl/src/widgets/lv_arc.h \
    lvgl/src/widgets/lv_bar.h \
    lvgl/src/widgets/lv_btn.h \
    lvgl/src/widgets/lv_btnmatrix.h \
    lvgl/src/widgets/lv_canvas.h \
    lvgl/src/widgets/lv_checkbox.h \
    lvgl/src/widgets/lv_dropdown.h \
    lvgl/src/widgets/lv_img.h \
    lvgl/src/widgets/lv_label.h \
    lvgl/src/widgets/lv_line.h \
    lvgl/src/widgets/lv_objx_templ.h \
    lvgl/src/widgets/lv_roller.h \
    lvgl/src/widgets/lv_slider.h \
    lvgl/src/widgets/lv_switch.h \
    lvgl/src/widgets/lv_table.h \
    lvgl/src/widgets/lv_textarea.h \
    platform/eos_config.h \
    platform/eos_init.h \
    platform/lvgl_integr.h \
    platform/mos.h \
    platform/mos_desktop_timer.h \
    platform/nat_cmd.h \
    lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.h \
    lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.h \
    lvgl/src/extra/widgets/calendar/lv_calendar.h \
    lvgl/src/extra/widgets/led/lv_led.h \
    lvgl/src/extra/widgets/win/lv_win.h \
    lvgl/src/extra/widgets/chart/lv_chart.h \
    lvgl/src/extra/widgets/spinbox/lv_spinbox.h \
    lvgl/src/extra/widgets/imgbtn/lv_imgbtn.h \
    lvgl/src/extra/widgets/spinner/lv_spinner.h \
    lvgl/src/extra/widgets/tabview/lv_tabview.h \
    lvgl/src/extra/widgets/msgbox/lv_msgbox.h \
    lvgl/src/extra/widgets/span/lv_span.h \
    lvgl/src/extra/widgets/colorwheel/lv_colorwheel.h \
    lvgl/src/extra/widgets/list/lv_list.h \
    lvgl/src/extra/widgets/menu/lv_menu.h \
    lvgl/src/extra/widgets/animimg/lv_animimg.h \
    lvgl/src/extra/widgets/meter/lv_meter.h \
    lvgl/src/extra/widgets/tileview/lv_tileview.h \
    lvgl/src/extra/widgets/keyboard/lv_keyboard.h \
    lvgl/src/extra/others/snapshot/lv_snapshot.h \
    lvgl/src/extra/others/gridnav/lv_gridnav.h \
    lvgl/src/extra/others/lv_others.h \
    lvgl/src/extra/others/monkey/lv_monkey.h \
    lvgl/src/extra/libs/ffmpeg/lv_ffmpeg.h \
    lvgl/src/extra/libs/sjpg/lv_sjpg.h \
    lvgl/src/extra/libs/sjpg/tjpgd.h \
    lvgl/src/extra/libs/sjpg/tjpgdcnf.h \
    lvgl/src/extra/libs/freetype/lv_freetype.h \
    lvgl/src/extra/libs/png/lodepng.h \
    lvgl/src/extra/libs/png/lv_png.h \
    lvgl/src/extra/libs/qrcode/lv_qrcode.h \
    lvgl/src/extra/libs/qrcode/qrcodegen.h \
    lvgl/src/extra/libs/rlottie/lv_rlottie.h \
    lvgl/src/extra/libs/fsdrv/lv_fsdrv.h \
    lvgl/src/extra/libs/bmp/lv_bmp.h \
    lvgl/src/extra/libs/lv_libs.h \
    lvgl/src/extra/libs/gif/lv_gif.h \
    lvgl/src/extra/libs/gif/gifdec.h




FORMS += \
    ./sim/mainwindow.ui \
    ./sim/termdlg.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
