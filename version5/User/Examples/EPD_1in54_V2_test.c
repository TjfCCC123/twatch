/*****************************************************************************
* | File      	:		main_interface.c
* | Author      :   Waveshare team
* | Function    :   1.54inch e-paper test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2019-06-11
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_Test.h"
#include "EPD_1in54_V2.h"
int testFlag = 0;
int main_interface(PAINT_TIME paintTime)
{
	int i= 2;
	printf("main_interface Demo\r\n");
	DEV_Module_Init();

	printf("e-Paper Init and Clear...\r\n");
	EPD_1IN54_V2_Init();
	EPD_1IN54_V2_Clear();
	DEV_Delay_ms(500);

	//Create a new image cache
	UBYTE *Image1;
	/* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
	UWORD Imagesize = ((EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1)) * EPD_1IN54_V2_HEIGHT;
	if((Image1 = (UBYTE *)malloc(Imagesize)) == NULL) 
	{
		printf("Failed to apply for black memory...\r\n");
		return -1;
	}
	printf("Paint_NewImage\r\n");
	Paint_NewImage(Image1, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, 270, WHITE);
	EPD_1IN54_V2_DisplayPartBaseImage(Image1);

	// enter partial mode
	EPD_1IN54_V2_Init_Partial();
	printf("Partial refresh\r\n");
	Paint_SelectImage(Image1);
	for (;;) 
	{
		paintTime.Sec = paintTime.Sec + 1;
		if (paintTime.Sec == 60) 
		{
			paintTime.Min = paintTime.Min + 1;
			paintTime.Sec = 0;
			if (paintTime.Min == 60) 
			{
				paintTime.Hour =  paintTime.Hour + 1;
				paintTime.Min = 0;
				if (paintTime.Hour == 24) 
				{
					paintTime.Hour = 0;
          paintTime.Min = 0;
          paintTime.Sec = 0;
					if(i == 6)	//到周六
					{
						i = 0;//切换到周日
					}
					else
					{
						++i;//非周六直接++
					}
        }
      }
    }
    Paint_ClearWindows(0, 0, 200, 200, WHITE);
		//T-WATCH
		Paint_DrawString_EN(45, 0, "T-WATCH",&Font24, WHITE, BLACK);
		//HOUR:MIN
		Paint_DrawTime1(20, 24, &paintTime, &Fontt, WHITE, BLACK);
		//SEC
		Paint_DrawTime2(50, 88, &paintTime, &Font24, WHITE, BLACK);
		//WEEK
		Paint_DrawString_EN(110, 88, paintTime.week[i],&Font24, WHITE, BLACK);
		//data
		Paint_DrawTime3(15, 112, &paintTime, &Font24, WHITE, BLACK);
		if(testFlag == 1)
		{
			Paint_ClearWindows(0, 0, 200, 200, WHITE);
		}

    EPD_1IN54_V2_DisplayPart(Image1);
		//Analog clock 1s
    DEV_Delay_ms(300);
	}


//  printf("Clear...\r\n");
//  EPD_1IN54_V2_Init();
//  EPD_1IN54_V2_Clear();

//  printf("Goto Sleep...\r\n");
//  EPD_1IN54_V2_Sleep();
//  free(BlackImage);
//  BlackImage = NULL;

//  // close 5V
//  printf("close 5V, Module enters 0 power consumption ...\r\n");
//  DEV_Module_Exit();
	return 0;
}

int ScreenInit()
{
	DEV_Module_Init();
  EPD_1IN54_V2_Init();
  EPD_1IN54_V2_Clear();
  DEV_Delay_ms(500);
}

void Debug_test(const char *string)
{
//  DEV_Module_Init();
//  EPD_1IN54_V2_Init();
//  EPD_1IN54_V2_Clear();
//  DEV_Delay_ms(500);
	
  UBYTE *Image2;
	
  UWORD Imagesize = ((EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1)) * EPD_1IN54_V2_HEIGHT;
  if((Image2 = (UBYTE *)malloc(Imagesize)) == NULL) {
		printf("Failed to apply for black memory...\r\n");
  }
  printf("Paint_NewImage\r\n");
  Paint_NewImage(Image2, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, 270, WHITE);
	
	EPD_1IN54_V2_DisplayPartBaseImage(Image2);
  // enter partial mode
	EPD_1IN54_V2_Init_Partial();
  printf("Partial refresh\r\n");
  Paint_SelectImage(Image2);
	Paint_ClearWindows(0, 0, 200, 200, WHITE);
	Paint_DrawString_EN(45, 0, string,&Font24, WHITE, BLACK);
	EPD_1IN54_V2_DisplayPart(Image2);
  DEV_Delay_ms(200);
}

/******************************************************************************
function :	show the function selection
parameter:
******************************************************************************/
int function_select_interface()
{
//	DEV_Module_Init();
//  EPD_1IN54_V2_Init();
//  EPD_1IN54_V2_Clear();
//  DEV_Delay_ms(500);
  UBYTE *Image3;
  UWORD Imagesize = ((EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1)) * EPD_1IN54_V2_HEIGHT;
  if((Image3 = (UBYTE *)malloc(Imagesize)) == NULL) 
	{
		//Failed to apply for black memory
		return 0;
  }
  //Paint_NewImage
  Paint_NewImage(Image3, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, 270, WHITE);
	EPD_1IN54_V2_DisplayPartBaseImage(Image3);
  // enter partial mode
	EPD_1IN54_V2_Init_Partial();
  //Partial refresh
  Paint_SelectImage(Image3);
	Paint_ClearWindows(0, 0, 200, 200, WHITE);
	/*******************************************
	                      *
	         Time         *       fresh
	       Setting        *       white
	                      *
	                      *
	                      *
	                      *
	********************************************
	                      *
	                      *
	                      *
	                      *
	                      *
	                      *
	                      *
	******************************************/
	Paint_DrawBitMap(gImage_Function_select1);
	//Time Setting
	Paint_DrawString_EN(20, 20, "TIME",&Font24, WHITE, BLACK);
	Paint_DrawString_EN(20, 48, "SETT",&Font24, WHITE, BLACK);
	Paint_DrawString_EN(20, 72, "-ING",&Font24, WHITE, BLACK);
	//fresh white
	Paint_DrawString_EN(115, 20, "WHITE",&Font12, WHITE, BLACK);
	Paint_DrawString_EN(115, 40, "WASHED",&Font12, WHITE, BLACK);
	//TEST
	Paint_DrawString_EN(20, 115, "TEST",&Font24, WHITE, BLACK);
	Paint_DrawString_EN(115, 115, "TEST",&Font24, WHITE, BLACK);
	//Choose
	Paint_DrawLine(14,14,92,14,BLACK,DOT_PIXEL_2X2,LINE_STYLE_DOTTED);
	Paint_DrawLine(92,14,92,92,BLACK,DOT_PIXEL_2X2,LINE_STYLE_DOTTED);
	Paint_DrawLine(92,92,14,92,BLACK,DOT_PIXEL_2X2,LINE_STYLE_DOTTED);
	Paint_DrawLine(14,92,14,14,BLACK,DOT_PIXEL_2X2,LINE_STYLE_DOTTED);
	
	EPD_1IN54_V2_DisplayPart(Image3);
  DEV_Delay_ms(300);
}

int white_washed()
{
//	DEV_Module_Init();
//  EPD_1IN54_V2_Init();
//  EPD_1IN54_V2_Clear();
//  DEV_Delay_ms(500);
	
  UBYTE *Image4;
	
  UWORD Imagesize = ((EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1)) * EPD_1IN54_V2_HEIGHT;
  if((Image4 = (UBYTE *)malloc(Imagesize)) == NULL) 
	{
		printf("Failed to apply for black memory...\r\n");
		return 0;
  }
  printf("Paint_NewImage\r\n");
  Paint_NewImage(Image4, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, 270, WHITE);
	
	EPD_1IN54_V2_DisplayPartBaseImage(Image4);
  // enter partial mode
	EPD_1IN54_V2_Init_Partial();
  printf("Partial refresh\r\n");
  Paint_SelectImage(Image4);
	// white washed
	Paint_ClearWindows(0, 0, 200, 200, WHITE);
	EPD_1IN54_V2_DisplayPart(Image4);
  DEV_Delay_ms(200);
	return 1;
}
