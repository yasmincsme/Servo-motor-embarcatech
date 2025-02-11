#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO 12
#define CLKDIV 125.0
#define WRAP 20000 

#define POSITION_180 2400
#define POSITION_90 1470
#define POSITION_0 500

uint get_slice() {
    gpio_set_function(SERVO, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(SERVO);
    pwm_set_clkdiv(slice, CLKDIV);
    pwm_set_wrap(slice, WRAP);
    pwm_set_enabled(slice, true);
    return slice;
}

void set_position(uint slice, uint16_t pulse_us) {
    uint cycle = (pulse_us * WRAP) / WRAP;
    pwm_set_gpio_level(SERVO, cycle);
}

int main() {
    stdio_init_all();

    uint slice = get_slice();

    set_position(slice, POSITION_180);
    sleep_ms(5000);
    set_position(slice, POSITION_90);
    sleep_ms(5000);
    set_position(slice, POSITION_0);
    sleep_ms(5000);

    while (true) {
        int i;
        for (i = POSITION_0; i <= POSITION_180; i += 5) {
            set_position(slice, i);
            sleep_ms(10);
        }
        for (i = POSITION_180; i>= POSITION_0; i-= 5) {
            set_position(slice, i);
            sleep_ms(10);
        }
    }
    return 0;
}