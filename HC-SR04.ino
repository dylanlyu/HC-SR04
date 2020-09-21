#include <Ultrasonic.h>
#define TRIG_PIN 5
#define ECHO_PIN 6
#define INPUT1 14
#define INPUT2 15
#define RXLED 17

int distance,runStopflat;
double runPumping,stopPumping,percent,ratio1,ratio2; 

Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);
void setup() {
  Serial.begin(115200);

  do{
    ratio1 = ultrasonic.read();
    delay(500);
    ratio2 = ultrasonic.read();
  }while(ratio1 == ratio2);

  percent = ratio2 / 100;
//  percent = 0.12;
  runPumping = percent * 30;
  stopPumping = percent * 100;
  pinMode(INPUT1,OUTPUT);
  pinMode(INPUT2,OUTPUT);
  pinMode(RXLED, OUTPUT);
  
  digitalWrite(INPUT1,LOW);
  digitalWrite(INPUT2,LOW);
  digitalWrite(RXLED,HIGH);
}

void loop() {
  distance = ultrasonic.read(); //不加參數就是輸出CM，可用read(INC)輸出英寸
  Serial.println(runPumping);
  Serial.println(stopPumping);
  if(distance <= runPumping || runStopflat == 1){
    digitalWrite(INPUT1,HIGH);
    digitalWrite(RXLED,LOW);
    Serial.println("RUN");
    runStopflat = 1;
  }

  if(distance >= stopPumping || runStopflat == 0 ){
    digitalWrite(INPUT1,LOW);
    digitalWrite(RXLED,HIGH);
    Serial.println("STOP");
    runStopflat = 0;
  }
  
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  delay(5000); //每次間格0.5秒
  digitalWrite(RXLED, LOW);
}
