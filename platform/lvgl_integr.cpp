/***************************************************************
 *
 *                 This code is part of LVGL-Qt-Simulator
 *
 * Copyrights 2021 - Varanda Labs Inc.
 *
 * License:
 *   Creative Commons: CC BY-NC-SA 4.0
 *   Attribution-NonCommercial-ShareAlike 4.0 International
 *   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 *
 *   Note: for purchasing a commertial license contact:
 *     m@varanda.ca
 *
 ***************************************************************
 */

#include "ui_mainwindow.h"
#include "lvgl.h"
#include "lvgl_integr.h"
#include "lv_hal_disp.h"
#include "log.h"

MainWindow * gMainObj;


static void updateDisplay (const lv_area_t * area, lv_color_t * color_p, bool last);


#ifdef __cplusplus
extern "C" {
#endif

#define DISP_BUF_SIZE (LV_HOR_RES_MAX * 10)

static lv_indev_drv_t indev_drv;
static int touchpad_x = 0, touchpad_y = 0;
static lv_indev_state_t touchpad_state = LV_INDEV_STATE_REL;
static lv_indev_state_t touchpad_old_state = LV_INDEV_STATE_REL;

//----------- prototypes ----------
static void disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p);
static bool touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static bool touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
  Q_UNUSED(indev_drv);
  bool ret = false;
  data->point.x = touchpad_x;
  data->point.y = touchpad_y;
  data->state = touchpad_state; //LV_INDEV_STATE_REL; //LV_INDEV_STATE_PR or LV_INDEV_STATE_REL;
  if ( touchpad_state != touchpad_old_state) {
      touchpad_old_state = touchpad_state;
      LOG("mouse down: x=%d y=%d", touchpad_x, touchpad_y);
  }
  return ret; /*No buffering now so no more data read*/
}

static void init_pointer(void)
{
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = (void (*)(struct _lv_indev_drv_t *, lv_indev_data_t * )) touchpad_read;
    lv_indev_drv_register(&indev_drv);
}

static void init_disp()
{
  static lv_disp_draw_buf_t draw_buf_dsc_1;
  static lv_color_t buf_1[DISP_BUF_SIZE];                          /*A buffer for 10 rows*/
  lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, DISP_BUF_SIZE);   /*Initialize the display buffer*/

  static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
  lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

  /*Set up the functions to access to your display*/

  /*Set the resolution of the display*/
  disp_drv.hor_res = LV_HOR_RES_MAX;
  disp_drv.ver_res = LV_VER_RES_MAX;

  /*Used to copy the buffer's content to the display*/
  disp_drv.flush_cb = disp_flush;

  /*Set a display buffer*/
  disp_drv.draw_buf = &draw_buf_dsc_1;

#if LV_USE_GPU
  /*Fill a memory array with a color*/
  disp_drv.gpu_fill_cb = gpu_fill;
#endif

  /*Finally register the driver*/
  lv_disp_drv_register(&disp_drv);
}

void lv_integr_run(void)
{
  LOG("runNative from LOG");

  lv_init();
  init_disp();
  init_pointer();
}

void lv_integr_update_pointer(int x, int y, int state)
{
    touchpad_x = x;
    touchpad_y = y;
    touchpad_state = (lv_indev_state_t) state;
}

void lv_integr_timer(void) {
      static int cnt = 0;
      lv_tick_inc(LVGL_TICK_TIME);
      if (cnt++ > 4) {
        cnt = 0;
        lv_task_handler();
      }

}

static void disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p)
{
  bool last = lv_disp_flush_is_last( disp);
  updateDisplay(area, color_p, last);
  lv_disp_flush_ready(disp);         /* Indicate you are ready with the flushing*/
}

#ifdef __cplusplus
};
#endif

//----------- C++ functions ---------

static void updateDisplay (const lv_area_t * area, lv_color_t * color_p, bool last)
{
    int32_t x, y;
    lv_color_t pixel;

    QRgb pixel_output;
#if 1
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            pixel = *color_p;
            pixel_output = pixel.ch.red << (16 + 3);
            pixel_output |= pixel.ch.green << (8 + 2);
            pixel_output |= pixel.ch.blue << 3;

            gMainObj->display_image.setPixelColor(x,y, pixel_output);
            color_p++;
        }
    }
    if (last) {
        gMainObj->ui->lb_display->setPixmap(QPixmap::fromImage(gMainObj->display_image));
    }
#endif

}

