    ckt 
    
 <img width="547" alt="ckt1" src="https://user-images.githubusercontent.com/73009807/148690928-7e630bba-105d-4f0f-b56b-0f4a76dbf248.png">



<img width="960" alt="ckt" src="https://user-images.githubusercontent.com/73009807/148690936-179da356-1016-410b-bbbb-2369a2b79642.png">

    
    
 youtube video for data transmission with interrupt
 
 https://youtu.be/HlHyMc9sRv4
 
  youtube video for data transmission without interrupt
  
  https://youtu.be/kNAvm81H24I
  
    
    data transmission program for arduino nano
    
    
                    # data-transmission


                      //include the lcd madule
                      #include<LiquidCrystal.h>

                      #define LCD_D4 4
                      #define LCD_D5 5
                      #define LCD_D6 6
                      #define LCD_D7 7
                      #define LCD_RS 8
                      #define LCD_EN 9
                      #define TX_CLOCK 2
                      // Transmit rate in bps
                      #define TX_RATE 5

                      //pin assignments
                      #define TX_DATA 3

                      const char *message = "Umesha, Ramesha";
                      void setup() {
                        pinMode(TX_CLOCK,OUTPUT);
                        pinMode(TX_DATA, OUTPUT);

                        //initialising the lcd
                        LiquidCrystal lcd(LCD_RS,LCD_EN,LCD_D4, LCD_D5, LCD_D6, LCD_D7);
                        lcd.begin(16, 2);
                        lcd.setCursor(0, 0);
                        lcd.print(message);

                        for (int byte_idx = 0; byte_idx < strlen(message); byte_idx++)
                        {
                          char tx_byte = message[byte_idx];

                          // clear the 2nd line of the display
                          lcd.noCursor();
                          lcd.setCursor(0, 1);
                          lcd.print("         ");
                          lcd.setCursor(byte_idx, 0);
                        lcd.cursor();

                          for (int bit_idx = 0; bit_idx < 8; bit_idx++)
                          {
                            bool tx_bit = tx_byte & (0x80 >> bit_idx);
                            digitalWrite(TX_DATA, tx_bit);
                            delay((1000 / TX_RATE)/2);

                            //update the lcd
                            lcd.noCursor();
                            lcd.setCursor(bit_idx, 1);
                            lcd.print(tx_bit ? "1" : "0");
                            lcd.setCursor(byte_idx, 0);
                            lcd.cursor();

                            //CLOCK
                            digitalWrite(TX_CLOCK,HIGH);
                            delay((1000 / TX_RATE)/2);
                            digitalWrite(TX_CLOCK,LOW);
                          }
                        }
                        digitalWrite(TX_DATA,LOW);
                      }

                      void loop() {

                      }
                      
                      
                      
   for reciver
   
                   #include<LiquidCrystal.h>

                //pin assignments
                #define RX_CLOCK 2
                #define RX_DATA 3

                #define LCD_D4 4
                #define LCD_D5 5
                #define LCD_D6 6
                #define LCD_D7 7
                #define LCD_RS 8
                #define LCD_EN 9



                char message[16];
                volatile byte rx_byte = 0;
                volatile int bit_position = 0;
                volatile bool update_lcd = true;
                LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
                void setup() {

                  pinMode(RX_DATA, INPUT);
                  strcpy(message, "");
                  lcd.begin(16, 2);
                  attachInterrupt(digitalPinToInterrupt(RX_CLOCK), onClockPulse, RISING);

                }
                void onClockPulse()
                {
                  bool rx_bit = digitalRead(RX_DATA);

                  if (bit_position == 8)
                  {
                    rx_byte = 0;
                    bit_position = 0;
                  }
                  if (rx_bit)
                  {
                    rx_byte |= (0x80 >> bit_position);
                  }
                  bit_position = bit_position + 1;
                  if (bit_position == 8)
                  {
                    strncat(message, &rx_byte, 1);
                  }
                  update_lcd = true;
                }


                void loop() {
                  if (update_lcd)
                  {
                    update_lcd = false;
                    lcd.noCursor();
                    lcd.setCursor(0, 0);
                    lcd.print(message);
                    lcd.setCursor(0, 1);
                    for (int i = 0; i < 8; i += 1)
                    {
                      if (i < bit_position)
                      {
                        lcd.print(rx_byte & (0x80 >> i) ? "1" : "0");
                      }
                      else
                      {
                        lcd.print(" ");
                      }
                    }
                    lcd.setCursor(strlen(message), 0);
                    lcd.cursor();
                  }

                }
