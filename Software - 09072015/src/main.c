/*******************************************************************************
 *
 * FileName     : BusIdDongle main.c
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

__CONFIG(FOSC_INTRC_NOCLKOUT & WDTE_ON & PWRTE_ON & MCLRE_ON & CP_ON & CPD_ON & BOREN_ON & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF & BOR4V_BOR40V );



/* DEFINE LOCAL CONSTANTS HERE -----------------------------------------------*/
#define DEFAULT_HEATER_START_TEMPERATURE    10
#define DEFAULT_HEATER_STOP_TEMPERATURE     20
#define DEFAULT_COOLER_START_TEMPERATURE    25
#define DEFAULT_MAX_TEMPERATURE             59
#define DEFAULT_RELAY_1_STATUS              0
#define DEFAULT_RELAY_2_STATUS              0
#define DEFAULT_RELAY_3_STATUS              0
#define DEFAULT_LCD_POWER_RELAY_STATUS      0
#define DEFAULT_DEBUG_MODE                  0

#define DEFAULT_DeviceSerial_ID0            1
#define DEFAULT_DeviceSerial_ID1            2
#define DEFAULT_DeviceSerial_ID2            3
#define DEFAULT_DeviceSerial_ID3            4
#define DEFAULT_DeviceSerial_ID4            5
#define DEFAULT_DeviceSerial_ID5            6
#define DEFAULT_DeviceSerial_ID6            7
#define DEFAULT_DeviceSerial_ID7            8


#define HEATER_START_TEMPERATURE_EEAddr     0
#define HEATER_STOP_TEMPERATURE_EEAddr      1
#define COOLER_START_TEMPERATURE_EEaddr     2
#define MAX_TEMPERATURE_EEaddr              3
#define RELAY_1_STATUS_EEAddr               4
#define RELAY_1_STATUS_EEAddr               5
#define RELAY_1_STATUS_EEAddr               6
#define LCD_POWER_RELAY_STATUS_EEAddr       7

#define DeviceSerial_EEAddr_0               8
#define DeviceSerial_EEAddr_1               9
#define DeviceSerial_EEAddr_2               10
#define DeviceSerial_EEAddr_3               11
#define DeviceSerial_EEAddr_4               12
#define DeviceSerial_EEAddr_5               13
#define DeviceSerial_EEAddr_6               14
#define DeviceSerial_EEAddr_7               15

#define DEBUG_MODE_EEAddr                   16

#define SM_IDLE                             0
#define SM_WAIT_STX                         1  
#define SM_WAIT_CMD                         2
#define SM_WAIT_DATA                        3
#define SM_WAIT_ETX                         4
#define SM_CMD_READY                        5


#define DEBOUNCE                            100

//#define __PICCPRO__

// Üretim Konfigurasyonu
__EEPROM_DATA(DEFAULT_HEATER_START_TEMPERATURE,DEFAULT_HEATER_STOP_TEMPERATURE,DEFAULT_COOLER_START_TEMPERATURE,DEFAULT_MAX_TEMPERATURE,DEFAULT_RELAY_1_STATUS,DEFAULT_RELAY_2_STATUS,DEFAULT_RELAY_3_STATUS,DEFAULT_LCD_POWER_RELAY_STATUS);
__EEPROM_DATA(DEFAULT_DeviceSerial_ID0,DeviceSerial_EEAddr_1,DeviceSerial_EEAddr_2,DeviceSerial_EEAddr_3,DeviceSerial_EEAddr_4,DeviceSerial_EEAddr_5,DeviceSerial_EEAddr_6,DeviceSerial_EEAddr_7);
__EEPROM_DATA(DEFAULT_DEBUG_MODE,0x3C,0x21,0x21,0x03,0x30,0x01,0x20);
__EEPROM_DATA('1','2','3','4','5','6','7','8');
__EEPROM_DATA('1','0',0,0,0,0,0,0);


/* DEFINE LOCAL TYPES HERE ---------------------------------------------------*/
/* DEFINE LOCAL MACROS HERE --------------------------------------------------*/
#define bit_set(var,bitno)          ((var) |= 1 << (bitno))
#define bit_clear(var,bitno)        ((var) &= ~(1 << (bitno)))
#define bit_test(data,bitno)        ((data>>bitno)&0x01)
#define bit_test_int(data,bitno) 	((data>>bitno)&0x0001)
#define hibyte(x)                   (unsigned char)	((x>>8) & 0xFF)
#define lobyte(x)                   (unsigned char)	(x & 0xFF)
#define HEATER_START_TEMPERATURE    EEPROM_READ(HEATER_START_TEMPERATURE_EEAddr);
#define HEATER_STOP_TEMPERATURE     EEPROM_READ(HEATER_STOP_TEMPERATURE_EEAddr);
#define COOLER_START_TEMPERATURE    EEPROM_READ(COOLER_START_TEMPERATURE_EEaddr);
#define MAX_TEMPERATURE             EEPROM_READ(MAX_TEMPERATURE_EEaddr);

/* DEFINE LOCAL VARIABLES HERE -----------------------------------------------*/
//Timer variables
volatile unsigned char tim10Hz, tim2Hz, tim1sec, tim1min;


volatile unsigned char uartReceiveBuffer[UART_RECEIVE_BUFFER_SIZE];
volatile unsigned char uartReceiveBufferR = 0;
volatile unsigned char uartReceiveBufferW = 0;

volatile unsigned char uartTransmitBuffer[UART_TRANSMIT_BUFFER_SIZE];
volatile unsigned char uartTransmitBufferR = 0;
volatile unsigned char uartTransmitBufferW = 0;

unsigned char dataBuffer[16];
unsigned char currentCommand;
unsigned char commandBuffer[COMMAND_SIZE];
unsigned char dataCounter;

volatile unsigned char buffer_SM = SM_WAIT_STX;

unsigned char bufferValue = 0;

const float a = 5000.0/1024.0;
volatile signed int currentTemperature;
volatile unsigned char currentTemperatureBuffer[6];
unsigned int activeFanGroups;

char printBuffer[6];

unsigned char j;
volatile unsigned char debugModeStatus = '0';
volatile unsigned char timerOverflow = 0;
volatile unsigned char oldTempLevel = 0;
volatile unsigned char debounceCounter;
bit debounceFlag;

volatile unsigned char tempH;
volatile unsigned char tempL;


char test;

volatile unsigned char tam;
volatile unsigned char ondalik;
char isaret;

unsigned int iSpeed;
bit sp;

unsigned char s1[] = "erdem";

unsigned char s2[] = "erdem";




/* DECLARE EXTERNAL VARIABLES HERE -------------------------------------------*/
/* DECLARE LOCAL FUNCTIONS HERE ----------------------------------------------*/
void vInitializeBoard(void);
void vAddToUartReceiveBuffer(unsigned char data);
unsigned char cGetFromReceiveBuffer(void);
void vCommandComplate(void);
void vAddToUartTransmitBuffer(unsigned char data);
unsigned char cGetFromTxBuffer(void);
unsigned char getTemperature(void);
void runFanGroups(void);
void vResetPrintBuffer(void);
void vSetDobounceTimer(void);

char * itoa (char * buf, int val, int base);
int atoi (const char * s);


/* DEFINE FUNCTIONS HERE -----------------------------------------------------*/
/* DEFINE LOCAL FUNCTIONS HERE -----------------------------------------------*/


/*******************************************************************************
 *
 * Function     :
 * PreCondition : None<
 * Input        : None
 * Output       : None
 * Side Effects : None
 * Overview     :
 * Note         : None
 *
 ******************************************************************************/
main(void)
{
    unsigned char i;
    unsigned char goster[6];
    vInitializeBoard();
    vInitializeVHN5019();
    vInitializeUart();
    vInitializeADC();
//    debounceFlag = 0;
    PEIE = 1;
    ei();
    uartTransmitBufferR = 0;
    uartTransmitBufferW = 0;
    uartReceiveBufferR = 0;
    uartReceiveBufferW = 0;
    currentTemperature = 0;


    LED_RED = 1;

    while(1)
    {
        CLRWDT();
//        tempH = oneWireReset();
        
//        __delay_ms(50);
//        __delay_ms(50);
//
//        if(sp == 1)
//        {
//            iSpeed -= 50;
//            if(iSpeed == 50)
//            {
//                sp = 0;
//            }
//        }
//        else
//        {
//            iSpeed += 50;
//            if(iSpeed == 1000)
//            {
//                sp = 1;
//            }
//        }
//        vSetSpeed(iSpeed);
//
//        currentTemperature = refreshTemperature();
        currentTemperature = getTemperature();
//        currentTemperature = 25;
//        currentTemperature = -100;
//        currentTemperature += 0.7;
        itoa(currentTemperatureBuffer, currentTemperature, 10);

        printBuffer[0] = '+';
        printBuffer[1] = currentTemperatureBuffer[0];
        printBuffer[2] = currentTemperatureBuffer[1];
        printBuffer[3] = currentTemperatureBuffer[2];
        printBuffer[4] = 'C';
        printBuffer[5] = '\0';

        if(currentTemperature < 100)
        {
            printBuffer[0] = '+';
            printBuffer[1] = '0';
            printBuffer[2] = currentTemperatureBuffer[0];
            printBuffer[3] = currentTemperatureBuffer[1];
            printBuffer[4] = 'C';
            printBuffer[5] = '\0';
        }
        if(currentTemperature < 10)
        {
            printBuffer[0] = '+';
            printBuffer[1] = '0';
            printBuffer[2] = '0';
            printBuffer[3] = currentTemperatureBuffer[0];
            printBuffer[4] = 'C';
            printBuffer[5] = '\0';
        }
        if(currentTemperature < 0)
        {
            printBuffer[0] = currentTemperatureBuffer[0];
            printBuffer[1] = '0';
            printBuffer[2] = currentTemperatureBuffer[1];
            printBuffer[3] = currentTemperatureBuffer[2];
            printBuffer[4] = 'C';
            printBuffer[5] = '\0';
        }
        if( (currentTemperature > -10) && (currentTemperature < 0) )
        {
            printBuffer[0] = currentTemperatureBuffer[0];
            printBuffer[1] = '0';
            printBuffer[2] = '0';
            printBuffer[3] = currentTemperatureBuffer[1];
            printBuffer[4] = 'C';
            printBuffer[5] = '\0';
        }

        for(i = 0; i<sizeof(printBuffer); i++)
        {
            if(printBuffer[i]=='\0') break;
            putch(printBuffer[i]);
        }
//
////        oneWireReset();
////        oneWireWriteByte(0xCC);
////        oneWireWriteByte(0x44);
////        __delay_us(120);
        __delay_ms(50);
        __delay_ms(50);
        __delay_ms(50);
        __delay_ms(50);
        __delay_ms(50);
        __delay_ms(50);
        __delay_ms(50);
        __delay_ms(50);
        CLRWDT();

        __delay_ms(50);
        __delay_ms(50);
        __delay_ms(50);
        __delay_ms(50);
        __delay_ms(50);
        __delay_ms(50);
        __delay_ms(50);
        __delay_ms(50);
//
//        __delay_ms(50);
//        __delay_ms(50);
//        __delay_ms(50);
//        __delay_ms(50);
//        __delay_ms(50);
//        __delay_ms(50);
//        __delay_ms(50);
//        __delay_ms(50);
//
//
//        __delay_ms(50);
//        __delay_ms(50);
//        __delay_ms(50);
//        __delay_ms(50);
//        __delay_ms(50);
//        __delay_ms(50);
//        __delay_ms(50);
//        __delay_ms(50);



        if(uartReceiveBufferW != uartReceiveBufferR)
        {
            bufferValue = cGetFromReceiveBuffer();

            if(bufferValue == STX)
            {
                buffer_SM = SM_WAIT_CMD;
                dataCounter = 0;
            }
            else if(buffer_SM == SM_WAIT_CMD)
            {
                commandBuffer[dataCounter] = bufferValue;
                dataCounter++;

                if(dataCounter == COMMAND_SIZE)
                {
                    buffer_SM = SM_WAIT_DATA;
                    dataCounter = 0;
                }
            }

            else if(buffer_SM == SM_WAIT_DATA)
            {
                if(dataCounter < MAX_DATA_SIZE)
                {
                    if(bufferValue == ETX)
                    {
                        buffer_SM = SM_CMD_READY;
                    }
                    else
                    {
                        dataBuffer[dataCounter] = bufferValue;
                    }
                    dataCounter++;
                }
                else
                {
                    buffer_SM = SM_WAIT_STX;
                }
            }
            if(buffer_SM == SM_CMD_READY)
            {
                if(commandBuffer[0] == 'C')
                {
                    currentCommand = (commandBuffer[1]-48) * 10;
                    currentCommand += (commandBuffer[2]-48);
                    switch(currentCommand)
                    {
                        case 1:
                            LED_GREEN = 1;
                            putch(tempH);
//                            vCommandComplate();
                            break;
                        case 2:
                            LED_GREEN = 0;
//                            vCommandComplate();
                            break;
                        case 3:
                            putch(dataBuffer[0]);
                            putch(dataBuffer[1]);
                            putch(dataBuffer[2]);
                            putch(dataBuffer[3]);
                            break;

                    }
                    buffer_SM = SM_WAIT_STX;
                }
                else
                {
                    buffer_SM = SM_WAIT_STX;
//                    vCommandComplate();
                }
            }
        }
    }   
}



void interrupt erdem(void)
{
    unsigned char temp;
    unsigned int i;

    if(T0IE && T0IF)
    {
        TMR0 = 93; // (1/5MHz)*256*163*12 = 100uS

        if(--tim10Hz==0) //100 uS
	{            
            tim10Hz=12;
            if(CONV==1)
            {                
                if(convert--==0)
                {
                    convert=9; 	// 8-9 ???????????? ????????? ??????????????? 0.75Cek
                    CONV=0;		//
                    conversionFinished = 1;
                    
                }
            }

            if(--tim2Hz==0)  //500 uS
            {
                tim2Hz=5;
                if(--tim1sec==0)  // 1 second
                {
                    tim1sec=2;
                    
                }//--------end period 1 sek.-----------------------------
            }//--------end period 2 Hz.-----------------------------
	}//--------end period 10 Hz.-----------------------------
        
        
        T0IF = 0;
        return;
    }
		
    if(RCIE && RCIF)
    {
        if (OERR)
        {
            CREN=0;
            CREN=1;
        }
        if(FERR)
        {
            temp = RCREG;
        }
        while(!RCIF)
        {
            vCheckError();
        }

        temp = RCREG;
        vAddToUartReceiveBuffer(temp);
        return;
    }

    if(TXIE && TXIF)
    {
        if(uartTransmitBufferR != uartTransmitBufferW)
        {
            temp = cGetFromTxBuffer();
            TXREG = temp;
            if(temp == ETX)
            {
                TXIE = 0;
            }
        }
    }
		

}



/*******************************************************************************
 *
 * Function     : void vInitializeBoard(void)
 * PreCondition : None
 * Input        : None
 * Output       : None
 * Side Effects : None
 * Overview     :
 * Note         : None
 *
 ******************************************************************************/
void vInitializeBoard(void)
{
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;

    CM1CON0 = 0;
    CM2CON0 = 0;
    OSCCON	= 0b01110101;


    C1ON = 0;
    C2ON = 0;


    WDTCON = 0b00010111;
    OPTION_REG	= 0b10000111; //pull ups disable TMR0 prescaler 1:256

    ANSELH = 0;
    ANSEL = 0;

    T0IF = 0;
    T0IE = 1;

    TRISA = 0b00000111; //
    TRISB = 0b00000000; //
    TRISC = 0b11000000; //
    TRISD = 0b00000000; //
    TRISE = 0b00000100; //

    tim10Hz = 5;
    tim2Hz = 5;
    tim1sec = 2;
    CONV = 0;
    conversionFinished = 0;
}


/*******************************************************************************
 *
 * Function     : void vAddToUartReceiveBuffer(unsigned char data)
 * PreCondition : None
 * Input        : None
 * Output       : None
 * Side Effects : None
 * Overview     :
 * Note         : None
 *
 ******************************************************************************/
void vAddToUartReceiveBuffer(unsigned char data)
{
    uartReceiveBuffer[ uartReceiveBufferW ] = data;
    uartReceiveBufferW++;
    if(uartReceiveBufferW == UART_RECEIVE_BUFFER_SIZE)
    {
        uartReceiveBufferW = 0;
    }
}

/*******************************************************************************
 *
 * Function     : unsigned char cGetFromReceiveBuffer(void)
 * PreCondition : None
 * Input        : None
 * Output       : None
 * Side Effects : None
 * Overview     :
 * Note         : None
 *
 ******************************************************************************/
unsigned char cGetFromReceiveBuffer(void)
{
    unsigned char value;

    value = uartReceiveBuffer[uartReceiveBufferR];
    uartReceiveBufferR++;
    if(uartReceiveBufferR == UART_RECEIVE_BUFFER_SIZE)
    {
        uartReceiveBufferR = 0;
    }
    return value;
}

/*******************************************************************************
 *
 * Function     : void vCommandComplate(void)
 * PreCondition : None
 * Input        : None
 * Output       : None
 * Side Effects : None
 * Overview     :
 * Note         : None
 *
 ******************************************************************************/
void vCommandComplate(void)
{
    unsigned char i;
    buffer_SM = SM_WAIT_STX;
    for(i=0; i<sizeof(commandBuffer); i++)
    {
        commandBuffer[i] = 0;
    }
    currentCommand = 0;
    TXIF = 0;
    TXIE = 1;
}

/*******************************************************************************
 *
 * Function     : void vAddToUartTransmitBuffer(unsigned char data)
 * PreCondition : None
 * Input        : None
 * Output       : None
 * Side Effects : None
 * Overview     :
 * Note         : None
 *
 ******************************************************************************/
void vAddToUartTransmitBuffer(unsigned char data)
{
    uartTransmitBuffer[uartTransmitBufferW ] = data;
    uartTransmitBufferW++;
    if(uartTransmitBufferW == UART_TRANSMIT_BUFFER_SIZE)
    {
        uartTransmitBufferW = 0;
    }
}

/*******************************************************************************
 *
 * Function     : unsigned char cGetFromTxBuffer(void)
 * PreCondition : None
 * Input        : None
 * Output       : None
 * Side Effects : None
 * Overview     :
 * Note         : None
 *
 ******************************************************************************/
unsigned char cGetFromTxBuffer(void)
{
    unsigned char value;

    value = uartTransmitBuffer[uartTransmitBufferR];
    uartTransmitBufferR++;
    if(uartTransmitBufferR == UART_TRANSMIT_BUFFER_SIZE)
    {
        uartTransmitBufferR = 0;
    }
    return value;
}

/*******************************************************************************
 *
 * Function     : unsigned char getTemperature(void)
 * PreCondition : None
 * Input        : None
 * Output       : None
 * Side Effects : None
 * Overview     :
 * Note         : None
 *
 ******************************************************************************/
unsigned char getTemperature(void)
{
    unsigned int iTempP, iTempN;
    float milliVolt;
    unsigned char m;

    iTempP = 0;
    for(m=0; m<16; m++)
    {
        iTempP += read_ADC(LM35_P);
    }
    iTempP /= 16;

    iTempN = 0;
    for(m=0; m<16; m++)
    {
        iTempN += read_ADC(LM35_N);
    }
    iTempN /= 16;

    milliVolt = (iTempP - iTempN) * a;
    m = milliVolt / 10.0;
    return m;
}


///*******************************************************************************
// *
// * Function     : void runFanGroups(void)
// * PreCondition : None
// * Input        : None
// * Output       : None
// * Side Effects : None
// * Overview     :
// * Note         : None
// *
// ******************************************************************************/
//void runFanGroups(void)
//{
//    unsigned char i, fBuf;
//    unsigned char levels[8];
//    unsigned char currentLevel;
//
//    for(i=0; i<8 ;i++)
//    {
//        levels[i] = EEPROM_READ(TEMP_LEVEL_START_EEADDR + i);
//    }
//    if(debugModeStatus == '0')
//    {
//        currentTemperature = getTemperature();
//    }
//
//    currentLevel = 0xFF;
//
//    for(i=0; i<8; i++)      //Ölçülen anlik isinin, hangi level oldugu bulunuyor
//    {
//        if(currentTemperature >= levels[i])
//        {
//            currentLevel = i;
//            break;
//        }
//        else
//        {
//            currentLevel = 7;
//        }
//    }
//
//    if(currentLevel != oldTempLevel)
//    {
//        oldTempLevel = currentLevel;
//        vSetDobounceTimer();
//    }
//
//    if(!debounceFlag)
//    {
//        if( currentLevel != 0xFF)
//        {
//            fBuf = EEPROM_READ(FAN_GROUP_START_EEADR_H + (currentLevel*2) );
//            activeFanGroups = 0;
//            activeFanGroups = fBuf;
//            fBuf &= 0b00111111;
//            FAN_PORT_H = 0x00;
//            FAN_PORT_H = fBuf;
//
//            activeFanGroups <<= 6;
//            fBuf = EEPROM_READ(FAN_GROUP_START_EEADR_H + (currentLevel*2) + 1);
//            activeFanGroups |= fBuf;
//            fBuf &= 0b00111111;
//            FAN_PORT_L = 0x00;
//            FAN_PORT_L = fBuf;
//        }
//        else//ISI okunam?yorsa tüm fanlar? devreye al?r
//        {
//            activeFanGroups = 0x0FFF;
//            FAN_PORT_H = 0x3F;
//            FAN_PORT_L = 0x3F;
//        }
//    }
//
//
//}


/*******************************************************************************
 *
 * Function     : void vResetPrintBuffer(void);
 * PreCondition : None
 * Input        : None
 * Output       : None
 * Side Effects : None
 * Overview     :
 * Note         : None
 *
 ******************************************************************************/
void vResetPrintBuffer(void)
{    
    unsigned char i;

    for(i=0; i<4; i++)
    {
        printBuffer[i]=0;
    }
}


/*******************************************************************************
 *
 * Function     : void vSetDobounceTimer(void)
 * PreCondition : None
 * Input        : None
 * Output       : None
 * Side Effects : None
 * Overview     :
 * Note         : None
 *
 ******************************************************************************/
void vSetDobounceTimer(void)
{
    debounceCounter = 0;
    debounceFlag = 1;
}
