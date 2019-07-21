#include "device.h"
#include <cstdint>

enum gpioPullMode : uint8_t { GPIO_PULL_OFF, GPIO_PULL_UP, GPIO_PULL_DOWN };
enum gpioDirection : uint8_t { GPIO_DIRECTION_OFF, GPIO_DIRECTION_IN, GPIO_DIRECTION_OUT };
enum gpioPort : uint8_t { GPIO_PORTA = 0, GPIO_PORTB = 1, GPIO_PORTC = 2, GPIO_PORTD = 3, GPIO_PORTE = 4 };
enum gpioFunc : uint8_t { GPIO_FUNC_A, GPIO_FUNC_B, GPIO_FUNC_C, GPIO_FUNC_D, GPIO_FUNC_E, GPIO_FUNC_F, GPIO_FUNC_G, GPIO_FUNC_H, GPIO_FUNC_I };
constexpr uint32_t GPIO_PIN_FUNCTION_OFF = 0xffffffffu;

constexpr uint8_t definePin(const enum gpioPort port, const uint8_t pin) noexcept {
    return ((static_cast<uint8_t>(port) & 0x07U) << 5U) + (pin & 0x1FU);  // binary compatable with atmel HAL
}

constexpr gpioPort getPort(const uint8_t pin) noexcept {
    return static_cast<gpioPort>(pin >> 5u);
}

constexpr uint8_t getPin(const uint8_t pin) noexcept {
    return pin & 0x1Fu;
}

constexpr uint8_t LED_BLUE  = definePin(GPIO_PORTA, 11);
constexpr uint8_t LED_RED   = definePin(GPIO_PORTB, 8);
constexpr uint8_t LED_GREEN = definePin(GPIO_PORTB, 9);


void gpio_set_pin_direction(const uint8_t pin, const gpioDirection direction) {
	const gpioPort port = getPort(pin);
	const uint32_t mask = 1U << getPin(pin);

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
    const gpioPort port = getPort(pin);
    const uint32_t mask = 1U << getPin(pin);
    PORT->Group[port].OUTTGL.reg = mask;
}

void delayMS(uint32_t t) {
    t *= 1000;      // hardcoded to handle the default CPU frequency
    while(t-- > 0) {
        // NOOP for delay
        asm volatile ("");
    }
}

int main() {
    SystemCoreClockUpdate();

    gpio_set_pin_direction(LED_BLUE, GPIO_DIRECTION_OUT);
    gpio_set_pin_direction(LED_GREEN, GPIO_DIRECTION_OUT);
    gpio_set_pin_direction(LED_RED, GPIO_DIRECTION_OUT);

    int delay = 250;

    while(1) {
        gpio_toggle_pin_level(LED_BLUE);
        delayMS(delay);
        gpio_toggle_pin_level(LED_GREEN);
        delayMS(delay);
        gpio_toggle_pin_level(LED_RED);
        delayMS(delay);

    }
}
