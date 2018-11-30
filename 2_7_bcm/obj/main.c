#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <time.h>
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "ImageData.h"
#include "EPD_2in7b.h"

    UBYTE *BlackImage, *RedImage;

void display_custom_pic(void)
{
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 110, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 70, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(70, 70, 20, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);      
    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawString_EN(10, 0, "Seeed", &Font16, BLACK, WHITE);    
    Paint_DrawString_CN(130, 20, "The IOT hardware enabler", &Font24CN, WHITE, BLACK);
    Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);
    
    //2.Draw red image
    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);
    Paint_DrawCircle(160, 95, 20, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(210, 95, 20, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawLine(85, 95, 125, 95, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(105, 75, 105, 115, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);  
    Paint_DrawString_CN(130, 0,"Seeed!", &Font12CN, BLACK, WHITE);
    Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
    
    printf("EPD_Display\r\n");
    EPD_Display(BlackImage, RedImage);
}


void  Handler(int signo)
{
    printf("\r\nHandler:Goto Sleep mode\r\n");
    EPD_Sleep();
    DEV_ModuleExit();

    free(BlackImage);
    BlackImage = NULL;
    free(RedImage);
    RedImage = NULL;
    exit(0);
}

int main(void)
{
    static int current_pic_num = 0;
    printf("2.7inch e-Paper B(C) demo\r\n");
    DEV_ModuleInit();

    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

    if(EPD_Init() != 0) {
        printf("e-Paper init failed\r\n");
    }
    // printf("clear...\r\n");
    // EPD_Clear();
    // DEV_Delay_ms(500);

    //Create a new image cache named IMAGE_BW and fill it with white

    UWORD Imagesize = ((EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1)) * EPD_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    if((RedImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for red memory...\r\n");
        exit(0);
    }
    Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 270, WHITE);
    Paint_NewImage(RedImage, EPD_WIDTH, EPD_HEIGHT, 270, WHITE);

    Paint_SelectImage(BlackImage);
    Paint_DrawBitMap(gImage_2in7b_b[current_pic_num]);
    Paint_SelectImage(RedImage);
    Paint_DrawBitMap(gImage_2in7b_r[current_pic_num]);
    EPD_Display(BlackImage, RedImage);
    printf("FLASH ELINK OK!!!\r\n");

    int button_stat = 0;
    while(1)
    {
        button_stat = block_for_button();
        switch(button_stat)
        {
            case 1:
            printf("KEY 1 PRESSED!!!\r\n");
            current_pic_num++;
            current_pic_num = current_pic_num > (IMAGE_QUANTITY) ? 0:current_pic_num;
            if(current_pic_num != IMAGE_QUANTITY)
            {
                Paint_SelectImage(BlackImage);
                Paint_DrawBitMap(gImage_2in7b_b[current_pic_num]);
                Paint_SelectImage(RedImage);
                Paint_DrawBitMap(gImage_2in7b_r[current_pic_num]);
                EPD_Display(BlackImage, RedImage);
                printf("FLASH ELINK OK!!!\r\n");
            }
            else
            {
                display_custom_pic();
                printf("FLASH ELINK OK!!!\r\n");
            }
            break;
            case 2:
            printf("KEY 2 PRESSED!!!\r\n");
            current_pic_num--;
            current_pic_num = current_pic_num < 0 ? (IMAGE_QUANTITY):current_pic_num;
            if(current_pic_num != IMAGE_QUANTITY)
            {
                Paint_SelectImage(BlackImage);
                Paint_DrawBitMap(gImage_2in7b_b[current_pic_num]);
                Paint_SelectImage(RedImage);
                Paint_DrawBitMap(gImage_2in7b_r[current_pic_num]);
                EPD_Display(BlackImage, RedImage);
                printf("FLASH ELINK OK!!!\r\n");
            }
            else
            {
                display_custom_pic();
                printf("FLASH ELINK OK!!!\r\n");
            }
            break;
        }
        
    }


#if 0   // Drawing on the image
    /*Horizontal screen*/
    //1.Draw black image
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 110, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 70, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(70, 70, 20, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);      
    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawString_EN(10, 0, "Seeed", &Font16, BLACK, WHITE);    
    Paint_DrawString_CN(130, 20, "The IOT hardware enabler", &Font24CN, WHITE, BLACK);
    Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);
    
    //2.Draw red image
    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);
    Paint_DrawCircle(160, 95, 20, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(210, 95, 20, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawLine(85, 95, 125, 95, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(105, 75, 105, 115, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);  
    Paint_DrawString_CN(130, 0,"Seeed!", &Font12CN, BLACK, WHITE);
    Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
    
    printf("EPD_Display\r\n");
    EPD_Display(BlackImage, RedImage);
    DEV_Delay_ms(2000);
#endif

#if 0
    printf("Goto Sleep mode...\r\n");
    EPD_Sleep();
    free(BlackImage);
    BlackImage = NULL;
    free(RedImage);
    RedImage = NULL;
#endif

    return 0;
}
