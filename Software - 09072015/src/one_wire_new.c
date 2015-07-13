/*******************************************************************************
 *
 * FileName     : adc.c
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
// Uart Variables
/* DECLARE EXTERNAL VARIABLES HERE -------------------------------------------*/
extern char printBuffer[6];
/* DECLARE LOCAL FUNCTIONS HERE ----------------------------------------------*/

//___________________?nteger ? stringe çevirir__________
void itoa_(unsigned int n,char s[6])
{
    unsigned long i,a ;
    if (n/100000)
            a=5;
    else if (n/10000)
            a=4;
    else if (n/1000)
            a=3;
    else if (n/100)
            a=2;
    else if (n/10)
            a=1;
    else
            a=0;
    i=a;
    do
    {
            s[i--]= n%10 + '0';
    }while ((n/=10)>0);

    s[a+1]='\0';
}


void putStr(unsigned char sayi)
{
    unsigned char i;
    unsigned char goster[6];
    if(sayi<100) putch('0');
    if(sayi<10) putch('0');
    itoa_((char)sayi,goster);
    for( i = 0; i<sizeof(goster); i++)
    {
        if(goster[i] == '\0')
        {
            break;
        }
        putch(goster[i]);
    }
   

}
/* DEFINE FUNCTIONS HERE -----------------------------------------------------*/
unsigned char oneWireReset(void) //Reset Yapmak için gereken prosedür
{
    signed char wireStatus = 0;
	di();
	LINE_TRIS = 0;
	LINE = 1;
	wireStatus = 0;
	__delay_us(1);
	LINE = 0;
	__delay_us(500);
	LINE = 1;
	__delay_us(700);
	
	LINE_TRIS = 1;
	__delay_us(1);
	if(LINE == 0)
	{
		wireStatus = 1;
	}
	__delay_us(400);
	ei();
    return wireStatus;
}

unsigned char oneWireReadByte(void)
{
    unsigned char iobyte = 0;
	unsigned char temp, i;
    di();
	for(i=0; i<8 ; i++)
	{
		LINE_TRIS = 0;
		__delay_us(1);
		LINE = 0;
		__delay_us(6);
		LINE = 1;
		__delay_us(4);
		
		LINE_TRIS = 1;
		__delay_us(1);
		
		if(LINE == 1)
		{
			iobyte = iobyte | ( 2^x );
		}
		else
		{
			temp = ~ ( 2^x );
            iobyte = iobyte & temp;          // Logig AND
		}
	}    
    ei();
    return iobyte;
}

void oneWireWriteByte( char val )
{
    unsigned char iobyte = 0;
	unsigned char temp, i;
    di();
    for (i=0; i<8; i++) // writes byte, one bit at a time
    {
       LINE_TRIS = 0;
	   __delay_us(1);
	   LINE = 0;
	   __delay_us(3);
	   
	   temp = iobyte & ( 2^x ); 
	   
	    if( temp == ( 2^x ) )
        {
            LINE = 1;                             // Set DQ pin high
        }
		
		__delay_us(60);
		LINE = 1;
		__delay_us(2);
    }
    ei();
}


//------------------      
signed int refreshTemperature(void)
{
    unsigned char lsb,msb,temp,isaret;
    unsigned int isi;

    if((CONV == 0) && (conversionFinished == 0))
    {
        CONV = 1;
        oneWireReset();
        oneWireWriteByte(0xCC);
        oneWireWriteByte(0x44);
        __delay_us(120);
    }
    else if(conversionFinished == 1)
    {

        oneWireReset();
        oneWireWriteByte(0xCC);
        oneWireWriteByte(0xBE);
        lsb = oneWireReadByte();
        msb = oneWireReadByte();      
//        msb = 0xFC; //-55
//        lsb = 0x90;
//        msb = 0xFE; //-25
//        lsb = 0x6F;
//        msb = 0xFF; //-10
//        lsb = 0x5E;
//        msb = 0x00; //0
//        lsb = 0x00;
//        msb = 0xFF; //-1
//        lsb = 0xF8;
//        msb = 0xFF; //0
//        lsb = 0xF8;

        if(msb & 0xF0)
        {
            isi = msb;
            isi <<= 4;
            temp = (lsb>>4) & 0x0F;
            isi += temp;
            isi |= 0xF000;
//            isi++;
        }
        else
        {
            isi = msb;
            isi <<= 4;
            temp = (lsb>>4) & 0x0F;
            isi += temp;
        }
    }
    return isi;
}


/* DEFINE LOCAL FUNCTIONS HERE -----------------------------------------------*/

