#include "../bibliotecas/config.h"
#include "../bibliotecas/lcd8bits.h"
#include <xc.h>
#define _XTAL_FREQ 8000000

void main(void) {
    // Desabilita I/O analógicas
    ADCON1 = 0x0F;
    
    // Lcd Modo 8 bits
    iniciaLcd();
    Lcd_Out(1, 1, "COMPARE 1KHZ");
    
    // Configura TMR1 Prescaler 1:2
    T1CON = 0b11010000;
    TMR1H = 0;
    TMR1L = 0;
    T1CONbits.TMR1ON = 1;
            
    // Configuração do CCP
    CCP1CON = 0b00000010;
    CCPR1H = 0x01;
    CCPR1L = 0xF4;
    PIR1bits.CCP1IF = 0;
    
    TRISCbits.TRISC2 = 0;
    
    while(1)
    {
        // Trata o Compare
        if(PIR1bits.CCP1IF == 1)
        {
            TMR1H = 0;
            TMR1L = 0;
            PIR1bits.CCP1IF = 0;
        }
    }
}
