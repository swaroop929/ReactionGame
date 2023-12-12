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

#include"project.h"
#include "seven.h"
#include <stdio.h>
#include<stdlib.h>

static int tick = 0; 
static int scores[10] = {};
static int game_round = 1;
static int random_seed;
static int correct_button_press = 0;
static int wait_time;

void game_logic(uint32 randomValue, EventMaskType ev);
