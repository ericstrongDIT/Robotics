#pragma config(Sensor, S4,sonarSensor,sensorSONAR)
#pragma config(Sensor, S1,lightSensor,sensorLightActive)

task main()
{
	int threshold = 55; // calibrate this
	int flag = 0;

	while(flag == 0)
	{
		while(SensorValue(lightSensor) < threshold && SensorValue(sonarSensor)>100)
		{
			// this runs forward and left while seeing dark
			motor[motorC] = 0; 		//right
			motor[motorB] = 20; 	//left

		}//end while

		while(SensorValue(lightSensor) > threshold && SensorValue(sonarSensor)>100)
		{
			// this runs forward and right while seeing bright
			motor[motorC] = 20; 		//right
			motor[motorB] = 0; 			//left

		}//end while
	}
	while(SensorValue(sonarSensor)>25)
	{
		motor[motorC] =0;//left motor
		motor[motorB] =50;//right
		wait1Msec(1000);
	}
}


