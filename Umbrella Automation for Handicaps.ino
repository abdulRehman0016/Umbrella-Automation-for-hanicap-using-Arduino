
#include <Stepper.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int Rain_Dpin = 4;
const int Rain_Apin= A0;

int const LDR_Dpin=   7;
int const LDR_Apin = A1;


float Celcius=0;
int LDR_Dvalue;
int LDR_Avalue;
int Rain_analogeValue;

int stepsPerRevolution = 2038;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
   pinMode(LDR_Dpin, INPUT);
   pinMode(LDR_Apin, INPUT);
   pinMode(Rain_Dpin, INPUT);
   pinMode(Rain_Apin, INPUT);
   sensors.begin();
  // set the speed at 60 rpm:
   myStepper.setSpeed(10);
  
 
  Serial.begin(9600);
  
}

void loop() {
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  LDR_Avalue=analogRead(LDR_Apin);
  Rain_analogeValue=analogRead(Rain_Apin);

  Serial.print("Analog value of weather: ");
  Serial.println( Rain_analogeValue);
   Serial.println("");
  

  Serial.print("Analog value of LDR: ");
  Serial.println(LDR_Avalue); 
  Serial.println("");

  Serial.print(" Temperature in Celcius: ");
  Serial.println(Celcius);
  Serial.println("");
  delay(1000);
  
  int motorcheck=0;
  if(Rain_analogeValue <  500 || LDR_Avalue <= 80 || Celcius >= 35) 
  {
    Serial.println("Umbrella is opening"); 
    myStepper.step(-stepsPerRevolution);
    int motorcheck=1;
    exit; 
    
    
  } 
  else if(motorcheck==1)
  {
    if (Rain_analogeValue >  500 && LDR_Avalue >= 350   && Celcius < 35) 
 { 
    Serial.println("Umbrella is closing");
    myStepper.step(stepsPerRevolution);
    exit; 
  }
    }
  
 

}
