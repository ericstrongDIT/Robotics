/*using the light Sensor 0-100
 bright surfaces (white) give back a high reading ie light = high
 dark surfaces(black) give back a low reading
 dark = low

Set a threshold first. (a rooms lighting can vary) so always calibrate. also check the height of the sensor from the surface. this can be a factor of calibration also

example readings. on nxt go to brick go to view mode>reflective light(plug sensor to port 1)

place sensor on both light and dark surface to get readings, you can gauge from here what the threshold will be.

ok now get average of both of these values. so light + dark / 2 = threshold. this is a good place to start 

1. make sure to read the above and set your threshold.
2. This program should move on a bright surface until it 
reaches a dark line(ie it stops)


*/

const tSensors lightSensor = (tSensors) S1; //ensure port 1
task main()
{
	int threshold = //enter your threshold here

	//WHILE THE LIGHT SENSOR IS > THAN THE THRESHOLD MOVE FORWRD 50
	while(SensorValue(lightSensor) > threshold)
	{
		motor[motorC] = 50;
		motor[motorB] = 50;

	}//end while

	//motors stop when the light changes
	motor[motorC] = 0;
	motor[motorB] = 0;

	motor[motorC] = -10;
	motor[motorB] = -10;







	

	
}//end main()