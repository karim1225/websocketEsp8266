#include "lcd.h"
#include "icon/skull.h"
#include "icon/target.h"
#include "icon/vest.h"
#include "icon/headband.h"
#include "icon/heart.h"
#include "icon/bullet.h"
#include "icon/cup.h"

void Lcd::init() {
  tft.init();                    
  tft.setRotation(1);             
  tft.fillScreen(TFT_BLACK);
  drawAmmo(10,30);
  drawHelth(100);
  drawTimer(0,0);
  drawGunId(3,TFT_RED);
  drawSkull(0);
  drawTarget(0);
  drawBatteryIcon(100);
  drawVest(false);
  drawHeadBand(false);
  drawHeart();
  drawBullet();
  drawCoin(0);
}

void Lcd::drawLoadingCircle(int x, int y, int radius, int angle, uint16_t color, int thickness) {
  tft.fillCircle(x, y, radius + thickness, TFT_BLACK);

  // رسم پس‌زمینه دایره
  for (int t = 0; t < thickness; t++) {
    tft.drawCircle(x, y, radius - t, TFT_WHITE);  // رسم دایره با ضخامت مشخص شده
  }

  // رسم قسمت لودینگ (مثلا 120 درجه از دایره) به صورت چرخشی
  int loadingAngle = 120;  // زاویه لودینگ
  for (int i = angle; i < angle + loadingAngle; i++) {
    int x1 = x + (radius - thickness / 2) * cos(radians(i));
    int y1 = y + (radius - thickness / 2) * sin(radians(i));

    for (int t = 0; t < thickness; t++) {
      int x2 = x + (radius - t) * cos(radians(i));
      int y2 = y + (radius - t) * sin(radians(i));
      tft.drawPixel(x2, y2, color);  // رسم پیکسل‌های قسمت لودینگ
    }
  }
}

void Lcd::drawAmmo(int magazines,int ammo) {
  int barHeight = 10;                          
  int maxBars = 10;                           
  int numBars = map(ammo, 0, 30, 0, maxBars); 

  int barWidth = 30;                           
  int x = 240 - barWidth;                      
  int yBase = 240 - 50;                        
  int numberY = yBase - (maxBars * (barHeight + 2)) - 5; 

 
  for (int i = 0; i < maxBars; i++) {
    int y = yBase - (i * (barHeight + 2));   
    uint16_t color;
    if (i == 0) {
      color = TFT_RED;      
    } else if (i == 1 || i == 2) {
      color = TFT_YELLOW;    
    } else {
      color = TFT_GREEN;     
    }

  
    if (i < numBars) {
      tft.fillRoundRect(x, y, barWidth, barHeight, 5, color); 
    } else {
      tft.fillRoundRect(x, y, barWidth, barHeight, 5, TFT_DARKGREY); 
    }
  }
   char buffer[2];  
   sprintf(buffer, "%02d", magazines);
   tft.setTextColor(TFT_BLACK);  
   tft.drawString("00",x,numberY - 5,4); 
   tft.setTextColor(TFT_WHITE);  
   tft.drawString(buffer,x,numberY - 5,4); 
                   
}
void Lcd::drawHelth(int helth) {
  int barHeight = 10;                          
  int maxBars = 10;                           
  int numBars = map(helth, 0, 100, 0, maxBars); 

  int barWidth = 30;                           
  int x =0;                      
  int yBase = 240 - 50;                        
  int numberY = yBase - (maxBars * (barHeight + 2)) - 5; 

 
  for (int i = 0; i < maxBars; i++) {
    int y = yBase - (i * (barHeight + 2));   
    
   
    uint16_t color;
    if (i == 0) {
      color = TFT_RED;      
    } else if (i == 1 || i == 2) {
      color = TFT_YELLOW;    
    } else {
      color = TFT_GREEN;     
    }

  
    if (i < numBars) {
      tft.fillRoundRect(x, y, barWidth, barHeight, 5, color); 
    } else {
      tft.fillRoundRect(x, y, barWidth, barHeight, 5, TFT_DARKGREY); 
    }
  }

   tft.setTextColor(TFT_BLACK);
   tft.drawNumber(100,x,numberY - 5,4); 
   tft.setTextColor(TFT_WHITE);  
   tft.drawNumber(helth,x,numberY - 5,4); 
                   
}
void Lcd::drawGunId(int id,uint16_t color) {
  int rectX = 75; 
  int rectY = 85; 
  int rectWidth = 90;
  int rectHeight = 52;

  tft.fillRoundRect(rectX, rectY, rectWidth, rectHeight,5, color);

  if(color == TFT_YELLOW){
    tft.setTextColor(TFT_BLACK); 
  }else{
    tft.setTextColor(TFT_WHITE); 
  }
  char buffer[2];  
  sprintf(buffer, "%02d", id);
  tft.drawString(buffer,90,87,7);
}
void Lcd::drawTimer(int minutes, int seconds) {
    char currentTimeStr[6]; 
    sprintf(currentTimeStr, "%02d:%02d", minutes, seconds);

    tft.setTextColor(TFT_BLACK);  
    tft.drawString(previousTimeStr, 50, 30, 7);  

    tft.setTextColor(TFT_WHITE);  
    tft.drawString(currentTimeStr, 50, 30, 7); 
    Serial.println(currentTimeStr);

    strcpy(previousTimeStr, currentTimeStr);  
}
void Lcd::drawSkull(int num){
  tft.setTextColor(TFT_RED);
  char buffer[3];  
  sprintf(buffer, "%02d", num);
  tft.drawString(buffer,35,200,6);
   tft.setTextColor(TFT_WHITE);
  tft.drawBitmap(0, 240 - 32, skull, 32, 32, TFT_RED);

}
void Lcd::drawTarget(int num){
  int x = 208;
  int y = 200;
  int width = 30;
  int height = 15;
  tft.setTextColor(TFT_BLUE);
  char buffer[3];  
  sprintf(buffer, "%02d", num);
  tft.drawString(buffer,x - 60,200,6);
  tft.setTextColor(TFT_WHITE);
  tft.drawBitmap(x, x, target, 32, 32, TFT_BLUE);
}
void Lcd::drawBatteryIcon(int percentage) {
  int x = 210;
  int y = 0;
  int width = 30;
  int height = 15;
  uint16_t bgColor = TFT_BLACK;

  tft.fillRect(x, y, width, height, TFT_WHITE); 
  int capWidth = width / 10;
  tft.fillRect(x - capWidth, y + (height / 3.5), capWidth, height / 2, TFT_WHITE);
  tft.fillRect(x + 2, y + 2, width - 4, height - 4, bgColor); 
  int filledWidth = (width - 4) * percentage / 100;

  uint16_t fillColor = TFT_GREEN;
  if (percentage <= 15) {
    fillColor = TFT_RED;  
  }else if (percentage > 10 && percentage <= 40) {
    fillColor = TFT_YELLOW;  
  }else {
    fillColor = TFT_GREEN;  
  }

  // رسم بخش پر شده از راست به چپ
  tft.fillRect(x + width - 2 - filledWidth, y + 2, filledWidth, height - 4, fillColor);  // پر کردن از سمت راست
}

void Lcd::drawStatusBar(){
  int lineWidth = tft.width();  // عرض کل صفحه نمایش برای رسم خط افقی
  tft.drawLine(0, 15 + 10, lineWidth, 15 + 10, TFT_CYAN);  // رسم خط
}
void Lcd::drawVest(bool enable){
    uint16_t color;
    if (!enable){
      color = 0x39C4;
    }else{
      color = TFT_WHITE;
    }
   tft.drawBitmap(0, 0, vest, 16, 16, color);
}
void Lcd::drawHeadBand(bool enable){
    uint16_t color;
    if (!enable){
      color = 0x39C4;
    }else{
      color = TFT_WHITE;
    }
   tft.drawBitmap(21, 0, headband, 16, 16, color);
}
void Lcd::drawHeart(){
  tft.drawBitmap(0,25, heart, 32, 32, TFT_RED);
}
void Lcd::drawBullet(){
  tft.drawBitmap(208,25, bullet, 32, 32, TFT_GREEN);
}
void Lcd::drawCoin(int coin) {
  this->clearNum( 55, 142, 7); 
  char buffer[5];  
  sprintf(buffer, "%04d", coin);  
  tft.setTextColor(TFT_WHITE);
  tft.drawString(buffer, 55, 142, 7); 
  tft.drawBitmap(100,208, cup, 32, 32, TFT_WHITE);
}
void Lcd::clearNum(int x,int y,int font){
  char buffer1[5];  
  sprintf(buffer1, "%04d", 8888);  
  tft.setTextColor(TFT_BLACK);
  tft.drawString(buffer1, x, y, font); 
  //  tft.fillRect(x, y, 80, tft.fontHeight(font), TFT_BLACK);  
}
// void timerTask(void *pvParameters) {
//     Lcd *lcd = (Lcd*)pvParameters;
//     while (true) {
//         lcd->drawTimer();  // فراخوانی تابع تایمر
//         if (lcd->isCountdownFinished()) {
//             Serial.println("Timer finished, stopping task!");
//             lcd->stopTimer();
//             break; 
//         }
//         vTaskDelay(1000 / portTICK_PERIOD_MS);  // تاخیر 1 ثانیه‌ای
//     }
// }

// void Lcd::startTimerTask(int time) {
//       countdownTime = time;  
     
//      if (timerTaskHandle == NULL) {
//         BaseType_t result = xTaskCreatePinnedToCore(timerTask, "TimerTask", 4096, this, 1, &timerTaskHandle,1);
//         if (result != pdPASS) {
//             Serial.println("Failed to create timer task!");
//         }
//      }else{
//         vTaskDelete(timerTaskHandle);  
//         timerTaskHandle = NULL; 
//         this->startTimerTask(time);
//      }
// }
// void Lcd::stopTimer() {
//     countdownTime = 0;
//     if (timerTaskHandle != NULL) {
//         vTaskDelete(timerTaskHandle);  
//         timerTaskHandle = NULL; 
//     }
// }