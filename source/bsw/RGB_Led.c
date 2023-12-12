#include "RGB_Led.h"

static LED_onoff LED__state[LED_ALL] = {LED_OFF, LED_OFF, LED_OFF};



/**
 * <Description>
 * @param <first para>
 * @return <return value>
 */

RC_t LED_init()
{
    RGB_PWM_blue_Start();
    RGB_PWM_green_Start();
    RGB_PWM_red_Start();
    
    //Green_Led_Write(0);
    //Red_Led_Write(0);
   // Yellow_Led_Write(0);
    LED_Set(LED_ALL, LED_OFF);
    
    return RC_SUCCESS;
}

RC_t LED_Set(LED_id_t ledid, LED_onoff ledOnOff)
{
    LED__state[ledid] = ledOnOff;
    
    switch(ledid)
    {
        case LED_RED:
        {
            Red_Led_Write(ledOnOff);
            break;
        }
        case LED_YELLOW:
        {
            Yellow_Led_Write(ledOnOff);
            break;
        }
        case LED_GREEN:
        {
            Green_Led_Write(ledOnOff);
            break;
        }
        case LED_ALL:
        {
            Red_Led_Write(ledOnOff);
            Yellow_Led_Write(ledOnOff);
            Green_Led_Write(ledOnOff);
            break;
        }
        default:
        break;
    }
    
    return RC_SUCCESS;
}

RC_t LED_Toggle(LED_id_t ledid)
{
    if(LED__state[ledid] == LED_ON)
    {
        LED__state[ledid] = LED_OFF;
        CyDelay(1000);
    }
    else
    {
        LED__state[ledid] = LED_ON;
        CyDelay(1000);
    }
    
    LED_Set(ledid, LED__state[ledid]);
    
    return RC_SUCCESS;   
}

RC_t LED_RGB_Set(uint8_t red, uint8_t green, uint8_t blue)
{          
        RGB_PWM_blue_WriteCompare(LED__Pulse_Width[blue]);
        RGB_PWM_green_WriteCompare(LED__Pulse_Width[green]);
        RGB_PWM_red_WriteCompare(LED__Pulse_Width[red]);
    
    return RC_SUCCESS;
}