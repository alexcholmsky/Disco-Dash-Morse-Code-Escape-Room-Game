// ECE 198: Group 150

// Written by Sairah Amuthan and Alex Cholmsky, November 2021

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions
#include <time.h>
#include "ece198.h"

//displays a pattern (array of 1s and 0s) using an LED
void patterndisplay(int pattern[], unsigned int capacity, uint16_t pin);
void patterndisplay(int pattern[], unsigned int capacity, uint16_t pin){

   
        for(int i=0; i < capacity; ++i){
                HAL_GPIO_WritePin(GPIOA, pin, pattern[i]);
                HAL_Delay(1200); 
            }

} 

//celebratory light display
void randomDisplay(uint16_t pin1,uint16_t pin2,uint16_t pin3,uint16_t pin4,uint16_t pin5,uint16_t pin6){
    int pattern1[] = {0,1,0,1,1,0,1,0,1,1,0,1,0,0,1,0,1,1,0};
    int pattern2[] = {1,0,1,0,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0};
    int pattern3[] = {0,1,0,1,1,0,1,0,1,1,0,0,0,0,1,0,1,1,0};
    int pattern4[] = {1,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,1,0};
    int pattern5[] = {1,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,0};
    int pattern6[] = {0,1,1,0,0,1,1,1,0,1,0,1,0,0,1,1,0,1,0};
    unsigned int capacity = 19;

    for(int i=0; i < capacity; ++i){
        HAL_GPIO_WritePin(GPIOA, pin1, pattern1[i]);
        HAL_GPIO_WritePin(GPIOA, pin2, pattern2[i]);
        HAL_GPIO_WritePin(GPIOA, pin3, pattern3[i]);
        HAL_GPIO_WritePin(GPIOA, pin4, pattern4[i]);
        HAL_GPIO_WritePin(GPIOA, pin5, pattern5[i]);
        HAL_GPIO_WritePin(GPIOA, pin6, pattern6[i]);
        
        HAL_Delay(100); 
    }



}

//randomizes the order and frequency of the patterns, and update the answer key to match 
void randomize(int **colour_order, unsigned int num_colours, int **colour_possibilites, int *answer, int *blue, int *red, int *green, int *yellow);
void randomize(int **colour_order, unsigned int num_colours, int **colour_possibilites, int *answer, int *blue, int *red, int *green, int *yellow) {

    //randomize order of colours 
    for(unsigned int i = 0; i < num_colours; i++){

        int index = rand(); 
        colour_order[i] = colour_possibilites[index%4]; 
        
        //updates answer key to match
        if(colour_order[i] == blue){
            answer[i] = 2;             
    

        } else if (colour_order[i] == green){
            answer[i] = 3;


        } else if (colour_order[i] == red){
            answer[i] = 4;
     
        }  else{
            answer[i] = 5;

        }
        HAL_Delay(100);



    }

};


int main(void){

    HAL_Init(); // initialize the Hardware Abstraction Layer

    // // // Peripherals (including GPIOs) are disabled by default to save power, so we
    // // // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // intitialization

    InitializePin(GPIOB, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);// green button;
    InitializePin(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);//red LED
    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);//green LED
    InitializePin(GPIOB, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);//blue button
    InitializePin(GPIOB, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);//yellow button
    InitializePin(GPIOB, GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);//red button
    InitializePin(GPIOB, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);//black button

    InitializePin(GPIOA, GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); 
        
    /*LEGEND
            - blue : [2]
            - green : [3]
            - red : [4]
            - yellow : [5]
            - black : [6]
    */

    // // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // // is required, since there's one on the board)

    // // set up for serial communication to the host computer
    // // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);

    // // as mentioned above, only one of the following code sections will be used
    // // (depending on which of the #define statements at the top of this file has been uncommented)

    //patterns 
        int blue[12] = {1,0,1,1,1,0,1,1,1,0,1,0};
        int red[12] =  {1,1,1,0,1,1,1,0,1,0,1,0};
        int yellow[12] = {1,0,1,0,1,0,1,1,1,0,1,0};
        int green[12] = {1,1,1,0,1,1,1,0,1,1,1,0};

        unsigned int num_colours = 6; 
        int *colour_possibilites[4] = {green, yellow, blue, red}; 
        int *colour_order[6] = {blue, blue, blue, blue, blue, blue};
        int correctPattern[6] = {};

        /*LEGEND
            - blue : [2]
            - green : [3]
            - red : [4]
            - yellow : [5]
            - black : [6]
        */


        bool GAME_CONTINUE = true;
        while(GAME_CONTINUE) {
        
        
        bool toggle = false;
        int userPattern[6] = {0};
        int counter = 0;

        //lengths
        unsigned int scapacity = 12; 

        
    //randomize

    while (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0));
    srand(HAL_GetTick());
    randomize(colour_order, num_colours, colour_possibilites, correctPattern, blue, red, green, yellow);
    HAL_Delay(100);


    //displaying patterns
        while(true){

                patterndisplay(colour_order[0], scapacity, GPIO_PIN_10);

                patterndisplay(colour_order[1], scapacity, GPIO_PIN_6);

                patterndisplay(colour_order[2], scapacity, GPIO_PIN_9);

                patterndisplay(colour_order[3], scapacity, GPIO_PIN_0);

                patterndisplay(colour_order[4], scapacity, GPIO_PIN_1);

                patterndisplay(colour_order[5], scapacity, GPIO_PIN_4);

                break;
            
        }

        //taking in user input
        while(true){

            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)){
                if(!toggle){
                    userPattern[counter] = 3;
                    toggle = true;
                    counter++;

                }
            }

            else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)){
                if(!toggle){
                    userPattern[counter] = 2;
                    toggle = true;
                    counter++;

                }
            }

            else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10)){
                if(!toggle){
                    userPattern[counter] = 4;
                    toggle = true;
                    counter++;

                }
            }

            else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8)){
                if(!toggle){
                    userPattern[counter] = 5;
                    toggle = true;
                    counter++;

                }
            }

            else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)){
                break;
            }
            else {
                toggle = false;
            }

        }
            //evaluating user input

            bool isCorrect = false;
            bool correctSize = false;

             
            for (int i = 0; i < 6; i++) {
                if(userPattern[i]>0){
                    correctSize = true;
                }else{
                    correctSize = false;
                }

                if(userPattern[i] == correctPattern[i]){
                    isCorrect = true;

                }else{
                    isCorrect = false;
                }
            } 

             //if user guessed right
            if(isCorrect && correctSize){
                HAL_Delay(500);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);
                HAL_Delay(500);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);

                randomDisplay(GPIO_PIN_10,GPIO_PIN_6,GPIO_PIN_9,GPIO_PIN_0,GPIO_PIN_4,GPIO_PIN_1);

            }else{
                HAL_Delay(1000);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true);
                HAL_Delay(500);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);

                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true);
                HAL_Delay(100);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true);
                HAL_Delay(100);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, true);
                HAL_Delay(100);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, true);
                HAL_Delay(100);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, true);
                HAL_Delay(100);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, true);
                HAL_Delay(1000);

                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, false);
                HAL_Delay(100);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, false);
                HAL_Delay(100);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, false);
                HAL_Delay(100);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, false);
                HAL_Delay(100);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, false);
                HAL_Delay(100);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);

            }

             //resets the game
            while(true) {
                if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)){
                    break;
                }
            }
            continue;
        }

    return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}
