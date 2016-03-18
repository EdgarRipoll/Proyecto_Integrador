
int POWERKEY = 4;
int RI = 3;
int DTR = 2;
void setup()
{
  // Open serial communications to computer
  Serial.begin(115200);

  Serial1.begin(115200); // Default for the board
  Serial.println("AT+IPR=0");  // Set baud to auto connect
  delay(100); // Let the command run
  Serial1.begin(115200); // Reconnect at lower baud, 115200 had issues with SoftwareSerial
  pinMode(POWERKEY, OUTPUT);
  pinMode(DTR, OUTPUT);
  pinMode(RI, INPUT);
  digitalWrite(POWERKEY, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(DTR, LOW);    // turn the LED off by making the voltage LOW
  delay(3000);               // wait for a second
  digitalWrite(POWERKEY, LOW);    // turn the LED off by making the voltage LOW
  //Clear out any waiting serial dat
}

void loop()
{
  /*
   * This loop just takes whatever comes in from the console and sends it to the board
   */
  if (Serial.available())
  {
    Serial1.write(Serial.read());
  }
  if (Serial1.available())
  {
    Serial.write(Serial1.read());
  }
  
}
