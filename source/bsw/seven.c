/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "seven.h"
/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

const uint8_t Seven_Lookup[] =
{
    0b00111111, //0
    0b00000110, //1
    0b01011011, //2
    0b01001111, //3
    0b01100110, //4
    0b01101101, //5
    0b01111101, //6
    0b00000111, //7 
    0b01111111, //8
    0b01101111, //9
    0b01110111, //0x0A
    0b11111111, //0x0B *Same as 8
    0b00111001, //0x0C 
    0b10111111, //0x0D *Same as 0
    0b01111001, //0x0E
    0b01110001, //0x0F
};
/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * To initalise the 7 seg with 0
 * 
 * @return RC_t error check
 */
RC_t Seven_init()
{
    Seven_Clear(SEVEN_DISPLAY_LEFT);
    Seven_Clear(SEVEN_DISPLAY_RIGHT);
    
    return RC_SUCCESS;
}

/**
 * To write into one of the 7 segement displays with a value from 0x00 to 0xFF
 * @param Seven_Display_t display   :   Left or Right display selector
 * @param uint8 value               :   Value that is to be displayed on the 7 seg
 * @return RC_t error check
 */
RC_t Seven_Write(Seven_Display_t display, uint8_t value)
{
    if(value > 15)
    {
        return RC_BAD_PARAM;
    }
    
    if(SEVEN_DISPLAY_RIGHT == display) //Selecting in which display to write
    {
        Pin_Sel_A_Write(0); //Selector pin, which is configured as 0 for Right and 1 for Left display
    }
    else
    {
        Pin_Sel_A_Write(1);
    }
    
    uint8_t data = Seven_Lookup[value]; //Checks entered number in the LUT
    SevenSeg_Reg_Write(data); //Write to the control register, the bits(uint8)
    
    return RC_SUCCESS;
    
}

/**
 * To write into one of the 7 segement displays in the Hex value
 * @param uint8 value               :   Value that is to be displayed on the 7 seg, this value is passed to write fucntion
 * @return RC_t error check
 */
RC_t Seven_Write_Hex(uint8_t value)
{
    uint8_t lower = value%16; //ex: 11%16 = 11 and 11th element in array is B
    uint8_t higher = value/16; //ex: 11/16 = 0 and then 0 will be displayed there in LEFT
    
    Seven_Write(SEVEN_DISPLAY_LEFT,higher);
    Seven_Write(SEVEN_DISPLAY_RIGHT,lower);
    
    return RC_SUCCESS;
}

/**
 * To write into one of the 7 segement displays decimal pointer
 * @param Seven_Display_t display   :   Left or Right display selector
 * @return RC_t error check
 */
RC_t Seven_Write_Dp(Seven_Display_t display)
{
    
    if(SEVEN_DISPLAY_RIGHT == display)
    {
        Pin_SevenSeg_SelA_Write(0);
    }
    else
    {
        Pin_SevenSeg_SelA_Write(1);
    }
    Control_Reg_7Seg_Write(0b10000000);
    
    return RC_SUCCESS;
}

/**
 * To clear one of the 7 segement displays
 * @param Seven_Display_t display   :   Left or Right display selector
 * @return RC_t error check
 */
RC_t Seven_Clear(Seven_Display_t display)
{
    Seven_Write(SEVEN_DISPLAY_LEFT,0b01111111);
    Seven_Write(SEVEN_DISPLAY_RIGHT,0b01111111);
    
    return RC_SUCCESS;
}