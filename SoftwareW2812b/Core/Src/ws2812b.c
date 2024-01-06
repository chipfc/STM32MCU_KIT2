#include <ws2812b.h>
#include "main.h"

static RGB_t leds[NUMBER_OF_LEDS] = {0};
static WS2812B_t ws2812b = {
	  .leds = leds,
	  .num_leds = NUMBER_OF_LEDS,
	  .pin = GPIO_PIN_WS2812,
	  .port = GPIO_PORT_WS2812
	};



static uint8_t _updateCNT = 0;
void setAllLEDs(uint8_t red, uint8_t green, uint8_t blue);
void setLED(uint8_t red, uint8_t green, uint8_t blue, uint8_t ledIndex);
void setLEDData(uint8_t red, uint8_t green, uint8_t blue, uint8_t ledIndex);

void WS2812B_Write(WS2812B_t* ws2812b);

void animateSine(uint8_t *baseColor, float speed, float scaling, float dimming);


void initWs2812b(void)
{
	setAllLEDs(0x0, 0x0, 0x0);
}
void running(){
	uint8_t color[3] = {128, 0, 0};
	_updateCNT++;

	while(1)
	{
		_updateCNT++;
		animateSine(color, 0.02, 220, 0.8);
		HAL_Delay(2);
	}
}
//
void animateSine(uint8_t *baseColor, float speed, float scaling, float dimming)
{
	double shift = _updateCNT * speed;

	for (uint8_t leds = 0; leds < NUMBER_OF_LEDS; leds++)
	{
		uint8_t red = (baseColor[0] == 0) ? 0 : (baseColor[0] + sin(leds + shift) * scaling * baseColor[0] / 255) * dimming;
		uint8_t green = (baseColor[1] == 0) ? 0 : (baseColor[1] + sin(leds + shift) * scaling * baseColor[1] / 255) * dimming;
		uint8_t blue = (baseColor[2] == 0) ? 0 : (baseColor[2] + sin(leds + shift) * scaling * baseColor[2] / 255) * dimming;

		setLED(red, green, blue, leds);
	}
}

//Sets all LEDs to the same color of red, green, blue
void setAllLEDs(uint8_t red, uint8_t green, uint8_t blue)
{
	for (uint8_t led = 0; led < NUMBER_OF_LEDS; led++)
	{
		setLED(red, green, blue, led);
	}
}

//Sets one specific LED to the color of red, green, blue
void setLEDData(uint8_t red, uint8_t green, uint8_t blue, uint8_t ledIndex)
{
	leds[ledIndex].r = red;
	leds[ledIndex].g = green;
	leds[ledIndex].b = blue;
}
//Sets one specific LED to the color of red, green, blue
void setLED(uint8_t red, uint8_t green, uint8_t blue, uint8_t ledIndex)
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

void running_example(void){
	static   uint8_t current_led = 0;

	clear_ws2812b_buffer();
	current_led = (current_led + 1) % ws2812b.num_leds;
	setLEDData(0,0,55, current_led);
	setLEDData(0,55,0, (current_led+1)% ws2812b.num_leds);
	setLEDData(55,0,0, (current_led+2)% ws2812b.num_leds);
//	leds[current_led].b= 55;
//	leds[(current_led+1)% ws2812b.num_leds].g = 55;
//	leds[(current_led+2)% ws2812b.num_leds].r = 55;

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
