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



void init_LED(void) {
    rcc_periph_clock_enable(RCC_GPIOD);
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO15 | GPIO14 | GPIO13 | GPIO12);
    gpio_clear(GPIOD, GPIO15);
}

void init_timer(void) {
    rcc_periph_clock_enable(RCC_TIM2);
    timer_set_prescaler(TIM2, 8399); // Предделитель (84 МГц / (8399 + 1) = 10 кГц)
    timer_set_period(TIM2, 9999); // Период (10 кГц / (9999 + 1) = 1 Гц)
    timer_enable_counter(TIM2); // Запускаем таймер
}

void timer_delay(uint32_t ms) {
    for (uint32_t i = 0; i < ms; i++) {
        timer_set_counter(TIM2, 0);
        while (timer_get_counter(TIM2) < 1000); // Ждем 1000 тиков
    }

     // timer_disable_counter(TIM2); // Останавливаем таймер
    


}


int main(void) {
    init_gpio();
    init_LED();
    init_timer();

    while (1) {
        // Движение вправо 512

        for (volatile uint32_t i = 0; i < 512; i++) {

            for (uint8_t step = 0; step < 8; step++) {
                step_motor_right(step);
               
                timer_delay(1000);
                
            }
            gpio_toggle(GPIOD, GPIO15);
        }

        // Движение влево 256
        for (volatile uint32_t i = 0; i < 256; i++) {
            for (uint8_t step = 0; step < 8; step++) {
                step_motor_left(step);
               
                timer_delay(1000); // Задержка 500 мс
            }

              gpio_toggle(GPIOD, GPIO14);
        }
    }

    return 0; // Этот код никогда не будет достигнут}
}
