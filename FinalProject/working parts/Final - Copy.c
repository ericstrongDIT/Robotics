#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     lightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)
//The format for the sensors. Keep note of the numbering

//REMEMBER CHANGE THE VALUE OF TIME TO SUIT THE SIZE OF THE GRID. 1sec = 1box may need to be adjusted
#define POWER1 100
#define ROWS 9
#define COLS 7

//global variables used to as timers per box
int move9 = 9000; //moves for 9 seconds
int move3 = 3000; // moves for 3 seconds
int move1 = 900; // moves for 1 second

/*The following are Sound Files to distinguish what colour the box is and other prompts*/
void cheering()
{
	setSoundVolume(100);
	playSoundFile("Cheering");
	sleep(1000);
}//end cheering()
void detect()
{
	setSoundVolume(100);
	playSoundFile("Laser");
	sleep(1000);
}//end detect()
void activate()
{
	setSoundVolume(100);
	playSoundFile("Activate");
	sleep(1000);
}//end activate()
void white()
{
	setSoundVolume(100);
	playSoundFile("White");
	sleep(1000);
}//end white()

void black()
{
	setSoundVolume(100);
	playSoundFile("Black");
	sleep(1000);
}//end black()

//This function scans the box, prompts a sound a writes to a file
//Fwrite the display of row col to a file along with the details of the box color
void scanBox(int threshold)
{
	if(SensorValue(lightSensor) < threshold)
	{
		black();
		//write to file Logic here. Place its array reference and X

	}//end while
	else
	{
		white();
		//write to file logic here. Place its array reference and O

	}//end else

}//end scanBox

/*Calculating the automatic threshold for light sensor*/
int thresHold(int threshold)
{
  int light; //stores light value
  int dark; // stores dark value
  int total; // stores sum of both

 while(SensorValue(touchSensor) == 0)
 {
   displayBigTextLine(3, "read light value");
 }//end while

 //reading light value
 light = SensorValue(lightSensor);
 displayBigTextLine(3, "Light=%d",light);
 wait1Msec(1000); // wait so you can press again

 while(SensorValue(touchSensor) == 0)
 {
    displayBigTextLine(3, "read dark value");
 }//end while
 //reading dark value

 dark = SensorValue(lightSensor);
 displayBigTextLine(3, "Dark = %d",dark);
 wait1Msec(1000); // wait so you can press again

 //calculating the threshold
 total = light + dark;
 threshold = total / 2;
 return(threshold);
}//end threshold

//oddTrav() is based on the odd numbered Rows. and does a specific behaviour of turns
int oddTurn(int turn,int row, int threshold)
{
	int col=8; // starts at 8 on Odd as the robot traverses backwards on odd lines
	clearTimer(T1);
  while(time1[T1] <= move9)
  {
  	displayBigTextLine(3, "row %d \nCol%d",row,col);
	  // setMotorSyncEncoder(nMotorOne, nMotorTwo, nTurnRatio, nEncoderCount, nSignedPower);
		setMotorSyncTime(left, right, 0, 1000, POWER1);
		detect(); // sound file
		wait1Msec(1000);
		col --;

		//scan box color to file
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
	row++; // increments a row at each row change

	}//end while
	//turn left
		setMotorSyncTime(left, right, -100, 1000, 50);
		wait1Msec(590);
		return (row);

}//end oddTrav()

//evenTrav()
int evenTurn(int turn,int row,int threshold)
{
	int col=0; // This count starts at 0 as on even lines the robot reads from right to left

	clearTimer(T1);
  while(time1[T1] <= move9)
  {
  	displayBigTextLine(3, "row%d ,Col%d",row,col);
	  // setMotorSyncEncoder(nMotorOne, nMotorTwo, nTurnRatio, nEncoderCount, nSignedPower);
		setMotorSyncTime(left, right, 0, 1000, POWER1);
		detect();
		wait1Msec(1000);
		col++;

		//scan box color to file
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

	}//end while
	//turn left
		setMotorSyncTime(left, right, turn, 1000, 50);
		wait1Msec(590);
		return (row);
}//end evenTrav()

//The following program is for the traverse logic.
void traverse(int lines,int threshold)
{
	int i = lines;
	static int rowCount=0;
	static int colCount=0;


	int left = -100;
	int right = 100;

	displayBigTextLine(3, "mapping...\nrow%d ,Col%d",rowCount,colCount);
	wait1Msec(1000);

	/*if the line is odd do something, if its even do something else. and keep count of all the lines. Lines will
	correspond to the number of Rows*/
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

/*the Following function will move from the starting postion to the Xspot, where counting and traversion begins*/
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
	// a flag is used from the main to determine what the logic does
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
	int left = -100; //used to gauge the turns(left)
	int right = 40;  //used to gauge the turns(Right)
	int flag = 0;		//used to flag a behaiour
	int lines = 1;	//line count, starting at 1
	int value = 0;	//value is used for the threshold
  int threshold=0; // stores the threshold returned from the function

  //get threshold from function
  threshold = thresHold(value);
  wait1Msec(3000); // to place the robot on the appropriate square

	//xspot
  activate(); // says activate when going to xspot
	xspot(left, flag);

	//traverse function
	traverse(lines,threshold);

	//xspot return
	wait1Msec(2000);
	flag = 1;
	xspot(right,flag);

	//Logic for locating object here
	//function

	//Ram object logic here
	//function

	//Lab complete!
	cheering();
}//end main
