/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Arduino Mecanum Omni Direction Wheel Robot Car Lesson5 Wifi Control
 * Tutorial URL http://osoyoo.com/?p=30176
 * CopyRight www.osoyoo.com
 * 
 *
 *  EDIT 2024/05/05 Several variable correction and "speed" value integration in sub functions
 *
 */
int SPEED = 128  ;  
int TURN_SPEED =  128  ;
int SHIFT_SPEED  = 128  ;
int udp_speed;

#define TURN_TIME 500  
#define MOVE_TIME 500  

#define speedPinR 9              // RIGHT WHEEL PWM pin D45 connect front MODEL-X ENA 
#define RightMotorDirPin1  22    // Front Right Motor direction pin 1 to Front MODEL-X IN1  (K1)
#define RightMotorDirPin2  24    // Front Right Motor direction pin 2 to Front MODEL-X IN2   (K1)                                 
#define LeftMotorDirPin1  26     // Left front Motor direction pin 1 to Front MODEL-X IN3 (K3)
#define LeftMotorDirPin2  28     // Left front Motor direction pin 2 to Front MODEL-X IN4 (K3)
#define speedPinL 10             // Left WHEEL PWM pin D7 connect front MODEL-X ENB

#define speedPinRB 11   //  RIGHT WHEEL PWM pin connect Back MODEL-X ENA 
#define RightMotorDirPin1B  5    //Rear Right Motor direction pin 1 to Back MODEL-X IN1 (K1)
#define RightMotorDirPin2B 6    //Rear Right Motor direction pin 2 to Back MODEL-X IN2 (K1) 
#define LeftMotorDirPin1B 7    //Rear left Motor direction pin 1 to Back MODEL-X IN3  K3
#define LeftMotorDirPin2B 8  //Rear left Motor direction pin 2 to Back MODEL-X IN4  k3
#define speedPinLB 12    //   LEFT WHEEL  PWM pin D8 connect Rear MODEL-X ENB


/* 
 * ———————————————————————————————————————————————————————————————————————
 * motors rotation direction definition added with speed parameter used in
 * combining wheel commands, for every motor, every direction :
 * Front left, Front Right, Rear Left, Reard Right : FL, FR, RL, RR
 * backward : bck
 * forward : fw
 * ———————————————————————————————————————————————————————————————————————
*/

void FR_bck(int speed)  //front-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2,HIGH); 
  analogWrite(speedPinR,speed);
}

void FR_fwd(int speed) // front-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1,HIGH);
  digitalWrite(RightMotorDirPin2,LOW); 
  analogWrite(speedPinR,speed);
}

void FL_bck(int speed) // front-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,HIGH);
  analogWrite(speedPinL,speed);
}

void FL_fwd(int speed) // front-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1,HIGH);
  digitalWrite(LeftMotorDirPin2,LOW);
  analogWrite(speedPinL,speed);
}

void RR_bck(int speed)  //rear-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1B, LOW);
  digitalWrite(RightMotorDirPin2B,HIGH); 
  analogWrite(speedPinRB,speed);
}

void RR_fwd(int speed)  //rear-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1B, HIGH);
  digitalWrite(RightMotorDirPin2B,LOW); 
  analogWrite(speedPinRB,speed);
}

void RL_bck(int speed)  //rear-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1B,LOW);
  digitalWrite(LeftMotorDirPin2B,HIGH);
  analogWrite(speedPinLB,speed);
}

void RL_fwd(int speed)    //rear-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1B,HIGH);
  digitalWrite(LeftMotorDirPin2B,LOW);
  analogWrite(speedPinLB,speed);
}

/* 
 * ———————————————————————————————————————————————————————————————————————
 * Wheels combination definition for defined moves : motor control
 * ———————————————————————————————————————————————————————————————————————
*/

void right_shift(int speed_fl_fwd,int speed_rl_bck ,int speed_rr_fwd,int speed_fr_bck) {
  FL_fwd(speed_fl_fwd); 
  RL_bck(speed_rl_bck); 
  FR_bck(speed_fr_bck);
  RR_fwd(speed_rr_fwd);
}

void left_shift(int speed_fl_bck,int speed_rl_fwd ,int speed_rr_bck,int speed_fr_fwd){
   FL_bck(speed_fl_bck);
   RL_fwd(speed_rl_fwd);
   FR_fwd(speed_fr_fwd);
   RR_bck(speed_rr_bck);
}

void go_advance(int speed){
   RL_fwd(speed);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_fwd(speed); 
}

void go_back(int speed){
   RL_bck(speed);
   RR_bck(speed);
   FR_bck(speed);
   FL_bck(speed); 
}

void left_turn(int speed){
   RL_bck(0);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_bck(0); 
}

void right_turn(int speed){
   RL_fwd(speed);
   RR_bck(0);
   FR_bck(0);
   FL_fwd(speed); 
}

void left_back(int speed){
   RL_fwd(0);
   RR_bck(speed);
   FR_bck(speed);
   FL_fwd(0); 
}

void right_back(int speed){
   RL_bck(speed);
   RR_fwd(0);
   FR_fwd(0);
   FL_bck(speed); 
}

void clockwise(int speed){
   RL_fwd(speed);
   RR_bck(speed);
   FR_bck(speed);
   FL_fwd(speed); 
}

void countclockwise(int speed){
   RL_bck(speed);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_bck(speed); 
}
 
void stop_Stop()    //Stop
{
   analogWrite(speedPinLB,0);
   analogWrite(speedPinRB,0);
   analogWrite(speedPinL,0);
   analogWrite(speedPinR,0);
}

/* 
 * ———————————————————————————————————————————————————————————————————————
 *                         Pins initialization 
 * ———————————————————————————————————————————————————————————————————————
*/

void init_GPIO()
{
  pinMode(RightMotorDirPin1, OUTPUT); 
  pinMode(RightMotorDirPin2, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
 
  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT); 
  pinMode(speedPinR, OUTPUT);
  pinMode(RightMotorDirPin1B, OUTPUT); 
  pinMode(RightMotorDirPin2B, OUTPUT); 
  pinMode(speedPinLB, OUTPUT);  
 
  pinMode(LeftMotorDirPin1B, OUTPUT);
  pinMode(LeftMotorDirPin2B, OUTPUT); 
  pinMode(speedPinRB, OUTPUT);
   
  stop_Stop();
}

/* 
 * ———————————————————————————————————————————————————————————————————————
 *                         WIFI initialization 
 * ———————————————————————————————————————————————————————————————————————
*/

#include "WiFiEsp.h"
#include "WiFiEspUDP.h"
char ssid[] = "osoyoo_robot"; 

int status = WL_IDLE_STATUS;
// use a ring buffer to increase speed and reduce memory allocation
 char packetBuffer[8]; 
WiFiEspUDP Udp;
unsigned int localPort = 8888;  // local port to listen on
void setup()
{
 init_GPIO();
  Serial.begin(9600);   // initialize serial for debugging
    Serial1.begin(115200);
    Serial1.write("AT+UART_DEF=9600,8,1,0,0\r\n");
  delay(200);
  Serial1.write("AT+RST\r\n");
  delay(200);
  Serial1.begin(9600);    // initialize serial for ESP module
  WiFi.init(&Serial1);    // initialize ESP module

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

    Serial.print("Attempting to start AP ");
   Serial.println(ssid);
   //AP mode
   status = WiFi.beginAP(ssid, 10, "", 0);

  Serial.println("You're connected to the network");
  printWifiStatus();
  Udp.begin(localPort);
  
  Serial.print("Listening on port ");
  Serial.println(localPort);
}

/* 
 * ———————————————————————————————————————————————————————————————————————
 *                           ARDUINO  LOOP
 * ———————————————————————————————————————————————————————————————————————
*/

void loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize) {                               // if you get a client,
    Serial.print("Received packet of size ");
    Serial.print(packetSize);
    int len = Udp.read(packetBuffer, 255);
    Serial.print(" Contents: ");  //for testing buffer content
    Serial.println(packetBuffer);  //for testing buffer content
   // Serial.print(packetBuffer[1]);
   // Serial.print(packetBuffer[2]);
   // Serial.print(packetBuffer[3]);
    Serial.print("udp_speed : ");
    Serial.print(udp_speed);
    Serial.print(" SPEED : ");
    Serial.println(SPEED);
    if (len > 0) {
      packetBuffer[len] = 0;
     }
       char lastthreechar[3];
     strncpy(lastthreechar, &packetBuffer[1],3);
     udp_speed = atoi(lastthreechar);
  
     SPEED = udp_speed;    
     TURN_SPEED = udp_speed;    
     SHIFT_SPEED = udp_speed;   
     
     char c=packetBuffer[0];
      switch (c)    //serial control instructions
      {  
        case 'A':go_advance(SPEED);break;
        case 'L':left_turn(TURN_SPEED);break;
        case 'R':right_turn(TURN_SPEED);break;
        case 'B':go_back(SPEED);break;
        case 'E':stop_Stop();break;
        case 'F':left_shift(0,SHIFT_SPEED,0,SHIFT_SPEED);break; //left ahead
        case 'H':right_shift(SHIFT_SPEED,0,SHIFT_SPEED,0);break; //right ahead
        case 'I':left_shift(SHIFT_SPEED,0,SHIFT_SPEED,0);break;//left back
        case 'K':right_shift(0,SHIFT_SPEED,0,SHIFT_SPEED);break;//right back
        case 'O':left_shift(SHIFT_SPEED,SHIFT_SPEED,SHIFT_SPEED,SHIFT_SPEED);break;//left shift
        case 'T':right_shift(SHIFT_SPEED,SHIFT_SPEED,SHIFT_SPEED,SHIFT_SPEED);break;//right shift
        case 'J':countclockwise(SPEED);break;//turn round left
        case 'G':clockwise(SPEED);break;//turn round right
        default:break;
      }
     
    
    }

}


 /* 
 * ———————————————————————————————————————————————————————————————————————
 *                       TEMPORARY CODE PARKING
 * ———————————————————————————————————————————————————————————————————————
*/

void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in the browser
  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println();
}
