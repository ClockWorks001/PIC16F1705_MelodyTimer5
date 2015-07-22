/*************************************************
*  Switch_Menu
*    Switch1 is status for Main routin.
*    Switch2 is status for Timer setting.
*************************************************/
#define VSWITCH_MENU_LIB

#include <xc.h>         // XC8 General Include File
#include "mcc_generated_files/mcc.h"
#include "vClock01.h"
#include "vLED.h"
#include "vSwitch_menu.h"
#include "vBuzzer_pwm.h"

SWITCHS SW1;
SWITCHS SW2;

static unsigned char cCountDownTime = WAIT3MIN;


//******************************************************************************
//  Switch SW1
//    push SW1 on/off check function
//    this function should be called at intervals 10msec.
//    SW1 go forward the eMenu_SW1_Status.
//******************************************************************************
void vSW1_Check(void)
{
        if(SW1_ON){
                switch(SW1.OnTime){
                        case 0:
                                eMenu_SW1_Status++;
                                break;

                        case 100:                       //10msec*100 wait for the first push
                                //select music status
                                eMenu_SW1_Status = eMenu_SW1_Music_Select;
                                break;

                        default:
                                break;
                }
                SW1.OnTime++;
        }else{
                SW1.OnTime = 0;
        }
}

//******************************************************************************
//  Switch SW2
//    push SW2 on/off check function
//    this function should be called at intervals 10msec.
//    SW2 go forward the eMenu_SW2_Status.
//******************************************************************************
void vSW2_Check(void)
{
        if(SW2_ON){
                switch(SW2.OnTime){
                        case 0:
                                eMenu_SW2_Status++;
                                break;

                        case 100:                       //10msec*100 wait for the first push
                                //repeat
                                eMenu_SW2_Status++;
                                SW2.OnTime = 100 - 30;  //10msec*30 wait for repeat
                                break;

                        default:
                                break;
                }
                SW2.OnTime++;
        }else{
                SW2.OnTime = 0;
        }
}

/*****************************
* Melody stop
*****************************/
void vMelodyStopAndClock01Clear(void)
{
    eMenu_Melody_Status = eMenu_Melody_stop;
    eMenu_LED_Status = eMenu_LED_ALL_OFF;
    vClock01_Clear();
}

/*****************************
* Menu for SW1
*****************************/
void vMenuForSW1(void)
{
        switch (eMenu_SW1_Status) {
                case    eMenu_SW1_Start :
                        eMenu_SW2_Status = eMenu_SW2_Wait;
                        vMelodyStopAndClock01Clear();
                        vSetMinCountDownTime(cCountDownTime); //clear the CountDown variable. カウントダウンタイマ初期化
                        eMenu_SW1_Status++;
                        break;

                case    eMenu_SW1_Time_Count_Down :
                        if (cIsMinCountDownTimeZero()) {       //IF Time is up
                            eMenu_SW1_Status++;
                        }
                        eMenu_LED_Status = eMenu_LED_Time_Count_Down;
                        break;

                case    eMenu_SW1_Melody_Start :              //play a melody
                        vBuzzerStartMusic(30);
                        eMenu_LED_Status = eMenu_LED_Melody;
                        vClock01_Clear();                   //countdown start for sleep
                        eMenu_SW1_Status++;
                        break;
                case    eMenu_SW1_Melody_Play :              //playing a melody
//                        if (ucGetMin01() >= 5 && ucMusicPosition() == 0) {        //音楽が5分以上経過し演奏が終わったら停止
                        if (cIsMusicStop()) {
                                eMenu_SW1_Status ++;
                        }
                        break;

                // ---------------------------------------------------
                case    eMenu_SW1_Wait :
                        vMelodyStopAndClock01Clear();
                        eMenu_SW2_Status = eMenu_SW2_Start;
                        eMenu_SW1_Status++;
                        break;
                case    eMenu_SW1_Wait2 :                   //Wait2の間に時間を選択する。時間が決まったらReturnToStart
                        if (ucGet1Secc() >= 7 ) {          //When it over 6sec, go to sleep
                                eMenu_SW1_Status = eMenu_SW1_Sleep;
                        }
                        break;
                case    eMenu_SW1_Return_To_Start :
                        eMenu_SW1_Status = eMenu_SW1_Start;
                        break;

                // ---------------------------------------------------
                case    eMenu_SW1_Sleep :
                        vMelodyStopAndClock01Clear();
                        eMenu_SW2_Status = eMenu_SW2_Wait;
                        eMenu_SW1_Status++;
                        break;

                case    eMenu_SW1_Sleep2 :
//                        INTERRUPT_PeripheralInterruptEnable();
//                        INTERRUPT_GlobalInterruptEnable();
                        TMR1_StopTimer();
                        TMR2_StopTimer();
                        INTCONbits.INTF = 0;
                        INTCONbits.INTE = 1;
//                        INTCONbits.IOCIF = 0;
//                        INTCONbits.IOCIE = 1; //INTERRUPT-ON-CHANGE needs system clock. It can't wake up from sleep.
//                        IOCBPbits.IOCBP0 = 1;
//                        IOCBNbits.IOCBN0 = 1;
                        VREGCONbits.VREGPM = 1; //Low Power Sleep Mode enabled.
                        SLEEP();
                        NOP();
                        INTCONbits.INTF = 0;
                        INTCONbits.INTE = 0;
//                        IOCBFbits.IOCBF0 = 0;
//                        INTCONbits.IOCIF = 0;
//                        INTCONbits.IOCIE = 0;
                        TMR1_StartTimer();
                        TMR2_StartTimer();
//
                // wake up 時の戻り先
                        eMenu_SW1_Status = eMenu_SW1_Start;
                        break;

                // ---------------------------------------------------
                case    eMenu_SW1_Music_Select :
                        vMelodyStopAndClock01Clear();
                        eMenu_SW2_Status = eMenu_SW2_Select_Start;
                        eMenu_SW1_Status++;
                        break;
                case    eMenu_SW1_Music_Select_Wait :        //Waitの間に曲を選択する。
                        if (ucGet1Secc() >= 40 ) {           //40sec以上経過したら停止
                                eMenu_SW1_Status = eMenu_SW1_Wait;
                        }
                        break;
                case    eMenu_SW1_Music_Select_End :         
                        eMenu_SW1_Status = eMenu_SW1_Wait;
                        break;
                // ---------------------------------------------------
                default:
                        eMenu_SW1_Status = eMenu_SW1_Start;
        }

}

/*****************************
* Menu for SW2 (time setting)
*****************************/
void vMenuForSW2(void)
{
        switch (eMenu_SW2_Status) {
                case    eMenu_SW2_Start :
                        switch (cCountDownTime) {
                        case    WAIT3MIN :
                                eMenu_SW2_Status = eMenu_SW2_Set_3min ;
                            break;
                        case    WAIT5MIN :
                                eMenu_SW2_Status = eMenu_SW2_Set_5min ;
                            break;
                        case    WAIT10MIN :
                                eMenu_SW2_Status = eMenu_SW2_Set_10min ;
                            break;
                        default:
                                eMenu_SW2_Status = eMenu_SW2_Set_3min ;
                        }
                        break;
                case    eMenu_SW2_Set_3min :
                        cCountDownTime = WAIT3MIN;              //カウントダウン時間を3分に設定
                        eMenu_LED_Status = eMenu_LED_LED3min_ON;
                        break;

                case    eMenu_SW2_Set_5min :
                        cCountDownTime = WAIT5MIN;              //カウントダウン時間を5分に設定
                        eMenu_LED_Status = eMenu_LED_LED5min_ON;
                        break;

                case    eMenu_SW2_Set_10min :
                        cCountDownTime = WAIT10MIN;     //カウントダウン時間を10分に設定
                        eMenu_LED_Status = eMenu_LED_LED10min_ON;
                        break;

                case    eMenu_SW2_Return_To_Set_3min:
                        eMenu_SW2_Status = eMenu_SW2_Set_3min;
                        break;

                //--------------------------------------------------------------
                case    eMenu_SW2_Select_Start :
                        switch (cBuzzerGetMusicNumber()) {
                        case    MUSIC_NUMBER_01 :
                                eMenu_SW2_Status = eMenu_SW2_Select_Music01 ;
                            break;
                        case    MUSIC_NUMBER_02 :
                                eMenu_SW2_Status = eMenu_SW2_Select_Music02 ;
                            break;
                        case    MUSIC_NUMBER_03 :
                                eMenu_SW2_Status = eMenu_SW2_Select_Music03 ;
                            break;
                        default:
                                eMenu_SW2_Status = eMenu_SW2_Select_Music01 ;
                        }
                        break;
                case    eMenu_SW2_Select_Music01 :
                        eMenu_LED_Status = eMenu_LED_LED1_ON;
                        vBuzzerSelectMusic01();
                        vBuzzerStartMusic(1);
                        eMenu_SW2_Status++;
                        break;
                case    eMenu_SW2_Select_Music01_Wait :
                        break;

                case    eMenu_SW2_Select_Music02 :
                        eMenu_LED_Status = eMenu_LED_LED2_ON;
                        vBuzzerSelectMusic02();
                        vBuzzerStartMusic(1);
                        eMenu_SW2_Status++;
                        break;
                case    eMenu_SW2_Select_Music02_Wait :
                        break;

                case    eMenu_SW2_Select_Music03 :
                        eMenu_LED_Status = eMenu_LED_LED3_ON;
                        vBuzzerSelectMusic03();
                        vBuzzerStartMusic(1);
                        eMenu_SW2_Status++;
                        break;
                case    eMenu_SW2_Select_Music03_Wait :
                        break;

                case    eMenu_SW2_Return_To_Select_Music01:
                        eMenu_SW2_Status = eMenu_SW2_Select_Music01;
                        break;
                //--------------------------------------------------------------

                case    eMenu_SW2_Wait: //during Count Down or Playing Melody
                        break;

                case    eMenu_SW2_Return_To_SW2_Start:
                        eMenu_SW1_Status = eMenu_SW1_Wait;
                        eMenu_SW2_Status = eMenu_SW2_Start;
                        break;

                //case    eMenu_SW2_End:
                default:
                        eMenu_SW2_Status = eMenu_SW2_Start;
        }

}



