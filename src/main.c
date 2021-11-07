// Sample code for ECE 198

// Written by Bernie Roehl, August 2021

// This file contains code for a number of different examples.
// Each one is surrounded by an #ifdef ... #endif block inside of main().

// To run a particular example, you should remove the comment (//) in
// front of exactly ONE of the following lines:

#define BUTTON_BLINK
// #define LIGHT_SCHEDULER
// #define TIME_RAND
// #define KEYPAD
// #define KEYPAD_CONTROL
// #define SEVEN_SEGMENT
// #define KEYPAD_SEVEN_SEGMENT
// #define COLOR_LED
// #define ROTARY_ENCODER
// #define ANALOG
// #define PWM

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

void patterndisplay(int pattern[], unsigned int capacity, unsigned int pin);
void patterndisplay(int pattern[], unsigned int capacity, unsigned int pin){

    while(true){
   
        for(int i=0; i < capacity; ++i){
                HAL_GPIO_WritePin(GPIOA, pin, pattern[i]);
                HAL_Delay(500); 
            }
    }
}

int main(void)
{

    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // initialize the pins to be input, output, alternate function, etc...

    // InitializePin(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED

    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);

    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)
        
        unsigned int capacity = 26; 



        int blue[26] = {1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0};
        int red[26] = {1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0};
        int yellow[26] = {1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0};
        int green[26] = {1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0};
        InitializePin(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
        InitializePin(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);

        while(true){

       
        // patterndisplay(pattern1, capacity, GPIO_PIN_6);

        // patterndisplay(pattern2, capacity, GPIO_PIN_7);
   
        for(int i=0; i < capacity; ++i){
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, blue[i]);
                HAL_Delay(500); 
            }
        
        for(int i=0; i < capacity; ++i){
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, red[i]);
                HAL_Delay(500); 
            }

                        
        }

        //button press
        int power = 0; 
        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
        {
            power = 1; 
        }

        // patterndisplay(pattern1, capacity, GPIO_PIN_6);
        // patterndisplay(pattern2, capacity, GPIO_PIN_7);
        
        // while(true){
        //     for(int i = 0; i < 20; ++i){
        //         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, pattern1[i]);
        //         HAL_Delay(500); 
        //     }
        // }
        // int power = 0;
        // if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)){
        //     if(power == 1){
        //          power = 0;
        //      }
        //      else{
        //          power = 1;
        //      }
        // }
        // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, power);

    return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}
