#pragma config(Sensor, S1,     lightSensor,    sensorLightActive)
/*Line counter*/

#define SPEED 20
int lineCounter(int counter,int threshold)
{
	int light = 60;
	int dark= 40;
	int flag = 0;

	while(flag == 0)
	{
		int counter = 0;

		motor[motorC]= SPEED;
		motor[motorB]= SPEED;

		if(SensorValue(lightSensor) > dark)
		{
			displayTextLine(1,"Lines Counted %d",counter);
			counter ++;
		}//end if
		if(counter > 0)
		{
			flag = 1;
		}

}

	return(counter);

}//end lineCounter


task main()
{
	int threshold = 55;
	int counter = 0;
		displayTextLine(1,"Lines Counted %d",counter);

	lineCounter(counter,threshold);

}//end main()
