#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     lightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     sonar,          sensorSONAR_Inch)
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//All of the Sensors the robot Uses

#define POWER1 40  //Set power for most of the grid
#define ROWS 7		//array Row
#define COLS 9		//array col

//global variables
//array used to map out the grid. All initialized to zero
int mapGrid[ROWS][COLS]={0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0};

int startingCol=1;	//used for the starting position
int boxTotal=0;			//counter for total boxes
int blackTotal=0;		//counter for black boxes
int whiteTotal=0;		//counter for white boxes
int finalROW =0;    //used to display final location
int finalCOL =0;		//used to display final object location on robot LCD

//Each variable is a counter value for the timers used to traverse the grid.
int move9i =10000;
int move9 = 25000;
int move06 = 5000;
int move03= 2000;
int move04 = 3000;
int move05 = 4000;
int move02 = 2000;
int move1 = 900; // moves for 1 second

//File names for the write to file part of phase 1 and phase 2
string filename = "T4_7_File1";
string filename2 = "T4_7_File2";

//FUNCTIONS
//write to file function takes the global array and uses this to look up each element to determine if the box is white or black
void part1(int rowReference)
{
	int finalMap[ROWS][COLS];
 	long fileHandle;
	string string1 =" White ,";
  int strlen1 = strlen(string1);
	string string2 = " Black, ";
  int strlen2 = strlen(string2);
  fileHandle = fileOpenWrite(filename);
	int i,j; //counters for the for loop

	for(i=0;i<ROWS;i++)
	{
	    for(j=0;j<COLS;j++)
	    {
	    	finalMap[i][j] = mapGrid[i][j]; //copying contents to a local array

		    if(finalMap[i][j]==1) //checking if the box is black
		    {
		    	 fileWriteData(fileHandle, string2, strlen2); //writing to the file (black)
		    }//end if
		    else
		    {
		   			fileWriteData(fileHandle, string1, strlen1); //writing to the file (white)
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

  //STARTING LOCATION
  string stringST = "Starting Point=";
  int strlenST = strlen(stringST);
  string stringR = rowReference;
  string stringC = startingCol;
  string comma = ",";

  fileWriteData(fileHandle, stringST, strlenST);
  fileWriteData(fileHandle, stringR, strlenNum);
  fileWriteData(fileHandle, comma, strlenNum);
  fileWriteData(fileHandle, stringC, strlenNum);

  //NUMBER OF ROWS AND COLS
  string stringN1 = "X";
  int strlenN1 = strlen(stringN1);
  string stringST1 = "ROWS=";
  int strlenST1 = strlen(stringST1);
  string stringR1 = i+1;			//index starts at 0, but humans read 1-n
  string stringST2 = "COLS=";
  int strlenST2 = strlen(stringST2);
  string stringC1 = j+1;		//index starts at 0

  fileWriteData(fileHandle, stringST1, strlenST1);
  fileWriteData(fileHandle, stringR1, strlenN1);
  fileWriteData(fileHandle, stringST2, strlenST2);
  fileWriteData(fileHandle, stringC1, strlenN1);


}//end part1

//write to file function for object Location
void part2(int C, int R)
{
	int i,j;
	int R1 = R+1;
	int C1= C+1;
	int finalMap[ROWS][COLS];
	long fileHandle;
	fileHandle = fileOpenWrite(filename2);

	//ITEM LOCATION
  string stringT = "ItemLocated at ";
  int strlenT = strlen(stringT);
  string stringR = R1+2;
  string stringC = C1;

  string stringN = "X";
  string comma = ",";
  int strlenNum = strlen(stringN);
  string stringBlack = "Box is Black";
  string stringWhite = "Box is White";
  int strlenNum1 = strlen(stringBlack);

  //to display on the robot LCD
  finalCOL = C1;
  finalROW = R1;

  fileWriteData(fileHandle, stringT, strlenT);
  fileWriteData(fileHandle, stringR, strlenNum);
  fileWriteData(fileHandle, comma, strlenNum);
  fileWriteData(fileHandle, stringC, strlenNum);

	//look up the array reference

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
    }	//end if
    else
    {
    	fileWriteData(fileHandle, stringWhite, strlenNum1);
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

//scanObject function used to scan for the object and locate its column
int scanObject(int objectMove)
{
	//int distanceToMaintain = 97; //value between 1-100
	int currentDistance = 0;
	int itemLocateCOL = 0;
	int RowCount=-1;  //because of the one extra, that way we dont miss row 0, col 0

   // Moves the Robot again to the top Grid
   if (objectMove == 3) // on row 3
   	{
   		forward(2.5,rotations,30);
 		}//end if move2

 	  if (objectMove == 4) // on row 4
   	{
   		 		forward(3.5,rotations,30);
 		}//end if move3

 		if (objectMove == 5) // on row 5
   	{
   		forward(4.5,rotations,30);
 		}//end if move4

  	else
  	{
  	 	searching();
  	}//end else

  //Moves forward half a box so the count can begin at 0
	forward(1,rotations,30);

	//Searching for oject
	while(RowCount <7) // wont allow the robot to go any more than 7 rows
	  {
			currentDistance = SensorValue[sonar];
			displayCenteredBigTextLine(3, "Dist: %d", currentDistance);

			if ((currentDistance) >=100)
			{
			currentDistance = SensorValue[sonar];
			displayCenteredBigTextLine(3, "Reading: %d", currentDistance);
				searching();
				backward(1,rotations,30);
				wait1Msec(3000);
				RowCount ++; //row counter
			}//end if
			//if object is detected
			else
			{
			currentDistance = SensorValue[sonar];
			displayCenteredBigTextLine(3, "found!: %d", currentDistance);
				object();
				motor[left] = 0;
				motor[right] = 0;

				turnRight(0.74,rotations,50);
				while(SensorValue(touchSensor)==0)
				{
					forward(1,rotations,30);
					wait1Msec(2000);
					itemLocateCOL ++;

				}//end while

					object();
							motor[left] = 0;
							motor[right] = 0;
							wait1Msec(3000);
							part2(itemLocateCOL,RowCount);

				//itemLocateCOL = currentDistance / 8; // because the robot is already on Col 1, there are only 8 columns to calculate
				//itemLocateCOL = itemLocateCOL +1;
			wait1Msec(3000);
			return 0;

		}//end else if
		sleep(50);
	}//end while
}//end scanObject

//This function scans the box, prompts a sound a writes to a file
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

//oddTurn() is based on the odd numbered Rows. and does a specific behaviour of turns
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
}//end oddTurn()

//evenTurn()
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
}//end evenTurn()

//The following program is for the traverse logic.
void traverse(int lines,int threshold)
{
	//int i = lines;
	int rowCount=0;
	int colCount=0;
	int left = -100;
	int right = 100;

	displayBigTextLine(3, "mapping...\nrow%d ,Col%d",rowCount,colCount);
	wait1Msec(1000);

	/*if the line is odd do something, if its even do something else. and keep count of all the lines. Lines will
	correspond to the number of Rows*/
	while(lines <= ROWS)
	{

		if(lines % 2 == 1)
		{
			oddTurn(left,rowCount,threshold);
		}//end if

		else if(lines % 2 == 0)
			{
			evenTurn(right,rowCount,threshold);
			}//end else
		lines ++;
		rowCount ++;
	}//end while
}//end traverse()

//XSPOT1
int xspot1(int turn, int flag)
{
	if(flag == 0) //used to determine if this is the xspot return
	{

		forward(10.5,rotations,30);
		wait1Msec(1000);
		// turns the robot left for over half a second. This makes it go left (all power to right)
		turnRight(1.35,rotations,50);
		sleep(1500);
	}//end if

	//flag for xspot Return
	else if(flag == 1)
	    {
	        // Turns right
	    		turnRight(0.7,rotations,50);
	        wait1Msec(500);

	        //straight forward for 7 boxes
	        wait1Msec(1000);
	        forward(6,rotations,30);
					wait1Msec(1000);
	        return 1; // determins what row we are on
    }//end else if
}//End xspot1()

/*
int xspot3(int turn, int flag)
{
	int objectMove;
	if(flag == 0)
	{
    clearTimer(T1);

    /* Moves forward over the 9 boxes
    while(time1[T1] <= move9i)
    {
		setMotorSyncTime(left, right, 0, 1000, POWER1);

		wait1Msec(1100);
		}//end while

		forward(10.5,rotations,30);

		wait1Msec(1000);

		// turns the robot left for over half a second. This makes it go left (all power to right)

		turnLeft(0.7,rotations,50);
		sleep(1500);

		 clearTimer(T1);

        while(time1[T1] <= move04) //move02 move04 move05*********************
        {
            setMotorSyncTime(left, right, 0, 1000, POWER1);
            //scan box color to file

        }//end while

  turnLeft(0.7,rotations,50);
	sleep(1500);

	}//end if


	if(flag == 1)

    {
        //turns Right
    		turnRight(0.7,rotations,50);
				sleep(1500);


		   //CHANGE OUT THE FOLLOWING VARIABLES DEPENDING ON THE MAP.
          //(map1 does not use this return. refere to xspotReturn)

        clearTimer(T1);
        while(time1[T1] <= move03) //move04  move03 move1 **************
        {
            setMotorSyncTime(left, right, 0, 1000, POWER1);

        }//end while *************************IMPORTANT
        objectMove = 4;
        return(objectMove); // return 3,4,5 is to be used to make the robot move again to the final position
       	//to locate the object
    }//end if
}//End xspot()
*/

task main()
{
	int left = -100; //used to gauge the turns(left)
	int flag = 0;		//used to flag a behaiour
	int lines = 1;	//line count, starting at 1
	int value = 0;	//value is used for the threshold
  int threshold=0; // stores the threshold returned from the function
  int objectMove=0;//

  //get threshold from function
  threshold = thresHold(value);
  wait1Msec(3000); // to place the robot on the appropriate square

	//xspot logic
  activate(); // says activate when going to xspot
	//xspot1(left, flag);  //this starts on map (1,1)
	//xspot3(left,flag);

	//traverse function
//	traverse(lines,threshold);

	//xspot return. This will change to whatever map(1-4)
	wait1Msec(3000);
	flag = 1; //use the flag to indicate its the return

	//The xspot return functions
	//objectMove=xspot1(left, flag);
	//objectMove = xspot3(left,flag);

	//Pass the global array over and write to file.
	//part1(objectMove);

	//display answers on LCD
  displayBigTextLine(3, "Total Boxes %d",boxTotal);
  wait1Msec(2000);
  displayBigTextLine(3, "white Boxes %d",whiteTotal);
  wait1Msec(2000);
  displayBigTextLine(3, "Black Boxes %d",blackTotal);
  wait1Msec(2000);
	cheering(); //end phase 1

	//Logic to move the robot to top grid for scan object
	while(SensorValue(touchSensor) == 0)
 	{
   displayBigTextLine(3, "Place Object.....");
 	}//end while

	//Logic for locating object here
	scanObject(objectMove);

	//Lab complete!
	displayBigTextLine(3, "Object Found!");
  wait1Msec(2000);
  displayBigTextLine(3, "R:%d ,C:%d",finalROW,finalCOL);
  wait1Msec(2000);
  displayBigTextLine(3, "Total Boxes %d",boxTotal);
  wait1Msec(2000);
  displayBigTextLine(3, "white Boxes %d",whiteTotal);
  wait1Msec(2000);
  displayBigTextLine(3, "Black Boxes %d",blackTotal);
  wait1Msec(2000);
	cheering();
}//end main
