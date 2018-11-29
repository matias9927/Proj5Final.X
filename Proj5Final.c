/**/
#pragma config JTAGEN = OFF     // Turn off JTAG - required to use Pin RA0 as IO
#pragma config FNOSC = PRIPLL   //configure system clock 80 MHz
#pragma config FSOSCEN = OFF    // Secondary Oscillator Enable (Disabled)
#pragma config POSCMOD = XT     // Primary Oscillator Configuration (XT osc mode)
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_1
#pragma config FPBDIV = DIV_2   //configure peripheral bus clock to 40 MHz

#ifndef _SUPPRESS_PLIB_WARNING
#define _SUPPRESS_PLIB_WARNING
#endif

#include <xc.h>
#include <stdio.h>
#include <plib.h>
#include "config.h"
//#include <math.h>
#include "adc.h"
#include "btn.h"
#include "lcd.h"
//#include "pmods.h"
//#include "rgbled.h"
#include "srv.h"
#include "ssd.h"
//#include "swt.h"
//#include "uart.h"
//#include "ultr.h"
#include "utils.h"

#define SYS_FREQ (80000000L)
#define INTSEC 10
#define CORE_TICK_RATE (SYS_FREQ / 2 / INTSEC)

int clockwise = 1600;
int counterClockwise = 1400;
enum modes {TEST, READY};
int mode = TEST;
int micInput;
int btnlock = 0;
char 

main(void) {
    LCD_Init();
    delay_ms(100);
    MIC_Init();
    delay_ms(100);
    LED_Init();
    delay_ms(100);
    BTN_Init();
    delay_ms(100);
    
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    OpenCoreTimer(CORE_TICK_RATE); //CoreTimer used for tenths of second capture
    mConfigIntCoreTimer((CT_INT_ON | CT_INT_PRIOR_5 | CT_INT_SUB_PRIOR_0));
    INTEnableSystemMultiVectoredInt(); //Enable Timer interrupts
    
    LCD_WriteStringAtPos("TEAM:1 MODE:", 0, 0);
    while(1) {
        while(mode == TEST){
            LCD_WriteStringAtPos("TEST ",1,0);
            micInput = MIC_Val();
            if(micInput > 512){
                LED_SetValue(0,1);
            }
            if(micInput > 565){
                LED_SetValue(1,1);
            }
            if(micInput > 577){
                LED_SetValue(2,1);
            }
            if(micInput > 642){
                LED_SetValue(3,1);
            }
            if(micInput > 707){
                LED_SetValue(4,1);
            }
            if(micInput > 772){
                LED_SetValue(5,1);
            }
            if(micInput > 837){
                LED_SetValue(6,1);
            }
            if(micInput > 902){
                LED_SetValue(7,1);
            }
            else{
                LED_SetGroupValue(0);
            }
        }

        while(mode == READY){
            LCD_WriteStringAtPos("READY",1,0);
        }
    }
}

void delay_ms(int ms){
    int i, counter;
    for (counter = 0; counter < ms; counter++) {
        for (i = 0; i < 300; i++) {
        } //software delay ~1 millisec 
    }
}

//void __ISR(_CORE_TIMER_VECTOR, ipl5) _CoreTimerHandler(void){
//    mCTClearIntFlag();
//    if(BTN_GetValue('C') && !btnlock){
//        if(mode == READY){
//            mode = TEST;
//        }
//        else{
//            mode = READY;
//        }
//        btnlock = 1;
//    }
//    if(!BTN_GetValue('C')){
//        btnlock = 0;
//    }
//    UpdateCoreTimer(CORE_TICK_RATE);
//}