
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)
/*this function moves the robot forward for 10.5 seconds. until it reaches the 9th column XSPOT FUNCTION
REMEMBER CHANGE THE VALUE OF TIME TO SUIT THE SIZE OF THE GRID. 1sec per box may need to be adjusted
*/
#define POWER1 100

//global variables used to as timers per box
int move9 = 9000;
int move3 = 3000;
int move1 = 900;

// a flag is used from the main to determine what the logic does
void xspot(int turn, int flag)
{
	//This mkes roboot move forward over 9 boxes(ensuring the motors are in Sync to go straight at full power)
	clearTimer(T1);
  while(time1[T1] <= move9)
  {
	  // setMotorSyncEncoder(nMotorOne, nMotorTwo, nTurnRatio, nEncoderCount, nSignedPower);
		setMotorSyncTime(left, right, 0, 1000, POWER1);
		wait1Msec(1000);

		//scan box color to file logic here

	}//end while
	wait1Msec(1000);

	if(flag == 0)
{
	// turns the robot left for over half a second. This makes it go left (all power to right)
	setMotorSyncTime(left, right, turn, 1000, 50);
	wait1Msec(590);

	//straight forward for 3 seconds
	clearTimer(T1);
  while(time1[T1] <= move3)
  {
	setMotorSyncTime(left, right, 0, 1000, POWER1);

	//scan box color to file logic here

	}//end while

		//turns left leaving us on the Xspot mark to start the count
		setMotorSyncTime(left, right, turn, 1000, 50);
		wait1Msec(590);

}//end if
else
{

	//turns Right
	clearTimer(T1);
  while(time1[T1] <= move1)
  {
			setMotorSyncTime(left, right, turn, 1000, 50);
			wait1Msec(650);
	}

		//straight forward for 3 seconds
	clearTimer(T1);
  while(time1[T1] <= move3)
  {
	setMotorSyncTime(left, right, 0, 1000, POWER1);
	//scan box color to file

	}//end while

}//end else


}//end xspot()

task main()
{
	int left = -100;
	int right = 40;
	int flag = 0;

	//automatic threshold here

	//xspot
	xspot(left, flag);

	//traverse logic




	//xspot return
	wait1Msec(2000);
	flag = 1;
	xspot(right,flag);


}//end main
