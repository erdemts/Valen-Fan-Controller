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
#ifndef _DS1820_H
#define _DS1820_H

/* DEFINE CONSTANTS HERE -----------------------------------------------------*/

#define TRISDAL   PORTAbits.RA2
#define DALLAS    TRISAbits.TRISA2

#define		COLDAT	1				// Sistemde izin verilen sens�r sayisi
#define		NACHAD	(0xFF-(8*COLDAT))+1		// EEPROM s?cakl?k sens�rleri ba?lang?� adresi konumunu


/* DEFINE TYPES HERE ---------------------------------------------------------*/
/* DECLARE EXTERNAL VARIABLES HERE -------------------------------------------*/
//?????
volatile bit CONV; 			// ???? ???????????? ? ???????????
volatile char convert;		// ?????????? ??????? ??????????????? ??????????? ???????????? ? ???????????

					// ????????
//---------------------------------------------------------------------------------------
//??????????
char crc, 					//crc
coldachu,					//?????????? ???????? ????????????(?????????? ? EEPROM)
naydendatch, 				//??????? ?? ????????? ??????.
posled_nesoot,				//???????? ?????????? ?????????????? ??? ?????? ???
error_con;					//???????? ?????? ?? ?????? ?????
char bufdt[8], 				//????? ??? ?????? ?????? ?? DS18B20
erroDT[COLDAT]; 			//?????? ?????? ???????? ??????????? (????????? ????????? ??????)

int TEMPDAT[COLDAT]; 		//?????? ?????????? ????????;

bit CON; 					//????? ?????? ??????????????? ???????????
bit TESTDT;					//????? ???????????? ???????? ??????????? (??? ??????? ?? ??????)
bit ET00,ET01,ET02,ET03,ET04,ET05,ET06,ET07,
ET08,ET09,ET10,ET11,ET12,ET13,ET14,ET15; //????? ?????? ????????
/* DEFINITION OF MACROS ------------------------------------------------------*/
/* DECLARATION OF FUNCTIONS --------------------------------------------------*/

void Level_HIGH (void);		//
void Level_LOW (void);		//
void Waiting_WR (void);		//
char CRC_BITS (int data);	//
char Reset_Dallas (void);	//
char Dreceive (void);		//
void Dsend (char COM_REG);	//
char Celsio (void);			//
char SeachROM (void);		//
char SaveROM (void);		// ????????? ????????? ????????
void EraseROM (void);		//
char Test_DT (void);		//





#endif	
