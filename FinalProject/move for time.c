/*this function moves the robot forward for 10.5 seconds. until it reaches the 9th column*/
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


		//turn left
	//	setMotorSync(motorB,motorC,50,-50);
	//	wait1Msec(1000);

		//straight for 3 boxes
		setMotorSync(motorB,motorC,0,SPEED);
		wait1Msec(3500);

		//turn left
		//setMotorSync(motorB,motorC,-50,50);
		//wait1Msec(1000);

		//NOW SHOULD BE ON THE
		//turn righ
		setMotorSync(motorC,motorB,50,-50);
		wait1Msec(1000);


	//turn righ
		setMotorSync(motorC,motorB,-50,50);
		wait1Msec(1000);



}//end main
