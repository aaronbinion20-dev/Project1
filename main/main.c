#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"


// A function to specify delays in milliseconds
void delay_ms(int t) {
  vTaskDelay(t /portTICK_PERIOD_MS);
}


// Defines GPIO_NUM_4 as DRIVER_SEAT
#define DRIVER_SEAT GPIO_NUM_4
// Defines GPIO_NUM_5 as PASS_SEAT
#define PASS_SEAT GPIO_NUM_5
// Defines GPIO_NUM_6 as DRIVER_BELT
#define DRIVER_BELT GPIO_NUM_6
// Defines GPIO_NUM_7 as PASS_BELT
#define PASS_BELT GPIO_NUM_7
// Defines GPIO_NUM_9 as IGN_BUTTON
#define IGN_BUTTON GPIO_NUM_9
// Defines GPIO_NUM_16 as GREEN_LED
#define GREEN_LED GPIO_NUM_16
// Defines GPIO_NUM_17 as YELLOW_LED
#define YELLOW_LED GPIO_NUM_17
// Defines GPIO_NUM_18 as BUZZER
#define BUZZER GPIO_NUM_18
// Defines LOOP_DELAY_MS as 25
#define LOOP_DELAY_MS 25


// Bool to display welcome message
bool welcome = true;
// Bool to display engine message       
bool engine = true;
//Bool to display post-ignition message
bool message = true;
// Bool to turn on / off green LED
bool green = true;
// Bool to turn off while loop after ignition
bool one_try = true;


void app_main(void)
{
  // Reset DRIVER_SEAT, set it as input, set it as pulldown
  gpio_reset_pin(DRIVER_SEAT);
  gpio_set_direction(DRIVER_SEAT, GPIO_MODE_INPUT);
  gpio_pulldown_en(DRIVER_SEAT);
  
  // Reset PASS_SEAT, set it as input, set it as pulldown
  gpio_reset_pin(PASS_SEAT);
  gpio_set_direction(PASS_SEAT, GPIO_MODE_INPUT);
  gpio_pulldown_en(PASS_SEAT);


  // Reset DRIVER_BELT, set it as input, set it as pulldown
  gpio_reset_pin(DRIVER_BELT);
  gpio_set_direction(DRIVER_BELT, GPIO_MODE_INPUT);
  gpio_pulldown_en(DRIVER_BELT);


  // Reset PASS_BELT, set it as input, set it as pulldown
  gpio_reset_pin(PASS_BELT);
  gpio_set_direction(PASS_BELT, GPIO_MODE_INPUT);
  gpio_pulldown_en(PASS_BELT);


  // Reset IGN_BUTTON, set it as input, set it as pulldown
  gpio_reset_pin(IGN_BUTTON);
  gpio_set_direction(IGN_BUTTON, GPIO_MODE_INPUT);
  gpio_pulldown_en(IGN_BUTTON);


  // Reset GREEN_LED, set it as output, set level to 0
  gpio_reset_pin(GREEN_LED);
  gpio_set_direction(GREEN_LED, GPIO_MODE_OUTPUT);
  gpio_set_level(GREEN_LED, 0);


  // Reset YELLOW_LED, set it as output, set level to 0
  gpio_reset_pin(YELLOW_LED);
  gpio_set_direction(YELLOW_LED, GPIO_MODE_OUTPUT);
  gpio_set_level(YELLOW_LED, 0);


  // Reset BUZZER, set it as output, set level to 0
  gpio_reset_pin(BUZZER);
  gpio_set_direction(BUZZER, GPIO_MODE_OUTPUT);
  gpio_set_level(BUZZER, 0);


  // Iterate while loop until one_try is false
  while (one_try) {
    // If driver seat & welcome message are true, print welcome message
    // and set welcome to false
    if (gpio_get_level(DRIVER_SEAT) && welcome) {
      printf("Welcome to enhanced alarm system model 218-W25!\n");
      welcome = false;
    }
    // If driver seat & passenger seat & driver belt & passenger belt
    // are true, set green led to 1, else 0
    if (green && gpio_get_level(DRIVER_SEAT) && gpio_get_level(PASS_SEAT) && gpio_get_level(DRIVER_BELT) && gpio_get_level(PASS_BELT)) {
      gpio_set_level(GREEN_LED, 1);
    }
    else {
      gpio_set_level(GREEN_LED, 0);
    // If driver seat & passenger seat & driver belt & passenger belt
    // & ignition button are true, set green LED to 0,
    // yellow LED to 1, and if engine is true print Engine started, 
    // set green to false,engine to false, and one_try to false
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
      // If either driver seat or passenger seat or driver belt or 
      // passenger belt is off and ign_button and message are true, 
      // print ignition inhibited if message is true, 
      //display correlating error messages for false inputs, 
      // set buzzer to 1, set message to false, set one_try to false
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
      // Delay the while loop by LOOP_DELAY_MS
      delay_ms(LOOP_DELAY_MS);
  }
}