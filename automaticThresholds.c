#pragma config(Sensor, S1,     touchSensor,    sensorTouch)
#pragma config(Sensor, S2,     lightSensor,    sensorLightActive)

/*Calculating the automatic threshold for light sensor*/

int thresHold(int threshold)
{
  int light;
  int dark;
  int total;

 while(SensorValue(touchSensor) == 0)
 {
   nxtDisplayBigTextLine(3, "read light value");
 }//end while

 //reading light value
 light = SensorValue(lightSensor);
 nxtDisplayBigTextLine(3, "Light Value is %d",light);
 wait1Msec(1000); // wait so you can press again

 while(SensorValue(touchSensor) == 0)
 {
    nxtDisplayBigTextLine(3, "read dark value");
 }//end while
 //reading dark value

 dark = SensorValue(lightSensor);
 nxtDisplayBigTextLine(3, "Dark Value is %d",dark);
 wait1Msec(1000); // wait so you can press again

 //calculating the threshold
 total = light + dark;
 threshold = total / 2;
 return(threshold);

}//end threshold


task main()
{
  int value = 0;
  int threshold=0;
  //get threshold from function
  threshold = thresHold(value);
}//end main()
