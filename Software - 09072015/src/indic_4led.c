/*Библиотека динамической индикации для семисегментного индикатора 4 разряда.
общий катод
Library for the seven-segment display dynamic LED 4 digits.
common cathode
for PIC16-PIC18 MPLAB v8.80
compilers
HI-TECH C Compiler for PIC18 MCUs (PRO Mode)  V9.80
HI-TECH C Compiler for PIC10/12/16 MCUs (PRO Mode)  V9.83
author
Геннадий Чернов, Днепропетровск 2011
Gennady Chernov, Dnepropetrovsk 2011
version v3.01.
Email: gena.chernov@gmail.com
*/
//--------------------------------------------------------------------------------------- 
#include <htc.h>							// стандартный заголовок описания
#include "indic_4led.h"						//
//--------------------------------------------------------------------------------------- 


//==================Индикация======indication=================================================
//программа управления портами ввода/вывода микроконтроллера //control program I/O ports of the microcontroller	
//============================================================================================
// Program scan display
void indic(void)	//программа развертки индикацией
{
				switch (reg_ind)
				{		
			  		case 0 :				// indication of a discharge
				    	reg_ind++;			// set the following display
				    	p_ind	= ind_1;	//	

				    	if(RAZR1==1)		// discharge should be blinking
				    	{
					    	if(B_MIG==1)p_ind &= 0b10000000; // flashing digit
					    }
					    if(TOCHm1==1)		// point should be flashing
					    {
						    if(B_MIG==0)p_ind &= 0b01111111;
						}
			    	break;
			  		
			  		case 1 :				// индикация 1 разряда
				    	reg_ind++;			// установить следующую индикацию
				    	p_ind	= ind_2;	//	

				    	if(RAZR2==1)		// разряд должен мигать
				    	{
					    	if(B_MIG==1)p_ind &= 0b10000000; // мигание разряда
					    }
					    if(TOCHm2==1)		// точка должна мигать
					    {
						    if(B_MIG==0)p_ind &= 0b01111111;
						}
			    	break;
			  		
			  		case 2 :				// индикация 1 разряда
				    	reg_ind++;			// установить следующую индикацию
				    	p_ind	= ind_3;	//	

				    	if(RAZR3==1)		// разряд должен мигать
				    	{
					    	if(B_MIG==1)p_ind &= 0b10000000; // мигание разряда
					    }
					    if(TOCHm3==1)			// точка должна мигать
					    {
						    if(B_MIG==0)p_ind &= 0b01111111;
						}
			    	break;
			  		
			  		default :				// индикация 1 разряда
				    	reg_ind	= 0;		// установить следующую индикацию
				    	p_ind	= ind_4;	//	

				    	if(RAZR4==1)		// разряд должен мигать
				    	{
					    	if(B_MIG==1)p_ind &= 0b10000000; // мигание разряда
					    }
					    if(TOCHm4==1)		// точка должна мигать
					    {
						    if(B_MIG==0)p_ind &= 0b01111111;
						}
			    	break;
			 }   	
// управления портами ввода вывода 				
// разряды портов которые не участвуют в индикации должны быть сохранены
// индикация должна быть погачена в текущем разряде, затем активирована в следующем.
// Input output of port management
// Discharge ports that do not participate in the display must be kept
// Display should be pogachena in the current discharge, and then activated in the following.


// чтение состояния регистра портов //reading the status register ports
	d_PORTA	= PORTA;	//
	d_PORTB	= PORTB;	//
	d_PORTC	= PORTC;	//

// очистка битов состояний разрядов индикации сегментов 0, а разрядов катодов в 1
// clearing status bits indicate bits of segment 0, bits and cathodes in a
	d_PORTA	= (d_PORTA & SEGPA) | OBSPA;
	d_PORTB	= (d_PORTB & SEGPB) | OBSPB;
	d_PORTC	= (d_PORTC & SEGPC) | OBSPC;

	if(GAIN==0)// флаг гашения индикации // flag display blanking
	{
		// дешифрация символа привязка к выводам контроллера.//decoding of the symbol bind to the conclusions of the controller.
		if(p_ind & 0b00000001) S_A;
		if(p_ind & 0b00000010) S_B;
		if(p_ind & 0b00000100) S_C;
		if(p_ind & 0b00001000) S_D;
		if(p_ind & 0b00010000) S_E;
		if(p_ind & 0b00100000) S_F;
		if(p_ind & 0b01000000) S_G;			
		if(p_ind & 0b10000000) S_H;

		// выбор индикации разряда //choice of display discharge
		if(reg_ind == 1) R1;
		if(reg_ind == 2) R2;
		if(reg_ind == 3) R3;	
		if(reg_ind == 0) R4;	
	}
// настройка портов управления внешними устройствами //setting port control external devices
/*	if(RELE1 == 1) UP1on;	// управлением реле //control relay
	else UP1of;
	if(RELE2 == 1) UP2on;	// управлением реле
	else UP2of;
	if(RELE3 == 1) UP3on;	// управлением реле
	else UP3of;
	if(RELE4 == 1) UP4on;	// управлением реле
	else UP4of;
	if(RELE5 == 1) UP5on;	// управлением реле
	else UP5of;
*/
//загрузка портов //loading ports
	PORTA	= d_PORTA;	//
	PORTB	= d_PORTB;	//
	PORTC	= d_PORTC;	//
}
//------------------------------------------------------------------------

//Преобразование 16 бит в 4 HEX //Convert 16 bit to 4 HEX
void bin_HEX (unsigned int chisloin, char point)
{
		edin=(chisloin & 0b00001111);
		chisloin>>=4;
		dest=(chisloin & 0b00001111);
		chisloin>>=4;				
		sotn=(chisloin & 0b00001111);
		chisloin>>=4;
		tysc=chisloin;
				
		edin=decodHEX[edin];
		if(point==4)edin |= 0b10000000;
		dest=decodHEX[dest];
		if(point==3)dest |= 0b10000000;
		sotn=decodHEX[sotn];
		if(point==2)sotn |= 0b10000000;
		tysc=decodHEX[tysc];
		if(point==1)tysc |= 0b10000000;			
}//------------------------------------------------------------------------	



// Convert 16 bit binary to decimal Chila signed
// range of decimal numbers up to 9999 -999
//Преобразование 16 бит двоичного чила в десятичное со знаком
//диапазон десятичных чисел 9999 до -999
//nul=0 - 0,1 - 00,
//des=0 -0,1 - 0.0
void bin_dec (int chisloin,char nul,char des)
{
	static bit MINUS;
	int	chislo;       	// регистры преобразователя
//инциализация переменных
	chislo=chisloin; 	// преобразование	
	MINUS=0; 		
//обработка отрицательных чисел
	if(chislo <0)
	{
		chislo=-chislo;
		MINUS=1;
	}	
		tysc=chislo%10000/1000;
		sotn=chislo%1000/100;
		dest=chislo%100/10;
		edin=chislo%10;
//очистка незначащих нулей
		if (tysc==0)
		{
			tysc=10;
			if (sotn==0)
			{
				sotn=10;
				if (dest==0)
				{
					if(!nul)dest=10;//если nul == 1 - индикации 00
				}	
			}
		}
// установка символа минус
		if(MINUS==1)
		{
			if(dest==10)
			{
				dest=11;
			}
			else if(sotn==10)
			{
				sotn=11;
			} 
			else if(tysc==10)
			{
				tysc=11;
			}
		}				
//преобразование чисел в символы индикатора
		edin=decod[edin];
		dest=decod[dest];
		if(des)dest |= 0b10000000;
		sotn=decod[sotn];
		tysc=decod[tysc];
}//--------------------------------------------------------------------------------------- 

//загрузка индикатора
//buf1-buf4 регистры индикатора или буфера
//nazn 
// 0 - загрузка на индикатор
// 1 - двигаемся вверх go_up()
// 2 - двигаемся вниз go_down()
// 3 - двигаемся влево go_left()
// 4 - двигаемся вправо go_right()
// 5 - накат влево imposeL()
// 6 - накат вправо imposeR()

void loading(char buf1, char buf2, char buf3, char buf4, char nazn)
{
	if(nazn==0 || nazn>6)
	{
		ind_1=buf1;
		ind_2=buf2;
		ind_3=buf3;
		ind_4=buf4;
	}
	else
	{
		indb[0]=buf1;
		indb[1]=buf2;
		indb[2]=buf3;
		indb[3]=buf4;
		 
		 if(nazn==1)go_up();	//двигаемся вверх
	else if(nazn==2)go_down();	//двигаемся вниз
	else if(nazn==3)go_left();	//двигаемся влево
	else if(nazn==4)go_right();	//двигаемся вправо
	else if(nazn==5)imposeL();	//накат влево
	else if(nazn==6)imposeR();	//накат вправо
	
	}
}//------------------------------------------------


//загрузка индикатора
//более тяжелая версия
//buf1-buf4 регистры индикатора или буфера
//nazn 
// 0 - загрузка на индикатор
// 1 - двигаемся вверх go_up()
// 2 - двигаемся вниз go_down()
// 3 - двигаемся влево go_left()
// 4 - двигаемся вправо go_right()
// 5 - накат влево imposeL()
// 6 - накат вправо imposeR()
// 7 - декоративный счетчик go_down_counr()
// 8 - декоративный счетчик go_up_counr()
void loadingD (char buf1, char buf2, char buf3, char buf4, char nazn)
{
	if(nazn==0 || nazn>8)
	{
		ind_1=buf1;
		ind_2=buf2;
		ind_3=buf3;
		ind_4=buf4;
	}
	else
	{
		indb[0]=buf1;
		indb[1]=buf2;
		indb[2]=buf3;
		indb[3]=buf4;
		 
		 if(nazn==1)go_up();	//двигаемся вверх
	else if(nazn==2)go_down();	//двигаемся вниз
	else if(nazn==3)go_left();	//двигаемся влево
	else if(nazn==4)go_right();	//двигаемся вправо
	else if(nazn==5)imposeL();	//накат влево
	else if(nazn==6)imposeR();	//накат вправо
	else if(nazn==7)go_down_counr();//декоративный счетчик	
	else if(nazn==8)go_up_counr();	//декоративный счетчик	
	
	}
}//------------------------------------------------

	
//задежка индикации
void zaderj(char dlit)
{
char pous;
	for(pous=0;pous<dlit;pous++)
	{
		__delay_ms(12);
		CLRWDT(); 					//сброс сторожевого таймера +++++++++++++++++++++- 
	}
}//------------------------------------------------
				
//очистка влево
void ochisL (char pomt)
{
	char cikle;
	for(cikle=0;cikle<4;cikle++)
	{
		ind_1=ind_2;
		ind_2=ind_3;
		ind_3=ind_4;
		ind_4=0;
		zaderj(pomt);
	}
}//------------------------------------------------

//очистка вправо
void ochisR (char pomt)
{
	char cikle;
	for(cikle=0;cikle<4;cikle++)
	{
		ind_4=ind_3;
		ind_3=ind_2;
		ind_2=ind_1;
		ind_1=0;
		zaderj(pomt);
	}
}//------------------------------------------------

//бегущая строка справо налево
void bigstroka(const char *str)
{
char ptr=0;
	ochisL(DLIT+11);			
	while (str[ptr] != 0) 
	{
		ind_1=ind_2;
		ind_2=ind_3;
		ind_3=ind_4;
		ind_4=str[ptr++];
		zaderj(DLIT+11);
	}
	ochisL(DLIT+11);			
}//------------------------------------------------



	
// выезд буфера справо налево
void go_left(void)
{
char cikle;
	ochisL(DLIT);

	for(cikle=0;cikle<4;cikle++)
	{
		ind_1=ind_2;
		ind_2=ind_3;
		ind_3=ind_4;
		ind_4=indb[cikle];
		zaderj(DLIT);
	}
}//------------------------------------------------	


// выезд буфера слево на право
void go_right(void)
{
char cikle;
	ochisR(DLIT);//очистка вправо

	for(cikle=0;cikle<4;cikle++)
	{
		ind_4=ind_3;
		ind_3=ind_2;
		ind_2=ind_1;
		ind_1=indb[3-cikle];
		zaderj(DLIT);
	}
}//------------------------------------------------



// выезд буфера снизу вверх
void go_up_counr(void)
{
	if(indb[3]!=ind_4 && indb[2]==ind_3 && indb[1]==ind_2 && indb[0]==ind_1)
	{
		ind_4 &= 0b01011100;	
		if(0b00000100 & ind_4) ind_4 |= 0b00000010;
		if(0b00001000 & ind_4) ind_4 |= 0b01000000;
		if(0b00010000 & ind_4) ind_4 |= 0b00100000;
		ind_4 &= 0b00111111;
		if(0b00001000 & ind_4) ind_4 |= 0b01000000;
		ind_4 &= 0b01100011;
		zaderj(DLITV);
		ind_4 &= 0b01111110;
		if(0b01000000 & ind_4) ind_4 |= 0b00000001;
		ind_4 &= 0b00000001;
		zaderj(DLITV);
		ind_4 = 0;		
		zaderj(DLITV);
		if(0b00000001 & indb[0]) ind_4 |= 0b00001000;		
		zaderj(DLITV);
		ind_4 = 0;		
		if(0b00000001 & indb[0]) ind_4 |= 0b01000000;
		if(0b00000010 & indb[3]) ind_4 |= 0b00000100;		
		if(0b00100000 & indb[3]) ind_4 |= 0b00010000;
		if(0b01000000 & indb[3]) ind_4 |= 0b00001000;				
		zaderj(DLITV);
		ind_4 = indb[3];	
		zaderj(DLITV);
	}
	else if(indb[3]!=ind_4 && indb[2]!=ind_3 && indb[1]==ind_2 && indb[0]==ind_1)
	{		
		ind_3 &= 0b01011100;
		ind_4 &= 0b01011100;	
		if(0b00000100 & ind_3) ind_3 |= 0b00000010;
		if(0b00000100 & ind_4) ind_4 |= 0b00000010;
		if(0b00001000 & ind_3) ind_3 |= 0b01000000;
		if(0b00001000 & ind_4) ind_4 |= 0b01000000;
		if(0b00010000 & ind_3) ind_3 |= 0b00100000;
		if(0b00010000 & ind_4) ind_4 |= 0b00100000;
		ind_3 &= 0b00111111;
		ind_4 &= 0b00111111;
		if(0b00001000 & ind_3) ind_3 |= 0b01000000;
		if(0b00001000 & ind_4) ind_4 |= 0b01000000;
		ind_3 &= 0b01100011;
		ind_4 &= 0b01100011;
		zaderj(DLITV);
		ind_3 &= 0b01111110;
		ind_4 &= 0b01111110;
		if(0b01000000 & ind_3) ind_3 |= 0b00000001;
		if(0b01000000 & ind_4) ind_4 |= 0b00000001;
		ind_3 &= 0b00000001;
		ind_4 &= 0b00000001;
		zaderj(DLITV);
		ind_3 = 0;
		ind_4 = 0;		
		zaderj(DLITV);
		if(0b00000001 & indb[0]) ind_3 |= 0b00001000;
		if(0b00000001 & indb[0]) ind_4 |= 0b00001000;		
		zaderj(DLITV);
		ind_3 = 0;
		ind_4 = 0;		
		if(0b00000001 & indb[0]) ind_3 |= 0b01000000;
		if(0b00000001 & indb[0]) ind_4 |= 0b01000000;
		if(0b00000010 & indb[2]) ind_3 |= 0b00000100;
		if(0b00000010 & indb[3]) ind_4 |= 0b00000100;		
		if(0b00100000 & indb[2]) ind_3 |= 0b00010000;
		if(0b00100000 & indb[3]) ind_4 |= 0b00010000;
		if(0b01000000 & indb[2]) ind_3 |= 0b00001000;
		if(0b01000000 & indb[3]) ind_4 |= 0b00001000;				
		zaderj(DLITV);
		ind_3 = indb[2];
		ind_4 = indb[3];	
		zaderj(DLITV);
	}
	else if(indb[3]!=ind_4 && indb[2]!=ind_3 && indb[1]!=ind_2 && indb[0]==ind_1)
	{		
		ind_2 &= 0b01011100;
		ind_3 &= 0b01011100;
		ind_4 &= 0b01011100;	
		if(0b00000100 & ind_2) ind_2 |= 0b00000010;
		if(0b00000100 & ind_3) ind_3 |= 0b00000010;
		if(0b00000100 & ind_4) ind_4 |= 0b00000010;
		if(0b00001000 & ind_2) ind_2 |= 0b01000000;
		if(0b00001000 & ind_3) ind_3 |= 0b01000000;
		if(0b00001000 & ind_4) ind_4 |= 0b01000000;
		if(0b00010000 & ind_2) ind_2 |= 0b00100000;
		if(0b00010000 & ind_3) ind_3 |= 0b00100000;
		if(0b00010000 & ind_4) ind_4 |= 0b00100000;
		ind_2 &= 0b00111111;
		ind_3 &= 0b00111111;
		ind_4 &= 0b00111111;
		if(0b00001000 & ind_2) ind_2 |= 0b01000000;
		if(0b00001000 & ind_3) ind_3 |= 0b01000000;
		if(0b00001000 & ind_4) ind_4 |= 0b01000000;
		ind_2 &= 0b01100011;
		ind_3 &= 0b01100011;
		ind_4 &= 0b01100011;
		zaderj(DLITV);
		ind_2 &= 0b01111110;
		ind_3 &= 0b01111110;
		ind_4 &= 0b01111110;
		if(0b01000000 & ind_2) ind_2 |= 0b00000001;
		if(0b01000000 & ind_3) ind_3 |= 0b00000001;
		if(0b01000000 & ind_4) ind_4 |= 0b00000001;
		ind_2 &= 0b00000001;
		ind_3 &= 0b00000001;
		ind_4 &= 0b00000001;
		zaderj(DLITV);
		ind_2 = 0;
		ind_3 = 0;
		ind_4 = 0;		
		zaderj(DLITV);
		if(0b00000001 & indb[0]) ind_2 |= 0b00001000;
		if(0b00000001 & indb[0]) ind_3 |= 0b00001000;
		if(0b00000001 & indb[0]) ind_4 |= 0b00001000;		
		zaderj(DLITV);
		ind_2 = 0;
		ind_3 = 0;
		ind_4 = 0;		
		if(0b00000001 & indb[0]) ind_2 |= 0b01000000;
		if(0b00000001 & indb[0]) ind_3 |= 0b01000000;
		if(0b00000001 & indb[0]) ind_4 |= 0b01000000;
		if(0b00000010 & indb[1]) ind_2 |= 0b00000100;
		if(0b00000010 & indb[2]) ind_3 |= 0b00000100;
		if(0b00000010 & indb[3]) ind_4 |= 0b00000100;		
		if(0b00100000 & indb[1]) ind_2 |= 0b00010000;
		if(0b00100000 & indb[2]) ind_3 |= 0b00010000;
		if(0b00100000 & indb[3]) ind_4 |= 0b00010000;
		if(0b01000000 & indb[1]) ind_2 |= 0b00001000;
		if(0b01000000 & indb[2]) ind_3 |= 0b00001000;
		if(0b01000000 & indb[3]) ind_4 |= 0b00001000;				
		zaderj(DLITV);
		ind_2 = indb[1];
		ind_3 = indb[2];
		ind_4 = indb[3];	
		zaderj(DLITV);
	}
	else if(indb[3]!=ind_4 && indb[2]!=ind_3 && indb[1]!=ind_2 && indb[0]!=ind_1) go_up();				
}//-------------------------------------------------------------------



// выезд буфера сверху вниз
void go_down_counr(void)
{
	if(indb[3]!=ind_4 && indb[2]==ind_3 && indb[1]==ind_2 && indb[0]==ind_1)
	{
		ind_4 &= 0b01100011;	
		if(0b01000000 & ind_4) ind_4 |= 0b00001000;
		if(0b00100000 & ind_4) ind_4 |= 0b00010000;
		if(0b00000010 & ind_4) ind_4 |= 0b00000100;
		ind_4 &= 0b00111111;
		if(0b00000001 & ind_4) ind_4 |= 0b01000000;
		ind_4 &= 0b01011100;
		zaderj(DLITV);
		ind_4 &= 0b01110111;
		if(0b01000000 & ind_4) ind_4 |= 0b00001000;
		ind_4 &= 0b00001000;
		zaderj(DLITV);
		ind_4 = 0;		
		zaderj(DLITV);
		if(0b00001000 & indb[0]) ind_4 |= 0b00000001;		
		zaderj(DLITV);
		ind_4 = 0;		
		if(0b00001000 & indb[3]) ind_4 |= 0b01000000;
		if(0b00000100 & indb[3]) ind_4 |= 0b00000010;		
		if(0b00010000 & indb[3]) ind_4 |= 0b00100000;
		if(0b01000000 & indb[3]) ind_4 |= 0b00000001;				
		zaderj(DLITV);
		ind_4 = indb[3];	
		zaderj(DLITV);
	}
	else if(indb[3]!=ind_4 && indb[2]!=ind_3 && indb[1]==ind_2 && indb[0]==ind_1)
	{
		ind_3 &= 0b01100011;
		ind_4 &= 0b01100011;	
		if(0b01000000 & ind_3) ind_3 |= 0b00001000;
		if(0b01000000 & ind_4) ind_4 |= 0b00001000;
		if(0b00100000 & ind_3) ind_3 |= 0b00010000;
		if(0b00100000 & ind_4) ind_4 |= 0b00010000;
		if(0b00000010 & ind_3) ind_3 |= 0b00000100;
		if(0b00000010 & ind_4) ind_4 |= 0b00000100;
		ind_3 &= 0b00111111;
		ind_4 &= 0b00111111;
		if(0b00000001 & ind_3) ind_3 |= 0b01000000;
		if(0b00000001 & ind_4) ind_4 |= 0b01000000;
		ind_3 &= 0b01011100;
		ind_4 &= 0b01011100;
		zaderj(DLITV);
		ind_3 &= 0b01110111;
		ind_4 &= 0b01110111;
		if(0b01000000 & ind_3) ind_3 |= 0b00001000;
		if(0b01000000 & ind_4) ind_4 |= 0b00001000;
		ind_3 &= 0b00001000;
		ind_4 &= 0b00001000;
		zaderj(DLITV);
		ind_3 = 0;
		ind_4 = 0;		
		zaderj(DLITV);
		if(0b00001000 & indb[0]) ind_3 |= 0b00000001;
		if(0b00001000 & indb[0]) ind_4 |= 0b00000001;		
		zaderj(DLITV);
		ind_3 = 0;
		ind_4 = 0;		
		if(0b00001000 & indb[2]) ind_3 |= 0b01000000;
		if(0b00001000 & indb[3]) ind_4 |= 0b01000000;
		if(0b00000100 & indb[2]) ind_3 |= 0b00000010;
		if(0b00000100 & indb[3]) ind_4 |= 0b00000010;		
		if(0b00010000 & indb[2]) ind_3 |= 0b00100000;
		if(0b00010000 & indb[3]) ind_4 |= 0b00100000;
		if(0b01000000 & indb[2]) ind_3 |= 0b00000001;
		if(0b01000000 & indb[3]) ind_4 |= 0b00000001;				
		zaderj(DLITV);
		ind_3 = indb[2];
		ind_4 = indb[3];	
		zaderj(DLITV);
	}
	else if(indb[3]!=ind_4 && indb[2]!=ind_3 && indb[1]!=ind_2 && indb[0]==ind_1)
	{
		ind_2 &= 0b01100011;
		ind_3 &= 0b01100011;
		ind_4 &= 0b01100011;	
		if(0b01000000 & ind_2) ind_2 |= 0b00001000;
		if(0b01000000 & ind_3) ind_3 |= 0b00001000;
		if(0b01000000 & ind_4) ind_4 |= 0b00001000;
		if(0b00100000 & ind_2) ind_2 |= 0b00010000;
		if(0b00100000 & ind_3) ind_3 |= 0b00010000;
		if(0b00100000 & ind_4) ind_4 |= 0b00010000;
		if(0b00000010 & ind_2) ind_2 |= 0b00000100;
		if(0b00000010 & ind_3) ind_3 |= 0b00000100;
		if(0b00000010 & ind_4) ind_4 |= 0b00000100;
		ind_2 &= 0b00111111;
		ind_3 &= 0b00111111;
		ind_4 &= 0b00111111;
		if(0b00000001 & ind_2) ind_2 |= 0b01000000;
		if(0b00000001 & ind_3) ind_3 |= 0b01000000;
		if(0b00000001 & ind_4) ind_4 |= 0b01000000;
		ind_2 &= 0b01011100;
		ind_3 &= 0b01011100;
		ind_4 &= 0b01011100;
		zaderj(DLITV);
		ind_2 &= 0b01110111;
		ind_3 &= 0b01110111;
		ind_4 &= 0b01110111;
		if(0b01000000 & ind_2) ind_2 |= 0b00001000;
		if(0b01000000 & ind_3) ind_3 |= 0b00001000;
		if(0b01000000 & ind_4) ind_4 |= 0b00001000;
		ind_2 &= 0b00001000;
		ind_3 &= 0b00001000;
		ind_4 &= 0b00001000;
		zaderj(DLITV);
		ind_2 = 0;
		ind_3 = 0;
		ind_4 = 0;		
		zaderj(DLITV);
		if(0b00001000 & indb[0]) ind_2 |= 0b00000001;
		if(0b00001000 & indb[0]) ind_3 |= 0b00000001;
		if(0b00001000 & indb[0]) ind_4 |= 0b00000001;		
		zaderj(DLITV);
		ind_2 = 0;
		ind_3 = 0;
		ind_4 = 0;		
		if(0b00001000 & indb[1]) ind_2 |= 0b01000000;
		if(0b00001000 & indb[2]) ind_3 |= 0b01000000;
		if(0b00001000 & indb[3]) ind_4 |= 0b01000000;
		if(0b00000100 & indb[1]) ind_2 |= 0b00000010;
		if(0b00000100 & indb[2]) ind_3 |= 0b00000010;
		if(0b00000100 & indb[3]) ind_4 |= 0b00000010;		
		if(0b00010000 & indb[1]) ind_2 |= 0b00100000;
		if(0b00010000 & indb[2]) ind_3 |= 0b00100000;
		if(0b00010000 & indb[3]) ind_4 |= 0b00100000;
		if(0b01000000 & indb[1]) ind_2 |= 0b00000001;
		if(0b01000000 & indb[2]) ind_3 |= 0b00000001;
		if(0b01000000 & indb[3]) ind_4 |= 0b00000001;				
		zaderj(DLITV);
		ind_2 = indb[1];
		ind_3 = indb[2];
		ind_4 = indb[3];	
		zaderj(DLITV);
	}			
	else  if(indb[3]!=ind_4 && indb[2]!=ind_3 && indb[1]!=ind_2 && indb[0]!=ind_1) go_down();
			
}//-------------------------------------------------------------------



// выезд буфера сверху вниз
void go_down(void)
{
		ind_1 &= 0b01100011;
		ind_2 &= 0b01100011;
		ind_3 &= 0b01100011;
		ind_4 &= 0b01100011;	
		
		if(0b01000000 & ind_1) ind_1 |= 0b00001000;  
		if(0b01000000 & ind_2) ind_2 |= 0b00001000;
		if(0b01000000 & ind_3) ind_3 |= 0b00001000;
		if(0b01000000 & ind_4) ind_4 |= 0b00001000;

		if(0b00100000 & ind_1) ind_1 |= 0b00010000;
		if(0b00100000 & ind_2) ind_2 |= 0b00010000;
		if(0b00100000 & ind_3) ind_3 |= 0b00010000;
		if(0b00100000 & ind_4) ind_4 |= 0b00010000;

		if(0b00000010 & ind_1) ind_1 |= 0b00000100;
		if(0b00000010 & ind_2) ind_2 |= 0b00000100;
		if(0b00000010 & ind_3) ind_3 |= 0b00000100;
		if(0b00000010 & ind_4) ind_4 |= 0b00000100;

		ind_1 &= 0b00111111;
		ind_2 &= 0b00111111;
		ind_3 &= 0b00111111;
		ind_4 &= 0b00111111;

		if(0b00000001 & ind_1) ind_1 |= 0b01000000;
		if(0b00000001 & ind_2) ind_2 |= 0b01000000;
		if(0b00000001 & ind_3) ind_3 |= 0b01000000;
		if(0b00000001 & ind_4) ind_4 |= 0b01000000;
						
		ind_1 &= 0b01011100;
		ind_2 &= 0b01011100;
		ind_3 &= 0b01011100;
		ind_4 &= 0b01011100;

		zaderj(DLITV);

		ind_1 &= 0b01110111;
		ind_2 &= 0b01110111;
		ind_3 &= 0b01110111;
		ind_4 &= 0b01110111;

		if(0b01000000 & ind_1) ind_1 |= 0b00001000;
		if(0b01000000 & ind_2) ind_2 |= 0b00001000;
		if(0b01000000 & ind_3) ind_3 |= 0b00001000;
		if(0b01000000 & ind_4) ind_4 |= 0b00001000;
		
		ind_1 &= 0b00001000;
		ind_2 &= 0b00001000;
		ind_3 &= 0b00001000;
		ind_4 &= 0b00001000;
		
		zaderj(DLITV);

		ind_1 = 0;
		ind_2 = 0;
		ind_3 = 0;
		ind_4 = 0;		

		zaderj(DLITV);
		
		if(0b00001000 & indb[0]) ind_1 |= 0b00000001;
		if(0b00001000 & indb[0]) ind_2 |= 0b00000001;
		if(0b00001000 & indb[0]) ind_3 |= 0b00000001;
		if(0b00001000 & indb[0]) ind_4 |= 0b00000001;		
		
		zaderj(DLITV);
		
		ind_1 = 0;
		ind_2 = 0;
		ind_3 = 0;
		ind_4 = 0;		
		
		if(0b00001000 & indb[0]) ind_1 |= 0b01000000;
		if(0b00001000 & indb[1]) ind_2 |= 0b01000000;
		if(0b00001000 & indb[2]) ind_3 |= 0b01000000;
		if(0b00001000 & indb[3]) ind_4 |= 0b01000000;
		
		if(0b00000100 & indb[0]) ind_1 |= 0b00000010;
		if(0b00000100 & indb[1]) ind_2 |= 0b00000010;
		if(0b00000100 & indb[2]) ind_3 |= 0b00000010;
		if(0b00000100 & indb[3]) ind_4 |= 0b00000010;		
		
		if(0b00010000 & indb[0]) ind_1 |= 0b00100000;
		if(0b00010000 & indb[1]) ind_2 |= 0b00100000;
		if(0b00010000 & indb[2]) ind_3 |= 0b00100000;
		if(0b00010000 & indb[3]) ind_4 |= 0b00100000;
		
		if(0b01000000 & indb[0]) ind_1 |= 0b00000001;
		if(0b01000000 & indb[1]) ind_2 |= 0b00000001;
		if(0b01000000 & indb[2]) ind_3 |= 0b00000001;
		if(0b01000000 & indb[3]) ind_4 |= 0b00000001;				
		
		zaderj(DLITV);
		
		ind_1 = indb[0];
		ind_2 = indb[1];
		ind_3 = indb[2];
		ind_4 = indb[3];	
		
		zaderj(DLITV);			
}//-------------------------------------------------------------------

// выезд буфера снизу вверх
void go_up(void)
{
//очистка
		ind_1 &= 0b01011100;
		ind_2 &= 0b01011100;
		ind_3 &= 0b01011100;
		ind_4 &= 0b01011100;	
		
		if(0b00000100 & ind_1) ind_1 |= 0b00000010;  
		if(0b00000100 & ind_2) ind_2 |= 0b00000010;
		if(0b00000100 & ind_3) ind_3 |= 0b00000010;
		if(0b00000100 & ind_4) ind_4 |= 0b00000010;

		if(0b00001000 & ind_1) ind_1 |= 0b01000000;
		if(0b00001000 & ind_2) ind_2 |= 0b01000000;
		if(0b00001000 & ind_3) ind_3 |= 0b01000000;
		if(0b00001000 & ind_4) ind_4 |= 0b01000000;

		if(0b00010000 & ind_1) ind_1 |= 0b00100000;
		if(0b00010000 & ind_2) ind_2 |= 0b00100000;
		if(0b00010000 & ind_3) ind_3 |= 0b00100000;
		if(0b00010000 & ind_4) ind_4 |= 0b00100000;

		ind_1 &= 0b00111111;
		ind_2 &= 0b00111111;
		ind_3 &= 0b00111111;
		ind_4 &= 0b00111111;

		if(0b00001000 & ind_1) ind_1 |= 0b01000000;
		if(0b00001000 & ind_2) ind_2 |= 0b01000000;
		if(0b00001000 & ind_3) ind_3 |= 0b01000000;
		if(0b00001000 & ind_4) ind_4 |= 0b01000000;
						
		ind_1 &= 0b01100011;
		ind_2 &= 0b01100011;
		ind_3 &= 0b01100011;
		ind_4 &= 0b01100011;

		zaderj(DLITV);

		ind_1 &= 0b01111110;
		ind_2 &= 0b01111110;
		ind_3 &= 0b01111110;
		ind_4 &= 0b01111110;

		if(0b01000000 & ind_1) ind_1 |= 0b00000001;
		if(0b01000000 & ind_2) ind_2 |= 0b00000001;
		if(0b01000000 & ind_3) ind_3 |= 0b00000001;
		if(0b01000000 & ind_4) ind_4 |= 0b00000001;
		
		ind_1 &= 0b00000001;
		ind_2 &= 0b00000001;
		ind_3 &= 0b00000001;
		ind_4 &= 0b00000001;
		
		zaderj(DLITV);

		ind_1 = 0;
		ind_2 = 0;
		ind_3 = 0;
		ind_4 = 0;		

		zaderj(DLITV);
//загрузка		
		if(0b00000001 & indb[0]) ind_1 |= 0b00001000;
		if(0b00000001 & indb[0]) ind_2 |= 0b00001000;
		if(0b00000001 & indb[0]) ind_3 |= 0b00001000;
		if(0b00000001 & indb[0]) ind_4 |= 0b00001000;		
		
		zaderj(DLITV);
		
		ind_1 = 0;
		ind_2 = 0;
		ind_3 = 0;
		ind_4 = 0;		
		
		if(0b00000001 & indb[0]) ind_1 |= 0b01000000;
		if(0b00000001 & indb[0]) ind_2 |= 0b01000000;
		if(0b00000001 & indb[0]) ind_3 |= 0b01000000;
		if(0b00000001 & indb[0]) ind_4 |= 0b01000000;
		
		if(0b00000010 & indb[0]) ind_1 |= 0b00000100;
		if(0b00000010 & indb[1]) ind_2 |= 0b00000100;
		if(0b00000010 & indb[2]) ind_3 |= 0b00000100;
		if(0b00000010 & indb[3]) ind_4 |= 0b00000100;		
		
		if(0b00100000 & indb[0]) ind_1 |= 0b00010000;
		if(0b00100000 & indb[1]) ind_2 |= 0b00010000;
		if(0b00100000 & indb[2]) ind_3 |= 0b00010000;
		if(0b00100000 & indb[3]) ind_4 |= 0b00010000;
		
		if(0b01000000 & indb[0]) ind_1 |= 0b00001000;
		if(0b01000000 & indb[1]) ind_2 |= 0b00001000;
		if(0b01000000 & indb[2]) ind_3 |= 0b00001000;
		if(0b01000000 & indb[3]) ind_4 |= 0b00001000;				
		
		zaderj(DLITV);
		
		ind_1 = indb[0];
		ind_2 = indb[1];
		ind_3 = indb[2];
		ind_4 = indb[3];	
		
		zaderj(DLITV);			
}//-------------------------------------------------------------------

#define NAEZD 3

// наложение слева направо
void imposeR(void)
{
		ind_1 &= 0b11001111; // стирание 1
		zaderj(NAEZD);
		
		ind_1 |= (indb[0] & 0b00110000);		
		ind_1 &= 0b10110110;  // стирание 2	
		zaderj(NAEZD);		
		
		ind_1 |= (indb[0] & 0b01001001);		
		ind_1 &= 0b01111001;  // стирание 3		
		zaderj(NAEZD);		
		
		ind_1 = indb[0];		
//--------------------------------------------------------------
		ind_2 &= 0b11001111; // стирание 1
		zaderj(NAEZD);
		
		ind_2 |= (indb[1] & 0b00110000);		
		ind_2 &= 0b10110110;  // стирание 2	
		zaderj(NAEZD);		
		
		ind_2 |= (indb[1] & 0b01001001);		
		ind_2 &= 0b01111001;  // стирание 3		
		zaderj(NAEZD);		
		
		ind_2 = indb[1];		
//--------------------------------------------------------------
		ind_3 &= 0b11001111; // стирание 1
		zaderj(NAEZD);
		
		ind_3 |= (indb[2] & 0b00110000);		
		ind_3 &= 0b10110110;  // стирание 2	
		zaderj(NAEZD);		
		
		ind_3 |= (indb[2] & 0b01001001);		
		ind_3 &= 0b01111001;  // стирание 3		
		zaderj(NAEZD);		
		
		ind_3 = indb[2];
//--------------------------------------------------------------
		ind_4 &= 0b11001111; // стирание 1
		zaderj(NAEZD);
		
		ind_4 |= (indb[3] & 0b00110000);		
		ind_4 &= 0b10110110;  // стирание 2	
		zaderj(NAEZD);		
		
		ind_4 |= (indb[3] & 0b01001001);		
		ind_4 &= 0b01111001;  // стирание 3		
		zaderj(NAEZD);		
		
		ind_4 = indb[3];			
}//------------------------------------------------



// наложение справа налево
void imposeL(void)
{
		ind_4 &= 0b01111001; // стирание 1
		zaderj(NAEZD);
		
		ind_4 |= (indb[3] & 0b00000110);		
		ind_4 &= 0b10110110;  // стирание 2	
		zaderj(NAEZD);		
		
		ind_4 |= (indb[3] & 0b01001001);		
		ind_4 &= 0b11001111;  // стирание 3		
		zaderj(NAEZD);		
		
		ind_4 = indb[3];		
//--------------------------------------------------------------
		ind_3 &= 0b01111001; // стирание 1
		zaderj(NAEZD);
		
		ind_3 |= (indb[2] & 0b00000110);		
		ind_3 &= 0b10110110;  // стирание 2	
		zaderj(NAEZD);		
		
		ind_3 |= (indb[2] & 0b01001001);		
		ind_3 &= 0b11001111;  // стирание 3		
		zaderj(NAEZD);		
		
		ind_3 = indb[2];		
//--------------------------------------------------------------
		ind_2 &= 0b01111001; // стирание 1
		zaderj(NAEZD);
		
		ind_2 |= (indb[1] & 0b00000110);		
		ind_2 &= 0b10110110;  // стирание 2	
		zaderj(NAEZD);		
		
		ind_2 |= (indb[1] & 0b01001001);		
		ind_2 &= 0b11001111;  // стирание 3		
		zaderj(NAEZD);		
		
		ind_2 = indb[1];		
//--------------------------------------------------------------
		ind_1 &= 0b01111001; // стирание 1
		zaderj(NAEZD);
		
		ind_1 |= (indb[0] & 0b00000110);		
		ind_1 &= 0b10110110;  // стирание 2	
		zaderj(NAEZD);		
		
		ind_1 |= (indb[0] & 0b01001001);		
		ind_1 &= 0b11001111;  // стирание 3		
		zaderj(NAEZD);		
		
		ind_1 = indb[0];		
}//------------------------------------------------


/* необходимо встроить в прерывания с частотой 200-400 Гц.
//----------------------------------------------
	//период 	488 Гц	start
	indic();	// индикация
//----------------------------------------------
*/
