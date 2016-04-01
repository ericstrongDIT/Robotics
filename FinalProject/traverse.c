#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     lightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)

#define POWER1 100
#define ROWS 9
#define COLS 7

int move1=1000;
int move9=2000;


//oddTrav() is based on the odd numbered Rows
int oddTurn(int turn)
{

	clearTimer(T1);
  while(time1[T1] <= move9)
  {
	  // setMotorSyncEncoder(nMotorOne, nMotorTwo, nTurnRatio, nEncoderCount, nSignedPower);
		setMotorSyncTime(left, right, 0, 1000, POWER1);
		wait1Msec(1000);

		//scan box color to file logic here

	}//end while
	wait1Msec(1000);

	// turns the robot left for over half a second. This makes it go left (all power to right)
	setMotorSyncTime(left, right, turn, 1000, 50);
	wait1Msec(590);

	//straight forward for 1 seconds
	clearTimer(T1);
  while(time1[T1] <= move1)
  {
	setMotorSyncTime(left, right, 0, 1000, POWER1);

	//scan box color to file logic here

	}//end while
	//turn left
		setMotorSyncTime(left, right, -100, 1000, 50);
		wait1Msec(590);
		return 0;

}//end oddTrav()

//evenTrav()
int evenTurn(int turn)
{

	clearTimer(T1);
  while(time1[T1] <= move9)
  {
	  // setMotorSyncEncoder(nMotorOne, nMotorTwo, nTurnRatio, nEncoderCount, nSignedPower);
		setMotorSyncTime(left, right, 0, 1000, POWER1);
		wait1Msec(1000);

		//scan box color to file logic here

	}//end while
	wait1Msec(1000);

	// turns the robot left for over half a second. This makes it go left (all power to right)
	setMotorSyncTime(left, right, turn, 1000, 50);
	wait1Msec(590);

	//straight forward for 1 seconds
	clearTimer(T1);
  while(time1[T1] <= move1)
  {
	setMotorSyncTime(left, right, 0, 1000, POWER1);

	//scan box color to file logic here

	}//end while
	//turn left
		setMotorSyncTime(left, right, turn, 1000, 50);
		wait1Msec(590);
		return 0;


}//end evenTrav()

//The following program is for the traverse logic
void traverse(int lines)
{
	int i = lines;


	int left = -100;
	int right = 100;
	/*
	while(SensorValue (touchSensor) == 0)
	{
		displayBigTextLine(3, "Press to begin...");
		wait1Msec(1000);
	}//end while*/

	displayBigTextLine(3, "mapping...");
	wait1Msec(1000);

	while(i < ROWS)
	{

		if(i % 2 == 1)
		{
			oddTurn(left);

		}//end if
		else if(i % 2 == 0)
		{
			evenTurn(right);


		}//end else
		i ++;
}//end while


}//end travers()

task main()
{
	int lines = 1;

	//traverse function
	traverse(lines);

}//end main()
