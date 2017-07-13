#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

const int irReceiverPin = 2;  // attach the ir receiver to pin 2
const int lightPin = 7;   // attach your light/led to pin 7
const int lightPin1 = 8;
int pirSensor = A0;  // attach the pirsensor (motion sensor) to an analog pin
int pirSensor1 = A1;
long currentState = 0;

IRrecv irrecv(irReceiverPin); // creates an IR rev object
decode_results decodedSignal;  // stores results from ir detector

int sensorValue = 0; //intializing and declaring the variable to  hold the value obtained from the pir
int sensorValue1 = 0;

void setup ()
{
   Serial.begin(9600);
   pinMode(lightPin,OUTPUT);
   pinMode(lightPin1,HIGH);
   irrecv.enableIRIn();    // start receiver object

}

boolean lightState = false;  // keep track if light is on

void loop ()
{
  checkSignal ();  // function that checks if a signal is sent to the ir receiver andc also checks the status of the pir sensor
  currentState = decodedSignal.value; // the value read is stored to a variable called currentState
  Serial.println(currentState,OCT);  // the value is converted to an octal number you can use any number system of your choice
  delay(300);

  if(currentState == 349819628 || sensorValue > 400)  // checks if the sent value is the correct one
 {
  lightState = !lightState;
  switchOn(); // if condition is satisfied it puts on the  ligt
 }
 else
 {
   lightState;
  switchOff(); // if condition is not satisfied the light remains off
 }

 if(currentState == 377777777 || sensorValue1 > 400)  // checks if the sent value is the correct one
{
 lightState = !lightState;
 switchOn(); // if condition is satisfied it puts on the  ligt
}
else
{
  lightState;
 switchOff(); // if condition is not satisfied the light remains off
}


}

void switchOn ()    // function for putting on the lights
{

  digitalWrite(lightPin,HIGH);
}

void switchOff () //function for putting off the lights
{
  digitalWrite(lightPin,LOW);
}

void checkSignal () // function that takes the readings from the receiver and the pir sensor
{
  while (irrecv.decode(&decodedSignal)==true) // true if message has beeen received
 // delay(100);
  {
    irrecv.resume(); // watch out for another message
  }

  sensorValue = analogRead(pirSensor);
  sensorValue1 = analogRead(pirSensor1);

}

