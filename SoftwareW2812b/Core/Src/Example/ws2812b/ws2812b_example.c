#include "ws2812b.h"



void running_example(void){
	static   uint8_t current_led = 0;

	clear_ws2812b_buffer();
	current_led = (current_led + 1) % NUMBER_OF_LEDS;
	set_led(0, 0, 55, current_led);
	set_led(0, 55, 0, (current_led+1)% NUMBER_OF_LEDS);
	set_led(55, 0, 0, (current_led+2)% NUMBER_OF_LEDS);
}


void running_example_2(void){
	static   uint8_t current_led = 0;

	set_all_leds(0, 0, 55);
	HAL_Delay(1000);
	set_all_leds(0, 55, 0);

	HAL_Delay(1000);
	set_all_leds(55, 0, 0);

	HAL_Delay(1000);
}
