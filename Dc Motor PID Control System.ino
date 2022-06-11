int setpoint =180 ; // as degree
const int R_IS=1; const int R_EN=8; const int R_PWM=10; const int L_IS=4; const int L_EN=5; const int L_PWM=6;  // motor driver's pins connection
const int Enc_outputA=2; const int Enc_outputB=3; //encoder motor's output A and B channels 
long tStart=millis(); //begining of the time
volatile int counter=0; volatile float pos; void risingCounter(); // attachInterrupt inital values and function
//PID constants
//motor works 255-0 
//double kp = 2;
//double ki = 5;
//double kd = 1;
// motor works 100-255 moves one by one 
//double kp = 0.00238957666274253;
//double ki = 0.00429075984737319;
//double kd = -0.000072619598461869;
// motor works 0-255 moves one by one 
double kp = 0.0066633975917676;
double ki = 0.00139049216784448;
double kd = -0.000292860253276174;
unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double cumError, rateError;
double output;
double computePID(double inp);
void setup() {
  Serial.begin(9600); // Set Baudrate at 9600
 // pinMode(Vin,INPUT); // Make Vin Input
  pinMode(R_IS,OUTPUT); pinMode(R_EN,OUTPUT); pinMode(R_PWM,OUTPUT); pinMode(L_IS,OUTPUT); pinMode(L_EN,OUTPUT); pinMode(L_PWM,OUTPUT);
  digitalWrite(R_IS,LOW); digitalWrite(L_IS,LOW); digitalWrite(R_EN,HIGH); digitalWrite(L_EN,HIGH);
  pinMode(Enc_outputA,INPUT); pinMode(Enc_outputB,INPUT);
  attachInterrupt(digitalPinToInterrupt(Enc_outputA),risingCounter,RISING); // interrupting when motor's output A is 0 to 5 volt
}

void loop() {
  output=computePID(pos);
  if(R_PWM>255){
    R_PWM==255;
  }
  if(L_PWM>255){
    L_PWM==255;
  }
  if(setpoint>pos){
    analogWrite(L_PWM,0); analogWrite(R_PWM,output);//cw
    Serial.println(pos);
    //Serial.print("output: "); Serial.println(output);
  }else{
     analogWrite(L_PWM,output); analogWrite(R_PWM,0);//ccw
  }
}
void risingCounter(){
   if(digitalRead(Enc_outputB)){
     counter++;
     pos=(float)counter/5.83;
   }else{
    counter--;
    pos=(float)counter/5.83;
   }
   if(counter==21550){
    counter=0;
   }
}
double computePID(double inp){
  currentTime=millis();
  elapsedTime=(double)(currentTime-previousTime);
  error = setpoint - inp;
  cumError += error*elapsedTime;
  rateError=(error-lastError)/elapsedTime;
  double out=kp*error+ki*cumError+kd*rateError;
  lastError=error; previousTime=currentTime;
  
   return out;
}
