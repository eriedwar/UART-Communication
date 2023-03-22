#include "msp.h"
#include "lcdLib_432.h"
#include <stdio.h>

// Declare function to send data
void sendData(char *str);
// Declare function to send data to LCD
void sendToLCD(char *str);

void main(void)
{
    // Disable watchdog timer
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    // Initialize the LCD and clear it
    lcdInit();
    lcdClear();

    // Set up UART communication
    P1->SEL0 |= BIT2 | BIT3;
    P1->SEL1 &= ~(BIT2 | BIT3);

    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST;
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;
    EUSCI_A0->BRW = 19;
    EUSCI_A0->MCTLW = (9 << EUSCI_A_MCTLW_BRF_OFS | EUSCI_A_MCTLW_OS16);
    EUSCI_A0->CTLW0 &= ~(EUSCI_A_CTLW0_SWRST);

    // Declare a character array to store user input
    char userInput[100];
    lcdSetText("Enter input:", 0, 0);
    int promptDisplayed = 0;

    // Infinite loop to keep the program running
    while (1)
    {
        if (!promptDisplayed) {
           printf("Enter your input: \n");
       }
        scanf(" %s", userInput);

        // Check if user entered "exit"
        if (strcmp(userInput, "exit") == 0) {
            // Exit program and display message on LCD
            lcdClear();
            printf("*******THE PROGRAM HAS EXITED.*******");
            lcdSetText("Program exited", 0, 0);
            return;
        }

        // Reset the promptDisplayed flag
        promptDisplayed = 1;

        // Send the input to the LCD display and UART communication
        sendToLCD(userInput);
        sendData(userInput);
        sendData(" ");

        // Clear the LCD and display the user input
        lcdClear();
        lcdSetText(userInput, 0, 0);

        // Print the user input to console
        printf("Input received by TX: %s\n", userInput);

        // Clear the user input array
        memset(userInput, 0, sizeof(userInput));
        }
    }

void sendData(char *str) {
    // Print the transmitted string to console
    for (; *str; str++) {
        while (!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));
        EUSCI_A0->TXBUF = *str;
    }
    __delay_cycles(1500000);
}

void sendToLCD(char *str) {
    lcdClear();
    lcdSetText(str, 0, 0);
}
