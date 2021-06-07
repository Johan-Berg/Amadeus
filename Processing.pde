import processing.serial.*;
import processing.sound.*;

SoundFile mySoundFile;
SoundFile negativFile;
Serial myPort; //porten som skal brukes
int theValue = 0;

void setup() {
 //tar inn to lydfiler
   myPort = new Serial(this, "/dev/tty.usbmodem1421", 9600);
   mySoundFile = new SoundFile(this, "Applaus.mp3");
   negativFile = new SoundFile(this,"336997__tim-kahn__boo-01.mp3");
}

void serialEvent (Serial myPort) {
   int sensorData = myPort.read(); //henter data fra lyssensoren
   theValue = sensorData;
 
}

void draw() {
   println(theValue); //testing
 
   if ((theValue ) == 250) {
      if(mySoundFile.isPlaying()== false){
         mySoundFile.play();
      } 
   }
      if ((theValue ) == 200) {
       if(negativFile.isPlaying()== false){
          negativFile.play();
        }    
      } 
   else if (theValue != 250 && theValue != 200) {
      if(mySoundFile.isPlaying()== true){
         mySoundFile.stop();
      }
   }
   
} 
