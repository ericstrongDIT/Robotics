/*Controlling the robot via target command
This program should make robot move 5 rotations but slow to a stop*/

task main()
{
	//ensure to clear these everytime you mean to use them
	nMotorEncoder[motorB] =0;
	nMotorEncoder[motorC] =0;

	nMotorEncoderTarget[motorB] =1800; //slows robot when meeting this target
	nMotorEncoderTarget[motorC] =1800;

	motor[motorC] = 50;
	motor[motorB] = 50;
	//wait1Msec(10000);

	//runStaterunning
	//runStateHoldPosition
	//RunStateIdle

	while(nMotorRunState[motorB] != runStateIdle || nMotorRunState[motorC] != runStateIdle)
	{
			//this is an idle loop

	}//end while
	
	

		

		
		


}//end main()