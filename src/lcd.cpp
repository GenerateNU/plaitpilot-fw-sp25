#include "lcd.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <lvgl.h>
#include <map>
#include <string>

#define TFT_MISO 19 // (leave TFT SDO disconnected if other SPI devices share MISO)
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_RST 15 // Reset pin (could connect to RST pin)
#define TFT_CS 4   // Chip select control pin
#define TFT_DC 2   // Data Command control pin

#define MIN_AMOUNT 0
#define MAX_AMOUNT 50

#define MIN_SIZE 0
#define MAX_SIZE 6 

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI,
                                        TFT_SCLK, TFT_RST, TFT_MISO);

// Labels for the size and quantity
static lv_obj_t *size_label;
static lv_obj_t *quantity_label;

// Declare bars globally but initialize in lcd_init()
static lv_obj_t *amountBar;
static lv_obj_t *sizeBar;

std::map<int, std::string> sizeMap = {
    {0, "XS"},
    {1, "S"},
    {2, "M"},
    {3, "L"},
    {4, "XL"},
    {5, "XXL"},
    {6, "XXXL"}
};

void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    uint16_t *buf16 = (uint16_t *)px_map;
    int32_t x1 = area->x1;
    int32_t y1 = area->y1;
    int32_t w = area->x2 - area->x1 + 1;
    int32_t h = area->y2 - area->y1 + 1;

    tft.startWrite();
    tft.setAddrWindow(x1, y1, w, h);

    for (int32_t row = 0; row < h; row++)
    {
        for (int32_t col = 0; col < w; col++)
        {
            tft.pushColor(*buf16++);
        }
    }

    tft.endWrite();
    lv_display_flush_ready(disp);
}

void lcd_init()
{
    tft.begin();
    tft.setRotation(3);

    lv_init();

    static lv_color_t buf1[320 * 10];
    static lv_display_t *disp = lv_display_create(320, 240);

    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    size_label = lv_label_create(lv_screen_active());
    lv_label_set_text(size_label, "Size: XS");
    lv_obj_align(size_label, LV_ALIGN_CENTER, -75, -60);

    quantity_label = lv_label_create(lv_screen_active());
    lv_label_set_text(quantity_label, "Quantity: 0");
    lv_obj_align(quantity_label, LV_ALIGN_CENTER, -60, 5);

    // Initialize bars 
    amountBar = lv_bar_create(lv_screen_active());
    sizeBar = lv_bar_create(lv_screen_active());

    // Setting up bars
    lv_bar_set_range(amountBar, MIN_AMOUNT, MAX_AMOUNT);
    lv_bar_set_range(sizeBar, MIN_SIZE, MAX_SIZE);
    lv_obj_set_size(amountBar, 200, 35);
    lv_obj_set_size(sizeBar, 200, 35);
    lv_obj_align(amountBar, LV_ALIGN_CENTER, 0, 35);
    lv_obj_align(sizeBar, LV_ALIGN_CENTER, 0, -30);
    lv_bar_set_value(amountBar, 0, LV_ANIM_OFF);
    lv_bar_set_value(sizeBar, 0, LV_ANIM_OFF);
}

// Update the display with live potentiometer values**
void update_pot_display(PotValues values) {
    static char size_text[16];
    static char quantity_text[16];

    auto it = sizeMap.find(values.size);
    const char *size_str = (it != sizeMap.end()) ? it->second.c_str() : "Unknown";

    snprintf(size_text, sizeof(size_text), "Size: %s", size_str);
    snprintf(quantity_text, sizeof(quantity_text), "Quantity: %d", values.quantity);

    lv_label_set_text(size_label, size_text);
    lv_label_set_text(quantity_label, quantity_text);

    lv_bar_set_value(amountBar, values.quantity, LV_ANIM_ON);
    lv_bar_set_value(sizeBar, values.size, LV_ANIM_ON);

    // Force LVGL to refresh
    lv_refr_now(NULL);
}
