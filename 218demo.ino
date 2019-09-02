#include <Servo.h>
#include <IRremote.h>
#include <FastLED.h>

#define NUM_LEDS 6
#define DATA_PIN 6
#define NUMRTTLSONGS 6
//#include "SoftwareSerial.h"
//#include "DFRobotDFPlayerMini.h"
//https://dragaosemchama.com/en/2019/02/songs-for-arduino/

#define REST 0
#define BENS_WAND 0x73371F01
#define OCTAVE_OFFSET -1
const int RECV_PIN = 7;
const int SERVO_PIN = 9;
const int SERVO_ZERO = 0;
const int DF_RX=10;
const int DF_TX=11;
const int POS_2 = 180;
const int MELODY_PIN=8;
const int tonePin = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;
Servo servo; 
CRGB leds[NUM_LEDS];
//SoftwareSerial mySoftwareSerial(DF_RX, DF_TX); // RX, TX
//DFRobotDFPlayerMini myDFPlayer;
int servo_pos = SERVO_ZERO;

int song=0;


#define isdigit(n) (n >= '0' && n <= '9')

//char *rttlsong = "GeorgeofthejungleTheme:d=4,o=6,b=127:f5,p,p,c5,p,p,f5,p,f5,p,f5,a5,p,c,p,f5,p,f5,p,g5,g5,p,a5,p,p,p,f5,f5,f5,f5,g5,g5,p,f5,p,p,p,f";
//char *rttlsong = "OneMoreT:d=16,o=5,b=125:4e,4e,4e,4e,4e,4e,8p,4d#.,4e,4e,4e,4e,4e,4e,8p,4d#.,4e,4e,4e,4e,4e,4e,8p,4d#.,4f#,4f#,4f#,4f#,4f#,4f#,8f#,4d#.,4e,4e,4e,4e,4e,4e,8p,4d#.,4e,4e,4e,4e,4e,4e,8p,4d#.,1f#,2f#";
//char *rttlsong = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
//char *rttlsong = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
//char *rttlsong = "TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5";
//char *rttlsong = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
//char *rttlsong = "Muppets:d=4,o=5,b=250:c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,8a,8p,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,8e,8p,8e,g,2p,c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,a,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,d,8d,c";
//char *rttlsong = "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";
//char *rttlsongng = "Looney:d=4,o=5,b=140:32p,c6,8f6,8e6,8d6,8c6,a.,8c6,8f6,8e6,8d6,8d#6,e.6,8e6,8e6,8c6,8d6,8c6,8e6,8c6,8d6,8a,8c6,8g,8a#,8a,8f";
//char *rttlsong = "20thCenFox:d=16,o=5,b=140:b,8p,b,b,2b,p,c6,32p,b,32p,c6,32p,b,32p,c6,32p,b,8p,b,b,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,g#,32p,a,32p,b,8p,b,b,2b,4p,8e,8g#,8b,1c#6,8f#,8a,8c#6,1e6,8a,8c#6,8e6,1e6,8b,8g#,8a,2b";
//char *rttlsong = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
//char *rttlsong5 = "MASH:d=8,o=5,b=140:4a,4g,f#,g,p,f#,p,g,p,f#,p,2e.,p,f#,e,4f#,e,f#,p,e,p,4d.,p,f#,4e,d,e,p,d,p,e,p,d,p,2c#.,p,d,c#,4d,c#,d,p,e,p,4f#,p,a,p,4b,a,b,p,a,p,b,p,2a.,4p,a,b,a,4b,a,b,p,2a.,a,4f#,a,b,p,d6,p,4e.6,d6,b,p,a,p,2b";
char *rttlsong0 = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
//char *rttlsong2 = "GoodBad:d=4,o=5,b=56:32p,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,d#,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,c#6,32a#,32d#6,32a#,32d#6,8a#.,16f#.,32f.,32d#.,c#,32a#,32d#6,32a#,32d#6,8a#.,16g#.,d#";
//char *rttlsong3 = "TopGun:d=4,o=4,b=31:32p,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,16f,d#,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,g#";
char *rttlsong4 = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
//char *rttlsong = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.,16a#6,32g6,16f6,16a#.,32f6,32f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,a#,16a6,16d.6,16a#6,32a6,32a6,32g6,32f#6,32a6,8g6,16g6,16c.6,32a6,32a6,32g6,32g6,32f6,32e6,32g6,8f6,16f6,16a#.,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#6,16c7,8a#.6";
//char *rttlsong = "Jeopardy:d=4,o=6,b=125:c,f,c,f5,c,f,2c,c,f,c,f,a.,8g,8f,8e,8d,8c#,c,f,c,f5,c,f,2c,f.,8d,c,a#5,a5,g5,f5,p,d#,g#,d#,g#5,d#,g#,2d#,d#,g#,d#,g#,c.7,8a#,8g#,8g,8f,8e,d#,g#,d#,g#5,d#,g#,2d#,g#.,8f,d#,c#,c,p,a#5,p,g#.5,d#,g#";
//char *rttlsong = "Gadget:d=16,o=5,b=50:32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,32d#,32f,32f#,32g#,a#,d#6,4d6,32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,8d#";
//char *rttlsong = "Smurfs:d=32,o=5,b=200:4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8f#,p,8a#,p,4g#,4p,g#,p,a#,p,b,p,c6,p,4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8b,p,8f,p,4f#";
//char *rttlsong = "MahnaMahna:d=16,o=6,b=125:c#,c.,b5,8a#.5,8f.,4g#,a#,g.,4d#,8p,c#,c.,b5,8a#.5,8f.,g#.,8a#.,4g,8p,c#,c.,b5,8a#.5,8f.,4g#,f,g.,8d#.,f,g.,8d#.,f,8g,8d#.,f,8g,d#,8c,a#5,8d#.,8d#.,4d#,8d#.";
//char *rttlsong = "LeisureSuit:d=16,o=6,b=56:f.5,f#.5,g.5,g#5,32a#5,f5,g#.5,a#.5,32f5,g#5,32a#5,g#5,8c#.,a#5,32c#,a5,a#.5,c#.,32a5,a#5,32c#,d#,8e,c#.,f.,f.,f.,f.,f,32e,d#,8d,a#.5,e,32f,e,32f,c#,d#.,c#";
//char *rttlsong = "DangerMo:d=4,o=5,b=355:a.,8g,a,8a,p,8a4,8p,d,p,a.,8g,a,8a,p,8a4,8p,d,p,a,a,a#,a#,a#,a#,a#,a#,a#,c6,2a,p,8a4,8p,d,p,a.,8g,a,8a,p,8a4,8p,d,p,a.,8g,a,8a,p,8a4,8p,d,p,a,a,a#,a#,a#,a#,a#,a#,a#,c6,2d6,p,8a4,8p,d,p,a.,8a,2a#.,8a#4,8p,d#,2p,a#,2a#,2f#,2d#,a#.,8a#,2b.,8b4,8p,e,2p,b,2b,2g,2e,b.,8d6,1e.6,e6,8e6,8e";
//char *rttlsong = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
char *rttlsong3 = "BlueDa-B:d=16,o=5,b=140:4a,4a#,8g,8a#,8c6,8f,8a,4a#,8g,8a#,8d6,4d#6,8d6,8c6,4a#,8g,8a#,8c6,8f,8a,4a#,8g,8a#,8d6,4d#6,8d6,8c6,4a#,8g,8a#,8c6,8f,8a,4a#,8g,8a#,8d6,4d#6,8d6,8c6,4a#,8g,8a#,8a,8f,8f,2g";
//char *rttlsong = "Sandstor:d=16,o=5,b=112:d6,d6,d6,d6,8d6,d6,d6,d6,d6,d6,d6,8d6,g6,g6,g6,g6,g6,g6,g6,g6,f6,f6,f6,f6,f6,f6,8f6,c6,c6,d6,d6,d6,d6,8d6,d6,d6,d6,d6,d6,d6,d6,d6,f6,f6,d6,d6,d6,d6,d6";
//char *rttlsong = "TheEcsta:d=4,o=6,b=100:c5,2g.5,a_5,2g.5,f5,2c.,d_,2c.,c5,2g.5,a_5,2g.5,f5,2c.,d_,2c.,c5,2g.5,a_5,2g.5,f5,2c.,d_,2c.,2c.";
//char *rttlsong = "RightHer:d=8,o=5,b=125:a,b,c6,b,d6,c6,b,a,g,a,b,a,c6,b,a,g,a,b,c6,b,d6,c6,b,a,g,a,b,a,c6,b,a,b,a,4p,a,e,4p,b,a,4p,a";
//char *rttlsong = "Airwolf1:d=16,o=6,b=100:4e5,a5,b5,d,4e,g,f#,d,4e,g,f#,d,4e,8d,f#,4b5,4a5,8g5,a5,8f#5,d5,4g5,c,d,f,4g,c,b,f,4g,c,b,f,4g,8f,a,4d,4c,8b5,d,8a5,f5,4g5";
//char *rttlsong = "Airwolf2:d=4,o=5,b=100:8a#,16p,16d#6,16f6,16g#6,8a#6,16p,16c#7,16c7,16g#6,8a#6,16p,16c#7,16c7,16g#6,8a#6,16p,8g#6,16c7,8f6,16p,8d#6,16p,8c#6,16d#6,8c6,16g#,8a#,16p,16d#6,16f6,16g#6,8a#6,16p,16c#7,16c7,16g#6,8a#6,16p,16c#7,16c7,16g#6,8a#6,16p,8g#6,16c7,8f6,16p,8d#6,16p,8c#6,16d#6,8c6,16g#,8c#6,16p,16f#6,16g#6,16b6,8c#7,16p,16f#7,16f7,16b6,8c#7,16p,16f#7,16f7,16b6,8c#7,16p,8b6,16d#7,8g#6,16p,8f#6,16p,8f6,16f#6,8d#6,16b,8c#6,16p,16f#6,16g#6,16b6,8c#7,16p,16f#7,16f7,16b6,8c#7,16p,16f#7,16f7,16b6,8c#7,16p,16b6,16a#7,16f#7,g#7";
//char *rttlsong = "Avengers:d=16,o=6,b=70:c#,c#,a#,g#,b,a#,32a#,32g#,f,c#,c#,a#,g#,b,a#,32a#,32g#,d#.,c.,c#.,d#.,c,8c#,8d#,4f,f#.,d#,f.,f#.,d#,8f,8f#,4g#.,a.,f#,g#.,a.,f#,8g#,8a,2g#.,c#5,c#5.,8g5.,2g#5.,g#5,c#.,4g5,2g#.";
//char *rttlsong = "Hawaii50:d=4,o=6,b=80:16a5,16a5,16c,16e.,8d.,a5,16a5,16a5,16g5,16c.,a.5,16a5,16a5,16c,16e.,8d.,a,16g,16g,16e,16c.,2a,16c7,16a#,16a,16g,16f,16e,16d,16e,16c,d,8d,16a#,16g#,16g,16e,16d,16c,16d,16e.,16d,16c.,8d,a,16g,16g,16e,16c.,2d";
//char *rttlsong = "PinkPant:d=4,o=5,b=160:8d#,8e,2p,8f#,8g,2p,8d#,8e,16p,8f#,8g,16p,8c6,8b,16p,8d#,8e,16p,8b,2a#,2p,16a,16g,16e,16d,2e";
char *rttlsong2 = "rickastley:d=4,o=5,b=120:16c,16d,16f,16d,16a.,16p,32p,8a,16p,g.,16c,16d,16f,16d,16g.,16p,32p,8g,16p,8f.,16e,8d,16c,16d,16f,16d,f,8g,8e.,16d,8c,8c4,8c,8g,8p,2f,16c,16d,16f,16d,16a.,16p,32p,8a,16p,g.,16c,16d,16f,16d,c6,8e,8f.,16e,8d,16c,16d,16f,16d,f,8g,8e.,16d,8c,8c4,8c,8g,8p,2f";
//char *rttlsong = "Whenever:d=4,o=6,b=180:e5,8e.5,16e.5,16e.5,16e.5,g.5,a.5,e5,8e.5,16e.5,16e.5,16e.5,g.5,f_.5,e5,8e.5,16e.5,16e.5,16e.5,g.5,a.5,e5,8e.5,16e.5,16e.5,16e.5,g.5,f_.5";
//char *rttlsong = "BridgeOv:d=4,o=6,b=70:8f_5,8e5,8d5,e5,8p,a5,16a5,8f_5,8e5,16d5,8d5,16e5,f_5,8p,8a5,8f_,8e,d,e,e,8f_,8e,d,8c_,8b5,8b5,8a5,8f_5,8a5,8p,16b5,16d,8e,8f_,d";
//char *rttlsong = "AllStar:d=4,o=5,b=40:16g.,32d.6,32b.,16b.,32a.,32g.,32g.,16c.6,32b.,32b.,32a.,32a.,16g.,32g.,32d.6,32b.,32b.,32a.,32a.,32g.,32g.,16e.,d,32g.,32g.,32d.6,32b.,32b.,32a.,32a.,32g.,32g.,16c.6,32b.,32b.,32a.,32a.,32g.,32g.,16d.6,32b.,32b.,16a.,32g.,32g.,16a.,8e";
//char *rttlsong5 = "Overworl:d=16,o=6,b=100:32p,e,e,p,e,p,c,e,p,g,8p.,g5,8p.,c,8p,g5,8p,e5,8p,a5,p,b5,p,a#5,a5,p,g5,e,g,a,p,f,g,p,e,p,c,d,b5,4p,g,f#,f,d#,p,e,p,g#5,a5,c,p,a5,c,d,8p,8d#,p,d,8p,8c";
char *rttlsong5 = "DeathMus:d=16,o=5,b=70:b,f6,p,f6,f6,f.6,e.6,d6,c6,g,p,e,c";
//char *rttlsong = "AxelF:d=16,o=5,b=100:4g6,8a#.6,g6,p,g6,8c7,8g6,8f6,4g6,8d.7,g6,p,g6,8d#7,8d7,8a#6,8g6,8d7,8g7,g6,f6,p,f6,8d6,8a6,2g6";
//char *rttlsong = "DonkeyKo:d=4,o=5,b=140:32p,8a#,8p,8d6,16p,16f.6,16g.6,16f.6,8a#,8p,8d6,16p,16f.6,16g.6,16f.6,8a#,8p,8d6,16p,16f.6,16g.6,16f.6,8a#,8p,8d6,16p,16f.6,16g.6,16f.6";
//char *rttlsong = "Fame:d=16,o=5,b=125:2c7,8a6,8a6,8a6,8a6,4a6,8a6,4a6,8g6,4g6,2p,8g6,8g6,8g6,4g6,8f6,8g6,8a6,4a6,2c7,4p,8a6,8a6,8a6,4a6,8b6,8a6,4a6,8g6,4g6,8g6,8g6,8g6,4g6,8f6,8g6,2f6,2p";
//char *rttlsong = "Simpsons:d=16,o=5,b=160:4c6,4e6,4f#6,8a6,4g.6,4e6,4c6,8a,8f#,8f#,8f#,2g,4p,8f#,8f#,8f#,8g,4a#,8c6,8c6,8c6,4c6";
//char *rttlsong = "Transfor:d=32,o=6,b=45:p,f5,16a#5,c,4c#,16a#5,c,16c#,f#5,4f#5,a#5,c,16c#,16c#,16d#,16f,f#,16d#,c#,16d#,f,16c#,c,16c#,d#,16c.,a#5,a5,c,a#5,8a#5";
//char *rttlsong = "Contra:d=4,o=5,b=225:a#,a#,c#6,a#,e.6,d#.6,c#6,a#,a#,c#6,a#,e.6,d#.6,c#6,a#,a#,c#6,a#,e.6,d#.6,a#,a#,c#6,a#,d#.6,e.6,f6,c6,c6,d#6,c6,f#.6,f6,d#6,c6,c6,d#6,c6,f#.6,f.6,d#6,c6,c6,d#6,c6,f#.6,f.6,d#6,c6";
//char *rttlsong = "BrownEye:b=140,o=5,d=8:g,a,16p,b,16p,a,g,16p,c6,d6,16p,e6,16p,d6,c6,16p,g,a,16p,b,16p,a,g,16p,4a,16p,f#.,g,a,16p,g,a,16p,b,16p,a,g,16p,c6,d6,16p,e6,16p,d6,c6,16p,g,a,16p,b,16p,a,g,16p,4a,16p,f#.,g,a.,4g.";
//char *rttlsong = "RideOfTh:d=4,o=5,b=160:a,32e,8a,c6,8p,a,8p,c6,32a,8c6,e6,8p,c6,8p,e6,32c6,8e6,g6,8p,g,8p,c6,32g,8c6,2e6,p";
//char *rttlsong = "7NationA:d=4,o=6,b=125:e.,8e,8g,16p,8e,32p,8d,c.,16d,16c,b5,p,32p,e.,8e,8g,16p,8e,32p,8d,c.,16d,16c,b5,p,32p,e.,8e,8g,16p,8e,32p,8d,c.,16d,16c,b5,p,32p,e.,8e,8g,16p,8e,32p,8d,c,16d,b5";
//char *rttlsong = "DancingQ:d=4,o=5,b=100:8e7,8d7,8d7,8d7,16p,8e7,8d7,8d7,8d7,8e7,8c7,16d7,8d7,16d7,16d7,8d6,16c7,16c6,8a6,8e7,16d7,8d7,8c7,8c6,8c7,16c7,8c7,8c6,16c7,8c7,8c7,8c7,16d7,8c7,16c6,16c6,8c7";
//char *rttlsong = "Thunders:d=4,o=5,b=180:8b5,8d#6,8b5,8f#6,8b5,8d#6,8b5,8f#6,8b5,8d#6,8b5,8f#6,8b5,8f#6,8b5,8f#6,8e6,8b5,8a6,8b5,8e6,8b5,8a6,8b5,8e6,8b5,8a6,8b5,8e6,8b5,8a6";
//char *rttlsong = "StayingA:d=16,o=5,b=100:c6,8p.,a#,8p.,g#,8p.,g,8p,p,g,g#,g#,g#,4p,g,g#,g#,g#,4p,c6,8p.,a#,8p,p,g#,8p.,g,8p,p,g#,g#,g#,2c.6,p,1a#,1g#,1g";
//char *rttlsong = "RockTheC:d=8,o=5,b=140:e6,f6,e6,d6,c6,4e6,d6,4c6,2p,4e6,g,4a,4a.,4e6,g,4a,4a.,e6,f6,e6,d6,c6,4e6,d6,4c6,2p,4e6,g,4a,4a.,4e6,g,4a,4a.";
//char *rttlsong6 = "Tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b.,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e.6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a";
//char *rttlsong = "MoneyFor:d=4,o=5,b=100:16d#7,8p,16p,8d#7,8p,8d#7,8c#7,8d#7,8f#7,8f#7,8p,8d#7,8c#7,8c#7,16g#6,8p,16p,16g#6,8p,16p,8g#6";
//char *rttlsong = "FirstLev:d=16,o=5,b=112:e,e,e6,e,e,d6,e,e,c6,e,e,a#,e,e,b,c6,e,e,e6,e,e,d6,e,e,c6,e,e,4a#,p,e,e,e6,e,e,d6,e,e,c6,e,e,a#,e,e,b,c6,e,e,e6,e,e,d6,e,e,c6,e,e,4a#,p,a,a,a6,a,a,g6,a,a,f6,a,a,d#6,a,a,e6,f6,a,a,a6,a,a,g6,a,a,f6,a,a,4d#6";
//char *rttlsong = "Rocky2Th:d=4,o=6,b=112:8d5,8e5,8f5,8p,8f5,16f5,8f5,16p,8e5,8d5,8c5,8c5,8d5,8e5,8d5,8p,8d5,8e5,8f5,16p,32p,8e5,8f5,8g5,16p,32p,8f5,16p,32a5,8p,16p,2a5,p,8d5,16c5,8d5,16p,8c5";
//char *rttlsong = "Delivera:d=4,o=5,b=200:8c#,8d,e,c#,d,b4,c#,a4,b4,p,16c#6,16p,16d6,16p,8e6,8p,8c#6,8p,8d6,8p,8b,8p,8c#6,8p,8a,8p,b,p,a4,a4,b4,c#,a4,c#,b4,p,8a,8p,8a,8p,8b,8p,8c#6,8p,8a,8p,8c#6,8p,8b";
//char *rttlsong = "ForrestG:d=4,o=5,b=180:8c5,8c#5,8d#5,8d#5,8c5,8d#5,8p,8p,8g#5,8d#5,8p,4c5,8c#5,8d#5,8f5,4f5,4c#5,4f5,2p,8c#5,8d#5,8f5,4f5,4c#5,4f5,8p,8a#5,4g5,4d#5,4c5";
//char *rttlsong = "FraggleR:d=4,o=5,b=112:8c5,16c5,8c5,16c5,8a4,2p,8b4,8b4,8a4,8g4,16e5,8d5,8c5,16a4,8g4,8c5,16c5,8c5,16d5,8a4,2p,8b4,16b4,8a4,16b4,8c5";
//char *rttlsong = "Friends1:d=8,o=5,b=90:b,16b,16a,16g,f,f,16g,a,4g,b,16b,16a,16g,f,f,16g,a,4g,4,6d,g,a,c6,b,a,g.,16g,d,g,a,2a,16d,g,a,c6,b,a,g.,16c6,b,a,g,2d6,16c6,c6,c6,c6,b,a,g.,16a,b,4b,16g,16a,16b,16c6,c6,c6,c6,c6,b,a,g,g.,16d,16g,16a,b,4a,4g,d,6,c6,4b,16a,g,b.,a";
//char *rttlsong = "Ghostbus:d=4,o=5,b=180:4c5,4c5,8e5,8f5,8g5,8p,4a#5,4a#5,4f5,4f5,4c5,4c5,8e5,8f5,8g5,8p,4a#5,4a#5,4f5";
//char *rttlsong = "KnightRi:d=4,o=6,b=90:16d.5,32d#.5,32d.5,8a.5,16d.,32d#.,32d.,8a.5,16d.5,32d#.5,32d.5,16a.5,16d.,2c,16d.5,32d#.5,32d.5,8a.5,16d.,32d#.,32d.,8a.5,16d.5,32d#.5,32d.5,16a.5,16d.,2d#,a4,32a#.4,32a.4,d5,32d#.5,32d.5,2a5,16c.,16d.";
//char *rttlsong = "Macgyver:d=4,o=5,b=160:8c6,8c6,8c6,8c6,8c6,8c6,2b,8f#,8a,8p,2g,8c6,8c6,8p,b,8a,8b,8a,8g,8p,e6,a.,16p,b.,16p,c6,8b,8a,c6";
//char *rttlsong = "Superman:d=4,o=5,b=180:8g,8g,8g,c6,8c6,2g6,8p,8g6,8a.6,16g6,8f6,1g6,8p,8g,8g,8g,c6,8c6,2g6,8p,8g6,8a.6,16g6,8f6,8a6,2g.6,p,8c6,8c6,8c6,2b.6,g.6,8c6,8c6,8c6,2b.6,g.6,8c6,8c6,8c6,8b6,8a6,8b6,2c7,8c6,8c6,8c6,8c6,8c6,2c.6";
//char *rttlsong = "TheGodfa:d=8,o=5,b=56:g,c6,d#6,d6,c6,d#6,c6,d6,c6,g#,a#,2g,g,c6,d#6,d6,c6,d#6,c6,d6,c6,g,f#,2f,f,g#,b,2d6,f,g#,b,2c6,c,d#,a#,g#,g,a#,g#,g#,g,g,b,2c6";
//char *rttlsong = "TheSaint:d=4,o=6,b=140:8g5,8c#,8d,8g5,c,a#.5,g5,8d5,8d5,8a#5,8a5,8f5,8g5,8c#,8d,8g5,c,a#.5,g5,8a#5,8a5,8a#5,8a5,8f5,8g5,8c#,8d,8g5,c,a#5,8c5,8f#5,8g5,8c5,f5,d#5,8g5,8c#,8d,8g5,c,a#.5,1g5";
//char *rttlsong = "WonderWo:d=16,o=5,b=125:a6,a6,p,a6,a6,a6,p,a6,p,a6,p,a6,a6,a6,2p,4p,8p,c#.6,32p,c#6,c#6,p,2d6,8p,p,c#.6,32p,c#6,c#6,p,2d.6,4p,8p,p,d,p,d,d,p,c#,p,c#,p,c#,p,c#,p,2d.,4p,8p,p,d,p,d,d,p,c#,p,c#,p,a4,p,2a.4,2p,p,d,p,a#4,d,p,e,p,e,2p,c,p,a4,c,p,d,p,d,2p,d,p,d,d,p,e,p,e,p,d,p,1e";
//char *rttlsong = "ThemeV1.:d=4,o=5,b=100:8c#7,16p,8f#6,8p,8f#7,16p,16d#7,16p,8c#7,16p,8f#6,8p,8c#7,16p,16p,16a#6,16p,16a#6,16p,16a#6,16p,16c#7,16p,8f#6,16p,16p,8a#6,16p";
//char *rttlsong = "WhatAFee:d=4,o=6,b=140:8f5,8a5,a_.5,a_.5,1p,8p,8f5,8a5,c.,8a_5,8a_5,8f5,g5,1p,8f5,8a5,a_5,a_5,c,8a_5,8a5,a_5,a_5,c,8f5,8f5,1f5";
//char *rttlsong = "StartMus:d=8,o=5,b=125:b,g,g,g,b,g,g,g,c6,c6,b,b,2a,c6,c6,b,b,a,a,e6,e6,d6,c6,b,a,4g";
//char *rttlsong = "Theme:d=4,o=5,b=80:8c#,8f#,8a#,8c#6,16d#6,8f6,2d#6,8d#,8g#,8b,8d#6,16f6,8f#6,2f6,8f,8a#,8d6,8f6,16f#6,8g#6,2f#6,16d#6,8d#6,2f6,16d#6,8d#6,2f6,16f6,16f6,8f6,8f#6,16g6,2g#6,8f#6,8f#6,16g#6,a#6,8g#6,8f#6,16g#6,f#6,8d#6,8d#6,16d#6,2f6,8f#6,8f#6,16g#6,a#6,8g#6";
//char *rttlsong = "Theme:d=4,o=6,b=125:2p,8p,8b5,8e.,16g5,8f_5,e5,8b5,a.5,f_.5,8e.5,16g5,8f_5,d5,8f5,2b5,8p,8b5,8e.,16g5,8f_5,e5,8b5,d7,8c_5,c5,8g_,8c.7,16b,8a5,f_5,8g5,2e5,8p,8g,b5,8g5,b5,8g5,c7,8b,a_5,8f_5,8g.5,16b5,8a_5,a_5,8b5,2b,8p";
//char *rttlsong = "Elise:d=32,o=5,b=300:16d#.2,16d.2,16d#.2,16d.2,16d#.2,16a#.,16c#.2,16h.,4g#.,16h.3,16d#.,16g#.,4a#.,16d#.,16g.,16a#.,4h.,16d#.,16d#.2,16d.2,16d#.2,16d.2,16d#.2,16a#.,16c#.2,16h.,4g#.,16h.3,16d#.,16g#.,4a#.,16d#.,16h.,16a#.,4g#.,16p.";
//char *rttlsong = "Bad(Bass:d=4,o=5,b=140:a4,c,d,8d#,8e,8p,8a4,c,d,8d#,8e,a4,c,d,8d#,8e,8p,8a4,c,d,8d#,8e,a4,c,d,8d#,8e,8p,8a4,c,d,8d#,8e,a4,c,d,8d#,8e,8p,8a4,c,d,8d#,8e";
//char *rttlsong = "Thriller:d=8,o=5,b=112:b,d6,b,e6,16p,2d6,4p,d6,16p,c#6,16p,b,4p,p,b,b,32a,16p,32p,a,16g,g,16p,e,g,a,b,a,a,16g,b";
//char *rttlsong = "Extreme:d=4,o=6,b=450:b4,d,p,b4,d,p,b4,d,p,b4,2e,b4,d,16f#5,8p.,16f#5,8p.,a4,c#,p,a4,c#,p,a4,c#,p,a4,2e,a4,c#,16e5,8p.,16e5,8p.,e5,g,p,e5,g,p,e5,g,p,e5,2a,e5,g,16b5,8p.,16b5,8p.,b4,d,p,b4,d,p,b4,d,p,b4,2e,b4,d,16f#5,8p.,16f#5";
//char *rttlsong = "ChittyCh:d=4,o=5,b=45:32c#6,32c#6,32c#6,32c#6,16c#6,16g#,32c#6,32c#6,32c#6,32c#6,16d#6,16c#6,16c#6,16c6,8c6,8d#6,8c6,32c6,32c6,32c6,32c6,16c6,16g#,32c6,32c6,32c6,32c6,16c6,16g#,16a#,16c6,8c6,8f6,8c#6,32c#6,32c#6,32c#6,32c#6,16c#6,16g#,32c#6,32c#6,32c#6,32c#6,16d#6,16c#6,c#6,16c#6,16c#6,32d#6,32c#6,32c6,32a#,16g#,8f6,16f6,16f#6,16d#6,16c6,16g#,f6,16c#6,16c#6,32d#6,32c#6,32c6,32a#,16g#,8f6,16f6,16f#6,16d#6,16c6,16g#,c#6";
//char *rttlsong = "ByeByeBy:d=4,o=5,b=320:2e.,d.,d.,d.,c.,2e.,2a.4,8d.,8d.,8d.,8c.,d.,c.,2e.,2a.4,d.,d.,d.,e.,2f.,2e.,d.,c.,e.,d.,2c.,2a.4,d.,d.,d.,c.,2e.,2a.4,d.,d.,d.,c.,2e.,2a.4,d.,d.,d.,e.,2f.,2e.,d.,c.,e.,1d,g.,f.,e.,f.,d.,c.,d.,e.,2d.,d.,e.,d.,1c,g.,f.,e.,f.,d.,c.,d.,e.,d.,8a.4,8c.,d.,e.,2d.";
char *rttlsong1 = "Supermar:d=16,o=6,b=100:e,e,p,e,p,c,e,p,g,p,g5,p,c,8p,g5,8p,e5,8p,a5,p,b5,p,a#5,a5,p,g5,e,g,a,p,f,g,p,e,p,c,d,b5,4p,g,f#,f,d#,p,e,p,g#5,a5,c,p,a5,c,d,8p,8d#,p,d,8p,8c";

int notes[] = { 0,
262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,
1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
};

char* rttlsongs[] = {
  rttlsong0,
  rttlsong1,
  rttlsong2,
  rttlsong3,
  rttlsong4,
  rttlsong5
};

void play_rtttl(char *p)
{
  // Absolutely no error checking in here

  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while(*p != ':') p++;    // ignore name
  p++;                     // skip ':'

  // get default duration
  if(*p == 'd')
  {
    p++; p++;              // skip "d="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   // skip comma
  }

  Serial.print("ddur: "); Serial.println(default_dur, 10);

  // get default octave
  if(*p == 'o')
  {
    p++; p++;              // skip "o="
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }

  Serial.print("doct: "); Serial.println(default_oct, 10);

  // get BPM
  if(*p == 'b')
  {
    p++; p++;              // skip "b="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }

  Serial.print("bpm: "); Serial.println(bpm, 10);

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

  Serial.print("wn: "); Serial.println(wholenote, 10);


  // now begin note loop
  while(*p)
  {
    // first, get note duration, if available
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    
    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch(*p)
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if(*p == '#')
    {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if(*p == '.')
    {
      duration += duration/2;
      p++;
    }
  
    // now, get scale
    if(isdigit(*p))
    {
      scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if(*p == ',')
      p++;       // skip comma for next note (or we may be at the end)

    // now play the note

    if(note)
    {
      Serial.print("Playing: ");
      Serial.print(scale, 10); Serial.print(' ');
      Serial.print(note, 10); Serial.print(" (");
      Serial.print(notes[(scale - 4) * 12 + note], 10);
      Serial.print(") ");
      Serial.println(duration, 10);
      tone(MELODY_PIN, notes[(scale - 4) * 12 + note]);
      delay(duration);
      noTone(MELODY_PIN);
    }
    else
    {
      Serial.print("Pausing: ");
      Serial.println(duration, 10);
      delay(duration);
    }
  }
}



void displayColor(CRGB color){
  for ( int i=0;i<NUM_LEDS;i++){
    leds[i] = color;
    
  } 
  FastLED.show(); 
}

void setup(){
  
  Serial.begin(9600);
  /*
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println("Unable to begin:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
    Serial.println("DFPlayer Mini online.");
  }
   */
  
  irrecv.enableIRIn();
  //irrecv.blink13(true);
  servo.attach(SERVO_PIN);
  servo.write(servo_pos);
//  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
//  myDFPlayer.play(1);  //Play the first mp3
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.println("Setup Complete.");
  displayColor(CRGB::Blue);
  //play_rtttl(rttlsong);
}


void dump(decode_results *results) {

  int count = results->rawlen;

  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  } 
  else if (results->decode_type == MAGIQUEST) {
    Serial.print("Decoded MAGIQUEST - Magnitude=");
    Serial.print(results->magiquestMagnitude);
    Serial.print(", wand_id=");
    
  }
  

}


void loop(){
  int songnumber = 0;
  
  
  leds[0] = CRGB::Red; 
  leds[1] = CRGB::Green;
  leds[2] = CRGB::Blue;
  leds[3] = CRGB::Red; 
  leds[4] = CRGB::Green;
  leds[5] = CRGB::Blue;  
  FastLED.show();
  
  if (irrecv.decode(&results)){

        displayColor(CRGB::Red);
        Serial.println(results.value,HEX);
        dump(&results);        

        
        //if ( results.value == BENS_WAND ){
          
          servo.write(90);
          //sing(random(0,8));
          //sing(7);
          songnumber = random(0,NUMRTTLSONGS);
          //play_rtttl(rttlsong2);
          play_rtttl(rttlsongs[songnumber]);
          delay(200);
          servo.write(SERVO_ZERO);              
          
        //}
        irrecv.resume();      
  }
  displayColor(CRGB::Blue);
}
