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

/** 
 * \brief This task is activated by the alarm alrm_1ms and is called every 1ms
 * This function increments a var, tick which will act as the time keeper
*/
ALARMCALLBACK(ticker)
{
    tick += 1; //Every 1 milli sec tick will increment
}

/** 
 * \brief This function is the game logic where the button press is checked and reaction time is displayed
 * \param uint32 randomValue    : [IN] This is the random value generated either 1 or 2
 * \param EventMaskType ev      : [IN] ev is button press event which is either button1 or button2
*/
void game_logic(uint32 randomValue, EventMaskType ev)
{
    if(tick < 1000 && game_round<=10) //10
        {
            
            char b[50];
            sprintf(b,"Reaction test program round %d \n",game_round);
            UART_LOG_PutString(b);
            
            if(ev & ev_button2)
            {
                //Right button
                if(randomValue == 1)
                {
                    UART_LOG_PutString("Great - correct button pressed \n");
                    char buffer[50];
                    sprintf(buffer, "Reaction time in ms: %d\n", tick);
                    //adding to array to calc avg
                    scores[game_round-1] = tick; //put it here because putting it on UART is taking around 1 ms
                    
                    UART_LOG_PutString(buffer);
                    UART_LOG_PutString("==========================================\n");
                    
                    correct_button_press++;
 
                    game_round++;
                }
                
                //Wrong button
                else if(randomValue == 2)
                {
                    UART_LOG_PutString("Wrong button pressed \n");
                    UART_LOG_PutString("==========================================\n");
                    
                    //adding to array to calc avg
                    scores[game_round-1] = 0;
                    game_round++;
                    
                    
                }
            }
            else if(ev & ev_button1)
            {
                //Wrong button
                if(randomValue == 1)
                {
                    UART_LOG_PutString("Wrong button pressed \n");
                    UART_LOG_PutString("==========================================\n");
                    
                    //adding to array to calc avg
                    scores[game_round-1] = 0; 
                    game_round++;
                    
                }
                
                //Right button
                else if(randomValue == 2)
                {
                    UART_LOG_PutString("Great - correct button pressed \n");
                    char buffer[50];
                    sprintf(buffer, "Reaction time in ms: %d\n", tick);
                    
                    //adding to array to calc avg
                    scores[game_round-1] = tick;
                    UART_LOG_PutString(buffer);
                    UART_LOG_PutString("==========================================\n");
                    
                    correct_button_press++;                    
                     
                    game_round++;
                }
            }       
        }
        else if(tick >= 1000 && game_round<=10) //11
        {
            char b[50];
            sprintf(b,"Reaction test program round %d \n",game_round);
            UART_LOG_PutString(b);
            UART_LOG_PutString("Too Slow \n");
            UART_LOG_PutString("==========================================\n");
            scores[game_round] = 0;
            game_round++;
            
           
        }
        if(game_round==11) //11
        {
            float sum = 0;
            float avg = 0;
            
            for(int j=0; j<10;j++)
            {
                sum = sum + scores[j];
            }
            
            
            avg = sum/(float)correct_button_press;
            
            char buff[10];
            sprintf(buff, "Avg reaction time in ms %d.%02d  \n", (int)avg, ((int)(avg * 100.0 + 0.5))%100) ;
            UART_LOG_PutString(buff);
            UART_LOG_PutString("==========================================\n");
            game_round++;
        }
        else if(game_round>11)
        {
            UART_LOG_PutString("Game over....\n");
            UART_LOG_PutString("Reset the board to start a new game \n");
            UART_LOG_PutString("==========================================\n");
        }
}

/** 
 * \brief This task is called whenever button3 or button4 are pressed
 * This task has a high priority than Arcadian task and tsk_game has the Reaction Game logic
*/
TASK(tsk_game)
{
    EventMaskType ev = 0;
    EventMaskType ev1 = 0;

    while(1) 
    {
        //2.2. Display on 7 seg
        Seven_Write(SEVEN_DISPLAY_LEFT,0);
        Seven_Write(SEVEN_DISPLAY_RIGHT,0);
        
        //Wait for starting the game
        WaitEvent(ev_ReStartButton);
        GetEvent(tsk_game,&ev1);
        ClearEvent(ev1);
        
        //random num generation
        
        srand(random_seed);
        uint32 randomValue = rand() % 2 + 1;
        
        //Display 1 or 2 on 7 segment
        Seven_Write(SEVEN_DISPLAY_LEFT,randomValue);
        Seven_Write(SEVEN_DISPLAY_RIGHT,randomValue);
        
        //Making tick to 0 so that the stopwatch will reset kindof !!
        tick = 0;
        
        //3. Check valid button press
        WaitEvent(ev_button1 | ev_button2);
        GetEvent(tsk_game,&ev);
        ClearEvent(ev);
        
        game_logic(randomValue, ev);
        
        /*if(tick < 1000 && game_round<=10) //10
        {
            
            char b[50];
            sprintf(b,"Reaction test program round %d \n",game_round);
            UART_LOG_PutString(b);
            
            if(ev & ev_button2)
            {
                //Right button
                if(randomValue == 1)
                {
                    UART_LOG_PutString("Great - correct button pressed \n");
                    char buffer[50];
                    sprintf(buffer, "Reaction time in ms: %d\n", tick);
                    //adding to array to calc avg
                    scores[game_round-1] = tick; //put it here because putting it on UART is taking around 1 ms
                    
                    UART_LOG_PutString(buffer);
                    UART_LOG_PutString("==========================================\n");
                    
                    correct_button_press++;
 
                    game_round++;
                }
                
                //Wrong button
                else if(randomValue == 2)
                {
                    UART_LOG_PutString("Wrong button pressed \n");
                    UART_LOG_PutString("==========================================\n");
                    
                    //adding to array to calc avg
                    scores[game_round-1] = 0;
                    game_round++;
                    
                    
                }
            }
            else if(ev & ev_button1)
            {
                //Wrong button
                if(randomValue == 1)
                {
                    UART_LOG_PutString("Wrong button pressed \n");
                    UART_LOG_PutString("==========================================\n");
                    
                    //adding to array to calc avg
                    scores[game_round-1] = 0; 
                    game_round++;
                    
                }
                
                //Right button
                else if(randomValue == 2)
                {
                    UART_LOG_PutString("Great - correct button pressed \n");
                    char buffer[50];
                    sprintf(buffer, "Reaction time in ms: %d\n", tick);
                    
                    //adding to array to calc avg
                    scores[game_round-1] = tick;
                    UART_LOG_PutString(buffer);
                    UART_LOG_PutString("==========================================\n");
                    
                    correct_button_press++;                    
                     
                    game_round++;
                }
            }       
        }
        else if(tick >= 1000 && game_round<=10) //11
        {
            char b[50];
            sprintf(b,"Reaction test program round %d \n",game_round);
            UART_LOG_PutString(b);
            UART_LOG_PutString("Too Slow \n");
            UART_LOG_PutString("==========================================\n");
            scores[game_round] = 0;
            game_round++;
            
           
        }
        if(game_round==11) //11
        {
            float sum = 0;
            float avg = 0;
            
            for(int j=0; j<10;j++)
            {
                sum = sum + scores[j];
            }
            
            
            avg = sum/(float)correct_button_press;
            
            char buff[10];
            sprintf(buff, "Avg reaction time in ms %d.%02d  \n", (int)avg, ((int)(avg * 100.0 + 0.5))%100) ;
            UART_LOG_PutString(buff);
            UART_LOG_PutString("==========================================\n");
            game_round++;
        }
        else if(game_round>11)
        {
            UART_LOG_PutString("Game over....\n");
            UART_LOG_PutString("Reset the board to start a new game \n");
            UART_LOG_PutString("==========================================\n");
        }*/
     
    }
    
    TerminateTask();
}

ISR2(isr_button_press)
{
    if(1 == Pin_Button_1_Read())
    {
        SetEvent(tsk_game,ev_button1);
    }
    if(1 == Pin_Button_2_Read())
    {
        SetEvent(tsk_game,ev_button2);
    }
}

/** 
 * \brief ISR when button3 or button4 are pressed which will call tsk_game and starts the game task
 * This even calls the scheduler and sets events when button3 or button4 are pressed
*/
ISR2(isr_start_game)
{    
    //seed for the random number generation
    random_seed = tick;
    srand(tick);

    
    //to start the game again
   if(1 == Pin_Button_3_Read() || 1 == Pin_Button_4_Read())
    {
        wait_time = 1000*(1+rand()%3);
        Timer_3secs_WritePeriod(wait_time);
        Timer_3secs_Start();
        //SetEvent(tsk_game,ev_button3);
    }
}

ISR1(isr_3secs)
{
   //To clear the timer interupt flag
    Timer_3secs_ReadStatusRegister(); 
    Timer_3secs_Stop();
    //Will initialise Timer again to 3 secs
    Timer_3secs_WriteCounter(Timer_3secs_ReadPeriod());
    SetEvent(tsk_game,ev_ReStartButton);
}

/* [] END OF FILE */