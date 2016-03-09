#pragma config(Sensor, S1,     lightSensor,    sensorLightActive)
#pragma config(Sensor, S2,     touchSensor,    sensorTouch)


/*Using automatic Thresholds*/
//prototype for automaticThreshold
#define SPEED 20
void lineFollow(int threshold )
{
	int flag = 0;

	while(flag == 0)
	{

		while(SensorValue(lightSensor) < threshold)
		{
			// this runs forward and left while seeing dark
			motor[motorC] = 0; 		//right
			motor[motorB] = SPEED; 	//left

		}//end while

		while(SensorValue(lightSensor) > threshold)
		{
			// this runs forward and right while seeing bright
			motor[motorC] = SPEED; 		//right
			motor[motorB] = 0; 			//left
		}//end while

	}//end while
}//end lineFollow

task main()
{
	int dark=0;
	int bright=0;
	int total=0;
	int threshold=0;



	while(SensorValue(touchSensor)==0)
	{
	}//end while

	dark = SensorValue(lightSensor);
	bright = SensorValue(lightSensor);

	total = bright + dark;
	threshold = total /2;

	lineFollow(threshold);



}//end main()
