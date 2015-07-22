/*************************************************
*  Making music by PWM module
*************************************************/
#define VBUZZER_PWM_LIB

#include <xc.h>         // XC8 General Include File
#include "mcc_generated_files/mcc.h"
#include "vBuzzer_pwm.h"
#include "vMusic_data.h"


AMELODY_DATA sAMD;
unsigned short* uspMusicNumber;

/*******************************
*  stop buzzer
*******************************/
void vBuzzerStop(void)
{
    // CCP2M P2AP2Chi_P2BP2Dhi; P2M halfbridge; DC2B 16;
    CCP2CON = 0x00;     // PWM clear
//    PORTAbits.RA6= 0;   // PWM output pin is low
//    PORTAbits.RA7= 0;   // PWM output pin is low
    TMR2_StopTimer();	// Timer2 stop
    COG_AutoShutdownEventSet();
}

/*******************************
*  restart buzzer
*******************************/
void vBuzzerReStart(void)
{
    PWM3_Initialize();     // PWM initialize
    TMR2_StartTimer();		// Timer2 start
     COG_AutoShutdownEventClear();
}

/*******************************
*  vBuzzerSetPWM
*******************************/
unsigned char ucTenkai, ucOnkaiNum;
void vBuzzerSetPWM(AMELODY_DATA* pAMD)
{
    ucTenkai = ucTenkaiTBL[(pAMD->uAM.F.ucScale >> 4) & 0b00000111];
    ucOnkaiNum = pAMD->uAM.F.ucScale & 0b00001111;

    if(ucOnkaiNum == 0){
        vBuzzerStop();			//PWM_OFF
    }else{
        T2CONbits.T2CKPS = (ucTenkai >> 1);
        PR2 = ucOnkaiTBL[ucTenkai & 0b00000001][ucOnkaiNum] - 1;
        CCPR2L	= PR2 / 2;		//rate 50%
//		CCPR2H	= 0x00;
        vBuzzerReStart();
    }
}

/*******************************
*  cBuzzerClearAMelodyData
*******************************/
char cBuzzerClearAMelodyData(AMELODY_DATA* pAMD)
{
    pAMD->ucMusicPosition = 0;
    pAMD->uAM.usAMelody = usMusicData01[pAMD->ucMusicPosition];
    vBuzzerReStart();
	return 0;
}

/*******************************
*  cBuzzerGetAMelodyData
*   return: 1:Playing 0:End of Music
*   input : AMELODY_DATA
*   output: return, AMELODY_DATA
*******************************/
char cBuzzerGetAMelodyData(AMELODY_DATA* pAMD)
{
//    pAMD->uAM.usAMelody = usMusicData01[pAMD->ucMusicPosition];
    pAMD->uAM.usAMelody = *(pAMD->uspMusic + pAMD->ucMusicPosition );
    pAMD->usLength = pAMD->uAM.F.ucLength * BASIC_LENGTH;
    pAMD->ucMusicPosition ++;
	if(pAMD->uAM.usAMelody == 0xFFFF){
		return 0;
	} else {
		return 1;
	}
}

/*******************************
*  cBuzzerWaitALength
*   return: 1:Waiting 0:End of Length
*   input : AMUUSICDATA
*   output: return, AMELODY_DATA
*******************************/
char cBuzzerWaitALength(AMELODY_DATA* pAMD)
{
    pAMD->usLength--;
	if(pAMD->usLength == 0){
		return 0;
	} else if(pAMD->usLength <= GAP_LENGTH) { //音の切れ目を作る
		vBuzzerStop();			//PWM_OFF
		return 1;
	} else {
		return 1;
	}
}

/*******************************
*  vMenuForMelody
*   return: -
*   input : -
*   output: Melody
*******************************/
void vMenuForMelody(void)
{
    switch (eMenu_Melody_Status) {

        case    eMenu_Melody_Start :
                sAMD.ucRepeat++;
                eMenu_Melody_Status++;
                break;

    //Play melody loop start from here------------------------------
        case    eMenu_Melody_Repeat_Count_Down :        
                sAMD.ucRepeat--;
                cBuzzerClearAMelodyData(&sAMD);        //set start point of a Melody data.
                if(sAMD.ucRepeat>0){
                    eMenu_Melody_Status++;
                }else{
                    eMenu_Melody_Status=eMenu_Melody_stop;
                }
                break;

        case    eMenu_Melody_get_a_Data :               
                if(cBuzzerGetAMelodyData(&sAMD)){       // when it have a MelodyData, go to Beep.
                    eMenu_Melody_Status++;
                }else{
                    eMenu_Melody_Status = eMenu_Melody_Repeat_Count_Down;
                }
                break;

        case    eMenu_Melody_set_a_Beep :               //set a scale to a PWM peripheral
                vBuzzerSetPWM(&sAMD);
                eMenu_Melody_Status++;
                break;

        case    eMenu_Melody_wait_a_Tone :               //wait a melody longth
                if(cBuzzerWaitALength(&sAMD)){
                    //wait!
                }else{
                    eMenu_Melody_Status=eMenu_Melody_get_a_Data;
                }
                break;
    //Play melody loop end------------------------------------------
        case    eMenu_Melody_stop :               //wait a musical note
                vBuzzerStop();
                break;
        default:
                eMenu_Melody_Status = eMenu_Melody_Start;
    }

}

/*******************************
*  ucMusicPosition
*   return: ucMusicPosition
*******************************/
unsigned char ucMusicPosition(void)
{
    return (sAMD.ucMusicPosition);
}

/*******************************
*  set Music Repeat Number to Repeat countdown.
*  start Music.
*******************************/
void vBuzzerStartMusic(unsigned char ucRepeatNumber)
{
    sAMD.uspMusic = uspMusicNumber ;
    sAMD.ucRepeat = ucRepeatNumber;
    eMenu_Melody_Status = eMenu_Melody_Start;
}

/*******************************
*  Music Stop : 1.
*******************************/
char cIsMusicStop()
{
    if(sAMD.ucRepeat>0){
        return 0;
    }else{
        return 1;
    }

}

/*******************************
*  vSelectMusic
*******************************/
void vBuzzerSelectMusic01(void)
{
    uspMusicNumber =  (unsigned short *) usMusicData01;
}
void vBuzzerSelectMusic02(void)
{
    uspMusicNumber =  (unsigned short *) usMusicData02;
}
void vBuzzerSelectMusic03(void)
{
    uspMusicNumber =  (unsigned short *) usMusicData03;
}

/*******************************
*  return Music Number
*******************************/
char cBuzzerGetMusicNumber(void)
{
    if(uspMusicNumber ==  (unsigned short *) usMusicData01) {
        return MUSIC_NUMBER_01;
    }else if(uspMusicNumber ==  (unsigned short *) usMusicData02) {
        return MUSIC_NUMBER_02;
    }else{
        return MUSIC_NUMBER_03;
    };
}
