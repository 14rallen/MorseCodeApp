//define interval in ms, dot = 1 unit, dash = 3 units, wordBeat = 7 units
int dot = 200;            //time length of short beeps and space between parts of same character
int dash = dot * 3;       //time length of long beeps and between character
int wordBeat = dot * 7;   //time length between words

bool blinking = false;

//decimal values for 0, 9, A, Z, and Space
int dec0 = 48;
int dec9 = 57;
int decA = 65;
int decZ = 90;
int decSp = 32;
//range from A-Z decimal values to value of where A-Z is indexed in morseCode array
int indexToDecimalRange = 55;

//message to be converted to morse code
String message;

//the end result of original message, to be converted to dots, dashes, spaces, and word breaks
String morseMessage;

// String array that holds International Morse Code short/long conversions for 0-9 and A-Z
String morseCode[36];


void setup() {
  Serial.begin(9600);

  DefineMorseCode();

  morseMessage = "";

  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  delay(2000);
}

String incoming = ""; //full message to be stored here
char alphaNum; //temp value for reading incoming data
void loop() {
  //checks for incoming data
  while(Serial.available() > 0){
    alphaNum = Serial.read();
    //only allow alphanumeric values and spaces to be in message
    if(isAlpha(alphaNum) || isDigit(alphaNum) || alphaNum == ' '){
      incoming += alphaNum;
    }
  }
  message = incoming;
  incoming = "";
  //convert message and flash LED lights while there is a valid message and lights
  //are not already flashing
  while(message.length() > 0 && !blinking){
    convertMessageToMorse(message);
    morseToLED(morseMessage);
  }
}

void convertMessageToMorse(String m){
  m.toUpperCase();
  //convert each character to decimal value
  for(int i = 0; i < m.length(); i++){
    char c = m.charAt(i);
    byte b = (byte)c;
    byte index = 0;

    if(b == decSp){
      morseMessage[morseMessage.length() - 1] = '/'; //if character is a space, replace last "space" of morseMessage with forward slash to indicate new word
      continue;
    }
    else if(b >= dec0 && b <= dec9){  //match numeric 0-9 decimal value to morseCode index
      index = b - dec0;
    }
    else if(b >= decA && b <= decZ){  ////match A-Z decimal value to morseCode index
      index = b - indexToDecimalRange;
    }
    morseMessage += morseCode[index] + ' '; //add a space at end of converted message to indicate new characer
  }
}

//takes converted message and displays as flashing LED
void morseToLED(String m){
  Serial.println(m);
  blinking = true;
  for(int i = 0; i < m.length(); i++){
    if(m.charAt(i) == ' '){
      //Serial.println("letter break");
      delay(dash);
    }
    else if(m.charAt(i) == '.'){
      digitalWrite(13, HIGH);
      //Serial.println("dot");
      delay(dot);
      digitalWrite(13, LOW);
      delay(dot);
    }
    else if(m.charAt(i) == '-'){
      digitalWrite(13, HIGH);
      //Serial.println("dash");
      delay(dash);
      digitalWrite(13, LOW);
      delay(dot);
    }
    else if(m.charAt(i) == '/'){
      //Serial.println("word break");
      delay(wordBeat);
    }
  }
  blinking = false;
  message = "";
  morseMessage = "";
  Serial.flush();
  Serial.println("end LED blinking");
}

void DefineMorseCode(){
  //define morse code for numerical 0-9
  morseCode[0] = "-----";
  morseCode[1] = ".----";
  morseCode[2] = "..---";
  morseCode[3] = "...--";
  morseCode[4] = "....-";
  morseCode[5] = ".....";
  morseCode[6] = "-....";
  morseCode[7] = "--...";
  morseCode[8] = "---..";
  morseCode[9] = "----.";

  //define morse code for A-Z
  morseCode[10] = ".-";     /*A*/
  morseCode[11] = "-...";   /*B*/
  morseCode[12] = "-.-.";   /*C*/
  morseCode[13] = "-..";    /*D*/
  morseCode[14] = ".";      /*E*/
  morseCode[15] = "..-.";   /*F*/
  morseCode[16] = "--.";    /*G*/
  morseCode[17] = "....";   /*H*/
  morseCode[18] = "..";     /*I*/
  morseCode[19] = ".---";   /*J*/
  morseCode[20] = "-.-";    /*K*/
  morseCode[21] = ".-..";   /*L*/
  morseCode[22] = "--";     /*M*/
  morseCode[23] = "-.";     /*N*/
  morseCode[24] = "---";    /*O*/
  morseCode[25] = ".--.";   /*P*/
  morseCode[26] = "--.-";   /*Q*/
  morseCode[27] = ".-.";    /*R*/
  morseCode[28] = "...";    /*S*/
  morseCode[29] = "-";      /*T*/
  morseCode[30] = "..-";    /*U*/
  morseCode[31] = "...-";   /*V*/
  morseCode[32] = ".--";    /*W*/
  morseCode[33] = "-..-";   /*X*/
  morseCode[34] = "-.--";   /*Y*/
  morseCode[35] = "--..";   /*Z*/
}