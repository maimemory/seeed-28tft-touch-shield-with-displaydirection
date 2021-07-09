/*  draw text's APP
    Tft.setDisplayDirect(direction);
      - direction : LEFT2RIGHT
                  : RIGHT2LEFT
                  : DOWN2UP
                  : UP2DOWN
                  
    drawChar(INT8U ascii,INT16U poX, INT16U poY,INT16U size, INT16U fgcolor);
    drawString(char *string,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);
*/

#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>


void setup()
{
    TFT_BL_ON;      // turn on the background light
    Tft.TFTinit();  // init TFT library
      
    Tft.setDisplayDirect(LEFT2RIGHT);
    Tft.drawString("UP",20,20,4,RED);
  
    Tft.setDisplayDirect(RIGHT2LEFT);
    Tft.drawString("DOWN",220,220,4,GREEN);
    
    Tft.setDisplayDirect(DOWN2UP);
    Tft.drawString("LEFT",20,220,4,BLUE);
  
    Tft.setDisplayDirect(UP2DOWN);
    Tft.drawString("RIGHT",220,20,4,WHITE);
   
}

void loop()
{
  
}
