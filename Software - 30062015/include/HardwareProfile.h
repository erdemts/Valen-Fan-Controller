/*******************************************************************************
 *
 * FileName     : HardwareProfile.h ( BusIdDongle Hardware profile file )
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
#ifndef HARDWAREPROFILE_H
#define HARDWAREPROFILE_H

#include <htc.h>

#define _XTAL_FREQ	20000000


/*****************************************************************************
 *	Uart
 *****************************************************************************/
#define UARTTX_TRIS                 (TRISCbits.TRISC6)
#define UARTRX_TRIS                 (TRISCbits.TRISC7)


/*****************************************************************************
 *	TEMPERATURE SENSORS
 *****************************************************************************/
#define DS18B20_TEMP_SENS           (PORTAbits.RA2)
#define DS18B20_TEMP_SENS_TRIS      (TRISAbits.TRISA2)

#define LM35_TEMP_SENS_P            (PORTAbits.RA0)
#define LM35_TEMP_SENS_P_TRIS       (TRISAbits.TRISA0)

#define LM35_TEMP_SENS_N            (PORTAbits.RA1)
#define LM35_TEMP_SENS_N_TRIS       (TRISAbits.TRISA1)

//Analog channels
#define LM35_P                      (0)
#define LM35_N                      (1)



/*****************************************************************************
 *	Relays
 *****************************************************************************/
#define RELAY_1_TRIS            (TRISDbits.TRISD2)//RELAY_1
#define RELAY_1                 (PORTDbits.RD2)

#define RELAY_2_TRIS            (TRISDbits.TRISD3)
#define RELAY_2                 (PORTDbits.RD3)

#define RELAY_3_TRIS            (TRISCbits.TRISC4)
#define RELAY_3                 (PORTCbits.RC4)

#define LCD_POWER_RELAY_TRIS    (TRISCbits.TRISC5)
#define LCD_POWER_RELAY         (PORTCbits.RC5)


/*****************************************************************************
 *	Motor Control
 *****************************************************************************/
#define M1_PWM_TRIS             (TRISCbits.TRISC2)
#define M1_PWM                  (PORTCbits.RC2)
#define M2_PWM_TRIS             (TRISCbits.TRISC1)
#define M2_PWM                  (PORTCbits.RC1)

#define M1_INA_TRIS             (TRISBbits.TRISB3)
#define M1_INA                  (PORTBbits.RB3)
#define M2_INA_TRIS             (TRISDbits.TRISD7)
#define M2_INA                  (PORTDbits.RD7)

#define M1_CS_TRIS              (TRISBbits.TRISB2)
#define M1_CS                   (PORTBbits.RB2)
#define M2_CS_TRIS              (TRISDbits.TRISD6)
#define M2_CS                   (PORTDbits.RD2)

#define M1_EN_A_B_TRIS          (TRISBbits.TRISB1)
#define M1_EN_A_B               (PORTBbits.RB1)
#define M2_EN_A_B_TRIS          (TRISDbits.TRISD5)
#define M2_EN_A_B               (PORTDbits.RD5)

#define M1_INB_TRIS             (TRISBbits.TRISB0)
#define M1_INB                  (PORTBbits.RB0)
#define M2_INB_TRIS             (TRISDbits.TRISD4)
#define M2_INB                  (PORTDbits.RD4)


/*****************************************************************************
 *	I/O Pins
 *****************************************************************************/
#define LED_GREEN                 (PORTAbits.RA4) //RED LED
#define LED_GREEN_TRIS		(TRISAbits.TRISA4) //RED LED

#define LED_RED               (PORTAbits.RA3) //GREEN LED
#define LED_RED_TRIS          (TRISAbits.TRISA3) //GREEN LED




#endif
