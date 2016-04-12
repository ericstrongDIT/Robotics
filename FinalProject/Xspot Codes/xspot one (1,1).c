/* Xspot one code 
    Starts on (1,1)
*/

#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)

#define POWER1 100

int move9 = 9000;
int move0 = 0;
int move1 = 900;

void xspot(int turn, int flag)
{
    clearTimer(T1); 
    
    // Moves forward over the 9 boxes
    while(time1[T1] <= move9)
    {
		setMotorSyncTime(left, right, 0, 1000, POWER1);
		wait1Msec(1000);

	}//end while
    
	wait1Msec(1000);

	if(flag == 0)
    {
        //Turns left
        setMotorSyncTime(left, right, turn, 1000, 50);
        wait1Msec(590);

        //straight forward for 0 seconds
        clearTimer(T1);
        
        while(time1[T1] <= move0)
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
    
}//End xspot()

task main()
{
	int left = -100;
	int right = 40;
	int flag = 0;

	//xspot
	xspot(left, flag);

	//enter other code here


	//xspot return
	wait1Msec(2000);
	flag = 1;
	xspot(right,flag);


}//end main