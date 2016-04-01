#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     lightSensor,    sensorEV3_Color)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*Program to measure Distance and Speed and display this while following a line. If an obstacle occurs then it exits the count
*/

#define SPEED 30
#define TIME 3000

/*Calculating the automatic threshold for light sensor*/
int thresHold(int threshold)
{
  int light;
  int dark;
  int total;

 while(SensorValue(touchSensor) == 0)
 {
   displayBigTextLine(3, "read light value");
 }//end while

 //reading light value
 light = SensorValue(lightSensor);
 displayBigTextLine(3, "Light is %d",light);
 wait1Msec(1000); // wait so you can press again

 while(SensorValue(touchSensor) == 0)
 {
    displayBigTextLine(3, "read dark value");
 }//end while
 //reading dark value

 dark = SensorValue(lightSensor);
 displayBigTextLine(3, "Dark is %d",dark);
 wait1Msec(1000); // wait so you can press again

 //calculating the threshold
 total = light + dark;
 threshold = total / 2;
 return(threshold);

}//end threshold

int forward(int threshold)
{
   //PID enabled to go forward straight
 // nMotorPIDSpeedCtrl[motorC]= mtrSpeedReg;
 // nMotorPIDSpeedCtrl[motorB]= mtrSpeedReg;
motor[motorB]= SPEED;
motor[motorC]=SPEED;
  int count = 0;
  int lastSeen=1; // this variable is used to indicate the transition from bright to dark
  clearTimer(T1);

  while(time1[T1] < 3000) //condition runs while the count is less than 5 ie after 5lines it exits
  {
    if(SensorValue(lightSensor) < threshold)
    {
      //motors are synced and only one motor is powered.
      //nSyncedMotors=synchBC;
	    motor[motorB]= SPEED;
	    motor[motorC]= SPEED;

	    //adds 1 every time it sees a a dark line
	    if(lastSeen == 1)
	    {
	      /* the counter is incremented everytime a transition is made then
	      lastseen is reset (like a flag) */

	       count ++;
	       lastSeen = 0;
	       displayBigTextLine(3, "Lines = %d",count);

	    }//end if

	  }//end if
	  else
	  {
	    lastSeen = 1;
	    /*this means dont count if the lightSensor sees light*/
	  }//end else

  }//end while
  return(count);

}//end forward

task main()
{
  int value = 0;
  int threshold=0;
  int counter=0;

  //get threshold from function
  threshold = thresHold(value);

  //go forward
  counter=forward(threshold);

    while(SensorValue(touchSensor) == 0)
    {
      displayBigTextLine(3, "Final Lines = %d",counter);
    }//touch to clear screen
}//end main()
