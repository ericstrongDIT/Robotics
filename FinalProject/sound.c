void testSounds()
{
	int nRead;
	int nFreq;

	for (int nVol = 0; nVol< 127; ++nVol)
	{
		setSoundVolume(nVol);
		nRead = getSoundVolume();
		VERIFY(nRead == nVol);
	}
	setSoundVolume(30);
	while (true)
	{
		for (nFreq = 50; nFreq < 4000; nFreq += 25)
		{
			//playTone(nFreq, 1);
			while (!bSoundQueueAvailable)
			{}
		}
		for (; nFreq > 50; nFreq -= 25)
		{
			//playTone(nFreq, 1);
			while (!bSoundQueueAvailable)
			{}
		}
	}


}


void checkSoundFile(const char *pFileName)
{
	bool bExists;

	bExists = bEv3FileExists(pFileName);
	while (!bSoundQueueAvailable)
	{}
	playSoundFile(pFileName);
	return;
}

void testPlaySoundFiles(int file1)
{
	checkSoundFile("Black");
	checkSoundFile("White");
	checkSoundFile("One");
	checkSoundFile("Nine");
	checkSoundFile("Seven");
}

void playSound(int file)
{
	setSoundVolume(100);
	testPlaySoundFiles(file);
	testSounds();

}


task main()
{
	int file = 1;
	playSound(file);

}
