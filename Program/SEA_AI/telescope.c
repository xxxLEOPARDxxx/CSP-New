void Telescope_Request()
{
	int nTelescopeIn = GetEventData();
	if( objISpyGlass.bNet=="1" ) {
		if (sti(NCDeckCamera.On))
		{
			SendMessage(&objISpyGlass, "ll", MSG_TELESCOPE_REQUEST,nTelescopeIn);
		}
	} else {
		if( GetCharacterEquipByGroup(pchar,SPYGLASS_ITEM_TYPE)=="" ) {
			nTelescopeIn = 0;
		}
		if( nTelescopeIn!=0 && SeaCameras.Camera=="SeaDeckCamera" ) 
		{
			SendMessage(&objISpyGlass, "ll", MSG_TELESCOPE_REQUEST,1);
			MouseSpeedFix(true);
		} 
		else 
		{
			SendMessage(&objISpyGlass, "ll", MSG_TELESCOPE_REQUEST,0);
			MouseSpeedFix(false);
		}
	}
}

void MouseSpeedFix(bool onoff)
{
	float fRealMouseXSens = 1.0;
	float fRealMouseYSens = 1.0;

	float fx = 0.5;
	float fy = 0.5;
	if( CheckAttribute(InterfaceStates,"mouse.x_sens") )
		fx = stf(InterfaceStates.mouse.x_sens);
	if( CheckAttribute(InterfaceStates,"mouse.y_sens") )
		fy = stf(InterfaceStates.mouse.y_sens);

	if(fx<=0.5) {fRealMouseXSens = 0.5 + fx;}
	else {fRealMouseXSens = fx*2.0;}
	if(fy<=0.5) {fRealMouseYSens = 0.5 + fy;}
	else {fRealMouseYSens = fy*2.0;}

	if (onoff) XI_SetMouseSensitivity(fRealMouseXSens/6, fRealMouseYSens/6);
	else XI_SetMouseSensitivity(fRealMouseXSens, fRealMouseYSens);
}

void Telescope_Off()
{
	SendMessage(&objISpyGlass, "ll", MSG_TELESCOPE_REQUEST, 0);
}