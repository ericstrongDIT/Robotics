#pragma config(Sensor, S1,     touchSensor,    sensorTouch)
#pragma config(Sensor, S2,     lightSensor,    sensorLightActive)
#pragma config(Sensor, S3,     sonarSensor,    sensorSONAR)
/*the following program is for lab 5 Question 8 and 9.
The program will display the speed and distance while following a line. if an obstacle occures then the program will stop the count
*/

int thresHold(int threshold)
{
   int light;
  int dark;
  int total;

 while(SensorValue(touchSensor) == 0)
 {
   nxtDisplayBigTextLine(3, "read light value");
   //nxtDisplayBigTextLine(3, "read light value");
 }//end while

 //reading light value
 light = SensorValue(lightSensor);
 nxtDisplayBigTextLine(3, "Light Value is %d",light);
 wait1Msec(1000); // wait so you can press again

 while(SensorValue(touchSensor) == 0)
 {
    nxtDisplayBigTextLine(3, "read dark value");
 }//end while
 //reading dark value

 dark = SensorValue(lightSensor);
 nxtDisplayBigTextLine(3, "Dark Value is %d",dark);
 wait1Msec(1000); // wait so you can press again

 //calculating the threshold
 total = light + dark;
 threshold = total / 2;
 return(threshold);

}//end threshold

int followLine(int threshold, int distance, int speed)
{
  	while(SensorValue(sonarSensor) > 30 && SensorValue(touchSensor)==0)

	  {

				while(SensorValue(lightSensor) > threshold && nMotorEncoderTarget[motorB] == distance && nMotorEncoderTarget[motorC] == distance)
			{
				// this runs forward and left while seeing dark

				nMotorEncoder[motorB] =speed;
	      nMotorEncoder[motorC] =0;

			}//end while

			while(SensorValue(lightSensor) > threshold && nMotorEncoderTarget[motorB] == distance && nMotorEncoderTarget[motorC] == distance)
			{
				// this runs forward and right while seeing bright


	     nMotorEncoder[motorB] =0;
	     nMotorEncoder[motorC] =speed;

			}//end while


	}//end infinite while loop
	if(SensorValue(touchSensor)==1)
	{
	  return(2);
	}//end if
	if(speed == distance)
	{
	  return(0);
	}//end if
	else
	{
	  return(1);
	}//end else


}//end followLine


task main()
{
  int threshold=0;
  int value=0;
  int distance= 1500;
  int speed = 20;
  int error=0;


  //get threshold first
  threshold = thresHold(value);

  //follow the line
  error=followLine(threshold,distance,speed);
  if(error ==0)
  {
    while(SensorValue(touchSensor) == 0)
    {
      nxtDisplayBigTextLine(3, "distance stopped");
    }//end while
  }//endif
  if(error ==1)
  {
    while(SensorValue(touchSensor) == 0)
    {
      nxtDisplayBigTextLine(3, "Sonar obstacle");
    }//end while
  }//end if
  if(error ==2)
  {
    while(SensorValue(touchSensor) == 0)
    {
      nxtDisplayBigTextLine(3, "Touch obstacle");
    }//end while
  }//end if

}//end task main()
