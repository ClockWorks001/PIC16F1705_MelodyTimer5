/*************************************************
*  LED for Timer Display
*************************************************/
#define VLED_LIB

#include <xc.h>         // XC8 General Include File
#include "mcc_generated_files/mcc.h"
#include "vClock01.h"
#include "vBuzzer_pwm.h"
#include "vLED.h"


//******************************************************************************
//  LED Clear
//******************************************************************************
void vLEDClear(void)
{
	LED3min_OFF();			//出力low
	LED5min_OFF();			//出力low
	LED10min_OFF();			//出力low
}

//******************************************************************************
//  LED output
//******************************************************************************
void vLED_Melody(AMELODY_DATA* pAMD)
{
        switch ((pAMD->ucMusicPosition)%3) {			//LED Blink
	case  	0 :
		LED3min_ON();			//出力low
		break;

	case  	1 :
		LED5min_ON();			//出力low
		break;

	case  	2 :
	default:
		LED10min_ON();			//出力low
		break;

	}
}

//******************************************************************************
//  LED output
//******************************************************************************
void vLED_CountDown(char cMinCountDownTime)
{
        if (sGet10mSecc() < 3) {			//LED Blink
                if (cMinCountDownTime <= WAIT3MIN) {
                    LED3min_ON();
                }else if (cMinCountDownTime <= WAIT5MIN) {
                    LED5min_ON();
                }else{
                    LED10min_ON();
                }
        }else{
                vLEDClear();			//LED all clear
        }
}

static char cWk1State = 0;
/*****************************
* LED Blink 01
* 曲に合わせてLEDを点滅させる。
*****************************/
void vLEDBlink01(void)
{
        vLEDClear();			//LED all clear
	switch (eMenu_LED_Status) {
	case  	eMenu_LED_LED3min_ON :
		LED3min_ON();			//出力low
		break;

	case  	eMenu_LED_LED5min_ON :
		LED5min_ON();			//出力low
		break;

	case  	eMenu_LED_LED10min_ON :
		LED10min_ON();			//出力low
		break;

	case  	eMenu_LED_Melody :
                vLED_Melody(&sAMD);
		break;

	case  	eMenu_LED_Time_Count_Down :
                vLED_CountDown(cGetMinCountDownTime());
		break;

	case  	eMenu_LED_ALL_OFF :
        	LED3min_OFF();			//出力low
                LED5min_OFF();			//出力low
                LED10min_OFF();			//出力low
		break;

	case  	eMenu_LED_LED1_ON :
                if ((sGet10mSecc() % 20) < 7) {	//LED Blink
                    LED1_ON();			
                } else {
                    LED1_OFF();
                }
		break;
	case  	eMenu_LED_LED2_ON :
                if ((sGet10mSecc() % 20) < 7) {	//LED Blink
                    LED2_ON();			
                } else {
                    LED2_OFF();
                }
		break;
	case  	eMenu_LED_LED3_ON :
                if ((sGet10mSecc() % 20) < 7) {	//LED Blink
                    LED3_ON();			
                } else {
                    LED3_OFF();
                }
		break;

	default:
		eMenu_LED_Status = eMenu_LED_ALL_OFF;
	}
}

