/**
  COG Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    cog.c

  @Summary
    This is the generated driver implementation file for the COG driver using MPLAB® Code Configurator

  @Description
    This header file provides implementations for driver APIs for COG.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.10.3
        Device            :  PIC16F1705
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X 2.26
*/

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "cog.h"

/**
  Section: COG APIs
*/

void COG_Initialize(void)
{
    // Reset double buffered register COG1CON0
    COG1CON0 = 0x00;

    // Set the COG to the options selected in MPLAB® Code Configurator

    // G1POLA Active high; G1POLC Active high; G1POLB Active high; G1POLD Active high; G1FDBS COGx_clock and COGxDBF; G1RDBS COGx_clock and COGxDBR; 
    COG1CON1 = 0x00;

    // G1RIS1 disabled; G1RIS3 disabled; G1RIS0 disabled; G1RIS2 disabled; G1RIS5 disabled; G1RIS4 disabled; G1RIS6 enabled; 
    COG1RIS = 0x40;

    // G1RSIM0 immediate; G1RSIM1 immediate; G1RSIM2 immediate; G1RSIM3 immediate; G1RSIM4 immediate; G1RSIM5 immediate; G1RSIM6 immediate; 
    COG1RSIM = 0x00;

    // G1FIS6 enabled; G1FIS1 disabled; G1FIS0 disabled; G1FIS5 disabled; G1FIS4 disabled; G1FIS3 disabled; G1FIS2 disabled; 
    COG1FIS = 0x40;

    // G1FSIM2 immediate; G1FSIM1 immediate; G1FSIM0 immediate; G1FSIM6 immediate; G1FSIM5 immediate; G1FSIM4 immediate; G1FSIM3 immediate; 
    COG1FSIM = 0x00;

    // G1ASDBD logic 0; G1ARSEN disabled; G1ASDAC logic 0 ; G1ASE not shutdown; 
    COG1ASD0 = 0x28;

    // G1AS2E disabled; G1AS3E disabled; G1AS1E disabled; G1AS0E disabled; 
    COG1ASD1 = 0x00;

    // G1SDATB static data low; G1SDATC static data low; G1SDATD static data low; G1SDATA static data low; G1STRA static level; G1STRB static level; G1STRC static level; G1STRD static level; 
    COG1STR = 0x00;

    // G1DBR 0x0; 
    COG1DBR = 0x00;

    // G1DBF 0x0; 
    COG1DBF = 0x00;

    // G1BLKR 0x0; 
    COG1BLKR = 0x00;

    // G1BLKF 0x0; 
    COG1BLKF = 0x00;

    // G1PHR 0x0; 
    COG1PHR = 0x00;

    // G1PHF 0x0; 
    COG1PHF = 0x00;

    // G1LD transfer complete; G1EN enabled; G1MD Half-Bridge mode; G1CS FOSC; 
    COG1CON0 = 0x8C;
}
void COG_initializerNew(void)
{
    // Reset double buffered register COG1CON0
    COG1CON0 = 0x00;

    // Set the COG to the options selected in MPLAB® Code Configurator

    // G1POLA Active high; G1POLC Active high; G1POLB Active high; G1POLD Active high; G1FDBS COGx_clock and COGxDBF; G1RDBS COGx_clock and COGxDBR; 
    COG1CON1 = 0x00;

    // G1RIS1 disabled; G1RIS3 disabled; G1RIS0 disabled; G1RIS2 disabled; G1RIS5 disabled; G1RIS4 disabled; G1RIS6 disabled; 
    COG1RIS = 0x00;

    // G1RSIM0 immediate; G1RSIM1 immediate; G1RSIM2 immediate; G1RSIM3 immediate; G1RSIM4 immediate; G1RSIM5 immediate; G1RSIM6 immediate; 
    COG1RSIM = 0x00;

    // G1FIS6 disabled; G1FIS1 disabled; G1FIS0 disabled; G1FIS5 disabled; G1FIS4 disabled; G1FIS3 disabled; G1FIS2 disabled; 
    COG1FIS = 0x00;

    // G1FSIM2 immediate; G1FSIM1 immediate; G1FSIM0 immediate; G1FSIM6 immediate; G1FSIM5 immediate; G1FSIM4 immediate; G1FSIM3 immediate; 
    COG1FSIM = 0x00;

    // G1ASDBD inactive state; G1ARSEN disabled; G1ASDAC inactive state; G1ASE not shutdown; 
    COG1ASD0 = 0x00;

    // G1AS2E disabled; G1AS3E disabled; G1AS1E disabled; G1AS0E disabled; 
    COG1ASD1 = 0x00;

    // G1SDATB static data low; G1SDATC static data low; G1SDATD static data low; G1SDATA static data low; G1STRA static level; G1STRB static level; G1STRC static level; G1STRD static level; 
    COG1STR = 0x00;

    // G1DBR 0x0; 
    COG1DBR = 0x00;

    // G1DBF 0x0; 
    COG1DBF = 0x00;

    // G1BLKR 0x0; 
    COG1BLKR = 0x00;

    // G1BLKF 0x0; 
    COG1BLKF = 0x00;

    // G1PHR 0x0; 
    COG1PHR = 0x00;

    // G1PHF 0x0; 
    COG1PHF = 0x00;

    // G1LD transfer complete; G1EN enabled; G1MD steered PWM mode; G1CS FOSC/4; 
    COG1CON0 = 0x80;
}

void COG_AutoShutdownEventSet()
{
    // Setting the GxASE bit of COGxASD0 register
    COG1ASD0bits.G1ASE = 1;
}

void COG_AutoShutdownEventClear()
{
    // Clearing the GxASE bit of COGxASD0 register
    COG1ASD0bits.G1ASE = 0;
}
/**
 End of File
*/

