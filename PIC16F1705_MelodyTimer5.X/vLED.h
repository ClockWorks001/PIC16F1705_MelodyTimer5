/*************************************************
*  LED for Timer Display
*************************************************/
#if !defined VLED_H
#define VLED_H

//output LED define
#define LED1_ON()		IO_RC3_SetHigh()
#define LED1_OFF()		IO_RC3_SetLow()
#define LED2_ON()		IO_RA4_SetHigh()
#define LED2_OFF()		IO_RA4_SetLow()
#define LED3_ON()		IO_RA5_SetHigh()
#define LED3_OFF()		IO_RA5_SetLow()

#define LED3min_ON()            IO_RC3_SetHigh()
#define LED3min_OFF()           IO_RC3_SetLow()
#define LED5min_ON()            IO_RA4_SetHigh()
#define LED5min_OFF()           IO_RA4_SetLow()
#define LED10min_ON()           IO_RA5_SetHigh()
#define LED10min_OFF()          IO_RA5_SetLow()

//******************************************************************************
//  Propertis
//******************************************************************************
enum eMenu_LED {
    eMenu_LED_LED3min_ON,
    eMenu_LED_LED5min_ON,
    eMenu_LED_LED10min_ON,
    eMenu_LED_Melody,
    eMenu_LED_Time_Count_Down,
    eMenu_LED_ALL_OFF,
    eMenu_LED_LED1_ON,
    eMenu_LED_LED2_ON,
    eMenu_LED_LED3_ON,
    eMenu_LED_End
    };

#if defined VLED_LIB
    enum eMenu_LED eMenu_LED_Status;

#else
	//extern unsigned char ucNagasa[];
    extern enum eMenu_LED eMenu_LED_Status;

#endif

//******************************************************************************
//  Prototype define
//******************************************************************************
//void vLEDClear(void);
//void vLED_Melody(AMELODY_DATA* pAMD);
//void vLED_CountDown(char cMinCountDownTime);
void vLEDBlink01(void);

#endif //LED_H