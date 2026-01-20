#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"


#define LED_PIN GPIO_NUM_5   // Choose your LED pin
#define BUTTON_PIN GPIO_NUM_4   // Choose your button pin

#define BUTTON_PIN2 GPIO_NUM_6

void app_main(void) {


    gpio_config_t led_conf = {
        .pin_bit_mask = (1ULL << LED_PIN),
        .mode = GPIO_MODE_OUTPUT,          
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&led_conf);


    gpio_config_t button_config = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,          
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE  
    };
    gpio_config(&button_config);

    gpio_config_t button_config2 = {
        .pin_bit_mask = (1ULL << BUTTON_PIN2),
        .mode = GPIO_MODE_INPUT,          
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE  
    };
    gpio_config(&button_config2);

    bool light = false;
    bool state = false;

    while (1) {
      if ((gpio_get_level(BUTTON_PIN) == 0) && !state && (gpio_get_level(BUTTON_PIN2) == 1)) {
        state = true;
      }
      if (!(gpio_get_level(BUTTON_PIN) == 0) && state && (gpio_get_level(BUTTON_PIN2) == 1)) {
        gpio_set_level(LED_PIN, light);
        light = !light;
        state = false;
      }
      vTaskDelay(1000 / portTICK_PERIOD_MS); 
      }
    }