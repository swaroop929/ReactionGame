/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */

#include "Arcadian.h"

static int RedHigh_GreenLow = 1;
static int YellowHigh_RedLow = 0;
static int GreenHigh_RedLow = 0;
static int count = 0;
static int curr_index = 0;
static int total_index = 9;

typedef struct
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
    uint16_t time;
}RG__Glow_t;

const RG__Glow_t RG_glowtable_1[] = {
//Red Green Blue TimeInMS
{255, 0, 0, 500},
{0, 255, 0, 500},
{0, 0, 255, 500},
{0, 0, 0, 100},
{255, 255, 255, 100},
{0, 0, 0, 100},
{255, 255, 255, 100},
{0, 0, 0, 100},
{255, 255, 255, 100}
};

/** 
 * \brief This task is activated by alrm_22ms cyclically
 * This task has lower priority than the tsk_game and the tsk_game can preempt this task
 * tsk_arcadian will make the Red, Yellow and Green LEDs glow in form of a travelling light and
 * will make the RGB light glow in a particular sequence defined in the array RG_glowtable_1[]
*/
TASK(tsk_arcadian)
{
    count++;
    
    //Fader
    if(RedHigh_GreenLow == 1)
    {
        PWM_Red_WriteCompare(PWM_Red_ReadCompare()+5);
        PWM_Green_WriteCompare(PWM_Green_ReadCompare()-5);
        if(PWM_Red_ReadCompare() == PWM_Red_ReadPeriod())
        {
            RedHigh_GreenLow = 0;
            YellowHigh_RedLow = 1;
        }
    }
    else if(YellowHigh_RedLow == 1)
    {
        PWM_Red_WriteCompare(PWM_Red_ReadCompare()-5);
        PWM_Yellow_WriteCompare(PWM_Yellow_ReadCompare()+5);
        if(PWM_Yellow_ReadCompare() == PWM_Yellow_ReadPeriod())
        {
            YellowHigh_RedLow = 0;
            GreenHigh_RedLow = 1;
        }
    }
    else if(GreenHigh_RedLow == 1)
    {
        PWM_Green_WriteCompare(PWM_Green_ReadCompare()+5);
        PWM_Yellow_WriteCompare(PWM_Yellow_ReadCompare()-5);
        if(PWM_Green_ReadCompare() == PWM_Green_ReadPeriod())
        {
            RedHigh_GreenLow = 1;
            GreenHigh_RedLow = 0;
        }
    }
        

    //LED GLOWER
   if(curr_index % total_index == 0)
    {
        curr_index = 0;
    }
        

    LED_RGB_Set(RG_glowtable_1[curr_index].Red, RG_glowtable_1[curr_index].Green, RG_glowtable_1[curr_index].Blue);
            
    if(count >= RG_glowtable_1[curr_index].time/22)
    {
       count = 0;
       curr_index++;
    }
    
    TerminateTask();
    
}



