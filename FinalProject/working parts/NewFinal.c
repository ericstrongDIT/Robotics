#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     lightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     sonar,    sensorSONAR_Inch)
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)
//The format for the sensors. Keep note of the numbering

//REMEMBER CHANGE THE VALUE OF TIME TO SUIT THE SIZE OF THE GRID. 1sec = 1box may need to be adjusted
#define POWER1 40
#define POWER2 80
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

int boxTotal=0;
int blackTotal=0;
int whiteTotal=0;

int move9i =10000; //moves for 9 boxes (25000 / 9 = 2.77per box including pause for 1 second)
int move9 = 25000;
int move06 = 5000;
int move07 = 6000;
int move03= 8300;
int move04 = 11100;
int move3 = 3000; // moves for 3 seconds
int move02 = 5550;
int move1 = 900; // moves for 1 second

int *ptr = &mapGrid;
string filename = "EricCraigPart1";
string filename2 = "EricCraigPart2";

//write to file function
void part1(int *p)
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

  string stringN = "XX.";
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

}//end part1

/*write to file function
void writeFile(int *ptr)
{

	string fileName = "GRIDMAPPING1";
	long filehandle;

	string finaloutput = "\n black boxes is %d";
	string info="White ,";
	string newLine = "\n";
	int strlen1 = strlen(newLine); // do the same for all rows, (line 1-7)
	int strlen2 = strlen(info);
	int strlen3 = strlen(finaloutput);
	int i,j;

	//char *bTotal= "\ntotal black boxes is %d";
	//char *wTotal= "\ntotal white boxes is %d";
	//char *ATotal= "\ntotal boxes is %d";
	char *white = "0 ,";
	char *black = "1 ,";
	char *spac = "\n";
	filehandle = fileOpenWrite(fileName);

	for (i = 0; i <  ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			if(mapGrid[i][j]==0)
			{
				fileWriteData(filehandle,white,strlen2);
			}//end if white
			if(mapGrid[i][j]==1)
			{
				fileWriteData(filehandle,black,strlen2);
			}//end if black
				//fileWriteData(filehandle,spac,strlen1);

		}//end inner for

	}//end outter for

	//wrinting the project requirments to the file

	//fileWriteData(filehandle,bTotal,strlen3);
	//fileWriteData(filehandle,wTotal,strlen3);
	//fileWriteData(filehandle,ATotal,strlen3);


fileClose(filehandle);
}//end writeFile()
*/


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
void scanObject()
{
	int distanceToMaintain = 90;

	int currentDistance = 0;
	 clearTimer(T1); // timer for each Row traversed
   // Moves forward over the 9 boxes

	while(true)
	  {

			currentDistance = SensorValue[sonar];

			displayCenteredBigTextLine(4, "Dist: %d", currentDistance);

			if ((distanceToMaintain - currentDistance) < 1)
			{
				searching();
				motor[left] = -30;
				motor[right] = -30;
			}//end if

			else if((distanceToMaintain - currentDistance) >0)
			{
				object();
				motor[left] = 0;
				motor[right] = 0;

				//take the cell reference
				//NEW PART2 in HERE!
				wait1Msec(5000);
	}//end while

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
			turnLeft(0.72,rotations,50);
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
	  turnLeft(0.72,rotations,50);
		sleep(1500);

			return (row);
				wait1Msec(625);

				//correct position here
				//PArt2 fixer


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

		//correct position

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
void xspot1(int turn, int flag)
{
	if(flag == 0)
	{
    clearTimer(T1);

    // Moves forward over the 9 boxes
    while(time1[T1] <= move9i)
    {
		setMotorSyncTime(left, right, 0, 1000, POWER1);

		wait1Msec(1100);
		}//end while
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
	        //setMotorSyncTime(left, right, turn, 900, -30);
	    		turnRight(0.7,rotations,50);
	        wait1Msec(500);

	        //straight forward for 7 boxes
	        wait1Msec(1000);
	        clearTimer(T1);
	        while(time1[T1] <= move06) //This will change based on where the starting position is****
	        {
	            setMotorSyncTime(left, right, 0, 1000, POWER1);
	        }//end while
    }//end if
}//End xspot1()

/*void xspot3(int turn, int flag)
{

	if(flag == 1)

    {
        //turns Right
        clearTimer(T1);
        while(time1[T1] <= move1)
        {
			setMotorSyncTime(left, right, turn, 1000, 50);
			wait1Msec(650);
        }

		   //CHANGE OUT THE FOLLOWING VARIABLES DEPENDING ON THE MAP.
          //(map1 does not use this return. refere to xspotReturn)

        clearTimer(T1);
        while(time1[T1] <= move02) //move2 move03 move4
        {
            setMotorSyncTime(left, right, 0, 1000, POWER1);
            //scan box color to file

        }//end while

    }//end if

}//End xspot()
*/




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

	//xspot logic pick a map (xspot1 is our map , xspot 3 is maps 2 3 and 4 **swap out the variable)
  activate(); // says activate when going to xspot
	xspot1(left, flag);  //this starts on map (1,1)
	//xspot3(left,flag);

	//traverse function
	traverse(lines,threshold);

	//Pass the global array over and write to file.
  part1(ptr);

	//xspot return. This will change to whatever map(1-4)
	wait1Msec(3000);
	flag = 1; //use the flag to indicate its the return
	//The xspot return functions

	xspot1(left, flag);
	//xspot3(left,flag);

	//display answers on LCD
  displayBigTextLine(3, "Total Boxes %d",boxTotal);
  wait1Msec(2000);
  displayBigTextLine(3, "white Boxes %d",whiteTotal);
  wait1Msec(2000);
  displayBigTextLine(3, "Black Boxes %d",blackTotal);
  wait1Msec(2000);
	cheering();

	//Logic for locating object here
	scanObject();

	//Lab complete!
  displayBigTextLine(3, "Total Boxes %d",boxTotal);
  wait1Msec(2000);
  displayBigTextLine(3, "white Boxes %d",whiteTotal);
  wait1Msec(2000);
  displayBigTextLine(3, "Black Boxes %d",blackTotal);
  wait1Msec(2000);
	cheering();

}//end main
