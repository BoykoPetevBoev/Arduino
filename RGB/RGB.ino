#include <LiquidCrystal_I2C.h>

#include <IRremote.h>

int pinR = A0;
int pinG = A1;
int pinB = A2;
int pinSignal = A3;

IRrecv irrecv(pinSignal);
decode_results results;

long codes[6]= {
	0xFD28D7,	//4
	0xFD18E7,	//7
	0xFDA857,	//5
	0xFD9867,	//8
	0xFD6897,	//6
	0xFD58A7	//9
};
int valR = 0;
int valG = 0;
int valB = 0;

void setup(){
	Serial.begin(9600);
	irrecv.enableIRIn();

	pinMode(pinR, OUTPUT);
	pinMode(pinG, OUTPUT);
	pinMode(pinB, OUTPUT);

}

void loop(){
	if(irrecv.decode(&results)){

    Serial.print("Received IR Signal: ");
    Serial.println(results.value, HEX);

		if(results.value == codes[0] && valR < 255){
			valR++;
		}

		else if(results.value == codes[1] && valR > 0){
			valR--;
		}

		else if(results.value == codes[2] && valG < 255){
			valG++;
		}

		else if(results.value == codes[3] && valG > 0){
			valG--;
		}

		else if(results.value == codes[4] && valB < 255){
			valB++;
		}

		else if(results.value == codes[5] && valB > 0){
			valB--;
		}
		display(valR, valG, valB);
		Serial.print("Red: ");
		Serial.println(valR);
		Serial.print("Green: ");
		Serial.println(valG);
		Serial.print("Blue: ");
		Serial.println(valB);
		Serial.println("");
		irrecv.resume();
	}
}

void display(int red, int green, int blue){
	analogWrite(pinR, constrain(red, 0, 255));
	analogWrite(pinG, constrain(green, 0, 255));
	analogWrite(pinB, constrain(blue, 0, 255));
}