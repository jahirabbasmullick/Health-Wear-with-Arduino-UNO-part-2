


//first calibrate on powering up the module 
//a poscal function to calculate avg values of x , y , z and print them on serial
//turn on the LED on pin13 and turn it off after the calibration is completed


//in loop continually read the data and calculate total accerelation vector 
//call stepdetect function
//print total number of steps on monitor
//if step occurs flash led 3 times
 
#include <Arduino.h>
#include <math.h>
#include <Wire.h>

//#include "MAX30100.h"
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

//#include "RTClib.h"
#include <LiquidCrystal.h>
/* Create object named lcd of the class LiquidCrystal */
LiquidCrystal lcd(13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3);  /* For 8-bit mode */
//LiquidCrystal lcd(13, 12, 11, 6, 5, 4, 3);  /* For 4-bit mode */

//RTC_DS1307 rtc;

//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const int xpin=A2;
int ypin=A3;
int zpin=A4;
int x;
float threshhold=10.0;

float xval[100]={0};
float yval[100]={0};
float zval[100]={0};
float xavg;
  float yavg;
  float zavg;
 int value=0;
int tempPin = A1;
int mv = 0;
 int cel = 0;
int steps=0,flag=0;                                  
void setup()
            {
                    
                    Serial.begin(9600);
                   Wire.begin();

                   // if (! rtc.begin()) {
                   // Serial.println("Couldn't find RTC");
                   // while (1);
                    //  }

                     //if (! rtc.isrunning()) {
                     //Serial.println("RTC is NOT running!");
                     // following line sets the RTC to the date & time this sketch was compiled
                  //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
                     // This line sets the RTC with an explicit date & time, for example to set
                    // January 21, 2014 at 3am you would call:
                    //   rtc.adjust(DateTime(2018, 5, 1, 3, 0, 0));
                                           //  }
                     lcd.begin(16,2);  /* Initialize 16x2 LCD */
                       //lcd.clear();  /* Clear the LCD */
                       lcd.print("HealthWear"); /* Print data on display */
                      // lcd.setCursor(0,1);
                      //lcd.print("Temp.: 28 C");
                     //pulseOxymeter->printRegisters();
                    
                    pinMode(13,OUTPUT);
                    calibrate();
            }
void loop()
            {
                     value = analogRead(tempPin);
                     mv = ( value/1024.0)*5000; 
                     cel = mv/10;
                    float farh = (cel*9)/5 + 32;
                    Serial.println(cel);

                    int acc=0;
                    float totvect[100]={0};
                    float totave[100]={0};
 
                    float xaccl[100]={0};
                    float yaccl[100]={0};
                    float zaccl[100]={0};
                    //return;
                    //DateTime now = rtc.now();
                   
                    
    
                     //lcd.setCursor(0,0);  /* Set cursor to column 0 row 0 */
                    // lcd.write("HealthWear"); /* Print data on display */
                      
                    lcd.print(cel);
                    lcd.write("*C");
               
                     //lcd.print(now.hour(), DEC);
                     //lcd.print(':');
                     //lcd.print(now.minute(), DEC);
                     //lcd.print(':');
                    // lcd.print(now.second(), DEC);
     
                     //lcd.setCursor(1,0);  
                     //lcd.print("Date"); /* Print data on display */
  
                     //lcd.print(now.year(), DEC);
                     //lcd.print('/');
                     //lcd.print(now.month(), DEC);
                     //lcd.print('/');
                    // lcd.print(now.day(), DEC);
       
                      delay(100);
                      lcd.setCursor(11,1);  /* Set cursor to column 0 row 0 */
                                                    
                                                   // lcd.write("steps=");
                                                    //lcd.print(steps);
                                                    Serial.println(steps);                                                                                                              
                                                    delay(40);
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(steps);              // sends x 
  Wire.endTransmission();    // stop transmitting 
                     
                       //You have to call update with frequency at least 37Hz. But the closer you call it to 100Hz the better, the filter will work.
                      
  
                    for (int i=0;i<100;i++)
                                          { 
                                                  xaccl[i]=float(analogRead(xpin));
                                                  delay(1);

                                                  yaccl[i]=float(analogRead(ypin));
                                                  delay(1);

                                                  zaccl[i]=float(analogRead(zpin));
                                                  delay(1);

                                                  totvect[i] = sqrt(((xaccl[i]-xavg)* (xaccl[i]-xavg))+ ((yaccl[i] - yavg)*(yaccl[i] - yavg)) + ((zval[i] - zavg)*(zval[i] - zavg)));
                                                  totave[i] = (totvect[i] + totvect[i-1]) / 2 ;

                                                  //Serial.println(totave[i]);
                                                  delay(20);

                      //cal steps 
                                                  if (totave[i] > threshhold && flag == 0)
                                                                                        {
                                                                                              steps=steps+1;
                                                                                              flag=1;
 
                                                                                        }
                                                  else if (totave[i] > threshhold && flag == 1)
                                                                                        {
                                                                                               //do nothing 
                                                                                        }
                                                  if (totave[i] <threshhold  && flag == 1)
                                                                                        {
                                                                                              flag=0;
                                                                                        }
                                                    
                                            }
                     delay(50);
             }

 //detect pushups or count  for number of dumbles
 
 //crossing the threshold and 
 
 //cross 20 in down and 80 in up 
 
 /*add one to counter and set a flag high to indicate it is above a threshhold value 

if a flag is high and threshhold is crossed :do nothing }
if signal falls below threshhold set flag to -1 indicating it is blow threshhold


 */
//calculate total accerelation vector

void calibrate()

              {

                      digitalWrite(13,HIGH);
  
                      float sum=0;
                      float sum1=0;
                      float sum2=0;
                      for (int i=0;i<100;i++)
                                            {
                                                          xval[i]=float(analogRead(xpin));

                                                          sum=xval[i]+sum;
                                            }
                      delay(100);
                      xavg=sum/100.0;

                      //Serial.println(xavg);

                      for (int j=0;j<100;j++)
                                            {
                                                          yval[j]=float(analogRead(ypin));

                                                          sum1=yval[j]+sum1;
                                            }
                      yavg=sum1/100.0;

                      //Serial.println(yavg);
                      delay(100);
                      for (int i=0;i<100;i++)
                                            {
                                                          zval[i]=float(analogRead(zpin));

                                                          sum2=zval[i]+sum2;
                                            }
                      zavg=sum2/100.0;
                      delay(100);
                      //Serial.println(zavg);

                      digitalWrite(13,LOW);

            }
//counting the pushups

