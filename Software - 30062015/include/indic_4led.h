//======================================================================================
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
//======================================================================================
//   --    --    --    --     -a-
//  |  |  |  |  |  |  |  |   f   b
//   --    --    --    --     -g-  
//  |  |  |  |  |  |  |  |   e   c
//   --.   -- .  --.   --.    -d- h
//    1     2     3     4
//======================================================================================
// функция индикации необходимо поместить в прерывания с периодом ~ 200-400 Гц.
// display function should be placed in an interrupt with a period of ~ 200-400 Hz.
void indic(void);	// функция индикации

// функции для преобразование чисел
//functions to convert numbers
// выходные данные переменные tysc, sotn, dest, edin - символы индикации
// Output variables tysc, sotn, dest, edin - symbols indicate
//Преобразование 16 бит двоичного числа в десятичное со знаком (диапазон 9999 до -999)
// Convert 16 bit binary number to decimal signed (range -999 to 9999)
void bin_dec (int chisloin,char nul,char des);
//Преобразование 16 бит в 4 HEX	
// Convert 16 bit to 4 HEX	
void bin_HEX (unsigned int chisloin, char point);

// функции вывода буфера на индикатор
// для использования этих функций надо предварительно загрузить буфер indb[]
// Output buffer to function indicator
// To use these functions need to pre-load buffer indb []
//		indb[0]=simbol;
//		indb[1]=simbol;
//		indb[2]=simbol;
//		indb[3]=simbol;
void imposeL(void);			// наложение справа налево //imposition from right to left
void imposeR(void);			// наложение слева направо // Overlay from left to right
void go_down(void);			// выезд буфера снизу вверх - идём вниз //leave a buffer from the bottom up - is going down
void go_up(void);			// выезд буфера сверху вниз - идем вверх //leave a buffer from the top down - we go up
void go_left(void);			// выезд буфера слево на право - идем налево //leave a buffer from left to right - go left
void go_right(void);		// выезд буфера справо налево - идем направо //leave a buffer right to left - go right
void bigstroka(const char *str);//бегущая строка справа налево //scrolling text from right to left
void go_down_counr(void); 	//счетчик с анимацией увеличение счета //counter with an increase in accounts animation
void go_up_counr(void);		//счетчик с анимацией уменьшение счета //- decrease in accounts

// вспомогательные функции
// pomt - задержка
// Helper functions
// Pomt - delay
void ochisR (char pomt);	//очистка индикатора вправо //cleaning indicator to the right
void ochisL (char pomt);	//очистка индикатора влево //cleaning indicator to the left
void zaderj (char dlit);	//задержка индикации //delay indicator

// функция универсальной загрузки индикатора //universal function of load indicator
// buf1-buf4 регистры индикатора или буфера
// nazn - тип индикации
// 0 - загрузка на индикатор
// 1 - двигаемся вверх go_up()
// 2 - двигаемся вниз go_down()
// 3 - двигаемся влево go_left()
// 4 - двигаемся вправо go_right()
// 5 - накат влево imposeL()
// 6 - накат вправо imposeR()
// Buf1-buf4 indicator registers or buffer
// Nazn - the type of display
// 0 - load indicator on
// 1 - go up go_up ()
// 2 - move down go_down ()
// 3 - move left go_left ()
// 4 - move to the right go_right ()
// 5 - reel to the left imposeL ()
// 6 - roll forward right imposeR ()
void loading(char buf1, char buf2, char buf3, char buf4, char nazn);

// более тяжелая версия (съедает дополнительно 0.6 кБ памяти)
// More severe version (0.6 kb in addition eats memory)
// nazn - тип индикации
// 0 - загрузка на индикатор
// 1 - двигаемся вверх go_up()
// 2 - двигаемся вниз go_down()
// 3 - двигаемся влево go_left()
// 4 - двигаемся вправо go_right()
// 5 - накат влево imposeL()
// 6 - накат вправо imposeR()
// 7 - декоративный счетчик go_down_counr()
// 8 - декоративный счетчик go_up_counr()
// 7 - a decorative counter go_down_counr ()
// 8 - a decorative counter go_up_counr ()
void loadingD(char buf1, char buf2, char buf3, char buf4, char nazn);
//---------------------------------------------------------------------------
#define DLIT 	8 			// константы длительностей для программ динамического вывода
#define DLITV	8			// constant duration for dynamic output programs
#define _XTAL_FREQ 40000000 // Наша тактовая (для текущего примера 40 Mhz) //Our clock (for example, the current 40 Mhz)
// установить с реальной величиной // Set to the real value
//---------------------------------------------------------------------------

//======================================================================================
// управляющие байты для работы программы индикации
// их необходимо конфигурировать под конкретную схему
// индикатор с общим катодом
// маски управления портами
//SEGxx в этих байтах установить в "1" те разряды, которые не участвуют в индикации,
//OBSxx в этих байтах установить в "1" биты, если они совпадают с управляющими портами разрядов индикаторов

// Control bytes for the program to display
// Need to be configured for a particular scheme
// Common-cathode display
// Mask of port management
// SEGxx in those bytes set to "1" are the bits that do not participate in the display,
// OBSxx in those bytes set to "1" bits, if they coincide with the discharge ports control indicators

// порт А
#define		SEGPA	0b11010011		// бит пищалки
#define		OBSPA	0b00101100		// управляющие 2/4-3/3-5/2
// порт В
#define		SEGPB	0b11000001
#define		OBSPB	0b00000000
// порт C
#define		SEGPC	0b11100100
#define		OBSPC	0b00000001		// управляющие 0/1

// описание портов индикации управление сегментами и разрядами индикатора
// 1 - обозначение разряда
// Description of the port control segment display and indicator bits
// 1 - designation of the discharge
#define		S_A		d_PORTB |= 0b00100000		// segment А
#define		S_B		d_PORTB |= 0b00010000		// segment B
#define		S_C		d_PORTB |= 0b00001000		// segment C	
#define		S_D		d_PORTB |= 0b00000100		// segment D
#define		S_E		d_PORTB |= 0b00000010		// segment E 
#define		S_F		d_PORTC |= 0b00010000		// segment F
#define		S_G		d_PORTC |= 0b00001000		// segment G
#define		S_H		d_PORTC |= 0b00000010		// segment H

#define		R1		d_PORTC &= 0b11111110		// управляющий бит первого знакоместа //control bit in the first familiarity
#define		R2		d_PORTA &= 0b11011111		// управляющий бит второго знакоместа //second control bit familiarity
#define		R3		d_PORTA &= 0b11110111		// управляющий бит третьего знакоместа // control bit third familiarity
#define		R4		d_PORTA &= 0b11111011		// управляющий бит четвертого знакоместа // control bit of the fourth familiarity
/*
// описание выходов на реле//description of the outputs on relay
#define		UP1on	d_PORTA |= 0b00000100		// relay1
#define		UP2on	d_PORTA |= 0b00100000		// relay2
#define		UP3on	d_PORTC |= 0b00000001		// реле3
#define		UP4on	d_PORTC |= 0b00001000		// реле4
#define		UP5on	d_PORTC |= 0b00000010		// реле5

#define		UP1of	d_PORTA &= 0b11111011		// реле1
#define		UP2of	d_PORTA &= 0b11011111		// реле2
#define		UP3of	d_PORTC &= 0b11111110		// реле3
#define		UP4of	d_PORTC &= 0b11110111		// реле4
#define		UP5of	d_PORTC &= 0b11111101		// реле4
*/


//======================================================================================
// символы знакогенератора
// цифры
// Characters signgenerator
// Number
//					  .gfedcba   
#define		c0		0b00111111			// 0-0
#define		c1		0b00000110			// 1-1
#define		c2		0b01011011			// 2-2 "z"
#define		c3		0b01001111			// 3-3
#define		c4		0b01100110			// 4-4 "Ч"
#define		c5		0b01101101			// 5-5 "S"
#define		c6		0b01111101			// 6-6
#define		c7		0b00000111			// 7-7
#define		c8		0b01111111			// 8-8
#define		c9		0b01101111			// 9-9
//======================================================================================
// символы //Characters
#define		c_		0b00000000			// символ "пробел" 
#define		cM		0b01000000			// символ "-"
#define		c__		0b00001000			// символ "подчеркивание"
#define		c_o		0b01100011			// символ "-o" верний нолик
#define		cn		0b01010100			// "n"
#define		cN		0b00110111			// "П"
#define		co		0b01011100			// "o" 
#define		cE		0b01111001			// "E"
#define		cr		0b01010000			// "r"
#define		cd		0b01011110			// "d"
#define		cb		0b01111100			// "b"
#define		ct		0b01111000			// "t"
#define		cA		0b01110111			// "A"
#define		cC		0b00111001			// "C"
#define		cH		0b01110110			// "H"
#define		cP		0b01110011			// "P"
#define		cc		0b01011000			// "c"
#define		ch		0b01110100			// "h"
#define		cL		0b00111000			// "L"
#define		ci		0b00010000			// "i"
#define		cq		0b01100111			// "q"
#define		cF		0b01110001			// "F"
#define		cU		0b00111110			// "U"
#define		cu		0b00011100			// "u"
#define		cuY		0b01101110			// "У"
#define		cI		0b00110000			// "I"
#define		cG		0b00111101			// "G"
#define		cS		0b01101101			// "S"
#define		cl		0b00011000			// "l"
#define		ca		0b01011111			// "a"
#define		cY		0b01110010			// "Y"
#define		cS		0b01101101			// "Y"
#define		ct3		0b01001001			// symbol "three features"
#define		ct2		0b01001000			// symbol "two features"
#define		ct1		0b00001000			// symbol "one feature"
//======================================================================================


// переменные используемые совместно с процедурой прерывания
// программа индикации
// Variables used in conjunction with a procedure interrupt
// Display program
 volatile char reg_ind,p_ind,				// внутрение регистры программы //internal registers of the program
  ind_1,ind_2,ind_3,ind_4,					// регистры индикации разрядов //registries display digits
  d_PORTA,d_PORTB,d_PORTC;					// буферные регистры // buffer registers

 volatile char  indb[4];					// регистры буфера индикации // registries display buffer

 volatile bit TOCHm1,TOCHm2,TOCHm3,TOCHm4,	// флаги мигания десятичной точки // flags flashing decimal point
  RAZR1,RAZR2,RAZR3,RAZR4,					// флаги мигания разрядов // flags flashing digits
  GAIN; 									// флаг гащения индикации //flag indicating enrichment
//RELE1,RELE2,RELE3,RELE4,RELE5;			// флаги управления внешними устройствами // Flags controlling external devices

//регистры системных часов					 // registers of the clock
 volatile char tim10gc,tim2gc; 
 volatile bit B_MIG; 						//флаг 2 герца. для эффектов мигания разрядов // flag 2 Hz. for the effects of flashing digits	

//-----------для функции bin_dec---------------------------------
char edin,dest,sotn,tysc; // регистры десятичных чисел	//registers decimal

// массив декодер чисел //decoder array of numbers
const char decod[]={c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c_,cM,c_};
//---------------------------------------------------------------
const char decodHEX[]={c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,cA,cb,cC,cd,cE,cF};
//---------------------------------------------------------------
