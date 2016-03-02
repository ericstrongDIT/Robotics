/*Line following using light Sensor and if touch sensor is touched stop the robot
Remember to set your threshold first and save to a variable.(dark + light / 2)[this is in the range of 0-100]

this program is run by this principal
-run forward and left while seeing dark
-run forward and right while seeing light
-alternate back and forth


NOTE IF THE ROBOT JUST SPINS IN A CIRCLE YOU GOTTA CONFIGURE THE
THRESHOLD. 


*/

const tSensor lightSensor = (tSensors) S1; // put light sensor to port 1
const tSensor touchSensor = (tSensors) S2; // put touch sensor to port 2
task main()
{
	int threshold; // calibrate this 
	int flag = 0;

	while(SensorValue (touchSensor) == 0) // follows a line until touch sensor is touched
	{

		if(SensorValue(lightSensor) < threshold)
		{
			// this runs forward and left while seeing dark
			motor[motorC] = 0; 		//right
			motor[motorB] = 80; 	//left

		}//end if

		else
		{
			// this runs forward and right while seeing bright
			motor[motorC] = 80; 		//right
			motor[motorB] = 0; 			//left

		}//end else

	}//end while

	motor[motorC] = 0; 		//right
	motor[motorB] = 0; 		//left


}//end main