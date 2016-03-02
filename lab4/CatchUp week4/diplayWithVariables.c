#pragma DebuggerWindows("nxtLCDScreen")
task main()
{
	int speedLeft = 10;

	nMotorPIDSpeedCtrl[motorC]= mtrSpeedReg; // left motor set to PID
	nMotorPIDSpeedCtrl[motorB]= mtrSpeedReg; // right motor set to PID



	nSyncedMotors= synchBC;
	nSyncedTurnRatio= 100;

	motor[motorB] = speedLeft;
	wait1Msec (5000);//goes straight 26"

	{

							displayTextLine(4, "speed is %d",speedLeft);
							wait1Msec(5000);
		}//end display

}
