/*************************************************
*  Clock01
*   Making 1msec for playing music.
*   Making 10msec for Switch menue.
*************************************************/
#if !defined VCLOCK01_H
#define VCLOCK01_H

#define WAIT3MIN		3	//wait time
#define WAIT5MIN		5	//wait time
#define WAIT10MIN		10	//wait time

//******************************************************************************
//  Propertis
//******************************************************************************
#if defined VCLOCK01_LIB
	short s1mSecc = 0,s10mSecc = 0;   // 時間計測用
	char cFlag1mSec = 0;		// 1msec時間計測用
	char cFlag10mSec = 0;		// 10msec時間計測用
	char cFlagSec = 0;		// 1sec時間計測用
	unsigned char ucSec01, ucMin01, ucHour01;
	char cMinCountDown;

#else
//	extern short s1mSecc,s10mSecc;     //10msec counter : sSsecc * 100 = 1sec
//	extern char cFlag1mSec;
//	extern char cFlag10mSec;
//	extern char cFlagSec;
//	extern unsigned char ucSec01, ucMin01, ucHour01;
//	char cMinCountDown;

#endif

//******************************************************************************
//  Prototype define
//******************************************************************************
void vClock01_Clear();
void vClock01_interrupt();
void vClock01();
char cFlag1mSec_ON();
char cFlag10mSec_ON();
void vSetMinCountDownTime(char cTime);
char cIsMinCountDownTimeZero();
char cGetMinCountDownTime();
short sGet1mSecc();
short sGet10mSecc();
unsigned char ucGet1Secc();
unsigned char ucGetMin01();

#endif //CLOCK01_H
