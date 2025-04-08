#include "potentiometer.h"
#ifndef LCD_H
#define LCD_H

#include <lvgl.h>

void lcd_init();
void create_text_label(const char *str, lv_align_t align, int32_t x, int32_t y);
void update_pot_display(PotValues values);
void button_pressed();
void clear_button_label();
#endif  // LCD_Hv