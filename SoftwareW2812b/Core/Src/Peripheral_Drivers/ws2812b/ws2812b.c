#include "ws2812b.h"
#include "main.h"

static RGB_t leds[NUMBER_OF_LEDS] = {0};
static WS2812B_t ws2812b = {
	  .leds = leds,
	  .num_leds = NUMBER_OF_LEDS,
	  .pin = GPIO_PIN_WS2812,
	  .port = GPIO_PORT_WS2812
	};




void WS2812B_Write(WS2812B_t* ws2812b);


void clear_all_leds(void)
{
	set_all_leds(0x0, 0x0, 0x0);
}

//Sets all LEDs to the same color of red, green, blue
void set_all_leds(uint8_t red, uint8_t green, uint8_t blue)
{
	for (uint8_t led = 0; led < NUMBER_OF_LEDS; led++)
	{
		set_led(red, green, blue, led);
	}
}

//Sets one specific LED to the color of red, green, blue
void set_led_data(uint8_t red, uint8_t green, uint8_t blue, uint8_t ledIndex)
{
	leds[ledIndex].r = red;
	leds[ledIndex].g = green;
	leds[ledIndex].b = blue;
}
//Sets one specific LED to the color of red, green, blue
void set_led(uint8_t red, uint8_t green, uint8_t blue, uint8_t ledIndex)
{
	leds[ledIndex].r = red;
	leds[ledIndex].g = green;
	leds[ledIndex].b = blue;

	WS2812B_Write(&ws2812b);
}


void clear_ws2812b_buffer(void){
	for(uint8_t i = 0; i < NUMBER_OF_LEDS; i ++){
		memset(&leds[i], 0, sizeof(RGB_t));
	}
}
void display_ws2812b(void){
	WS2812B_Write(&ws2812b);
}


static inline void send_zero(GPIO_TypeDef *port, uint16_t pin) {
	port->ODR |= pin; //Pin HIGH - 120ns

	// +300ns
	__asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

  	port->ODR &= ~(pin); //Pin LOW - 120ns

  // +680ns
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  __asm__ volatile("nop\nnop\nnop\nnop\nnop");

}

static inline void send_one(GPIO_TypeDef *port, uint16_t pin) {
  port->ODR |= pin; //Pin HIGH - 120ns

  // +680ns
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  __asm__ volatile("nop\nnop\nnop\nnop\nnop");


  port->ODR &= ~(pin);//Pin LOW - 120ns

  // +300ns
  __asm__ volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

}
void WS2812B_Write(WS2812B_t* ws2812b) {
  for (uint16_t i = 0; i < ws2812b->num_leds; i++) {
    RGB_t led = ws2812b->leds[i];

    // Green
    for (uint8_t mask = 0x80; mask != 0; mask >>= 1) {
      if (led.g & mask) {
        send_one(ws2812b->port, ws2812b->pin);
      } else {
        send_zero(ws2812b->port, ws2812b->pin);
      }
    }

    // Red
    for (uint8_t mask = 0x80; mask != 0; mask >>= 1) {
      if (led.r & mask) {
        send_one(ws2812b->port, ws2812b->pin);
      } else {
        send_zero(ws2812b->port, ws2812b->pin);
      }
    }

    // Blue
    for (uint8_t mask = 0x80; mask != 0; mask >>= 1) {
      if (led.b & mask) {
        send_one(ws2812b->port, ws2812b->pin);
      } else {
        send_zero(ws2812b->port, ws2812b->pin);
      }
    }
  }

  // Reset code - optional, may not need this piece of code
  for (uint16_t i = 0; i < 600; i++) {
    __asm__ volatile("nop\nnop\n");
  }
}
