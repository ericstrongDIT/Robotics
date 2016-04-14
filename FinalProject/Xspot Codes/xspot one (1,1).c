/* Xspot one code
    Starts on (1,1)
*/
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)

#define POWER1 40
#define POWER2 80

int move9 = 2500;
int move0 = 0;
int move1 = 900;

void xspot1(int turn, int flag)
{
    clearTimer(T1);

    // Moves forward over the 9 boxes
    while(time1[T1] <= move9)
    {
		setMotorSyncTime(left, right, 0, 1000, POWER1);
		wait1Msec(1000);
		}//end while

		wait1Msec(1000);
		//do a 180 turn
		// turns the robot left for over half a second. This makes it go left (all power to right)
		setMotorSyncTime(left, right, turn, 1000, 50);
		wait1Msec(1000);

		//flag for xspot Return

		if(flag == 1)
	    {
	        // Turns left
	        setMotorSyncTime(left, right, turn, 1000, 50);
	        wait1Msec(500);

	        //straight forward for 9 boxes
	        clearTimer(T1);
	        while(time1[T1] <= move9)
	        {
	            setMotorSyncTime(left, right, 0, 1000, POWER1);
	        }//end while
    }//end if
}//End xspot()

task main()
{
	int left = -100;
	int right = 40;
	int flag = 0;

	//xspot
	xspot1(left, flag);

	//enter other code here


	//xspot return
	wait1Msec(2000);
	flag = 1;
	xspot1(right,flag);


}//end main
