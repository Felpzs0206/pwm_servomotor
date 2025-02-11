# Controle de Servo Motor com Raspberry Pi Pico

## Descrição
Este projeto utiliza um Raspberry Pi Pico para controlar um servomotor por meio do PWM (Pulse Width Modulation). O código configura o PWM no pino 22 e ajusta o ângulo do servo motor para 0°, 90° e 180°, além de realizar um movimento suave entre essas posições.

## Como funciona
1. O código configura o GPIO 22 para operar em modo PWM.
2. Define os ciclos de trabalho (duty cycle) para 0°, 90° e 180°.
3. Move o servo para cada uma dessas posições, aguardando 5 segundos entre elas.
4. Inicia um loop onde o servo se move suavemente de 0° a 180° e de volta.

## Estrutura do Código
- ```setup_pwm(pin)```: Configura o pino especificado para operar com PWM.
- ```set_duty_cycle(pin, duty_us)```: Ajusta o ciclo de trabalho do PWM para um valor específico.

## Vídeo demonstração
