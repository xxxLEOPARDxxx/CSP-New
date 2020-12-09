// SLiB ����� ���� ��� ���, ��� �� �3 �������
void TavernWaitDate(string date)
{
	int iTime, iAddTime, iTmp;
	iTime = sti(environment.time);
	if (date == "wait_day")
	{
		if (iTime >= 21) iAddTime = 24 - iTime + 7;
		if (iTime < 7) iAddTime = 7 - iTime;
		// boal 03.03.05 -->
		if (iTime >= 7 && iTime < 21) iAddTime = 24  + 7 - iTime;
		// boal <--
		StoreDayUpdate();
	}
	else
	{
		if (iTime < 24) iAddtime = 24 - iTime;
	}
	LAi_Fade("", "");
	WaitDate("",0,0,0,iAddtime,5);
	//navy --> ��� ������� ��������... 2 ���� = ������
	if (CheckAttribute(pchar, "questTemp.Rum") && CheckAttribute(pchar, "chr_ai.drunk"))
	{
		iTmp = sti(pchar.chr_ai.drunk);
		iTmp -= (iAddtime * 900);
		if (iTmp < 0) LAi_SetAlcoholNormal(pchar);
		else pchar.chr_ai.drunk = iTmp;
	}
	//navy <--
	RecalculateJumpTable();
	// boal -->
	RefreshWeather();
	RefreshLandTime();
	// boal <--
}

//Boyer add
void WasteTime(int baseHours)
{
	int nMinutes, nHours;
	nMinutes = rand(15);
	nHours = func_max(baseHours, 1);
	if(rand(1)) nMinutes = -1 * nMinutes;

	LAi_Fade("", "");
	WaitDate("",0,0,0,nHours,nMinutes);
	//RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
}
//End Boyer add

void TavernWaitDate_LSC(string date)
{
	int iTime, iAddTime, iTmp;
	iTime = sti(environment.time);
	if (date == "wait_day")
	{
		if (iTime >= 21) iAddTime = 24 - iTime + 7;
		if (iTime < 7) iAddTime = 7 - iTime;
		// boal 03.03.05 -->
		if (iTime >= 7 && iTime < 21) iAddTime = 24  + 7 - iTime;
		// boal <--
		StoreDayUpdate();
	}
	else
	{
		if (iTime < 24) iAddtime = 23 - iTime;
	}
	WaitDate("",0,0,0,iAddtime,5);
	//navy --> ��� ������� ��������... 2 ���� = ������
	if (CheckAttribute(pchar, "questTemp.Rum") && CheckAttribute(pchar, "chr_ai.drunk"))
	{
		iTmp = sti(pchar.chr_ai.drunk);
		iTmp -= (iAddtime * 900);
		if (iTmp < 0) LAi_SetAlcoholNormal(pchar);
		else pchar.chr_ai.drunk = iTmp;
	}
	//navy <--
	DoReloadCharacterToLocation("FleuronTavern",  "quest", "bed");
	RecalculateJumpTable();
	// boal -->
	RefreshWeather();
	RefreshLandTime();
	// boal <--
}
