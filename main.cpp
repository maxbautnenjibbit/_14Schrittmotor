/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "LCD.h"

lcd mylcd;

void initTimer() {
    RCC -> APB1ENR |= 0b10000;
    TIM6 -> PSC = 31999;
    TIM6 -> ARR = 1000;
    TIM6 -> CNT = 0;
    TIM6 -> SR = 0;
    TIM6 -> CR1 = 1;
}


int mainA() {
    initTimer();

    mylcd.clear();
    mylcd.cursorpos(0);

    int second = 0;

    while (true) {
        if (second >= 60) {
            second = 0;
        }

        if (TIM6 -> SR == 1) {
            TIM6 -> SR = 0;
            second++;
        }

        mylcd.printf("%02d", second);
        mylcd.cursorpos(0);
    }
}

int mainB() {
    initTimer();

    int minutes = 0;
    int seconds = 0;
    
    mylcd.clear();
    mylcd.cursorpos(0);

    while (true) {
        if (TIM6 -> SR == 1) {
            TIM6 -> SR = 0;
            seconds++;
        }

        if (seconds >= 60) {
            seconds = 0;
            minutes++;

            if (minutes >= 60) {
                minutes = 0;
            }
        }

        mylcd.printf("%02d:%02d", minutes, seconds);
        mylcd.cursorpos(0);
    }
}

int mainC() {
    initTimer();

    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    
    mylcd.clear();
    mylcd.cursorpos(0);

    while (true) {
        if (TIM6 -> SR == 1) {
            TIM6 -> SR = 0;
            seconds++;
        }

        if (seconds >= 60) {
            seconds = 0;
            minutes++;

            if (minutes >= 60) {
                minutes = 0;
                hours++;

                if (hours >= 24) {
                    hours = 0;
                }
            }
        }

        mylcd.printf("%02d:%02d:%02d", hours, minutes, seconds);
        mylcd.cursorpos(0);
    }
}

int main() {
    //mainA();
    //mainB();
    mainC();
}