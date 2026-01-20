#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"


// A function to specify delays in milliseconds
void delay_ms(int t) {
  vTaskDelay(t /portTICK_PERIOD_MS);
}


#define DRIVER_SEAT GPIO_NUM_4
#define PASS_SEAT GPIO_NUM_5
#define DRIVER_BELT GPIO_NUM_6
#define PASS_BELT GPIO_NUM_7
#define IGN_BUTTON GPIO_NUM_9
#define GREEN_LED GPIO_NUM_16
#define YELLOW_LED GPIO_NUM_17
#define BUZZER GPIO_NUM_18
#define LOOP_DELAY_MS 25


bool welcome = true;        // Flag to indicate a button press event
bool engine = true;
bool message = true;
bool green = true;
bool one_try = true;


void app_main(void)
{
  gpio_reset_pin(DRIVER_SEAT);
  gpio_set_direction(DRIVER_SEAT, GPIO_MODE_INPUT);
  gpio_pulldown_en(DRIVER_SEAT);


  gpio_reset_pin(PASS_SEAT);
  gpio_set_direction(PASS_SEAT, GPIO_MODE_INPUT);
  gpio_pulldown_en(PASS_SEAT);


  gpio_reset_pin(DRIVER_BELT);
  gpio_set_direction(DRIVER_BELT, GPIO_MODE_INPUT);
  gpio_pulldown_en(DRIVER_BELT);


  gpio_reset_pin(PASS_BELT);
  gpio_set_direction(PASS_BELT, GPIO_MODE_INPUT);
  gpio_pulldown_en(PASS_BELT);


  gpio_reset_pin(IGN_BUTTON);
  gpio_set_direction(IGN_BUTTON, GPIO_MODE_INPUT);
  gpio_pulldown_en(IGN_BUTTON);


  gpio_reset_pin(GREEN_LED);
  gpio_set_direction(GREEN_LED, GPIO_MODE_OUTPUT);
  gpio_set_level(GREEN_LED, 0);


  gpio_reset_pin(YELLOW_LED);
  gpio_set_direction(YELLOW_LED, GPIO_MODE_OUTPUT);
  gpio_set_level(YELLOW_LED, 0);


  gpio_reset_pin(BUZZER);
  gpio_set_direction(BUZZER, GPIO_MODE_OUTPUT);
  gpio_set_level(BUZZER, 0);


  while (one_try) {
    if (gpio_get_level(DRIVER_SEAT) && welcome) {
      printf("Welcome to enhanced alarm system model 218-W25!\n");
      welcome = false;
    }
    if (green && gpio_get_level(DRIVER_SEAT) && gpio_get_level(PASS_SEAT) && gpio_get_level(DRIVER_BELT) && gpio_get_level(PASS_BELT)) {
      gpio_set_level(GREEN_LED, 1);
    }
    else {
      gpio_set_level(GREEN_LED, 0);
    }
    if (gpio_get_level(IGN_BUTTON) && gpio_get_level(DRIVER_SEAT) && gpio_get_level(PASS_SEAT) && gpio_get_level(DRIVER_BELT) && gpio_get_level(PASS_BELT)) {
      gpio_set_level(GREEN_LED, 0);
      gpio_set_level(YELLOW_LED, 1);
      if (engine) {
        printf("Engine started!\n");
        green = false;
        engine = false;
        one_try = false;
      }
    }
      if (message && gpio_get_level(IGN_BUTTON) && !(gpio_get_level(DRIVER_SEAT) && gpio_get_level(PASS_SEAT) && gpio_get_level(DRIVER_BELT) && gpio_get_level(PASS_BELT))) {
        gpio_set_level(BUZZER, 1);
        if (message) {
          printf("Ignition inhibited.\n");
        }
        if (!gpio_get_level(DRIVER_SEAT)) {
          printf("Driver seat not occupied.\n");
        }
        if (!gpio_get_level(PASS_SEAT)) {
          printf("Passenger seat not occupied.\n");
        }
        if (!gpio_get_level(DRIVER_BELT)) {
          printf("Driver seatbelt not fastened.\n");
        }
        if (!gpio_get_level(PASS_BELT)) {
          printf("Passenger seatbelt not fastened.\n");
        }
        message = false;
        one_try = false;
      }
      delay_ms(LOOP_DELAY_MS);
  }
}