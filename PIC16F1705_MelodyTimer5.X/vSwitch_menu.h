/*************************************************
*  Switch_Menu
*    Switch1 is status for Main routin.
*    Switch2 is status for Timer setting.
*************************************************/
#if !defined VSWITCH_MENU_H
#define VSWITCH_MENU_H

#include "vInteger.h"

//******************************************************************************
//  User define
//******************************************************************************

//pushbuttons define
#define SW1_ON		IO_RA2_GetValue() == 0
#define SW1_OFF		IO_RA2_GetValue() == 1
#define SW2_ON		IO_RC0_GetValue() == 0
#define SW2_OFF		IO_RC0_GetValue() == 1

//#define SWITCH_ON 		1
//#define SWITCH_OFF 		0

//******************************************************************************
//  Propertis
//******************************************************************************
typedef struct {
	WORD  OnTime;
//	BYTE  flag = 0;
} SWITCHS;
enum eMenu_SW1 {
        eMenu_SW1_Start,
        eMenu_SW1_Time_Count_Down,
        eMenu_SW1_Melody_Start,
        eMenu_SW1_Melody_Play,

        eMenu_SW1_Wait,
        eMenu_SW1_Wait2,
        eMenu_SW1_Return_To_Start,
        eMenu_SW1_Sleep,
        eMenu_SW1_Sleep2,

        eMenu_SW1_Music_Select,
        eMenu_SW1_Music_Select_Wait,
        eMenu_SW1_Music_Select_End,
        eMenu_SW1_End
        };
enum eMenu_SW2 {
        eMenu_SW2_Start,
        eMenu_SW2_Set_3min,
        eMenu_SW2_Set_5min,
        eMenu_SW2_Set_10min,
        eMenu_SW2_Return_To_Set_3min,

        eMenu_SW2_Select_Start,
        eMenu_SW2_Select_Music01,
        eMenu_SW2_Select_Music01_Wait,
        eMenu_SW2_Select_Music02,
        eMenu_SW2_Select_Music02_Wait,
        eMenu_SW2_Select_Music03,
        eMenu_SW2_Select_Music03_Wait,
        eMenu_SW2_Return_To_Select_Music01,

        eMenu_SW2_Wait,
        eMenu_SW2_Return_To_SW2_Start,
        eMenu_SW2_End
        };

#if defined VSWITCH_MENU_LIB
	enum eMenu_SW1 eMenu_SW1_Status;
	enum eMenu_SW2 eMenu_SW2_Status;

#else
	//extern char ucTestCount = 0;
#endif


//******************************************************************************
//  Prototype define
//******************************************************************************
void vSW1_Check(void);
void vSW2_Check(void);

void vMenuForSW1(void);          // time count down
void vMenuForSW2(void);          // time setting
//void vModeStatusClr(void);

#endif //SWITCH_MENU_H

