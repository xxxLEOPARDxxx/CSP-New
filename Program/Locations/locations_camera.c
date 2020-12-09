#define LOCCAMERA_FOLLOW	1
#define LOCCAMERA_TOPOS		2
#define LOCCAMERA_FREE		3
//#20190815-01
#define DEFAULT_CAM_RAD 3.0
#define DEFAULT_CAM_RAD_DEN 0.22
#define DEFAULT_LCAM_PERSP 1.285
#define DEFAULT_LCAM_PERSP_DEN 1.25
//#20190327-01
#event_handler("evtCameraSwitchedView","evtCameraSwitchedView");

// Warship 20.07.09 �����
#define LOCCAMERA_MAX_STATES 15
#define LOCCAMERA_ROTATE "Rotate"
#define LOCCAMERA_FLYTOPOS "FlyToPosition"
#define LOCCAMERA_NEARHERO "LockNearHero"

#event_handler("frame", "locCameraUpdate");

Object objLocCameraStates[LOCCAMERA_MAX_STATES];
int iLocCameraCurState = -1;
int locCameraCurMode;
bool locCameraEnableSpecialMode;
bool locCameraEnableFree;

void locCameraInit()
{
	locCameraEnableFree = false;
	locCameraEnableSpecialMode = false;
	//locCameraEnableFree = true;
	locCameraCurMode = LOCCAMERA_FOLLOW;
}
// ��� � ���� to_do
/*void locCameraSetRadius(float fRadius)
{
	SendMessage(&locCamera, "lf", MSG_CAMERA_SET_RADIUS, fRadius);
}
*/
//#20190327-01
int locGetCameraEyes()
{
	if(IsEntity(&locCamera) == 0) return 0;
	int res = SendMessage(&locCamera, "l", MSG_CAMERA_GETEYES);
	return res;
}

void locSetCameraEyes(int nSet)
{
	if(IsEntity(&locCamera) == 0) return;
	if(locCameraCurMode != LOCCAMERA_FOLLOW) return;
	int res = SendMessage(&locCamera, "ll", MSG_CAMERA_SETEYES, nSet);
}

void evtCameraSwitchedView()
{
    int nView = GetEventData();

    //trace("cam switch " + nView);
}

//Set camera follow mode
bool locCameraFollow()
{
	if(IsEntity(&locCamera) == 0) return false;
	bool res = SendMessage(&locCamera, "l", MSG_CAMERA_FOLLOW);
	locCameraCurMode = LOCCAMERA_FOLLOW;
	return res;
}

//Set camera toPos mode
bool locCameraToPos(float x, float y, float z, bool isTeleport)
{
	if(IsEntity(&locCamera) == 0) return false;
	if(locCameraEnableFree == true) return true;
	bool res = SendMessage(&locCamera, "lfffl", MSG_CAMERA_TOPOS, x, y, z, isTeleport);
	locCameraCurMode = LOCCAMERA_TOPOS;
	return res;
}

//Set camera move mode (speed meter per second)
bool locCameraFree()
{
	if(IsEntity(&locCamera) == 0) return false;
	bool res = SendMessage(&locCamera, "l", MSG_CAMERA_FREE);
	locCameraCurMode = LOCCAMERA_FREE;
	return res;
}

bool locCameraLock(float ax)
{
	if(IsEntity(&locCamera) == 0) return false;
	bool res = SendMessage(&locCamera, "lf", MSG_CAMERA_MOVE, ax);
	return res;
}

void locCameraSleep(bool isSleep)
{
	SendMessage(&locCamera, "ll", MSG_CAMERA_SLEEP, isSleep);
}

void locCameraSwitch()
{
	if(locCameraEnableFree == false) return;
	string controlName = GetEventData();
	if(controlName != "ChrCamCameraSwitch") return;
	if(locCameraCurMode != LOCCAMERA_FREE)
	{
		locCameraFree();
	}else{
		locCameraFollow();
	}
}

void locCameraSetSpecialMode(bool isEnable)
{
	locCameraEnableSpecialMode = isEnable;
}

#event_handler("EventGetSpecialMode", "locCameraGetSpecialMode");
int locCameraGetSpecialMode()
{
	return false;
}
void LoadTrackCamera(string sTrackName,float fTrackTime,aref arTrackPause)
{
	SendMessage(&locCamera, "lsfa", -2, sTrackName, fTrackTime, arTrackPause);
}

void TurnOffTrackCamera()
{
	SendMessage(&locCamera, "l", -3);
}
// boal -->
void locCameraTarget(ref _char)
{
    SendMessage(&locCamera, "li", MSG_CAMERA_SETTARGET, _char);
}
// boal <--
// to_do ��� � ����  
bool locCameraFromToPos(float from_x,float from_y,float from_z, bool isTeleport, float to_x,float to_y,float to_z)
{
	if(IsEntity(&locCamera) == 0)
	{
		return false;
	}
	if(locCameraEnableFree == true)
	{
		return true;
	}
	bool res = SendMessage(&locCamera, "lffflfff", -4, from_x,from_y,from_z, isTeleport, to_x,to_y,to_z);
	locCameraCurMode = LOCCAMERA_TOPOS;
	return res;
}
//#20190815-01
void SetPerspective2Settings()
{
    float fCamPersp = CalcLandPerspective();
    float fCamRad = CalcLandRadius();

    locCamera.FOV = fCamPersp;
    locCamera.radius = fCamRad;
}

float CalcLandPerspective()
{
    float fCamPerspAdj = 0.0;
    if(CheckAttribute(&InterfaceStates, "Persp2Details"))
       fCamPerspAdj = stf(InterfaceStates.Persp2Details) / DEFAULT_LCAM_PERSP_DEN;

    return (DEFAULT_LCAM_PERSP + fCamPerspAdj);
}

float CalcLandRadius()
{
    float fCamRadAdj = 0.0;
    if(CheckAttribute(&InterfaceStates, "RadDetails"))
       fCamRadAdj = stf(InterfaceStates.RadDetails) / DEFAULT_CAM_RAD_DEN;

    return (DEFAULT_CAM_RAD + fCamRadAdj);
}


/////////////////////////////////////////////////////////////////////////////////////////
//							Warship 20.07.09 ����� - ������� ����
/////////////////////////////////////////////////////////////////////////////////////////

// ������� ������� �������� ������ ������ ���������.
// ���������:
// float  _offsetX ... _offsetZ - �������� ������ ������������ ������� ������� ���������
// float _rotateX, _rotateY - �������� �������� �� ������ ���, �� 0.01 � ������ �� 0.3, ����� ���� ������������
// float _radius - ������, �� �� ��������� �� ��������� ����� �� ������
// float _startAngle- ��������� ����, ������ ������
// int _time - ����� �������� � ������. ��� ������� - � ������� 30 ������, �� ���� ��������� �������, �� ����� ���� � 10
// bool _teleport - ���� true, ������������ � �������� ����� ���������, ����� - ������� �����
bool locCameraRotateAroundHero(float _offsetX, float _offsetY, float _offsetZ, float _rotateX, float _rotateY,  float _radius, float _startAngle, int _time)
{
	ref curCameraState;
	int cameraCurState = locCameraGetFirstEmptyState();
	float charX, charY, charZ;
	
	if(cameraCurState == -1 || !GetCharacterPos(PChar, &charX, &charY, &charZ)) return false;
	
	curCameraState = &objLocCameraStates[cameraCurState];
	curCameraState.curCameraX = charX + _offsetX;
	curCameraState.curCameraY = charY + _offsetY;
	curCameraState.curCameraZ = charZ + _offsetZ;
	curCameraState.offsetX = _offsetX;
	curCameraState.offsetY = _offsetY;
	curCameraState.offsetZ = _offsetZ;
	curCameraState.rotateX = _rotateX;
	curCameraState.rotateY = _rotateY;
	curCameraState.rotateRadius = _radius;
	curCameraState.time = _time;
	curCameraState.angle = _startAngle;
	curCameraState.type = LOCCAMERA_ROTATE; // ��� ������
	
	if(iLocCameraCurState == -1) iLocCameraCurState = 0;
	
	return true;
}

// ����� ������ �� ��������� ����� _startX ... _startZ �� �������� ����� _endX ... _endZ
// float _speed - ��������� �������� � ������ ������ _time == -1. ���� _speed == 1, �� ��� ����������� ��������
// int _time - ���-�� ������, �� ������� ������ ��������. ���� -1, �� ������������� ������ �� ����������
// bool _fromCurCameraPos - ���� true, �� ��� �������� �� ��� ������ ������, ��������� ������� ����� ��������� ��� ������� ������� ������
bool locCameraFlyToPosition(float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _speed, int _time)
{
	ref curCameraState;
	int cameraCurState = locCameraGetFirstEmptyState();
	float distance;
	
	if(cameraCurState == -1) return false;
	
	distance = GetDistance3D(_startX, _startY, _startZ, _endX, _endY, _endZ);

	curCameraState = &objLocCameraStates[cameraCurState];
	curCameraState.curCameraX = _startX;
	curCameraState.curCameraY = _startY;
	curCameraState.curCameraZ = _startZ;
	curCameraState.endCameraX = _endX;
	curCameraState.endCameraY = _endY;
	curCameraState.endCameraZ = _endZ;
	
	if(_time == -1)
	{
		curCameraState.speedX = (_endX - _startX) / (distance * (1 / _speed));
		curCameraState.speedY = (_endY - _startY) / (distance * (1 / _speed));
		curCameraState.speedZ = (_endZ - _startZ) / (distance * (1 / _speed));
	}
	else
	{
		curCameraState.speedX = (_endX - _startX) / _time;
		curCameraState.speedY = (_endY - _startY) / _time;
		curCameraState.speedZ = (_endZ - _startZ) / _time;
	}
	
	curCameraState.speed = _speed;
	curCameraState.time = _time;
	curCameraState.type = LOCCAMERA_FLYTOPOS; // ��� ������
	
	if(iLocCameraCurState == -1) iLocCameraCurState = 0;
	
	return true;
}

// ������������ ������ � ������������ ����� ������������ ��
// float _offsetX ... _offsetZ - �������� ������������ ��������� ��, ��� ����������� �����, ��� ����� ���������� ������
// int _time - ���-�� ������, ������� ����� ������. ���� -1 - ����� ������ �����
// bool _canRotate - ���� true, �� ������ ����� ��������� ������ � ����������
bool locCameraLockNearHero(float _offsetX, float _offsetY, float _offsetZ, int _time, bool _canRotate)
{
	ref curCameraState;
	int cameraCurState = locCameraGetFirstEmptyState();
	float charX, charY, charZ, offsetAY;
	
	if(cameraCurState == -1 || !GetCharacterPos(PChar, &charX, &charY, &charZ)) return false;
	
	offsetAY = atan2(_offsetZ, _offsetX);
	
	if(_offsetX > 0 && _offsetZ > 0)
	{
		offsetAY = offsetAY + PI;
	}
	
	curCameraState = &objLocCameraStates[cameraCurState];
	curCameraState.curCameraX = charX;
	curCameraState.curCameraY = charY;
	curCameraState.curCameraZ = charZ;
	curCameraState.offsetX = _offsetX;
	curCameraState.offsetY = _offsetY;
	curCameraState.offsetZ = _offsetZ;
	curCameraState.time = _time;
	curCameraState.canRotate = _canRotate;
	curCameraState.offsetAY = offsetAY;
	curCameraState.type = LOCCAMERA_NEARHERO; // ��� ������
	
	if(iLocCameraCurState == -1) iLocCameraCurState = 0;
	
	return true;
}

int locCameraGetFirstEmptyState()
{
	for(int i = 0; i < LOCCAMERA_MAX_STATES; i++)
	{
		if(!CheckAttribute(&objLocCameraStates[i], "time"))
		{
			return i;
		}
	}
	
	return -1;
}

// ������� � ��������� ������� ��������� ������
// ������������������ ������� ��������, ��������, ���:
// locCameraRotateAroundHero(0.0, 1.0, 0.0, 0.03, 0.0, 3.0, 0.0, 200);
// locCameraRotateAroundHero(0.0, 1.0, 0.0, 0.0, 0.01, 5.0, 0.0, 150);
// locCameraRotateAroundHero(0.0, 1.0, 0.0, -0.03, 0.03, 7.0, 0.0, 225);
// � ���������� �������� ���������������� ������ ������
void locCameraNextState()
{
	ref prevCamera, curCamera, nextCamera;
	float distance;
	int time;
	
	prevCamera = &objLocCameraStates[iLocCameraCurState];
	DeleteAttribute(prevCamera, "time"); // �������� ����������
	iLocCameraCurState++;
	
	curCamera = &objLocCameraStates[iLocCameraCurState];
	
	if(iLocCameraCurState == LOCCAMERA_MAX_STATES || !CheckAttribute(&curCamera, "curCameraX"))
	{
		locCameraResetState();
		return;
	}
	
	time = sti(curCamera.time);
	
	Log_TestInfo("locCameraNextState() == " + curCamera.type); 
}

// ����� ����������� ��������� ������ - ������������ � ���������
void locCameraResetState()
{
	locCameraFollow();
	
	iLocCameraCurState = -1;
	
	// ������ ���
	for(int i = 0; i < LOCCAMERA_MAX_STATES; i++)
	{
		DeleteAttribute(&objLocCameraStates[i], "");
	}
	
	Log_TestInfo("locCameraResetState()");
}

// ���������� ������� ������ ��� ����� � ����
void locCameraUpdate()
{
	ref curCameraState; 
	float charX, charY, charZ, charAY;
	float offsetX, offsetZ;
	float rotateRadius, rotateAngle;
	float time; // ����� ����� �������, �.�. ����������� ��� ��������� �������
	
	float timeScale = 1 + TimeScaleCounter * 0.25; // ������� ��������� �������
	
	if(iLocCameraCurState != -1 && !sti(InterfaceStates.Launched))
	{
		if(GetCharacterPos(PChar, &charX, &charY, &charZ))
		{
			curCameraState = &objLocCameraStates[iLocCameraCurState];
			
			time = stf(curCameraState.time);
			
			switch(curCameraState.type)
			{
				case LOCCAMERA_ROTATE:
					rotateRadius = stf(curCameraState.rotateRadius);
					rotateAngle = stf(curCameraState.angle);
					
					// X rotation
					if(stf(curCameraState.rotateX) != 0.0)
					{
						curCameraState.curCameraX = charX + sin(rotateAngle) * rotateRadius + stf(curCameraState.offsetX);
						curCameraState.curCameraZ = charZ + cos(rotateAngle) * rotateRadius + stf(curCameraState.offsetZ);
						curCameraState.angle = rotateAngle + stf(curCameraState.rotateX) * timeScale;
					}
					else // ����� ������ ����������
					{
						curCameraState.curCameraX = charX + stf(curCameraState.offsetX);
						curCameraState.curCameraZ = charZ + stf(curCameraState.offsetZ);
					}
					
					// Y rotation
					if(stf(curCameraState.rotateY) != 0.0)
					{
						curCameraState.curCameraY = charY + cos(rotateAngle) * rotateRadius + stf(curCameraState.offsetY);
						curCameraState.curCameraX = charX + sin(rotateAngle) * rotateRadius + stf(curCameraState.offsetX);
						curCameraState.angle = rotateAngle + stf(curCameraState.rotateY) * timeScale;
					}
					else
					{
						curCameraState.curCameraY = charY + stf(curCameraState.offsetY);
					}
				break;
				
				case LOCCAMERA_FLYTOPOS:
					curCameraState.curCameraX = stf(curCameraState.curCameraX) + stf(curCameraState.speedX) * timeScale;
					curCameraState.curCameraY = stf(curCameraState.curCameraY) + stf(curCameraState.speedY) * timeScale;
					curCameraState.curCameraZ = stf(curCameraState.curCameraZ) + stf(curCameraState.speedZ) * timeScale;
				break;
				
				case LOCCAMERA_NEARHERO:
					offsetX = stf(curCameraState.offsetX);
					offsetZ = stf(curCameraState.offsetZ);
					
					if(sti(curCameraState.canRotate) && GetCharacterAy(PChar, &charAY))
					{
						curCameraState.curCameraX = charX + offsetX * sin(charAY + stf(curCameraState.offsetAY));
						curCameraState.curCameraZ = charZ + offsetZ * cos(charAY + stf(curCameraState.offsetAY));
					}
					else
					{
						curCameraState.curCameraX = charX + offsetX;
						curCameraState.curCameraZ = charZ + offsetZ;
					}
					
					curCameraState.curCameraY = charY + stf(curCameraState.offsetY);
				break;
			}
			
			locCameraToPos(stf(curCameraState.curCameraX), stf(curCameraState.curCameraY), stf(curCameraState.curCameraZ), true);
			
			if(time != -1.0)
			{
				time -= 1 * timeScale; // ���� ��������� �������
				curCameraState.time = time;
			}
			
			if(time <= 0.0 && time != -1.0)
			{
				locCameraNextState();
			}
			
			// ��� ����������� ��������� � ������ �����
			if(time == -1.0 && curCameraState.type == LOCCAMERA_FLYTOPOS)
			{
				if(stf(curCameraState.curCameraX) + stf(curCameraState.speedX) * timeScale >= stf(curCameraState.endCameraX) &&
					stf(curCameraState.curCameraX) - stf(curCameraState.speedX) * timeScale <= stf(curCameraState.endCameraX) &&
					stf(curCameraState.curCameraY) + stf(curCameraState.speedY) * timeScale >= stf(curCameraState.endCameraY) &&
					stf(curCameraState.curCameraY) - stf(curCameraState.speedY) * timeScale <= stf(curCameraState.endCameraY) &&
					stf(curCameraState.curCameraZ) + stf(curCameraState.speedZ) * timeScale >= stf(curCameraState.endCameraZ) &&
					stf(curCameraState.curCameraZ) - stf(curCameraState.speedZ) * timeScale <= stf(curCameraState.endCameraZ))
				{
					locCameraNextState();
				}
			}
		}
	}
}													  