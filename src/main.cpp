#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/syscfg.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/common.h>

#define STEP_PIN_A GPIO0
#define STEP_PIN_B GPIO1
#define STEP_PIN_C GPIO2
#define STEP_PIN_D GPIO3

void init_gpio(void) {
    rcc_periph_clock_enable(RCC_GPIOA);

    // Настройка пинов A0, A1, A2 и A3 как выходы
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, STEP_PIN_A | STEP_PIN_B | STEP_PIN_C | STEP_PIN_D);
}

void step_motor_right(uint8_t step) {
    switch(step) {
        case 0:
            gpio_set(GPIOA, STEP_PIN_A);
            gpio_clear(GPIOA, STEP_PIN_B | STEP_PIN_C | STEP_PIN_D);
            break;
        case 1:
            gpio_set(GPIOA, STEP_PIN_A | STEP_PIN_B);
            gpio_clear(GPIOA, STEP_PIN_C | STEP_PIN_D);
            break;
        case 2:
            gpio_set(GPIOA, STEP_PIN_B);
            gpio_clear(GPIOA, STEP_PIN_A | STEP_PIN_C | STEP_PIN_D);
            break;
        case 3:
            gpio_set(GPIOA, STEP_PIN_B | STEP_PIN_C);
            gpio_clear(GPIOA, STEP_PIN_A | STEP_PIN_D);
            break;
        case 4:
            gpio_set(GPIOA, STEP_PIN_C);
            gpio_clear(GPIOA, STEP_PIN_A | STEP_PIN_B | STEP_PIN_D);
            break;
        case 5:
            gpio_set(GPIOA, STEP_PIN_C | STEP_PIN_D);
            gpio_clear(GPIOA, STEP_PIN_A | STEP_PIN_B);
            break;
        case 6:
            gpio_set(GPIOA, STEP_PIN_D);
            gpio_clear(GPIOA, STEP_PIN_A | STEP_PIN_B | STEP_PIN_C);
            break;
        case 7:
            gpio_set(GPIOA, STEP_PIN_A | STEP_PIN_D);
            gpio_clear(GPIOA, STEP_PIN_B | STEP_PIN_C);
            break;
    }
}

void step_motor_left(uint8_t step) {
    switch(step) {
        case 0:
            gpio_set(GPIOA, STEP_PIN_A | STEP_PIN_D);
            gpio_clear(GPIOA, STEP_PIN_B | STEP_PIN_C);
            break;
        case 1:
            gpio_set(GPIOA, STEP_PIN_D);
            gpio_clear(GPIOA, STEP_PIN_A | STEP_PIN_B | STEP_PIN_C);
            break;
        case 2:
            gpio_set(GPIOA, STEP_PIN_C | STEP_PIN_D);
            gpio_clear(GPIOA, STEP_PIN_A | STEP_PIN_B);
            break;
        case 3:
            gpio_set(GPIOA, STEP_PIN_C);
            gpio_clear(GPIOA, STEP_PIN_A | STEP_PIN_B | STEP_PIN_D);
            break;
        case 4:
            gpio_set(GPIOA, STEP_PIN_B | STEP_PIN_C);
            gpio_clear(GPIOA, STEP_PIN_A | STEP_PIN_D);
            break;
        case 5:
            gpio_set(GPIOA, STEP_PIN_B);
            gpio_clear(GPIOA, STEP_PIN_A | STEP_PIN_C | STEP_PIN_D);
            break;
        case 6:
            gpio_set(GPIOA, STEP_PIN_A | STEP_PIN_B);
            gpio_clear(GPIOA, STEP_PIN_C | STEP_PIN_D);
            break;
        case 7:
            gpio_set(GPIOA, STEP_PIN_A);
            gpio_clear(GPIOA, STEP_PIN_B | STEP_PIN_C | STEP_PIN_D);
            break;
    }
}

void delay(uint32_t delay) {
    for (volatile uint32_t i = 0; i < delay; i++) {
        asm("nop");
    }
}

int main(void) {
    init_gpio();

    while (1) {

for(volatile uint32_t i=0; i<512; i++){

        for (uint8_t step = 0; step < 8; step++) {
            step_motor_right(step);
            delay(1000); // Увеличьте или уменьшите задержку для регулировки скорости
        }

    }


for(volatile uint32_t i=0; i<256; i++){

        for (uint8_t step = 0; step < 8; step++) {
            step_motor_left(step);
            delay(1000); // Увеличьте или уменьшите задержку для регулировки скорости
        }

    }
}
    return 0;
}