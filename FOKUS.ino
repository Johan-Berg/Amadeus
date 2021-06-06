#include <LiquidCrystal.h>

 const int button = 3;
 const int grontLys = 4;
 const int rodtLys = 6;
 int timerMode = 1;
 long startTime; 
 int sensorValue = 0;
 int sensorValue2;
 int tid = 0;
 int nyTid = 0;
 int minutter = 0;
 int sekunder = 0;
 int timer = 0;
 int forskjell;
 int knappStatus = 0;
 boolean tidSatt = false;
 boolean kjoorerIkke = true;
 byte spillLyd;

 LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

 void setup(){
  pinMode(A5, INPUT);
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(button, INPUT);
  Serial.begin(9600);
  pinMode(grontLys, OUTPUT);
  pinMode(rodtLys, OUTPUT);
 }


void loop(){
  //Sjekker om lyset allerede er på, vil være det hvis timeren har blitt avbrutt. Spiller så av en negativ lyd med processing.
  if(digitalRead(rodtLys)==HIGH){
    spillLyd = 200;
    Serial.write(spillLyd);
    delay(1000);
  }
  //Tilbakestiller lysene og begynner å sjekke verdien til potentiometeret og knappen. BLir knappen trykket, så går den videre og begynner å sjekke verdien til lyssensoren. 
  digitalWrite(rodtLys, LOW);
  digitalWrite(grontLys, LOW);
  checkValue();
  knappStatus = digitalRead(button);
  delay(200);
  if(knappStatus == LOW){
    tidSatt = HIGH;
  }
  if(tidSatt == true){
    kjoorerIkke = true;
    countDown();
  }
 
 }
//Hele denne metoden er egentlig for å lese av verdien til et potentiometer. 
void checkValue(){
  //Her leser vi av verdien til lyssensoren
  sensorValue = analogRead(A5);
  //Serial.println(sensorValue);
  delay(5);
  lcd.clear();
  //Her lager vi flere if sjekker. Meningen med disse er at de tar inn en verdi fra et potentiometer. 
  //Denne verdien skal da avgjøre hvilken tid man skal stille tidtakeren til å begynne med. eks. 10, 20 eller 30 min. 
  if (sensorValue < 150){
    tid = 0;
    tekst(tid);
    delay(1000);
  }
  if (sensorValue < 300 && sensorValue > 150){
    tid = 10;
    tekst(tid);
    delay(1000);
  }
  if (sensorValue < 500 && sensorValue > 300){
    tid = 20;
    tekst(tid);
    delay(1000);
  }
  if (sensorValue < 650 && sensorValue > 500){
    tid = 30;
    tekst(tid);
    delay(1000);
  }
  if (sensorValue < 800 && sensorValue > 650){
    tid = 40;
    tekst(tid);
    delay(1000);
  }
  if (sensorValue < 950 && sensorValue > 800){
    tid = 50;
    tekst(tid);
    delay(1000);
  }
  if (sensorValue > 950){
    tid = 60;
    tekst(tid);
    delay(1000);
  }
  
  
 }
//En metode for å vise tiden som er blitt bestemt med potentiometeret på lcd skjermen. 
//SKriver også ut "Press to start" på lcd skjermen under den bestemte tiden. 
void tekst(int tid){
  lcd.setCursor(5, 0);
  lcd.print(tid);
  lcd.print(" Min");
  lcd.setCursor(1, 1);
  lcd.print("Press to start");
}

//Denne metoden er selve tidtakeren som blir vist på lcd skjermen.
void countDown(){
  //for at metoden skal starte å kjøre, så må knappen ha blitt trykket ned, og lyssensoren ha under en bestemt verdi. 
  if(kjoorerIkke && lysSensor() > 1000){
    digitalWrite(rodtLys, HIGH);
    digitalWrite(grontLys, LOW);
    //Fjerner alt som står på lcd skjermen, og setter inn "Time left:" på øvre linje, og gjenstående tid på nedre linje. 
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Time left:");
    startTime = millis();
    minutter = tid -1;
    sekunder = 59;
    tid = tid * 60;
    nyTid = tid;
    tidSatt = false;
    //Så lenge lyssensoren har under en bestemt verdi, så skal denne while løkka kjøre. Denne while løkka teller ned timeren. 
    while(lysSensor() > 1000){
      kjoorerIkke = false;
      lcd.setCursor(0, 1);    
      delay(400);
      if (timerMode == 1){
        lcd.setCursor(6, 1);
        //Serial.println(tid);
        
        timer = (tid - (millis() - startTime) / 1000.0);
        forskjell = nyTid - timer;
        //her sjekker vi om det har gått mer enn et sekund siden forrige gang løkka var innom her, hvis det, så skal timeren bli et sekund mindre. 
        if(forskjell >= 1){
          sekunder -= 1;
          nyTid -= 1;
        }
        //Hvis sekund telleren er blitt til 0, så skal minuttelleren gå ned med 1. 
        if(sekunder < 0){
          sekunder = 59;
          minutter -= 1;
        }
        //For at timeren ikke skal begynne på feil plass hvis det er igjen mindre enn 10 minutter, så legger vi inn en 0 foran tiden som skrives inn.
        if(minutter < 10){
          lcd.print(0);    
        }
        lcd.print(minutter);
        lcd.print(":");
        //For at timeren ikke skal begynne på feil plass hvis det er igjen mindre enn 10 sekunder, så legger vi inn en 0 foran tiden som skrives inn.
        if(sekunder < 10){
          lcd.print(0);
        }
        lcd.print(sekunder);

        //Hvis timeren har telt helt til null, så skal timeren avslutte, og det grønne lyset tennes. Spiller av positiv lyd gjennom proseccing. 
        if(minutter == 0 && sekunder == 0){
          tidSatt = false;
          digitalWrite(grontLys, HIGH);
          digitalWrite(rodtLys, LOW);
          spillLyd = 250;
          Serial.write(spillLyd);
          delay(4000);
          break;
        }
        
        if((tid-(millis() - startTime)) == 0){
          tidSatt = false;
          return;
        }
      }  
    } 
  }  
}

int lysSensor(){
  int sValue = analogRead(A1);
  sensorValue2 = map(sValue, 0, 255, 0, 255);
  delay(100);
  return sensorValue2;
}
