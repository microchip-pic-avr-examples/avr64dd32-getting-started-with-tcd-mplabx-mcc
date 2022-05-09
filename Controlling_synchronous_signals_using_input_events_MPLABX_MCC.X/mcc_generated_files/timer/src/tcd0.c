/**
  * TCD0 Generated Driver File
  *
  * @file tcd0.c
  *
  * @ingroup tcd0
  *
  * @brief This file contains the driver code for TCD0 module.
  *
  * @version TCD0 Driver Version 2.0.2
*/
/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/


#include "../tcd0.h"

void (*TCD0_TRIG_isr_cb)(void) = NULL;
void (*TCD0_OVF_isr_cb)(void) = NULL;

void TCD0_SetTRIGIsrCallback(TCD0_cb_t cb)
{
    TCD0_TRIG_isr_cb = cb;
}

void TCD0_SetOVFIsrCallback(TCD0_cb_t cb)
{
   TCD0_OVF_isr_cb = cb;
}

int8_t TCD0_Initialize(void)
{
    //Clear A
    TCD0.CMPACLR = 0x2C;

    //SET A
    TCD0.CMPASET = 0x4;

    //Clear B
    TCD0.CMPBCLR = 0x2C;

    //SET B
    TCD0.CMPBSET = 0x4;

    //WGMODE Four ramp mode; 
    TCD0.CTRLB = 0x2;

    //AUPDATE disabled; CMPCSEL PWM A output; CMPDSEL PWM B output; CMPOVR disabled; FIFTY disabled; 
    TCD0.CTRLC = 0x80;

    //CMPAVAL 1; CMPBVAL 1; 
    TCD0.CTRLD = 0x11;

    //DISEOC disabled; RESTART disabled; SCAPTUREA disabled; SCAPTUREB disabled; SYNC disabled; SYNCEOC disabled; 
    TCD0.CTRLE = 0x0;

    //DBGRUN disabled; FAULTDET disabled; 
    TCD0.DBGCTRL = 0x0;

    //DITHERSEL ONTIMEB; 
    TCD0.DITCTRL = 0x0;

    //DITHER 0x0; 
    TCD0.DITVAL = 0x0;

    //DLYPRESC DIV1; DLYSEL OFF; DLYTRIG CMPASET; 
    TCD0.DLYCTRL = 0x0;

    //DLYVAL undefined; 
    TCD0.DLYVAL = 0x0;

    //ACTION Event trigger a fault; CFG Input Capture Noise Cancellation Filter enabled; EDGE The falling edge or low level of event generates retrigger or fault action; TRIGEI enabled; 
    TCD0.EVCTRLA = 0x41;

    //ACTION Event trigger a fault; CFG Neither Filter nor Asynchronous Event is enabled; EDGE The falling edge or low level of event generates retrigger or fault action; TRIGEI disabled; 
    TCD0.EVCTRLB = 0x0;

    //CMPA disabled; CMPAEN enabled; CMPB disabled; CMPBEN enabled; CMPC disabled; CMPCEN enabled; CMPD disabled; CMPDEN enabled; 
    ccp_write_io((void*)&(TCD0.FAULTCTRL),0xF0);

    //INPUTMODE Stop all outputs, jump to next compare cycle and wait; 
    TCD0.INPUTCTRLA = 0x6;

    //INPUTMODE Input has no actions; 
    TCD0.INPUTCTRLB = 0x0;

    //OVF disabled; TRIGA disabled; TRIGB disabled; 
    TCD0.INTCTRL = 0x0;

    while ((TCD0.STATUS & TCD_ENRDY_bm) == 0); // Wait for Enable Ready to be high.

    //PWMACTA disabled; PWMACTB disabled; 
    TCD0.STATUS = 0x0;

    //CLKSEL Internal High-Frequency oscillator; CNTPRES DIV4; ENABLE enabled; SYNCPRES DIV1; 
    TCD0.CTRLA = 0x9;

    return 0;
}

ISR(TCD0_OVF_vect)
{
    /* The interrupt flag has to be cleared manually */
    TCD0.INTFLAGS = TCD_OVF_bm;
    
    /* Insert your TCD Over Flow interrupt handling code here */
    if(TCD0_OVF_isr_cb != NULL)
    {
        TCD0_OVF_isr_cb();
    }
}

ISR(TCD0_TRIG_vect)
{
    /* TRIGA interrupt flag has to be cleared manually */
    TCD0.INTFLAGS = TCD_TRIGA_bm;

    /* Insert your TCD interrupt handling code here */
    if(TCD0_TRIG_isr_cb != NULL)
    {
        TCD0_TRIG_isr_cb();
    }
}
