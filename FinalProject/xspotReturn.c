/*this function moves the robot forward for 10.5 seconds. until it reaches the 9th column XSPOT FUNCTION RETURN*/
#define SPEED 100
#define TIME 10500

task main()
{
	clearTimer(T1);
  while(time1[T1] < TIME)
  {
  	setMotorSync(motorB,motorC,0,SPEED);
		wait1Msec(TIME);

	}//end while

	//turn right
	motor[motorB]= 50;
	motor[motorC]=-50;
	wait1Msec(500);

	//straight for 3 boxes
	setMotorSync(motorB,motorC,0,SPEED);
	wait1Msec(3500);



}//end main
