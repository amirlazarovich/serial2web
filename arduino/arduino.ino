#define DEBUG

#define BAUD 9600L

#define PIN_MAIN_LED 13
#define PIN_LED 2
#define PIN_BTN_STOP 7
#define PIN_BTN_FORWARD 9
#define PIN_BTN_BACKWARD 5
#define PIN_BTN_LEFT 6
#define PIN_BTN_RIGHT 8
#define PIN_BTN_UP 3
#define PIN_BTN_DOWN 4

#define DELAY_AFTER_STOP 500
#define LED_FLASH_TIME 100

unsigned long ledOnTime;
char buffer[32];
int positionInBuffer;

void setup() {                
  Serial.begin(BAUD);
  pinMode(PIN_MAIN_LED, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BTN_STOP, INPUT);
  pinMode(PIN_BTN_FORWARD, INPUT);
  pinMode(PIN_BTN_BACKWARD, INPUT);
  pinMode(PIN_BTN_LEFT, INPUT);
  pinMode(PIN_BTN_RIGHT, INPUT);
  pinMode(PIN_BTN_UP, INPUT);
  pinMode(PIN_BTN_DOWN, INPUT); 
  
  // turn on the internal pull up resistors
  digitalWrite(PIN_BTN_STOP, HIGH);
  digitalWrite(PIN_BTN_FORWARD, HIGH);
  digitalWrite(PIN_BTN_BACKWARD, HIGH);
  digitalWrite(PIN_BTN_LEFT, HIGH);
  digitalWrite(PIN_BTN_RIGHT, HIGH);
  digitalWrite(PIN_BTN_UP, HIGH);
  digitalWrite(PIN_BTN_DOWN, HIGH);  
  
  // default values
  ledOnTime = 0;
  positionInBuffer = 0;
}


void loop() {
  if (ledOnTime != 0 && ledOnTime < millis()) {
    digitalWrite(PIN_LED, LOW);
    digitalWrite(PIN_MAIN_LED, LOW);
    ledOnTime = 0;
  }
  
  handleButton(PIN_BTN_UP);
  handleButton(PIN_BTN_DOWN);
  handleButton(PIN_BTN_LEFT);  
  handleButton(PIN_BTN_RIGHT);  
  handleButton(PIN_BTN_FORWARD);  
  handleButton(PIN_BTN_BACKWARD);
  handleButton(PIN_BTN_STOP);
  
  readSerial();
}

void onSerialRead(char *in) {
  int val = atoi(in);
  if (val == PIN_MAIN_LED || val == PIN_LED) {
    digitalWrite(val, HIGH);
    ledOnTime = millis() + LED_FLASH_TIME;
    // echo back
    Serial.print(in);
  }
}

void onButtonPressed(int btn) {  
  switch (btn) {
    case PIN_BTN_UP:  
      Serial.println("UP");
      break;
    
    case PIN_BTN_DOWN:
      Serial.println("DOWN");
      break;
      
    case PIN_BTN_LEFT:
      Serial.println("LEFT");
      break;
    
    case PIN_BTN_RIGHT:
      Serial.println("RIGHT");
      break;
      
    case PIN_BTN_FORWARD:
      Serial.println("FORWARD");
      break;
      
    case PIN_BTN_BACKWARD:
      Serial.println("BACKWARD");
      break;
      
    case PIN_BTN_STOP:
      Serial.println("STOP");
      break;
  }
  
  digitalWrite(PIN_LED, HIGH);
  ledOnTime = millis() + LED_FLASH_TIME;
}











void handleButton(int btn) {
  if (digitalRead(btn) == LOW) {
      onButtonPressed(btn);
  }
}

void readSerial() {
  if (Serial.available() > 0) {
    if (positionInBuffer == 0) {
      // workaround: ignore first char
      Serial.read(); 
      while (Serial.available() <= 0);
    }
    
    buffer[positionInBuffer] = (char) Serial.read();
    if (buffer[positionInBuffer] == '\n') {
      // done reading
      buffer[++positionInBuffer] = '\0';
      positionInBuffer = 0;
      onSerialRead(buffer);
    } else {
      // read until reached a "\n" character
      positionInBuffer++;
    }
  }
}
