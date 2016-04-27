// The name of the file that we're saving data to
string filename = "numberFile";

int whiteTotal = 200;
int blackTotal = 500;
int boxTotal=0;

void testData()
{
 	long fileHandle;
 	fileHandle = fileOpenWrite(filename);

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





  // Close the file, this automatically flushes the
  // buffers to the "disk".
  //fileClose(fileHandle);

  // Open the file for reading and return a handle.
 // fileHandle = fileOpenRead(filename);

  // Close the file
 // fileClose(fileHandle);
}


task main()
{
  testData();
}
