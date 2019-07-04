#include "device.h"
#include <cstdint>

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7
#define GPIO_PIN_FUNCTION_I 8

#define CLK_ALARM GPIO(GPIO_PORTA, 1)
#define BATLVL GPIO(GPIO_PORTA, 2)
#define MOD2P0 GPIO(GPIO_PORTA, 4)
#define MOD2P1 GPIO(GPIO_PORTA, 5)
#define MOD2P2 GPIO(GPIO_PORTA, 6)
#define MOD2P3 GPIO(GPIO_PORTA, 7)
#define SYS_SDA GPIO(GPIO_PORTA, 8)
#define SYS_SCL GPIO(GPIO_PORTA, 9)
#define AIN GPIO(GPIO_PORTA, 10)
#define LED_BLUE GPIO(GPIO_PORTA, 11)
#define IMU_SDA GPIO(GPIO_PORTA, 12)
#define IMU_SCL GPIO(GPIO_PORTA, 13)
#define IMU_INT1 GPIO(GPIO_PORTA, 14)
#define IMU_INT2 GPIO(GPIO_PORTA, 15)
#define MEM_MISO GPIO(GPIO_PORTA, 16)
#define MEM_CLK GPIO(GPIO_PORTA, 17)
#define MEM_CS0 GPIO(GPIO_PORTA, 18)
#define MEM_MOSI GPIO(GPIO_PORTA, 19)
#define MOD1P2 GPIO(GPIO_PORTA, 20)
#define MOD1P3 GPIO(GPIO_PORTA, 21)
#define MOD1P0 GPIO(GPIO_PORTA, 22)
#define MOD1P1 GPIO(GPIO_PORTA, 23)
#define USB_N GPIO(GPIO_PORTA, 24)
#define USB_P GPIO(GPIO_PORTA, 25)
#define MEMCS3 GPIO(GPIO_PORTA, 27)
#define VBUS_DETECT GPIO(GPIO_PORTB, 2)
#define MOD2INT GPIO(GPIO_PORTB, 3)
#define LED_RED GPIO(GPIO_PORTB, 8)
#define LED_GREEN GPIO(GPIO_PORTB, 9)
#define MOD1INT GPIO(GPIO_PORTB, 10)
#define IMU_INT3 GPIO(GPIO_PORTB, 11)
#define MEMCS1 GPIO(GPIO_PORTB, 22)
#define MEMCS2 GPIO(GPIO_PORTB, 23)

#define GPIO_PIN(n) (((n)&0x1Fu) << 0)
#define GPIO_PORT(n) ((n) >> 5)
#define GPIO(port, pin) ((((port)&0x7u) << 5) + ((pin)&0x1Fu))
#define GPIO_PIN_FUNCTION_OFF 0xffffffff

enum gpio_pull_mode { GPIO_PULL_OFF, GPIO_PULL_UP, GPIO_PULL_DOWN };
enum gpio_direction { GPIO_DIRECTION_OFF, GPIO_DIRECTION_IN, GPIO_DIRECTION_OUT };
enum gpio_port { GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE };

void gpio_set_pin_direction(const uint8_t pin, const enum gpio_direction direction) {
	const uint8_t port = GPIO_PORT(pin);
	const uint32_t mask = 1U << GPIO_PIN(pin);

	switch (direction) {
	case GPIO_DIRECTION_OFF:
        PORT->Group[port].DIRCLR.reg = mask;
        PORT->Group[port].WRCONFIG.reg = PORT_WRCONFIG_WRPINCFG | (mask & 0xffff);
        PORT->Group[port].WRCONFIG.reg = PORT_WRCONFIG_HWSEL | PORT_WRCONFIG_WRPINCFG | ((mask & 0xffff0000) >> 16);
		break;

	case GPIO_DIRECTION_IN:
        PORT->Group[port].DIRCLR.reg = mask;
        PORT->Group[port].WRCONFIG.reg = PORT_WRCONFIG_WRPINCFG | PORT_WRCONFIG_INEN | (mask & 0xffff);
        PORT->Group[port].WRCONFIG.reg = PORT_WRCONFIG_HWSEL | PORT_WRCONFIG_WRPINCFG | PORT_WRCONFIG_INEN | ((mask & 0xffff0000) >> 16);
		break;

	case GPIO_DIRECTION_OUT:
	    PORT->Group[port].DIRSET.reg = mask;
        PORT->Group[port].WRCONFIG.reg = PORT_WRCONFIG_WRPINCFG | (mask & 0xffff);
        PORT->Group[port].WRCONFIG.reg = PORT_WRCONFIG_HWSEL | PORT_WRCONFIG_WRPINCFG | ((mask & 0xffff0000) >> 16);
		break;
	}
}

void gpio_toggle_pin_level(const uint8_t pin) {
    const uint8_t port = (enum gpio_port)GPIO_PORT(pin);
    const uint32_t mask = 1U << GPIO_PIN(pin);
    PORT->Group[port].OUTTGL.reg = mask;
}

//void gpio_set_pin_level(const uint8_t pin, const bool level) {
//	_gpio_set_level((enum gpio_port)GPIO_PORT(pin), 1U << GPIO_PIN(pin), level);
//}

void delayMS(int t) {
    while(t-- > 0) { }
}

int main() {
    SystemCoreClockUpdate();

    gpio_set_pin_direction(LED_BLUE, GPIO_DIRECTION_OUT);
    gpio_set_pin_direction(LED_GREEN, GPIO_DIRECTION_OUT);
    gpio_set_pin_direction(LED_RED, GPIO_DIRECTION_OUT);

    while(1) {
        gpio_toggle_pin_level(LED_BLUE);
        delayMS(100000);
        gpio_toggle_pin_level(LED_GREEN);
        delayMS(100000);
        gpio_toggle_pin_level(LED_RED);
        delayMS(100000);

    }
}