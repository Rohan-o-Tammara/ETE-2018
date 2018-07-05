// Pins assigned to Echo and Trig pins of 2 utlrasounds - PWM pins
#define ECHO_1 
#define TRIG_1
#define ECHO_2
#define TRIG_2

// Pins assigned to vibration modules - Non PWM pins
#define VIB_1
#define VIB_2
#define VIB_3
#define VIB_4
#define UP_DELAY 500
#define DOWN_DELAY 200

// Safe distance
#define safeDistanceHigh 175
#define safeDistanceLow 100

float getDistance(int trigPin, int echoPin, int device);
void vibrate(int pin);
void vibrateClock();
void vibrateAnti();

void setup() {
  //Initialize Ultrasound pins
  pinMode(ECHO_1, INPUT);
  pinMode(TRIG_1, OUTPUT);
  pinMode(ECHO_2, INPUT);
  pinMode(TRIG_2, OUTPUT);

  // Iniitialize Vibration modules pins as out pins
  pinMode(VIB_1, OUTPUT);
  pinMode(VIB_2, OUTPUT);
  pinMode(VIB_3, OUTPUT);
  pinMode(VIB_4, OUTPUT);

  //Serial initialization
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float ultraDistanceOne = getDistance(TRIG_1, ECHO_1, 1);
  float ultraDistanceTwo = getDistance(TRIG_2, ECHO_2, 2);

  if (ultraDistanceOne <= safeDistanceLow || ultraDistanceTwo <= safeDistanceLow){
    Serial.println("Something is approaching nigga");
    if (ultraDistanceOne <= safeDistanceLow && ultraDistanceTwo <= safeDistanceLow){
      vibrateAll();
    } else if (ultraDistanceOne <= safeDistance) {
      vibrateClockOnce();
    } else {
      vibrateAntiOnce();
    }
  } else if(ultraDistanceOne >= safeDistanceHigh || ultraDistanceTwo >= safeDistanceHigh){ 
      if (ultraDistanceOne >= safeDistanceHigh && ultraDistanceTwo >= safeDistanceHigh){
      continue;
    } else if (ultraDistanceOne >= safeDistanceHigh) {
      vibrateClockTwice();
    } else {
      vibrateAntiTwice();
    }
   } else {
    Serial.println("Everything's fine and far nigga");
  }
}

float getDistance(int trigPin, int echoPin, int device) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= (float) (duration*0.034/2);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: Device ");
  Serial.print(device);
  Serial.print("   ");
  Serial.println(distance);
  return distance;
}

void vibrate(int pin, int up_delay, int down_delay){
  digitalWrite(pin, HIGH);
  delay(up_delay);
  digitalWrite(pin, LOW);
  delay(down_delay);
}

void vibrateClockOnce(){
  Serial.println("Clock start")
  vibrate(VIB_1, UP_DELAY, DOWN_DELAY);
  vibrate(VIB_2, UP_DELAY, DOWN_DELAY);
  vibrate(VIB_3, UP_DELAY, DOWN_DELAY);
  vibrate(VIB_4, UP_DELAY, DOWN_DELAY);
  Serial.println("Clock end")
}

void vibrateAntiOnce(){
  Serial.println("Anti start")
  vibrate(VIB_4, UP_DELAY, DOWN_DELAY);
  vibrate(VIB_3, UP_DELAY, DOWN_DELAY);
  vibrate(VIB_2, UP_DELAY, DOWN_DELAY);
  vibrate(VIB_1, UP_DELAY, DOWN_DELAY);
  Serial.println("Anti end")
}

void vibrateAll(){
  Serial.println("All start");
  vibrate(VIB_1, 0, 0);
  vibrate(VIB_2, 0, 0);
  vibrate(VIB_3, 0, 0);
  vibrate(VIB_4, 0, 0);
  Serial.println("All end");
}

void vibrateClockTwice(){
  vibrateClockOnce();
  vibrateClockOnce();
}

void vibrateAntiTwice(){
  vibrateAntiOnce();
  vibrateAntiOnce();
}


