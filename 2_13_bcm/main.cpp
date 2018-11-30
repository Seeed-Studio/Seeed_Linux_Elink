/**
 *  @filename   :   main.cpp
 *  @brief      :   2.13inch e-paper display (B) demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 15 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdlib.h>
#include <stdio.h>
#include "epd2in13b.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <signal.h>

#define COLORED      1
#define UNCOLORED    0

Epd epd;

void display_custom(void)
{
    unsigned char* frame_black = (unsigned char*)malloc(epd.width * epd.height / 8);
    unsigned char* frame_red = (unsigned char*)malloc(epd.width * epd.height / 8);

    Paint paint_black(frame_black, epd.width, epd.height);
    Paint paint_red(frame_red, epd.width, epd.height);
    paint_black.Clear(UNCOLORED);
    paint_red.Clear(UNCOLORED);

    paint_black.SetRotate(ROTATE_0);
    paint_red.SetRotate(ROTATE_0);
    paint_black.DrawRectangle(10, 60, 50, 100, COLORED);
    paint_black.DrawLine(10, 60, 50, 100, COLORED);
    paint_black.DrawLine(50, 60, 10, 100, COLORED);
    paint_black.DrawCircle(80, 80, 15, COLORED);
    paint_red.DrawFilledRectangle(10, 120, 50, 180, COLORED);
    paint_red.DrawFilledRectangle(0, 6, 128, 26, COLORED);
    paint_red.DrawFilledCircle(80, 150, 15, COLORED);

    paint_black.DrawStringAt(4, 30, "Seeedstudio!!", &Font12, COLORED);
    paint_red.DrawStringAt(6, 10, "Hello world!", &Font12, UNCOLORED);
   
    /* Display the frame_buffer */
    epd.DisplayFrame(frame_black, frame_red);
    free(frame_black);
    free(frame_red);
}


void  Handler(int signo)
{
    printf("\r\nHandler:Goto Sleep mode\r\n");
    epd.Sleep();

    exit(0);
}


int main(void)
{
    static int current_pic_num = 0;
    
    signal(SIGINT, Handler);

    if (epd.Init() != 0) {
        printf("e-Paper init failed\n");
        return -1;
    }
    epd.DisplayFrame(IMAGE_BLACK[current_pic_num],IMAGE_RED[current_pic_num]);
    printf("FLASH ELINK OK!!!\r\n");
    int button_stat = 0;
    while(1)
    {
        button_stat = epd.block_for_button();
        switch(button_stat)
        {
            case 1:
            printf("KEY 1 PRESSED!!!\r\n");
            current_pic_num++;
            current_pic_num = current_pic_num > (IMAGE_QUANTITY) ? 0:current_pic_num;
            if(current_pic_num != IMAGE_QUANTITY)
            {
                epd.DisplayFrame(IMAGE_BLACK[current_pic_num],IMAGE_RED[current_pic_num]);
                printf("FLASH ELINK OK!!!\r\n");
            }
            else
            {
                display_custom();
                printf("FLASH ELINK OK!!!\r\n");
            }
            break;

            case 2:
            printf("KEY 2 PRESSED!!!\r\n");
            current_pic_num--;
            current_pic_num = current_pic_num < 0 ? (IMAGE_QUANTITY):current_pic_num;
            if(current_pic_num != IMAGE_QUANTITY)
            {
                epd.DisplayFrame(IMAGE_BLACK[current_pic_num],IMAGE_RED[current_pic_num]);
                printf("FLASH ELINK OK!!!\r\n");
            }
            else
            {
                display_custom();
                printf("FLASH ELINK OK!!!\r\n");
            }
            break;
        }
        
    }
    epd.Sleep();
    return 0;
}

