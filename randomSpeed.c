
task main()
{
	int speedLeft = (random(100));

	nMotorPIDSpeedCtrl[motorC]= mtrSpeedReg; // left motor set to PID
	nMotorPIDSpeedCtrl[motorB]= mtrSpeedReg; // right motor set to PID

		{

							displayTextLine(4, "speed is %d",speedLeft);
							wait1Msec(100);
		}//end display

		nSyncedMotors= synchBC;
	//nSyncedMotors= synchBC;
	nSyncedTurnRatio= 100;

	motor[motorB] = (random(100));
	wait1Msec (5000);//goes straight 26"



}
