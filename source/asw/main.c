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

#include "game.h"
#include "Arcadian.h"



//ISR that will increment the systick every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //Set systick period to 1 ms and  Start systick
    EE_systick_set_period(MILLISECONDS_TO_TICKS(1,BCLK__BUS_CLK__HZ)); 
    EE_systick_enable_int();
    

         

 for(;;) 
 {
    StartOS(OSDEFAULTAPPMODE);  // Start Operating System
 }
}

/** 
 * \brief This task is auto started by OS and it initialises ISRs and actiavates 
 * the tsk_arcadian and tsk_background
*/
TASK(tsk_init)
{
    //Seven Seg
    Seven_init();
    Seven_Write_Hex(0);
    
    //PWM init for RGB lights (Fader)
    PWM_Red_Start();
    PWM_Yellow_Start();
    PWM_Green_Start();
    
    //Glower init
    LED_init();
    
    //Initialisation of interupt of timer for 3 secs
    isr_3secs_StartEx(isr_3secs);
    
    //UART Print welcome message
    UART_LOG_Start();
      
    
    //Reconfigure ISRs prio from interupts tab with OSs new ISR parameters
    EE_system_init();
    
    //Start systick
    EE_systick_start();
    
    //Start alarm 1msec
    SetRelAlarm(alrm_1ms,1,1);
    SetRelAlarm(alrm_22ms,22,22);
    
    ActivateTask(tsk_background);
    ActivateTask(tsk_game);
    

    
    UART_LOG_PutString("Welcome to the Reaction Game \n");

    TerminateTask();
}

/** 
 * \brief This task is just the background task which will be running
 * when the system is in busy waiting state
*/
TASK(tsk_background)
{
    while(1)
    {
       /*Do Nothing*/ 
    }
    
    TerminateTask();
}










