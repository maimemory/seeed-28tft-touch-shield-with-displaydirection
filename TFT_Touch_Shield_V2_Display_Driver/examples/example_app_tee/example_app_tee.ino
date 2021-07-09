/* ******************* Example for Display ADC , Voltate , Virtual Switch by Thaieasyelec  ********************************* //
   CONNECT
      A5 -> ADC Module
      LED1 -> D8
      LED2 -> D9
      
****************************************** Enjoy for Programming ********************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <TFTv2.h>
#include <SPI.h>
#include <SeeedTouchScreen.h> 


#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // mega
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 54   // can be a digital pin, this is A0
#define XP 57   // can be a digital pin, this is A3 

#elif defined(__AVR_ATmega32U4__) // leonardo
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 18   // can be a digital pin, this is A0
#define XP 21   // can be a digital pin, this is A3 

#else //168, 328, something else
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 14   // can be a digital pin, this is A0
#define XP 17   // can be a digital pin, this is A3 

#endif

//Measured ADC values for (0,0) and (210-1,320-1)
//TS_MINX corresponds to ADC value when X = 0
//TS_MINY corresponds to ADC value when Y = 0
//TS_MAXX corresponds to ADC value when X = 240 -1
//TS_MAXY corresponds to ADC value when Y = 320 -1

#define TS_MINX 116*2
#define TS_MAXX 890*2
#define TS_MINY 83*2
#define TS_MAXY 913*2



// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// The 2.8" TFT Touch shield has 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM);

Point bt1,bt2 ;
int error = 25;

#define LED1 8
#define LED2 9
#define ADCPIN A5
void setup()
{  Serial.begin(9600);
    bt1.x = 180;
    bt1.y = 319-60;
    bt2.x = 180;
    bt2.y = 60;
    
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);
    
    TFT_BL_ON;                // turn on the background light
    Tft.TFTinit();            // init TFT library

    // create Header    
    Tft.setDisplayDirect(LEFT2RIGHT);
    Tft.fillRectangle(0,0, 90, 319, WHITE); // up bar
    
    Tft.fillRectangle(0,0, 30, 90, YELLOW); // right up coner
    
    
    
    Tft.fillCircle(bt1.x,bt1.y,40,GRAY1); // left circle
    Tft.fillCircle(bt1.x,bt1.y,30,YELLOW);   
    
    Tft.fillCircle(bt2.x,bt2.y,40,GRAY1);     // right circle
    Tft.fillCircle(bt2.x,bt2.y,30,YELLOW);  
   
    Tft.fillRectangle(220,108, 20, 100,CYAN ); // down center 
    
   
   // Tft.fillRectangle(180,50, 40, 80, WHITE); 
    
    Tft.setDisplayDirect(DOWN2UP);
    Tft.drawString(" ADC : ",20,319,2,BLUE);
    Tft.drawString("ExampleApp",15,85,1,BLACK);
    Tft.drawString(" Volt: ",50,319,3,DARK_GREEN);
    Tft.drawString("BT2",120,80,2,PINK);
    Tft.drawString("BT1",120,280,2,PINK);   
    Tft.drawString("ThaiEasyElec",229,205,1,BLACK);   
    // create Header

   
}
void sw_touch(int no){
  Tft.setDisplayDirect(LEFT2RIGHT);  
  switch(no){
    case 1:
          Tft.fillCircle(bt1.x,bt1.y,30,GRAY2);   // bt1 press
          digitalWrite(LED1,LOW);  
          
    break;
    
    case 2:
        Tft.fillCircle(bt2.x,bt2.y,30,GRAY2);     // bt2 press
        digitalWrite(LED2,LOW);
            
    break;
    
    case 3 :
      Tft.fillCircle(bt1.x,bt1.y,30,YELLOW);      // bt1 unpress
      digitalWrite(LED1,HIGH);
    break;
    
    case 4 :  
      Tft.fillCircle(bt2.x,bt2.y,30,YELLOW);      // bt2 unpress 
      digitalWrite(LED2,HIGH);
    break;
  }
    Tft.setDisplayDirect(DOWN2UP);  
}

void show_adc(){
  static int adc_now,adc_temp;
  static float volt_now,volt_temp;
  char sadc_now[5],sadc_temp[5],svolt_now[5],svolt_temp[5];
  
 // ******************* show ADC ************************ //  
  adc_now = analogRead(ADCPIN); 
  if (adc_now != adc_temp){
    sprintf(sadc_temp,"%04d",adc_temp);
    Tft.drawString(sadc_temp, 20,200,2,WHITE); 
    
    adc_temp = adc_now;
    sprintf(sadc_now,"%04d",adc_now);    
    Tft.drawString(sadc_now, 20,200,2,BLUE); 
    
    
  }else{
    sprintf(sadc_now,"%04d",adc_now);    
    Tft.drawString(sadc_now, 20,200,2,BLUE); 
   }
 
 // *************** show voltage  ************************ //
    volt_now = adc_now*(5.0/1023); 
    if (volt_temp != volt_now){
        dtostrf(volt_temp,1, 2, svolt_temp);        // convert float to string in 1.22 format
        Tft.drawString(svolt_temp, 50,150,3,WHITE); // delete old label
         
        volt_temp = volt_now;
        dtostrf(volt_now,1, 2, svolt_now);        // convert float to string in 1.22 format
        Tft.drawString(svolt_now, 50,150,3,DARK_GREEN); // delete old label            
    }else{
        dtostrf(volt_now,1, 2, svolt_now);        // convert float to string in 1.22 format
        Tft.drawString(svolt_now, 50,150,3,DARK_GREEN); // delete old label    
     }

}

void loop()
{
  Point p = ts.getPoint();

/*
  if (p.z > __PRESURE)  {
     Serial.print("Raw X = "); Serial.print(p.x);
     Serial.print("\tRaw Y = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z);
  } 
*/ 

  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > __PRESURE) {
    
      if ((( p.x >= bt1.x-error) && ( p.x <= bt1.x+error)) && (( p.y >= bt1.y-error) && ( p.y <= bt1.y+error))){
        // button 1 press
        sw_touch(1);
      }
 
      if ((( p.x >= bt2.x-error) && ( p.x <= bt2.x+error)) && (( p.y >= bt2.y-error) && ( p.y <= bt2.y+error))){
        // button 2 press
        sw_touch(2);
      }         
    
     //Serial.print("X = "); Serial.print(p.x);
     //Serial.print("\tY = "); Serial.print(p.y);
     //Serial.print("\tPressure = "); Serial.println(p.z);
      show_adc();
  }else {
    // unpress all switch
    sw_touch(3);  
    sw_touch(4);
    show_adc();
  }
}


