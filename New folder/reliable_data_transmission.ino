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
