#pragma config(Sensor, S3,     soundSensor,    sensorSoundDB)
/*This program will read the sound and act on its power */

/*following on from sound sensor*/
task main()
{
  ClearTimer(T1);
 while(time1[T1] < 10000)
{
  motor[motorC] = SensorValue(soundSensor);
  motor[motorB] = SensorValue(soundSensor);
}//end while

}//end main
