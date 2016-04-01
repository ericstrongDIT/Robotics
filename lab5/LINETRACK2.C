#pragma config(Sensor, S2,     lightSensor,    sensorLightActive)
#pragma config(Sensor, S1,     touchSensor,    sensorTouch)

/*Line following using light Sensor (within Functions)and if touch sensor is touched stop the robot
Remember to set your threshold first and save to a variable.(dark + light / 2)[this is in the range of 0-100]

this program is run by this principal
-run forward and left while seeing dark
-run forward and right while seeing light
-alternate back and forth


NOTE IF THE ROBOT JUST SPINS IN A CIRCLE YOU GOTTA CONFIGURE THE
THRESHOLD.
*/

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
}//end dark

task main()
{
  int go = 80;
  int motorStop = 0;
	int threshold; // calibrate this
	//int flag = 0;

	while(SensorValue (touchSensor) == 0) // follows a line until touch sensor is touched
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

	motor[motorC] = 0; 		//right
	motor[motorB] = 0; 		//left
}//end main
