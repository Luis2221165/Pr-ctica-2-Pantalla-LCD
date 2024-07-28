#define F_CPU 16000000
#include "LCD8b.h"
#include <avr/io.h>
#include <util/delay.h>

// Funci�n para inicializar el LCD en modo de 8 bits
void initLCD8bits(void) {
	// Configuraci�n de los pines de datos y control como salidas
	DDRD |= 0xFF; // Pines D0-D7 como salidas
	PORTD = 0;    // Inicializar los pines de datos a 0
	DDRB |= 0x07; // Pines B0-B2 como salidas (RS, RW, EN)
	PORTB = 0;    // Inicializar los pines de control a 0

	_delay_ms(20); // Esperar m�s tiempo para asegurarse de que el LCD se inicializa correctamente

	// Secuencia de inicializaci�n en 8 bits
	LCD_CMD(0x38);
	_delay_ms(5);
	LCD_CMD(0x38);
	_delay_ms(1);
	LCD_CMD(0x38);
	_delay_ms(1);

	// Configuraci�n del LCD
	LCD_CMD(0x38); // Funci�n set
	LCD_CMD(0x0C); // Display on, cursor off
	LCD_CMD(0x01); // Clear display
	_delay_ms(2);  // Esperar para el clear display
	LCD_CMD(0x06); // Entry mode set
}

// Funci�n para enviar un valor a los pines de datos del LCD
void LCD_port(char data) {
	PORTD = data; // Escribir el valor en los pines D0-D7
}

// Funci�n para enviar un comando al LCD
void LCD_CMD(char cmd) {
	PORTB &= ~(1 << PORTB2); // RS=0 (comando)
	LCD_port(cmd);           // Enviar comando
	PORTB |= (1 << PORTB0);  // EN=1
	_delay_us(1);            // Pulso de habilitaci�n
	PORTB &= ~(1 << PORTB0); // EN=0
	_delay_ms(2);            // Esperar a que el comando se ejecute
}

// Funci�n para enviar un car�cter al LCD
void LCD_WriteCaracter(char data) {
	PORTB |= (1 << PORTB2);  // RS=1 (datos)
	LCD_port(data);          // Enviar datos
	PORTB |= (1 << PORTB0);  // EN=1
	_delay_us(1);            // Pulso de habilitaci�n
	PORTB &= ~(1 << PORTB0); // EN=0
	_delay_ms(2);            // Esperar a que el dato se escriba
}

// Funci�n para enviar una cadena de caracteres al LCD
void LCD_Write_String(char *str) {
	while (*str) {
		LCD_WriteCaracter(*str++);
	}
}

// Funci�n para desplazar el contenido del LCD a la derecha
void Lcd_Shift_Right(void) {
	LCD_CMD(0x1C);
}

// Funci�n para desplazar el contenido del LCD a la izquierda
void Lcd_Shift_Left(void) {
	LCD_CMD(0x18);
}

// Funci�n para establecer la posici�n del cursor en el LCD
void LCD_Set_Cursor(char col, char row) {
	char address = (row == 1) ? 0x80 : 0xC0;
	address += col - 1;
	LCD_CMD(address);
}
