#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     lightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)

/*Fwrite the display of row col to a file along with the details of the box color*/

#define POWER1 100
#define ROWS 9
#define COLS 7

int move1=1000; //Change this value when you want to count x boxes
int move9=9000;


//oddTrav() is based on the odd numbered Rows
int oddTurn(int turn,int row)
{
	int col=0;

	clearTimer(T1);
  while(time1[T1] <= move9)
  {
  	displayBigTextLine(3, "row %d \nCol%d",row,col);
	  // setMotorSyncEncoder(nMotorOne, nMotorTwo, nTurnRatio, nEncoderCount, nSignedPower);
		setMotorSyncTime(left, right, 0, 1000, POWER1);
		wait1Msec(1000);
		col ++;

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
  displayBigTextLine(3, "row %d \nCol%d",row,col);
	setMotorSyncTime(left, right, 0, 1000, POWER1);
	row++;

	//scan box color to file logic here

	}//end while
	//turn left
		setMotorSyncTime(left, right, -100, 1000, 50);
		wait1Msec(590);
		return (row);

}//end oddTrav()

//evenTrav()
int evenTurn(int turn,int row)
{
	int col=0;

	clearTimer(T1);
  while(time1[T1] <= move9)
  {
  	displayBigTextLine(3, "row%d ,Col%d",row,col);
	  // setMotorSyncEncoder(nMotorOne, nMotorTwo, nTurnRatio, nEncoderCount, nSignedPower);
		setMotorSyncTime(left, right, 0, 1000, POWER1);
		wait1Msec(1000);
		col ++;

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
  displayBigTextLine(3, "row %d \nCol%d",row,col);
	setMotorSyncTime(left, right, 0, 1000, POWER1);
	row ++;

	//scan box color to file logic here

	}//end while
	//turn left
		setMotorSyncTime(left, right, turn, 1000, 50);
		wait1Msec(590);
		return (row);


}//end evenTrav()

//The following program is for the traverse logic
void traverse(int lines)
{
	int i = lines;
	static int rowCount=0;
	static int colCount=0;


	int left = -100;
	int right = 100;
	/*
	while(SensorValue (touchSensor) == 0)
	{
		displayBigTextLine(3, "Press to begin...");
		wait1Msec(1000);
	}//end while*/

	displayBigTextLine(3, "mapping...\nrow%d ,Col%d",rowCount,colCount);
	wait1Msec(1000);

	while(i < ROWS)
	{

		if(i % 2 == 1)
		{
			oddTurn(left,rowCount);

		}//end if
		else if(i % 2 == 0)
		{
			evenTurn(right,rowCount);


		}//end else
		i ++;
		rowCount ++;
}//end while


}//end travers()

task main()
{
	int lines = 1;

	//traverse function
	traverse(lines);

}//end main()
