/* Xspot three code
    Starts on (3,1)
*/

#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)

#define POWER1 100

int move9 = 9000;
int move7 = 7000;
int move4 = 4000;
int move2 = 2000;
int move1 = 900;

void xspot3(int turn, int flag)
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

		  /* CHANGE OUT THE FOLLOWING VARIABLES DEPENDING ON THE MAP.
        MAP 3 = move2 : MAP 4 = move3 : MAP5 = move4   (map1 does not use this return. refere to xspotReturn)*/
        clearTimer(T1);
        while(time1[T1] <= move2) //move2 move3 move4
        {
            setMotorSyncTime(left, right, 0, 1000, POWER1);
            //scan box color to file

        }//end while

    }//end if

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
