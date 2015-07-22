/*************************************************
*  Making music by PWM module
*************************************************/
#if !defined VBUZZER_PWM_H
#define VBUZZER_PWM_H

#define MUSIC_NUMBER_01 1
#define MUSIC_NUMBER_02 2
#define MUSIC_NUMBER_03 3

#define BEEP_3min  1
#define BEEP_5min  2
#define BEEP_10min 3

//******************************************************************************
//  Propertis
//******************************************************************************

// 楽譜 music sheet / music chart
// 音階 scale
// 音の長さ length

typedef union {
    unsigned short 	usAMelody;		// 2Byte data
    struct AMELODY_FACTER{
        unsigned char 	ucLength, ucScale;	// 1Byte Scale(音階), 1Byte Length(長さ)
    } F ;
} AMELODY;

typedef struct {
        unsigned short* uspMusic;
	unsigned char ucMusicPosition;		//music position
	unsigned short usLength;		// 2Byte Length(長さ)
	unsigned char ucRepeat;                 //a number for repeat music
	AMELODY uAM;
} AMELODY_DATA;

enum eMenu_Melody {
//typedef enum eMenu_Melody{
    eMenu_Melody_Start,
    eMenu_Melody_Repeat_Count_Down,
    eMenu_Melody_get_a_Data,
    eMenu_Melody_set_a_Beep,
    eMenu_Melody_wait_a_Tone,
    eMenu_Melody_stop,
    eMenu_Melody_End
    } EMENU_MELODY;

#if defined VBUZZER_PWM_LIB
    enum eMenu_Melody eMenu_Melody_Status;

    //----------------------------------------------------------------------------------------------
    //Melody data -> PWM parameter cheange table

    //wave length ratio for 2 octaves // 2オクターブ分の波長比
    const unsigned char ucOnkaiTBL[2][16] = {
            {0, 238, 225, 212, 200, 189, 178, 168, 159, 150, 142, 134, 126},
            {0, 119, 112, 106, 100, 94, 89, 84, 79, 75, 71, 67, 63}
    } ;

    //Timer Prescaler change table //オクターブからTimerのPrescaler値への変換テーブル。
    const unsigned char ucTenkaiTBL[6] = {0B100, 0B101, 0B010, 0B011, 0B000, 0B001};
    //１音の基本長さ
    #define BASIC_LENGTH	25
    #define GAP_LENGTH          5


#else
    //extern unsigned char ucNagasa[];
    extern enum eMenu_Melody eMenu_Melody_Status;
    //extern EMENU_MELODY eMenu_Melody_Status;
    extern AMELODY_DATA sAMD;
#endif

//******************************************************************************
//  Prototype define
//******************************************************************************
void vMenuForMelody(void);
unsigned char ucMusicPosition(void);
void vBuzzerStartMusic(unsigned char ucRepeat_Number);
char cIsMusicStop();
void vBuzzerSelectMusic01(void);
void vBuzzerSelectMusic02(void);
void vBuzzerSelectMusic03(void);
char cBuzzerGetMusicNumber(void);

#endif //BUZZER_PWM_H
