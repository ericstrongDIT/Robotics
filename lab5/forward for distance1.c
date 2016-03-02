/*Using the motor encoders 
REMEMBER 350 degrees = 1 roration so 1800 in while loop is for 5 rotations. Measure what one rotation goes in CM to get more accurate distances
*/
task main()
{
	//ensure to clear these everytime you mean to use them
	nMotorEncoder[motorB] =0;
	nMotorEncoder[motorC] =0;

	while(nMotorEncoder[motorB] < 1800)
	//NB**1800 /360 (gives amount of rotations)=5rotations
	{

		motor[motorC] = 50;
		motor[motorB] = 50;

		
	}//end while	


}//end main()