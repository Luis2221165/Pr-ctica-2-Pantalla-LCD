//***************************************************************************
//Universidad del valle de Guatemala
//IE2023: Programación de Microcontroladores
//Autor: Luis Angel Ramirez Orózco
//Proyecto: Lab
//Hardware: ATMEGA328P
//Creado: 19/07/2024
//***************************************************************************

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include "LCD8b.h"

volatile int contador = 0;

void USART_Init(unsigned int ubrr) {
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    /* Set frame format: 8 data bits, 1 stop bit */
    UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

unsigned char USART_Receive(void) {
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)));
    /* Get and return received data from buffer */
    return UDR0;
}

void mostrar_valores_LCD(uint8_t valor_ADC0, uint8_t valor_ADC1, int contador) {
    char buffer[17];
    float voltaje0 = valor_ADC0 * 5.0 / 255.0;
    float voltaje1 = valor_ADC1 * 5.0 / 255.0;
    LCD_CMD(0x01); // Clear display
    LCD_Set_Cursor(1, 1);
    snprintf(buffer, 17, "S1: %.2fV S2: %.2fV", voltaje0, voltaje1);
    LCD_Write_String(buffer);
    LCD_Set_Cursor(1, 2);
    snprintf(buffer, 17, "Cont: %d", contador);
    LCD_Write_String(buffer);
}

int main(void) {
    uint8_t valor_ADC0, valor_ADC1;
    char comando;
    
    // Inicialización
    init_ADC(0, 1, 128); // Referencia 5V, justificación derecha, prescaler 128
    initLCD8bits();
    USART_Init(103); // Configurar USART con baud rate 9600
    
    sei(); // Habilitar interrupciones globales
    
    while (1) {
        // Leer valores de los potenciómetros
        valor_ADC0 = readADC(0);
        valor_ADC1 = readADC(1);
        
        // Mostrar valores en la LCD
        mostrar_valores_LCD(valor_ADC0, valor_ADC1, contador);
        
        // Leer comando desde la consola
        comando = USART_Receive();
        
        // Incrementar o decrementar contador
        if (comando == '+') {
            contador++;
        } else if (comando == '-') {
            contador--;
        }
        
        _delay_ms(500); // Pequeño retraso para actualizar la pantalla
    }
}
