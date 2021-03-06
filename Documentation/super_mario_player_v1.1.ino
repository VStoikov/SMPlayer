/*
************************************************************
* Authors: 44 group, TU-Sofia                              *
* Year: 2015                                               *
* Version: 1.1                                             *
* Software: Arduino 1.6.3                                  *
* Hardware: Arduino pro mini                               *
* Used sources: 1.http://www.arduino.cc/en/Reference/Tone  *
* 2.http://www.arduino.cc/en/Tutorial/Pushbutton           *
* 3.http://www.arduino.cc/en/Tutorial/Melody               *
* 4.http://www.arduino.cc/en/Tutorial/Button               *
*                                                          *
************************************************************
*/
int speakerPin = 6;
int  buttonPin = 7;  // play/pause button
int  buttonPin2 = 8;  //stop button
int  buttonPin1 = 9; //restart button
int ledPin = 5; //red       
int ledPin1 = 4; //green

int length = 295; // the number of notes
char notes[] = "EE E CE G  g  C  g e  a b ia gEGA FG E CDb C  g e  a b ia gEGA FG E CDb  GNFR E uaC aCD GNFR E 1 11   GNFR E uaC aCD L  D C   CC C CD EC ag  CC C CDE  CC C CD EC ag  EE E CE G  g  C  g e  a b ia gEGA FG E CDb C  g e  a b ia gEGA FG E CDb EC g u aF Fa  bAAAGFEC ag  EC g u aF Fa  bF FFEDCe ec  "; // a space represents a rest
float beats[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, //Page 1
                2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 4, //Page 2
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, //Page4
                1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, //Page 5
                1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1.3, 1.3, 1.3, 1, 1, 1, 1, 1, 1, 2 }; //Page 6
                
int tempo = 130;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int buttonState1 = 0;
int buttonState2 = 0;
int lastButtonState = 0;     // previous state of the button
int i;
int control = 0;

void playTone(int tone1, int duration)
{
    //read the pushbutton input pin
    buttonState = digitalRead(buttonPin);
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);

    // compare the buttonState to its previous state
    if (buttonState != lastButtonState)
    {
        // if the state has changed, increment the counter
        if (buttonState == HIGH)
        {
            // if the current state is HIGH then the button
            // wend from off to on:
            buttonPushCounter++;
            Serial.println("Play");
            control = 0;
            digitalWrite(ledPin1, HIGH);
            digitalWrite(ledPin, LOW);
        }
        else
        {
            // if the current state is LOW then the button
            // wend from on to off:
            Serial.println("Pause");
            control = 0;
            digitalWrite(ledPin, HIGH);
            digitalWrite(ledPin1, LOW);
        }
    }
    if (buttonState1 == HIGH)
    {
        i = 0;
        Serial.println("Restart!");
        //delay (100);
        control = 0;
    }
    if (buttonState2 == HIGH)
    {

        Serial.println("Stop!");
        //delay (100);
        control = 1;
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPin1, LOW);
    }


    // save the current state as the last state,
    //for next time through the loop
    lastButtonState = buttonState;
    if (buttonPushCounter %2 == 0 && control == 0)
    {
        for (long i = 0; i < duration * 1000L; i += tone1)
        {
            tone(speakerPin, tone1);
            delayMicroseconds(tone1);
        }
        noTone(speakerPin);
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin, LOW);
    }
    else
    {
        digitalWrite(ledPin, HIGH);
        digitalWrite(ledPin1, LOW);
    }
}

void playNote(char note, int duration)
{
 //                        c    c#   d    d#   e    f    f#   g    g#   a    a#   b
  char names[] = { ' ',  '!', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G', 'A', 'B', 'i', 'N', 'R', 'u',  '1', 'L', 'k'}; // [i = b flat] [N = G flat] [R = D#] [u = g#] [1 = C oct. 5] [L = E flat]
  int tones[] =  {   0, 1046, 138, 146, 155, 164, 174, 184, 195, 207, 220, 233, 246, 261, 293, 329, 349, 391, 440, 493, 523, 587, 659, 698, 783, 880, 987, 466, 740, 622, 415, 1046, 622u, 227};
  
    // play the tone corresponding to the note name
    for (int i = 0; i < 34; i++)
    {
        if (names[i] == note)
        {
            playTone(tones[i], duration);
        }
    }
}

void setup()
{
    pinMode(speakerPin, OUTPUT);
    // initialize the button pin as a input:
    pinMode(buttonPin, INPUT);
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);
    // initialize the LED as an output:
    pinMode(ledPin, OUTPUT);
    pinMode(ledPin1, OUTPUT);
    // initialize serial communication:
    Serial.begin(9600);
}

void loop()
{

// buttonState1 = digitalRead(buttonPin1);
    for (i = 0; i < length; i++)
    {
        if (notes[i] == ' ')
        {
            delay(beats[i] * tempo); // rest
        }
        else
        {
            playNote(notes[i], beats[i] * tempo);
        }

        // pause between notes
        delay(tempo / 2);
    }

}

