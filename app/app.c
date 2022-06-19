
#include "../lvgl/lvgl.h"

#ifdef USE_SIM_LOG  // for dimulator this is defined in .pro file
#include "log.h"
#undef LV_LOG_USER
#define LV_LOG_USER LOG
#undef LV_LOG_ERROR
#define LV_LOG_ERROR LOG_E
#undef LV_LOG_WARN
#define LV_LOG_WARN LOG_W
#endif

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}

void lvgl_app_main (void)
{
    lv_obj_t * label;

    lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);
    label = lv_label_create(btn1);
    lv_label_set_text(label, "Button");

}
