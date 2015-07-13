/*******************************************************************************
 * 
 * FileName     : ds1820.h
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
#ifndef _ONE_WIRE_H
#define _ONE_WIRE_H

#include "HardwareProfile.h"


/* DEFINE CONSTANTS HERE -----------------------------------------------------*/
//One wire pini tan?m?. Kullanilacak pin burada tanimlanir.
#define LINE_TRIS   DS18B20_TEMP_SENS_TRIS
#define LINE        DS18B20_TEMP_SENS
/* DEFINE TYPES HERE ---------------------------------------------------------*/
/* DECLARE EXTERNAL VARIABLES HERE -------------------------------------------*/

volatile bit CONV; 			// ???? ???????????? ? ???????????
volatile char convert;
volatile bit conversionFinished;


/* DEFINITION OF MACROS ------------------------------------------------------*/
/* DECLARATION OF FUNCTIONS --------------------------------------------------*/
void lineHigh(void);
void lineLow(void);
unsigned char oneWireReset(void);
unsigned char oneWireReadBit(void);
void oneWireWriteBit(char bitval);
unsigned char oneWireReadByte(void);
void oneWireWriteByte( char val );
signed int refreshTemperature(void);

#endif	
