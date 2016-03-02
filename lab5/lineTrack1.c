/*Line following using light Sensor
Remember to set your threshold first and save to a variable.(dark + light / 2)[this is in the range of 0-100]

this program is run by this principal
-run forward and left while seeing dark
-run forward and right while seeing light
-alternate back and forth


NOTE IF THE ROBOT JUST SPINS IN A CIRCLE YOU GOTTA CONFIGURE THE
THRESHOLD. 


*/

const tSensor lightSensor = (tSensors) S1; // put light sensor to port 1

task main()
{
	int threshold; // calibrate this 
	int flag = 0;

	while(flag == 0)
	{

		while(SensorValue(lightSensor) < threshold)
		{
			// this runs forward and left while seeing dark
			motor[motorC] = 0; 		//right
			motor[motorB] = 80; 	//left

		}//end while

		while(SensorValue(lightSensor) > threshold)
		{
			// this runs forward and right while seeing bright
			motor[motorC] = 80; 		//right
			motor[motorB] = 0; 			//left

		}//end while

	}//end infinite while loop


}//end main