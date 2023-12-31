#pragma once
#include <stdint.h>
#include "stm32f1xx_hal.h"
#include <math.h>



#define	GPIO_PORT_WS2812 	GPIOB
#define GPIO_PIN_WS2812 	GPIO_PIN_3
#define NUMBER_OF_LEDS 		4


typedef struct RGB_t {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGB_t;

typedef struct WS2812B_t {
  RGB_t* leds;
  uint16_t num_leds;
  GPIO_TypeDef* port;
  uint16_t pin;
} WS2812B_t;


void set_all_leds(uint8_t red, uint8_t green, uint8_t blue);
void set_led(uint8_t red, uint8_t green, uint8_t blue, uint8_t ledIndex);
void set_led_data(uint8_t red, uint8_t green, uint8_t blue, uint8_t ledIndex);


void  clear_all_leds(void);
void display_ws2812b(void);
