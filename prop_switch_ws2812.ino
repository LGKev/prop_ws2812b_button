/*
	a short demo to show how we want a button to react. 
	Plan: push button off camera, for each press change color of the ws2812 led. 
			note: the switch on camera doesn't function as a switch, only functions to show general shape
				and more importantly how the led changes color. 
*/

#define LED 				13
#define SWITCH_INPUT		3	

#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN			5
#define PIXEL_COUNT			1
#define NUMBER_OF_COLORS	4

Adafruit_NeoPixel BUTTON_LED = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

volatile int color_index = 0;
volatile int debounce_count =0; //used this as a cheap counter to debounce switch.
void setup() {
  // put your setup code here, to run once:
  pinMode(SWITCH_INPUT, INPUT);
  pinMode(LED, OUTPUT);
  
  //INIT the led in the button head
  BUTTON_LED.begin();
  BUTTON_LED.show(); // initialize off state.
  Serial.begin(9600);
  Serial.println("I'm alive!");
  
}

// Variables will change:
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void loop() {

int reading = digitalRead(SWITCH_INPUT);
  // put your main code here, to run repeatedly:
  
  Serial.print("color index:  ");
  Serial.println(color_index);
  
  	 if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        //cycle colors here
		show(color_index);
		color_index++;
		if(color_index > NUMBER_OF_COLORS)color_index = 0;
      }
    }
  }




  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
	


void show(int color_index){
	switch(color_index){
		
		case 1 :
		BUTTON_LED.setPixelColor(0, BUTTON_LED.Color(255,0,0)); //set the color, remember indexed at 0.
		BUTTON_LED.show(); //display the color
		break;
		
		case 2 :
		BUTTON_LED.setPixelColor(0, BUTTON_LED.Color(0,255,0)); //set the color, remember indexed at 0.
		BUTTON_LED.show(); //display the color
		break;
		
		case 3:
		BUTTON_LED.setPixelColor(0, BUTTON_LED.Color(0,0,255)); //set the color, remember indexed at 0.
		BUTTON_LED.show(); //display the color
		break;
		
		case 4:
		BUTTON_LED.setPixelColor(0, BUTTON_LED.Color(155,0,155)); //set the color, remember indexed at 0.
		BUTTON_LED.show(); //display the color
		break;
		
		default:
		BUTTON_LED.setPixelColor(0, BUTTON_LED.Color(0,0,0)); //set the color, remember indexed at 0.
		BUTTON_LED.show(); //display the color
		color_index = 0; //should force loop around..
		Serial.println("******************");
		break;
	}
		
		
}