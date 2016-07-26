//========================================================//
//         Charles Competition Library v2015.1.19
//========================================================//

//Tasks (Each task runs simultaneously in its own thread)

//Define bool
typedef int bool;
#define true 1
#define false 0

#define LCD uart1

//Functions

int speedLfromRPM(int i);
int speedRfromRPM(int i);
void joystickMap();
void beep();
void boop();
void soundSpeedUp();
void soundSpeedDown();


//Global Vars

//motors
const unsigned char W_LF = 1;
const unsigned char W_RF = 2;
const unsigned char W_HF = 3;
const unsigned char INTAKE = 4;
const unsigned char S_L = 5;
const unsigned char S_R = 6;
const unsigned char CON = 7;
const unsigned char W_HB = 8;
const unsigned char W_LB = 9;
const unsigned char W_RB = 10;

//sensors
const unsigned char GYRO = 2;
const unsigned char EXPANDER = 3;
const unsigned char SEL = 8;
const unsigned char QUADL = 11;
const unsigned char QUADR = 13;
const unsigned char SONAR = 15;
const unsigned char SONAR_L = 17;
const unsigned char SONAR_R = 19;
//const unsigned char SQUAD_L = 1; //I2C_1
//const unsigned char SQUAD_R = 2; //I2C_2

extern int shooter;

float Kp = 300.0;
float bsFix = 2.0;

float speedL = 0;
float speedR = 0;//Calculated right flywheel speed (-127 to 127)

float errL = 0,
			errR = 0;

//int SPEED_CONV_FACTOR = 300;
int PID_THRESH = 30;

int timeElapsed = 0;

int driveX = 0,
		driveY = 0,
		driveH = 0; //Intake speed (-127 to 127)

int AUTON_PID_THRESH = 5;
