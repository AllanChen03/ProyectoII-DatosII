#include <Keypad.h>

#include <AnalogKeypad.h>


const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns
char caracter = ' ';

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();

  if(Serial.available())
  {
    caracter = Serial.read();
  }

  if(caracter == '1')
  {
    for (int i = 0; i < 5; i++){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
    caracter = ' ';
  }
    
  if (key){
    Serial.println(key);
  }

  if (key == '*'){
    for (int i = 0; i < 10; i++){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
  }
}
