#pragma config(Sensor, S1,     lightSensor,    sensorLightActive)
#pragma config(Sensor, S2,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S3,     touchSensor,    sensorTouch)


/*The following program is for lab 5 part part 9
9.	Follow the line but use the ultrasonic sensor to detect an object, then go around it and find the line again.
*/
#define POWER 20  //setting the power of the motors to 20
#define TURN 17   //setting the power of the turn to 17,

/*implementing the dark fucntion*/
void dark(int go, int motorStop)
{
  	// this runs forward and left while seeing dark
			motor[motorC] = motorStop; 		//right
			motor[motorB] = go; 	        //left
}//end dark

/*implementing the bright fucntion*/
void bright(int go, int motorStop)
{
  	// this runs forward and right while seeing bright
			motor[motorC] = go; 		      //right
			motor[motorB] = motorStop; 	  //left
}//end brigh

void stop1(int motorStop)
{
  	// this runs forward and left while seeing dark
			motor[motorC] = motorStop; 		//right
			motor[motorB] = motorStop; 	  //left
}//end stop1

void left(int go)
{

		motor[motorC] = -TURN;    //left motor
		motor[motorB] = TURN;     //right motor
		wait1Msec(1000);
}//end left

void right(int go)
{
		motor[motorC] = TURN;     //left motor
		motor[motorB] = -TURN;    //right motor
		wait1Msec(1000);
}//end right

void forward(int go)
{
		motor[motorC] = go;       //left motor
		motor[motorB] = go;       //right motor
		wait1Msec(1000);
}//end right

task main()
{
  int go = POWER;
  int motorStop =0;
  int threshold=0;
  int i;



  while(SensorValue(sonarSensor) > 10) // 10 cm
  {
    if(SensorValue(lightSensor) < threshold)
		{
		  dark(go,motorStop);
		}//end if
		else
		{
		  bright(go,motorStop);
		}//end else

  }//end while

  stop1(motorStop);   //exits the loop stops
  left(go);
  forward(go);
  right(go);

  //The forward function will go twice as much to pass the obstacle
  for(i=0;i<3;i++)
  {
    forward(go);
  }//end for

  stop1(motorStop);
  right(go);
  forward(go);
  left(go);

  //back to the line following until touch sensor is pressed
   while(SensorValue(touchSensor) ==0) // 10 cm
  {
    if(SensorValue(lightSensor) < threshold)
		{
		  dark(go,motorStop);
		}//end if
		else
		{
		  bright(go,motorStop);
		}//end else

  }//end while



}//end task main()
