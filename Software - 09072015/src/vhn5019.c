/*******************************************************************************
 *
 * FileName     : uart.c
 * Dependencies :
 * Description  :
 * Processor    : PIC16F887
 * Compiler     : Hi-tech Picc 9.83
 * Linker       :
 * Company      : Inno Technology Incorporated
 *
 * Software License Agreement
 * Copyright (C) 2011 - 2012 Inno Technology Inc.  All rights
 * reserved.
 *
 * Version    Author                     Date             Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 1.0        Erdem Tayfun Salman       11/14/2014       Initial Version
 ******************************************************************************/
#include "includes.h"

/* DEFINE LOCAL CONSTANTS HERE -----------------------------------------------*/
/* DEFINE LOCAL TYPES HERE ---------------------------------------------------*/
/* DEFINE LOCAL MACROS HERE --------------------------------------------------*/
/* DEFINE LOCAL VARIABLES HERE -----------------------------------------------*/
/* DECLARE EXTERNAL VARIABLES HERE -------------------------------------------*/
/* DECLARE LOCAL FUNCTIONS HERE ----------------------------------------------*/
/* DEFINE FUNCTIONS HERE -----------------------------------------------------*/

/*******************************************************************************
 *
 * Function     : void vInitializeUart( void )
 * PreCondition : None
 * Input        : None
 * Output       : None
 * Side Effects : None
 * Overview     :
 * Note         : None
 *
 ******************************************************************************/
void vInitializeVHN5019( void )
{
    M1_PWM_TRIS = 0;    //PWM_OUT_TRIS = 0;
    M1_PWM = 0;         //PWM_OUT = 0;
    M2_PWM_TRIS = 0;    //PWM_OUT_TRIS = 0;
    M2_PWM = 0;         //PWM_OUT = 0;

    M1_EN_A_B_TRIS = 0;    //M1EN_TRIS = 0;
    M1_EN_A_B = 1;         //M1EN = 1;
    M2_EN_A_B_TRIS = 0;    //M1EN_TRIS = 0;
    M2_EN_A_B = 1;         //M1EN = 1;

    M1_INA_TRIS = 0;       //M1INA_TRIS = 0;
    M1_INA = 1;            //M1INA = 1;
    M2_INA_TRIS = 0;       //M1INA_TRIS = 0;
    M2_INA = 1;            //M1INA = 1;

    M1_INB_TRIS = 0 ;       //M1INB_TRIS = 0;
    M1_INB = 0;             //M1INB = 0;
    M2_INB_TRIS = 0 ;       //M1INB_TRIS = 0;
    M2_INB = 0;             //M1INB = 0;

//    M1_CS_TRIS = 1;
//    M2_CS_TRIS = 1;

    T2CON = 0b00000011;
    PIE1bits.TMR2IE = 0;
    CCP1CON = 0b00001100;
    CCP2CON = 0b00001100;
    CCPR1L  = 0;
    CCPR2L  = 0;
    PR2 = 255;//488 Hz
    __delay_ms(1);
    T2CONbits.TMR2ON = 1;
}

void vSetSpeed(unsigned int iSp)
{
    unsigned char temp;

    if(iSp == 0)
    {
        M1_EN_A_B = 0;
        M2_EN_A_B = 0;
    }
    else
    {
        M1_EN_A_B = 1;
        M2_EN_A_B = 1;
        temp = (iSp << 4) & 0b00110000;
        CCP1CON |= temp;
        CCPR1L  = (iSp >> 2) & 0xFF;
        CCP2CON |= temp;
        CCPR2L  = (iSp >> 2) & 0xFF;
    }
}






/* DEFINE LOCAL FUNCTIONS HERE -----------------------------------------------*/

