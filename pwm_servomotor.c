#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definições
#define PWM_PIN 22          // GPIO conectado ao servomotor (pino 22)
#define CLOCK_DIV 125       // Divisor de clock (125 MHz / 125 = 1 MHz)
#define PWM_WRAP 20000      // Período do PWM em microssegundos (20 ms)
#define DELAY_MS 10         // Atraso entre ajustes (10 ms)
#define STEP_US 5           // Incremento/decremento do ciclo ativo (5 µs)

// Função para configurar o PWM
void setup_pwm(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM); // Configura o pino para função PWM
    uint slice_num = pwm_gpio_to_slice_num(pin); // Obtém o slice do PWM

    // Configura o divisor de clock para 125 (125 MHz / 125 = 1 MHz)
    pwm_set_clkdiv(slice_num, CLOCK_DIV);

    // Configura o período do PWM (wrap)
    pwm_set_wrap(slice_num, PWM_WRAP - 1);

    // Habilita o PWM
    pwm_set_enabled(slice_num, true);
}

// Função para definir o ciclo ativo (duty cycle)
void set_duty_cycle(uint pin, uint duty_us) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), duty_us);
}

// Função principal
int main() {
    stdio_init_all(); // Inicializa a comunicação serial (para debug)

    // Configura o PWM no pino definido
    setup_pwm(PWM_PIN);

    // Definição dos ciclos ativos
    uint duty_180 = 2400; // 2.400 µs (180 graus)
    uint duty_90 = 1470;  // 1.470 µs (90 graus)
    uint duty_0 = 500;    // 500 µs (0 graus)

    // Posição 180 graus
    printf("180 graus\n");
    set_duty_cycle(PWM_PIN, duty_180);
    sleep_ms(5000); // Aguarda 5 segundos
    
    // Posição 90 graus
    printf("90 graus\n");
    set_duty_cycle(PWM_PIN, duty_90);
    sleep_ms(5000); // Aguarda 5 segundos
    
    // Posição 0 graus
    printf("0 graus\n");
    set_duty_cycle(PWM_PIN, duty_0);
    sleep_ms(5000); // Aguarda 5 segundos

    // Movimentação do servomotor
    while (true) {
        // Movimentação suave entre 0° e 180°
        for (uint i = duty_0; i <= duty_180; i += STEP_US) {
            set_duty_cycle(PWM_PIN, i); // muda o duty cycle
            sleep_ms(DELAY_MS);
        }
        for (uint i = duty_180; i >= duty_0; i -= STEP_US) {
            set_duty_cycle(PWM_PIN, i); // muda o duty cycle
            sleep_ms(DELAY_MS);
        }
    }

    return 0;
}