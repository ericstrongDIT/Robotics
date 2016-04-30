#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     lightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     sonar,    sensorSONAR_Inch)
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)
//The format for the sensors. Keep note of the numbering

//REMEMBER CHANGE THE VALUE OF TIME TO SUIT THE SIZE OF THE GRID. 1sec = 1box may need to be adjusted
#define POWER1 40
#define ROWS 7
#define COLS 9

//global variables
int mapGrid[ROWS][COLS]={0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0};
int startingCol=1;
int boxTotal=0;
int blackTotal=0;
int whiteTotal=0;
int move9 = 25000;
int move1 = 900; // moves for 1 second

string filename = "T4_7_File1";
string filename2 = "T4_7_File2";

//write to file function
void part1(int rowReference)
{
	int finalMap[ROWS][COLS];

 	long fileHandle;

  string string1 =" White ,";
  int strlen1 = strlen(string1);

  string string2 = " Black, ";
  int strlen2 = strlen(string2);

  fileHandle = fileOpenWrite(filename);

	int i,j;

for(i=0;i<ROWS;i++)
{
    for(j=0;j<COLS;j++)
    {

    finalMap[i][j] = mapGrid[i][j];
    if(finalMap[i][j]==1)
    {

    	 fileWriteData(fileHandle, string2, strlen2);

    }//end if
    else
    {
   			  fileWriteData(fileHandle, string1, strlen1);
    }//end else

    }//end inner for
}//end outter for

  	//WHITE BOX TOTAL
  string stringW = "Total White Boxes=";
  int strlenW = strlen(stringW);
  string stringWn = whiteTotal;

  string stringN = "XX";
  int strlenNum = strlen(stringN);

  fileWriteData(fileHandle, stringW, strlenW);
  fileWriteData(fileHandle, stringWn, strlenNum);

  	//BLACK BOX TOTAL
  string stringB = "Total Black Boxes=";
  int strlenB = strlen(stringB);
  string stringBn = blackTotal;

  fileWriteData(fileHandle, stringB, strlenB);
  fileWriteData(fileHandle, stringBn, strlenNum);

    	//TOTAL BOX TOTAL
  string stringT = "Total Boxes=";
  int strlenT = strlen(stringT);
  string stringTn = boxTotal;

  fileWriteData(fileHandle, stringT, strlenT);
  fileWriteData(fileHandle, stringTn, strlenNum);

  	//Starting Location
  string stringST = "Starting Point=";
  int strlenST = strlen(stringST);
  string stringR = rowReference;
  string stringC = startingCol;
  string comma = ",";

  fileWriteData(fileHandle, stringST, strlenST);
  fileWriteData(fileHandle, stringR, strlenNum);
  fileWriteData(fileHandle, comma, strlenNum);
  fileWriteData(fileHandle, stringC, strlenNum);

}//end part1

//write to file function for object Location
void part2(int C, int R)
{
	int i,j;
	int finalMap[ROWS][COLS];

	long fileHandle;
	fileHandle = fileOpenWrite(filename2);

	  	//ITEM LOCATION
  string stringT = "ItemLocated at ";
  int strlenT = strlen(stringT);
  string stringR = R;
  string stringC = C;

  string stringN = "X";
  string comma = ",";
  int strlenNum = strlen(stringN);
  string stringBlack = "Box is Black";
  string stringWhite = "Box is White";
  int strlenNum1 = strlen(stringBlack);

  fileWriteData(fileHandle, stringT, strlenT);
  fileWriteData(fileHandle, stringR, strlenNum);
  fileWriteData(fileHandle, comma, strlenNum);
  fileWriteData(fileHandle, stringC, strlenNum);

	//look up the array reference
	//Remember to subtract 1 from each value as the values are in Human form not array form
		for(i=0;i<ROWS;i++)
{
    for(j=0;j<COLS;j++)
    {

    finalMap[R][C] = mapGrid[R][C];

    }//end inner for
}//end outter for

	if(finalMap[R][C]==1)
    {

    	 fileWriteData(fileHandle, stringBlack, strlenNum1);

			//break;
    }	//end if
    else
    {
   			  fileWriteData(fileHandle, stringWhite, strlenNum1);
   	 //break;
    }//end else
}//end part2

/*The following are Sound Files to distinguish what colour the box is and other prompts*/
void cheering()
{
	setSoundVolume(100);
	playSoundFile("Cheering");
	sleep(1000);
}//end cheering()

void searching()
{
	setSoundVolume(100);
	playSoundFile("Searching");
	sleep(1000);
}//end cheering()

void object()
{
	setSoundVolume(100);
	playSoundFile("Object");
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
	whiteTotal++;
	sleep(1000);
}//end white()

void black()
{
	setSoundVolume(100);
	playSoundFile("Black");
	blackTotal ++;
	sleep(1000);
}//end black()

//scanObject function ................
int scanObject(int objectMove)
{
	int distanceToMaintain = 90;
	int currentDistance = 0;
	int itemLocateCOL = 0;
	clearTimer(T1); // timer for each Row traversed
	//int RowCount = objectMove; // object move value is also the Row reference
	int RowCount=-1;  //because of the one extra, that way we dont miss row 0, col 0

   // Moves the Robot again to the top Grid
   if (objectMove == 3)
   {
   		forward(2.5,rotations,30);
 	}//end if move2

 	   if (objectMove == 4)
   	{
   		 		forward(3.5,rotations,30);


 		}//end if move3

 		   if (objectMove == 5)
   	{
   		forward(4.5,rotations,30);
 		}//end if move4

  else {
  	 searching();

  		}
  	//THE EXTRA ONE FORWARD!!!!
		clearTimer(T1);
	  forward(1,rotations,30);

	//Searching for oject
	while(RowCount <8)
	  {
			currentDistance = SensorValue[sonar];
			displayCenteredBigTextLine(4, "Dist: %d", currentDistance);

			if ((distanceToMaintain - currentDistance) < 1)
			{
				searching();

				//setMotorSyncTime(left, right, 0, 1000, -POWER1);
				forward(1,rotations,-30);
				wait1Msec(3000);
				RowCount ++;
			}//end if

			else if((distanceToMaintain - currentDistance) >0)
			{
				object();
				motor[left] = 0;
				motor[right] = 0;

				itemLocateCOL = currentDistance / 8; // because the robot is already on Col 1, there are only 8 columns to calculate
				itemLocateCOL = itemLocateCOL +1;
				//take the cell reference and print to file Final part
				part2(itemLocateCOL,RowCount);
				wait1Msec(3000);
				return 0;

		}//end else if

		sleep(50);
	}//end while

}//end scanObject
//This function scans the box, prompts a sound a writes to a file
//Fwrite the display of row col to a file along with the details of the box color
void scanBox(int threshold, int r, int c)
{
	if(SensorValue(lightSensor) < threshold) //value will get a 1
	{
		black();
		//write to file Logic here. Place its array reference and 1

		mapGrid[r][c]=1;

	}//end if
	else if(SensorValue(lightSensor) > threshold)
	{
		white();
		mapGrid[r][c]=0;

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

	int col=9; // starts at 8 on Odd as the robot traverses backwards on odd lines
	int r,c;
	r=row+1;
	c=col;
	static int lineCount = 0;

	lineCount ++;
	//This line stops the robot from making a turn at the very last line. This is so it can return to the starting position.
	if(lineCount == 4)
	{
				clearTimer(T1);
	  while(time1[T1] <= move9)
	  {
	  	displayBigTextLine(3, "row %d \nCol%d",r,c);

		  // setMotorSyncEncoder(nMotorOne, nMotorTwo, nTurnRatio, nEncoderCount, nSignedPower);
			setMotorSyncTime(left, right, 0, 1000, POWER1);

			detect(); // sound file
			boxTotal ++;
			wait1Msec(1000);
			c--;
			col --;

			//scan box color
			scanBox(threshold,row,col);

		}//end while
		wait1Msec(1000);
		}//Final Line count

	else{
		clearTimer(T1);
	  while(time1[T1] <= move9)
	  {
	  	displayBigTextLine(3, "row %d \nCol%d",r,c);

		  // setMotorSyncEncoder(nMotorOne, nMotorTwo, nTurnRatio, nEncoderCount, nSignedPower);
			setMotorSyncTime(left, right, 0, 1000, POWER1);
			detect(); // sound file
			boxTotal ++;
			wait1Msec(1000);
			c--;
			col --;

			//scan box color
			scanBox(threshold,row,col);

		}//end while
		wait1Msec(1000);

		//THE EXTRA ONE FORWARD!!!!
		clearTimer(T1);
	  while(time1[T1] <= move1)
	  {

		setMotorSyncTime(left, right, 0, 1000, POWER1);

		}//end while

		// turns the robot left for over half a second. This makes it go left (all power to right)
			turnLeft(0.74,rotations,50);
		sleep(1500);

		//straight forward for 1 seconds
		clearTimer(T1);
	  while(time1[T1] <= move1)
	  {

		setMotorSyncTime(right, left, 0, 1000, POWER1);
		r++;
		row++; // increments a row at each row change

		}//end while

		displayBigTextLine(3, "Total Boxes %d",boxTotal);

	  displayBigTextLine(3, "white Boxes %d",whiteTotal);

	  displayBigTextLine(3, "Black Boxes %d",blackTotal);

	  	//Turn to the Left
	  turnLeft(0.74,rotations,50);
		sleep(1500);

			return(row);
				wait1Msec(625);

	}//end else
}//end oddTrav()

//evenTrav()
int evenTurn(int turn,int row,int threshold)
{
	int col=-1; // This count starts at 0 as on even lines the robot reads from right to left

	clearTimer(T1);
	int r,c;
	r=row+1;
	c=col +2;
  while(time1[T1] <= move9)
  {
  	displayBigTextLine(3, "row%d ,Col%d",r,c);
	  // setMotorSyncEncoder(nMotorOne, nMotorTwo, nTurnRatio, nEncoderCount, nSignedPower);
		setMotorSyncTime(left, right, 0, 1000, POWER1);
		detect();
		boxTotal ++;
		wait1Msec(1000);
		c++;
		col++;

		//scan box color
		scanBox(threshold,row,col);

	}//end while
	wait1Msec(1000);

	//THE EXTRA ONE FORWARD!!!!
	clearTimer(T1);
  while(time1[T1] <= move1)
  {

	setMotorSyncTime(left, right, 0, 1000, POWER1);

	}//end while
	//turn right
	turnRight(0.7,rotations,50);
	sleep(1500);

	//straight forward for 1 seconds
	clearTimer(T1);
  while(time1[T1] <= move1)
  {
  //displayBigTextLine(3, "row %d \nCol%d",row,col);
	setMotorSyncTime(left, right, 0, 1000, POWER1);
	r++;
	row ++;

	}//end while
	//turn Right
	turnRight(0.7,rotations,50);
	sleep(1500);

	return (row);
	wait1Msec(1000);

}//end evenTrav()

//The following program is for the traverse logic.
void traverse(int lines,int threshold)
{
	int i = lines;
	int rowCount=0;
	int colCount=0;

	int left = -100;
	int right = 100;

	displayBigTextLine(3, "mapping...\nrow%d ,Col%d",rowCount,colCount);
	wait1Msec(1000);

	/*if the line is odd do something, if its even do something else. and keep count of all the lines. Lines will
	correspond to the number of Rows*/
	while(i <= ROWS)
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

//XSPOT1
int xspot1(int turn, int flag)
{

	if(flag == 0)
	{

		forward(10.5,rotations,30);
		wait1Msec(1000);
		//do a 180 turn
		// turns the robot left for over half a second. This makes it go left (all power to right)

	turnRight(1.35,rotations,50);
	sleep(1500);

	}

		//flag for xspot Return

	else if(flag == 1)
	    {
	        // Turns left
	    		turnRight(0.7,rotations,50);
	        wait1Msec(500);

	        //straight forward for 7 boxes
	        wait1Msec(1000);
	        forward(6,rotations,30);
					wait1Msec(1000);

	        return 1;

    }//end if
}//End xspot1()

task main()
{
	int left = -100; //used to gauge the turns(left)
	//int right = 40;  //used to gauge the turns(Right)
	int flag = 0;		//used to flag a behaiour
	int lines = 1;	//line count, starting at 1
	int value = 0;	//value is used for the threshold
  int threshold=0; // stores the threshold returned from the function
  int objectMove=0;


  //get threshold from function
  threshold = thresHold(value);
  wait1Msec(3000); // to place the robot on the appropriate square

	//xspot logic pick a map (xspot1 is our map , xspot 3 is maps 2 3 and 4 **swap out the variable)
  activate(); // says activate when going to xspot
	xspot1(left, flag);  //this starts on map (1,1)


	//traverse function
	traverse(lines,threshold);

	//xspot return. This will change to whatever map(1-4)
	wait1Msec(3000);
	flag = 1; //use the flag to indicate its the return

	//The xspot return functions
	objectMove=xspot1(left, flag);


	//Pass the global array over and write to file.
	part1(objectMove);

	//display answers on LCD
  displayBigTextLine(3, "Total Boxes %d",boxTotal);
  wait1Msec(2000);
  displayBigTextLine(3, "white Boxes %d",whiteTotal);
  wait1Msec(2000);
  displayBigTextLine(3, "Black Boxes %d",blackTotal);
  wait1Msec(2000);
	cheering();

	//Logic to move the robot to top grid for scan object
	while(SensorValue(touchSensor) == 0)
 {
   displayBigTextLine(3, "Place Object.....");
 }//end while

	//Logic for locating object here
	scanObject(objectMove);

	//Lab complete!
  wait1Msec(2000);
  displayBigTextLine(3, "Total Boxes %d",boxTotal);
  wait1Msec(2000);
  displayBigTextLine(3, "white Boxes %d",whiteTotal);
  wait1Msec(2000);
  displayBigTextLine(3, "Black Boxes %d",blackTotal);
  wait1Msec(2000);
	cheering();
}//end main
