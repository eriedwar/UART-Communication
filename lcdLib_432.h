#ifndef LCDLIB_432_H_
#define LCDLIB_432_H_

#include <msp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Delay Functions
#define delay_ms(x)     __delay_cycles((long) (x) * 3000)
#define delay_us(x)     __delay_cycles((long) (x) * 3)

// Pins
#define EN  BIT4
#define RS  BIT5
#define DATA    0x0F

// Commands
#define CLEAR   0x01

// Functions
void lcdInit();                 // Initialize LCD
void lcdTriggerEN();                // Trigger Enable
void lcdWriteData(unsigned char data);      // Send Data (Characters)
void lcdWriteCmd(unsigned char cmd);        // Send Commands
void lcdClear();                // Clear LCD
void lcdSetText(char * text, int x, int y); // Write string
void lcdSetInt(int val, int x, int y);      // Write integer
void displayScreenSaver();
void lcdSetText(char * text, int x, int y);
void lcdWriteChar(char c);
void lcdPrint(char* str);

#endif /* LCDLIB_432_H_ */

