#ifndef LCD8BITS_H_
#define LCD8BITS_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

// Declaraciones de funciones para el control del LCD en modo de 8 bits

// Inicializa el LCD en modo de 8 bits
void initLCD8bits(void);

// Env�a un comando al LCD
void LCD_Send_Command(char command);

// Establece los valores en los pines de datos del LCD
void LCD_Set_Data_Port(char data);

// Env�a un car�cter al LCD
void LCD_Write_Character(char character);

// Env�a una cadena de caracteres al LCD
void LCD_Write_String(char *string);

// Desplaza el contenido del LCD hacia la derecha
void LCD_Shift_Right(void);

// Desplaza el contenido del LCD hacia la izquierda
void LCD_Shift_Left(void);

// Establece la posici�n del cursor en el LCD
void LCD_Set_Cursor(char column, char row);

#endif /* LCD8BITS_H_ */
