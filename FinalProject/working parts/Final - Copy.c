#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     lightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)
/*this function moves the robot forward for 10.5 seconds. until it reaches the 9th column XSPOT FUNCTION
REMEMBER CHANGE THE VALUE OF TIME TO SUIT THE SIZE OF THE GRID. 1sec per box may need to be adjusted
*/
#define POWER1 100
#define ROWS 9
#define COLS 7

//global variables used to as timers per box
int move9 = 9000;
int move3 = 3000;
int move1 = 900;
/*The following are Sound Files to distinguish what colour the box is*/
void white()
{
	setSoundVolume(100);
	playSoundFile("White");
	sleep(1000);

}

void black()
{
	setSoundVolume(100);
	playSoundFile("Black");
	sleep(1000);

}

void scanBox(int threshold)
{
	if(SensorValue(lightSensor) < threshold)
	{
		black();
		//write to file Logic here
	}//end while
	else
	{
		white();
		//write to file logic here
	}//end else


}//end scanBox

/*Calculating the automatic threshold for light sensor*/
int thresHold(int threshold)
{
  int light;
  int dark;
  int total;

 while(SensorValue(touchSensor) == 0)
 {
   displayBigTextLine(3, "read light value");
 }//end while

 //reading light value
 light = SensorValue(lightSensor);
 displayBigTextLine(3, "Light is %d",light);
 wait1Msec(1000); // wait so you can press again

 while(SensorValue(touchSensor) == 0)
 {
    displayBigTextLine(3, "read dark value");
 }//end while
 //reading dark value

 dark = SensorValue(lightSensor);
 displayBigTextLine(3, "Dark is %d",dark);
 wait1Msec(1000); // wait so you can press again

 //calculating the threshold
 total = light + dark;
 threshold = total / 2;
 return(threshold);

}//end threshold

/*Fwrite the display of row col to a file along with the details of the box color*/
//oddTrav() is based on the odd numbered Rows
int oddTurn(int turn,int row, int threshold)
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
		scanBox(threshold);

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
int evenTurn(int turn,int row,int threshold)
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
		scanBox(threshold);

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
void traverse(int lines,int threshold)
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
			oddTurn(left,rowCount,threshold);

		}//end if
		else if(i % 2 == 0)
		{
			evenTurn(right,rowCount,threshold);


		}//end else
		i ++;
		rowCount ++;
}//end while


}//end travers()


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
	int lines = 1;
	int value = 0;
  int threshold=0;


  //get threshold from function
  threshold = thresHold(value);

	//xspot
	xspot(left, flag);


	//traverse function
	traverse(lines,threshold);


	//xspot return
	wait1Msec(2000);
	flag = 1;
	xspot(right,flag);


}//end main
