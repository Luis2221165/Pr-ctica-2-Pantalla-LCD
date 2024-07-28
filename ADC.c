#include "ADC.h"

// Funci�n para inicializar el ADC con las configuraciones especificadas
void init_ADC(int referencia, int justificacion, int preescaler) {
	ADMUX = 0;
	ADCSRA = 0;

	// Configurar referencia de voltaje del ADC
	switch (referencia) {
		case 0:
		// Referencia de voltaje interna de 5V
		ADMUX |= (1 << REFS0);
		break;
		case 1:
		// Referencia de voltaje interna de 1.1V
		ADMUX |= (1 << REFS0) | (1 << REFS1);
		break;
	}

	// Configurar justificaci�n de resultados
	if (justificacion == 0) {
		// Justificaci�n a la izquierda
		ADMUX |= (1 << ADLAR);
		} else {
		// Justificaci�n a la derecha
		ADMUX &= ~(1 << ADLAR);
	}

	// Configurar preescaler del ADC
	switch (preescaler) {
		case 2:
		ADCSRA |= (1 << ADPS0);
		break;
		case 4:
		ADCSRA |= (1 << ADPS1);
		break;
		case 8:
		ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
		break;
		case 16:
		ADCSRA |= (1 << ADPS2);
		break;
		case 32:
		ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
		break;
		case 64:
		ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
		break;
		case 128:
		ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
		break;
	}

	// Habilitar el ADC
	ADCSRA |= (1 << ADEN);
}

// Funci�n para leer un valor del ADC en el canal especificado
uint8_t readADC(int canal) {
	// Deshabilitar interrupci�n del ADC
	ADCSRA &= ~(1 << ADIE);

	// Limpiar los bits del canal MUX del ADC
	ADMUX &= ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);

	// Configurar el canal del ADC
	ADMUX |= canal & 0x0F;

	// Iniciar la conversi�n
	ADCSRA |= (1 << ADSC);

	// Esperar a que la conversi�n se complete
	while (ADCSRA & (1 << ADSC)) {}

	// Retornar el valor le�do
	return ADCH;
}

// Funci�n para leer un valor del ADC en el canal especificado con interrupciones
void readADC_ISR(int canal) {
	// Habilitar interrupci�n del ADC
	ADCSRA |= (1 << ADIE);

	// Limpiar los bits del canal MUX del ADC
	ADMUX &= ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);

	// Configurar el canal del ADC
	ADMUX |= canal & 0x0F;

	// Iniciar la conversi�n
	ADCSRA |= (1 << ADSC);
}
