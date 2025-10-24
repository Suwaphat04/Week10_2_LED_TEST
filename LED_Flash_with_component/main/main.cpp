#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "LED.h"

// 🧩 กำหนด GPIO ของแต่ละหลอด
LED led1(16);
LED led2(17);
LED led3(5);
LED led4(18);
LED led5(19);
LED led6(21);
LED led7(22);
LED led8(23);

LED leds[] = {led1, led2, led3, led4, led5, led6, led7, led8};
const int LED_COUNT = sizeof(leds) / sizeof(leds[0]);

#define DELAY_MS 150

// ปิดไฟทุกดวง
void all_off() {
    for (int i = 0; i < LED_COUNT; i++) leds[i].OFF();
}

// แสดง pattern ใน Serial Monitor
void print_pattern(int active1, int active2 = -1) {
    for (int i = 0; i < LED_COUNT; i++) {
        if (i == active1 || i == active2)
            printf("*");
        else
            printf(".");
    }
    printf("\n");
}

// 🔹 Pattern 1: ไฟวิ่งดวงเดียว
void pattern_single_run() {
    printf("\n--- Pattern 1: Single LED Running ---\n");
    for (int i = 0; i < LED_COUNT; i++) {
        all_off();
        leds[i].ON();
        print_pattern(i);
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
    }
}

// 🔹 Pattern 2: วิ่งสวนกันตรงกลาง
void pattern_meet_in_center() {
    printf("\n--- Pattern 2: Meet in Center ---\n");
    for (int i = 0; i < LED_COUNT / 2; i++) {
        all_off();
        leds[i].ON();
        leds[LED_COUNT - 1 - i].ON();
        print_pattern(i, LED_COUNT - 1 - i);
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
    }
    for (int i = (LED_COUNT / 2) - 1; i >= 0; i--) {
        all_off();
        leds[i].ON();
        leds[LED_COUNT - 1 - i].ON();
        print_pattern(i, LED_COUNT - 1 - i);
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
    }
}

// 🔹 Pattern 3: วิ่งไปกลับ
void pattern_bounce() {
    printf("\n--- Pattern 3: Bounce LED ---\n");
    // ไปขวา
    for (int i = 0; i < LED_COUNT; i++) {
        all_off();
        leds[i].ON();
        print_pattern(i);
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
    }
    // กลับซ้าย
    for (int i = LED_COUNT - 2; i >= 0; i--) {
        all_off();
        leds[i].ON();
        print_pattern(i);
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
    }
}

// 🧠 Main Task
extern "C" void app_main(void)
{
    printf("\n🚀 ESP32 LED Pattern Challenge Started!\n");
    while (1) {
        pattern_single_run();
        pattern_meet_in_center();
        pattern_bounce();
    }
}
