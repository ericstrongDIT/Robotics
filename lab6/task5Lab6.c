#pragma config(Sensor, S1,     lightSensor,    sensorLightActive)
#pragma config(Sensor, S2,     touchSensor,    sensorTouch)
#pragma config(Sensor, S3,     sonarSenor,     sensorSONAR)


/*doing the arch. TASK 5. Program will get automatci threshold first*/
//prototype for automaticThreshold
#define SPEED 20
void arch(int threshold)
{
	 clearTimer(T1);  //declaring the timer

		while(time1[T1] < 1000)
		 {
			motor[motorC]=SPEED;
			motor[motorB]= SPEED + 20; // right motor goes faster
		}//end while

		clearTimer(T1);  //declaring the timer

		 while(time1[T1] < 1500)
		 {
			motor[motorC]=SPEED + 20 ;
			motor[motorB]= SPEED; // right motor goes faster

		}//end while
			while(SensorValue(sonarSenor) > 30)

	{

		while(SensorValue(lightSensor) < threshold)
		{
			// this runs forward and left while seeing dark
			motor[motorC] = 0; 		//right
			motor[motorB] = 20; 	//left

		}//end while

		while(SensorValue(lightSensor) > threshold)
		{
			// this runs forward and right while seeing bright
			motor[motorC] = 20; 		//right
			motor[motorB] = 0; 			//left



		}//end while


	}//end infinite while loop

}//end arch
void lineFollow(int threshold )
{

	while(SensorValue(sonarSenor) > 30)

	{

		while(SensorValue(lightSensor) < threshold)
		{
			// this runs forward and left while seeing dark
			motor[motorC] = 0; 		//right
			motor[motorB] = 20; 	//left

		}//end while

		while(SensorValue(lightSensor) > threshold)
		{
			// this runs forward and right while seeing bright
			motor[motorC] = 20; 		//right
			motor[motorB] = 0; 			//left



		}//end while


	}//end infinite while loop
		arch(threshold);

}//end lineFollow

task main()
{
	int threshold = 55;
	lineFollow(threshold);


}//end main()
