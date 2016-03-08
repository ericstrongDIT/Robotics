#pragma config(Sensor, S3,     soundSensor,    sensorSoundDB)
/*This program will tell robot to stop when it hears a loud noise for 2seconds*/

/*following on from sound sensor*/
task main()
{
  int power = 10;
  int flag = 0;

  while(flag == 0)
  {
	  motor[motorC] = power;
	  motor[motorB] = power;

	  if(SensorValue(soundSensor) > power)
	  {
	    wait1Msec(2000);
	  }
  }//end while

}//end main
