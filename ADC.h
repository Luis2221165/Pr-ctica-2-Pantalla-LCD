#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Prototipos de funciones para la inicialización y lectura del ADC
void initADC(int referencia, int justificacion, int preescaler);
uint8_t readADC(uint8_t canal);
void startADCISR(uint8_t canal);

#endif /* ADC_H_ */
