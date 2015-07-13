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



void lineHigh(void)
{
    LINE = 1;
    __delay_us(6);
    LINE_TRIS = 1;
}

void lineLow(void)
{
    LINE = 0;
    LINE_TRIS = 0;
    __delay_us(10);
}


unsigned char oneWireReset(void) //Reset Yapmak için gereken prosedür
{
    signed char wireStatus = 0;

    lineLow();
    __delay_us(700);
    di();
    lineHigh();
    __delay_us(120);
    wireStatus = LINE;
    __delay_us(700);
    ei();
    return wireStatus;
}

unsigned char oneWireReadBit(void)
{
    unsigned char i;
    di();
    lineLow();
    __delay_us(5);
    lineHigh();
    __delay_us(15);
    i = LINE;
    ei();
    return i;
}

void oneWireWriteBit(char bitval)
{
    unsigned char i;
    di();
    lineLow();
    __delay_us(5);
    if(bitval==1) lineHigh();
    __delay_us(60);
    lineHigh();
    __delay_us(5);
    ei();
}

unsigned char oneWireReadByte(void)
{
    unsigned char i;
    unsigned char value = 0;
    di();
    for (i=0;i<8;i++)
    {
        if(oneWireReadBit()) value|=0x01<<i; // reads byte in, one byte at a time and then
        // shifts it left
        __delay_us(120); // wait for rest of timeslot
    }
    ei();
    return(value);
}


void oneWireWriteByte( char val )
{
    unsigned char i;
    unsigned char temp;
    di();
    for (i=0; i<8; i++) // writes byte, one bit at a time
    {
        temp = val>>i; // shifts val right 'i' spaces
        temp &= 0x01; // copy that bit to temp
        oneWireWriteBit(temp); // write bit in temp into
        __delay_us(60);
    }
//    __delay_us(150);
    ei();
}


//------------------      ?s?y? olcup buffer'a +001.5 ?eklinde yazar
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

