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
			playTone(nFreq, 1);
			while (!bSoundQueueAvailable)
			{}
		}
		for (; nFreq > 50; nFreq -= 25)
		{
			playTone(nFreq, 1);
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

void testPlaySoundFiles()
{
	checkSoundFile("White");
	checkSoundFile("Black");
}

task main()
{
	setSoundVolume(100);
	testPlaySoundFiles();
	//testSounds();

}
