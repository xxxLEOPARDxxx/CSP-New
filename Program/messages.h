#ifndef COMMON_MESSAGES_HPP
#define COMMON_MESSAGES_HPP

//============================================================================================
//Backscene messages
//============================================================================================

#define MSG_BACKSCENE_LOADMODEL 0
#define MSG_BACKSCENE_SETCAMERA 1
#define MSG_BACKSCENE_SETSHIPPOSITION 2
#define MSG_BACKSCENE_CREATEMENULIST 3
#define MSG_BACKSCENE_MENUCONTROL 4
#define MSG_BACKSCENE_GETCURRENTMENU 5
#define MSG_BACKSCENE_SETCURRENTMENU 6
#define MSG_BACKSCENE_SETMENUSELECT 7
#define MSG_BACKSCENE_SETLIGHTSOURCE 8
#define MSG_BACKSCENE_ADDANIMATION 9
#define MSG_BACKSCENE_ADDMODEL 10
#define MSG_BACKSCENE_MOVECAMERA 15

//============================================================================================
//Model messages
//============================================================================================
#define MSG_MODEL_LOAD_GEO			20500		// "ls", string
#define MSG_MODEL_LOAD_ANI			20501
#define MSG_MODEL_SET_PARENT		20502		// "li", entity_id
#define MSG_MODEL_SET_LIGHT_PATH	20503
#define MSG_MODEL_RELEASE			20504
#define MSG_MODEL_RESTORE			20505
#define MSG_MODEL_SET_POSITION			20506
//	SendMessage(ref _model, "lffffffffffff", MSG_MODEL_SET_POSITION, float _x, float _y, float _z,
//		float _vxx, float _vxy, float _vxz, float _vyx, float _vyy, float _vyz, float _vzx, float _vzy, float _vzz);

#define MSG_MODEL_BLEND        			20507
#define MSG_MODEL_SET_LIGHT_LMPATH	20508
#define MSG_MODEL_SET_DIRPATH		20509 // "s" = "texture_path\\"
#define MSG_MODEL_SET_TECHNIQUE		20510 // "s" = technique
#define MSG_MODEL_SET_FOG			20511
#define MSG_MODEL_SET_MAX_VIEW_DIST	20512
//#20170911-01 Ambient light mod
#define MSG_MODEL_SET_AMBIENT_LIGHT 20530 // "ll"
//#20180325-02
#define MSG_MODEL_LOAD_GEO_ALT			20600		// "lsffff"

//============================================================================================
//blade messages
//============================================================================================
#define MSG_BLADE_SET 21000	//"lisfll, entity, modelName, lifeTime, color[2]
#define MSG_BLADE_BELT 21001	//"l", default
#define MSG_BLADE_HAND 21002	//"l"
#define MSG_BLADE_TRACE_ON 21003	//"l"
#define MSG_BLADE_TRACE_OFF 21004	//"l"
#define MSG_BLADE_BLOOD 21005	//"l"
#define MSG_BLADE_LIGHT 21006	//"l"
#define MSG_BLADE_GUNSET 21007	//"lis, entity, modelName
#define MSG_BLADE_GUNBELT 21008	//l
#define MSG_BLADE_GUNHAND 21009	//l
#define MSG_BLADE_GUNFIRE 21010	//l
#define MSG_CHARACTER_BLADEHAND 21011 //"ll", boolBladeInHand
#define MSG_BLADE_ALPHA 21012	//"ll", alpha|0xFFFFFF
//#20171102-01 Add hat/helmet
#define MSG_BLADE_HEADSET 21050	//"lis, entity, modelName
#define MSG_BLADE_HEADMOUNT 21051 //l
//#20200610-01
#define MSG_BLADE_LOOKEYES 21055

//Grass Messages
#define MSG_GRASS_LOAD_DATA			40666
#define MSG_GRASS_SET_TEXTURE		41666
#define MSG_GRASS_SET_PARAM			42666

//============================================================================================
//Island Messages
//============================================================================================
#define MSG_ISLAND_LOAD_GEO				50100		// "ls", island name
#define MSG_ISLAND_SET_GEO				50101		// "lis", model_id,island name
#define MSG_ISLAND_START				50102		// "lis", model_id,island name
#define MSG_ISLAND_ADD_FORT				50103		// "li", model_id
//#20180325-02
#define MSG_ISLAND_LOAD_GEO_ALT			50110		// "lsffff"
//#20180618-01
#define MSG_ISLAND_SET_TECHNIQUE		50120		// "ls"

//============================================================================================
//Sea Reflection Messages
//============================================================================================
#define MSG_SEA_REFLECTION_DRAW			50200		// "ls", island name
#define MSG_SEA_SUNROAD_DRAW			50201		// "ls", island name

//============================================================================================
//Ship Messages
//============================================================================================
#define MSG_SHIP_CREATE						50300
#define MSG_SHIP_DELETE						50301
#define MSG_SHIP_SEA_INFO					50302
#define MSG_SHIP_ACTIVATE_FIRE_PLACE		50304
#define MSG_SHIP_SET_SAIL_STATE				50305
#define MSG_SHIP_GET_NUM_FIRE_PLACES		50306
#define MSG_SHIP_GET_CHARACTER_INDEX		50307
#define MSG_SHIP_ADD_MOVE_IMPULSE			50308
#define MSG_SHIP_RESET_TRACK				50309
#define MSG_SHIP_SETLIGHTSOFF				50310
#define MSG_SHIP_FLAG_REFRESH				50312   // boal 20.08.06
#define MSG_SHIP_SAFE_DELETE				50315
#define MSG_SHIP_GET_SAIL_STATE				50325
#define MSG_SHIP_CURVES						50400
//Boyer add #20170201
#define MSG_SHIP_FLAG_REFRESH_ENTITY				50500
#define MSG_SHIP_FLAG_REMOVE				50510
//#20181027-02 
#define MSG_SHIP_RESETISLAND				50520
//#20181102-02
#define MSG_SHIP_REMOVE						50525
//#20190211-01
#define MSG_SHIP_LIGHTSRELEASEALL			50320
#define MSG_SHIP_LIGHTSRESET				50321

//============================================================================================
//Weather Messages
//============================================================================================
#define MSG_WHR_LIGHTNING_ADD			54000

//============================================================================================
//Location messages
//============================================================================================
//Локация
//Добавить модельку в локацию
#define MSG_LOCATION_ADD_MODEL				30100		//"lssl" загрузить статическую модельку, считать её локаторы, установить технику рендера и уровень рисования
#define MSG_LOCATION_GET_MODEL				30101		//"le" получить идентификатор модельки
//Установить последней добавленной модельке свойства
#define MSG_LOCATION_MODEL_SET_POS			30110		//"lss" поместить в локатор последнюю загруженную модельку
#define MSG_LOCATION_MODEL_SET_ROT			30111		//"lfff" установть скорость вращения последней загруженной модельке
#define MSG_LOCATION_MODEL_SET_UVS			30112		//установить эффект скольжения текстуры на последнюю загруженную модельку (ffff - скорости u0, v0, u1, v1)
#define MSG_LOCATION_MODEL_LAMPS			30113		//"l" добавить текущую модельку с вписок игнорирования при трейсе лучей от ламп
#define MSG_LOCATION_MODEL_REFLECTION		30114		//"lf" установить эффект генерации матрицы для отражения, f - коэфициент масштабирования
//Установить патчи
#define MSG_LOCATION_SET_CHRS_PATCH			30120		//"ls" загрузить патч для персонажей
#define MSG_LOCATION_SET_CAM_PATCH			30121		//"ls" загрузить патч для камеры
#define MSG_LOCATION_SET_JMP_PATCH			30122		//"ls" загрузить патч для прыжков
#define MSG_LOCATION_SET_GRS_PATCH			30123		//"ls" загрузить траву
//Радиусы локаторов
#define MSG_LOCATION_GRP_RADIUS				30125		//"lsf" установить радиус группе локаторов
#define MSG_LOCATION_LOC_RADIUS				30126		//"lssf" установить радиус локатору
//Добавить источник освещения
#define MSG_LOCATION_ADD_LIGHT				30128		//"lsfff" имя источника, позиция источника
//Прописать локаторы
#define MSG_LOCATION_UPDATELOCATORS			30130		//"l" скопировать все локаторы в аттрибуты локации
//Пути до файлов
#define MSG_LOCATION_MODELSPATH				30140		//"ls" относительный установить путь до моделей локации
#define MSG_LOCATION_TEXTURESPATH			30141		//"ls" относительный установить путь до текстур локации
#define MSG_LOCATION_LIGHTPATH				30142		//"ls" относительный установить путь до освещения локации
#define MSG_LOCATION_SHADOWPATH				30143		//"ls" относительный установить путь для текстуры на полу
//Утилитные
#define MSG_LOCATION_CHECKENTRY				30150		//"lss" проверить вход в локацию на возможность прихода в неё (свободен ли он)
#define MSG_LOCATION_PAUSE					30151		//"ll" установить паузу в локации
#define MSG_LOCATION_SETCHRPOSITIONS		30152		//"l" сохранить позиции для востонавления
#define MSG_LOCATION_TLPCHRPOSITIONS		30153		//"l" переместить и удалить позиции для востонавления
#define MSG_LOCATION_CLRCHRPOSITIONS		30154		//"l" удалить позиции для востонавления
#define MSG_LOCATION_EX_MSG					30155		//"ls" расширенная команда s, ...
//20180926-01 Animation speed mod
#define MSG_CHARACTER_MULTANISPEED			30380		//"lsf"
//Отладочные
#define MSG_LOCATION_VIEWLGROUP				30180		//"lsffl" показать группу локаторов в виде шариков с коэфициентом скалирования радиуса, дистанции видимости меток, цветом
#define MSG_LOCATION_HIDELGROUP				30181		//"ls" скрыть группу локаторов

//Boyer add so that compiles with KK's addition #20170201
#define MSG_LOCATION_CREATELOCATOR			30190		// "lssffffff" name, group, x, y, z, angX, angY, angZ
#define MSG_LOCATION_DELETELOCATOR			30191		// "lss" name, group

//#20170911-01 Ambient light mod
#define MSG_LOCATION_SET_AMBIENT_LIGHT 30250 // "ll"
#define MSG_LOCATION_LOCATOREXIST 30255 // "ls"

//Персонажи
//Моделька персонажа
#define MSG_CHARACTER_SETMODEL				30200		//"lss" загрузить модель с анимацией
#define MSG_CHARACTER_GETMODEL				30201		//"le" получить модельку персонажа
#define MSG_CHARACTER_GETPOS				30202		//"leee" получить позицию персонажа
#define MSG_CHARACTER_GETAY					30203		//"le" получить позицию персонажа
#define MSG_CHARACTER_DIST2D				30204		//"lie" получить дистанцию до персонажа
#define MSG_CHARACTER_DIST3D				30205		//"lie" получить дистанцию до персонажа
//Телепортация
#define MSG_CHARACTER_TELEPORT				30210		//"lfff" переместить персонажа в точку x, y, z
#define MSG_CHARACTER_TELEPORT_AY			30211		//"lffff" переместить персонажа в точку x, y, z и направить по ay
#define MSG_CHARACTER_TELEPORT_TO_LOCATOR	30212		//"lss" переместить персонажа в локатор указанный как имя группы, имя локатора
//Анализ локаторов
#define MSG_CHARACTER_ADD_DETECTOR			30220		//"ls" добавить группу локаторов для анализа
#define MSG_CHARACTER_DEL_DETECTOR			30221		//"ls" удалить группу локаторов для анализа
//Динамическое перемещение персонажа
#define MSG_CHARACTER_ENTRY_TO_LOCATION		30330		//"lss" динамически разместить персонажа в локации
#define MSG_CHARACTER_EXIT_FROM_LOCATION	30331		//"l" удалить персонажа из локации
//Поворот персонажа
#define MSG_CHARACTER_TURNBYLOC				30340		//"lss" направить в направлении локатора
#define MSG_CHARACTER_TURNBYCHR				30341		//"le" направить на другого персонажа
#define MSG_CHARACTER_TURNBYPOINT			30342		//"lfff" направить в направлении точки
#define MSG_CHARACTER_TURNAY				30343		//"lf" направить по углу
#define MSG_CHARACTER_TURNPUSH				30344		//"l" сохранить в стеке поворот персонажа
#define MSG_CHARACTER_TURNPOP				30345		//"l" сохранить в стеке поворот персонажа
//Проигрывание анимации
#define MSG_CHARACTER_ACTIONPLAY			30350		//"ls" проиграть действие, если "" - перейти в режим idle анимации
//Установить персонажу саблю
#define MSG_CHARACTER_SETBLADE				30360		//"lsfll" установить саблю
#define MSG_CHARACTER_SETGUN				30361		//"ls" установить саблю
#define MSG_CHARACTER_SETFTGLEVEL			30362		//"lf" установить уровень fighting'a

//#20171102-01 Add hat/helmet
#define MSG_CHARACTER_SETHEAD				30365		//SendMessage(pchar,"lsss",MSG_CHARACTER_SETHEAD,pchar.model, "hat2", "pscripts\HeadGear.ini");

//Поиск персонажей
#define MSG_CHARACTER_FINDNEAR				30370		//"leeffffll" установить саблю
														//l - MSG_CHARACTER_FINDNEAR
														//e - ссылка на массив из object который будет заполняться:
														//    index - индекс персонажа
														//    dist - дистанция между персонажами
														//    dx, dy, dz - дельты в направлении персонажа
														//    если понадобиться размеры массива будут увеличены
														//e - ссылка на переменную int - количество найденных персонажей
														//Условия поиска:
														//f - радиус поиска
														//f - угол теста по высоте -> sin(ax)*dist 0 на протяжении всего растояния пол персонажа
														//f - угол анализа в горизонтальной плоскости, 0 не анализировать
														//f - дистанция переднего режущего плана, если работает предыдущий тест
														//l - 1 тестировать видимость, 0 нет
														//l - 1 сортировать по дальности, 0 нет
														
//Проверка видимости нами его
#define MSG_CHARACTER_VISIBLE				30371		//"i"

#define MSG_CHARACTER_VIEWDAMAGE			30372		//"lfff"	вывести о повреждении нанесёному персонажу f - нанес. повр, f - текущее hp, f - всего hp
#define MSG_CHARACTER_EX_MSG				30373

//Установка задач персонажу
#define MSG_NPCHARACTER_SETTASK				30400
#define MSG_NPCHARACTER_PUSHTASK			30401
#define MSG_NPCHARACTER_POPTASK				30402
#define MSG_NPCHARACTER_GETTASK				30403

//Камера
#define MSG_CAMERA_SETTARGET				30500		//"li" установить модельку за которой следить
#define MSG_CAMERA_FOLLOW					30510		//"l" установить режим камеры - преследование персонажа
#define MSG_CAMERA_LOOK						30511		//"l" установить режим камеры - вид из глаз
#define MSG_CAMERA_TOPOS					30512		//"lfffl" установить режим камеры - находиться в точке и наблюдать за персонажем
#define MSG_CAMERA_MOVE						30513		//"lffff" установить режим камеры - перемещаться в точку с заданной скоростью и следить за персонажем
#define MSG_CAMERA_FREE						30514		//"l" свободный полёт камеры

#define MSG_CAMERA_SLEEP					30520		//"ll" остановить работу камеры (1) или возобновить (0)
//#20190327-01
#define MSG_CAMERA_GETEYES					30521
#define MSG_CAMERA_SETEYES					30522
//#20200331-01
#define MSG_CAMERA_LIMITRANGE				30533

//Пятна на корабле
#define MSG_BLOTS_SETMODEL					30600		//"li" установить модельку, model_id
#define MSG_BLOTS_HIT						30601		//"lffffff" установить точку x, y, z, nx, ny, nz

//============================================================================================
//World map messages
//============================================================================================
//Storm
#define MSG_WORLDMAP_CREATESTORM			31000	//"l" Создать шторм
#define MSG_WORLDMAP_CREATESTORM_TIME		31001	//"lf" Создать шторм и указать время жизни в секундах
//Encounter ships
//Коэфициент скорости kSpeed определяет скорость энкоунтера относительно игрока, 1.0 одинаковы, 1.2 на 20 процентов выше, 1.0/1.2 на 20 процентов ниже
//Merchant - событийный корабль с поведением купца (следование к острову)
#define MSG_WORLDMAP_CREATEENC_MER			31100	//"lsssff" type, nation, kSpeed (1.0f - player speed), island name  time
// boal 04/10/06 новый метод
#define MSG_WORLDMAP_CREATEENC_MER_XZ			31102	//"lsffffff"  sName, fx1, fz1, fx2, fz2, kSpeed, timeOut
#define MSG_WORLDMAP_CREATEENC_MER_TIME		31101	// бутафория, не юзается //"lllsff" type, nation, kSpeed (1.0f - player speed), island name, live time in sec
//Follow - событийный корабль преследующий нас
#define MSG_WORLDMAP_CREATEENC_FLW			31110	//"lllf" type, nation, kSpeed
#define MSG_WORLDMAP_CREATEENC_FLW_TIME		31111	//"lllff" type, nation, kSpeed, live time in sec
//Warring - пара воюющих корабликов
#define MSG_WORLDMAP_CREATEENC_WAR			31120	//"lllll" type1, nation1, type2, nation2
#define MSG_WORLDMAP_CREATEENC_WAR_TIME		31121	//"lllllf" type1, nation1, type2, nation2, live time in sec
//Удалить все энкоунтеры
#define MSG_WORLDMAP_CREATEENC_RELEASE		31200	//""
//Запустить выход в море из скрипта
#define MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA		31130	//""

//============================================================================================
//Effects
//============================================================================================
//Fader
#define FADER_OUT							33000	//"lfl", fade time in sec, true - autodelte
#define FADER_IN							33001	//"lfl", fade time in sec, true - autodelte
#define FADER_STARTFRAME					33002	//"l", if send, then make shot from next frame & show it
#define FADER_PICTURE						33003	//"ls", texture name
#define FADER_PICTURE0						33004	//"ls", texture name
//Boyer add so compiles #20170201
#define FADER_DATA						33005

//============================================================================================
// Particle system
//============================================================================================
#define PS_CREATE			10000
#define PS_SETVECTORS		10001
#define PS_CREATEX			10002
#define PS_CREATEXX			10003
#define PS_ADDTRACKPOINT	10004
#define PS_USESURFACE		10005
#define PS_CLEARALL			10006
#define PS_DELETE			10007
#define PS_CREATE_RIC		10008
#define PS_CREATEX_RIC		10009
#define PS_PAUSEALL		10010
#define PS_CREATIONCAPTURE_BEG    10011
#define PS_CREATIONCAPTURE_END    10012
#define PS_CLEAR_CAPTURED 10013
#define PS_VALIDATE_PARTICLE	10014

#define LM_SET_GEOMETRY		1500
#define LM_LOCATE			1501
#define LM_LOCATE_FIRST		1502
#define LM_LOCATE_NEXT		1503
#define LM_LOCATE_I			1504

#define LM_SETPOINT				1600
#define LM_SETPOINTANDANGLES	1601
#define LM_SETPOINTANDVECTOR	1602

//============================================================================================
//Sound Service messages
//============================================================================================
//Control functions
#define MSG_SOUND_SET_ENABLED				77016   //"l"		  enabled
#define MSG_SOUND_SET_CAMERA_POSITION		77001	//"fff"       vector_x, vector_ym, vector_z
#define MSG_SOUND_SET_CAMERA_ORIENTATION	77002	//"ffffff"    nose_vector_x, nose_vector_ym, nose_vector_z, head_vector_x, head_vector_y, head_vector_z
#define MSG_SOUND_SET_MASTER_VOLUME			77021	//"fff"       FX, music, speech volumes
#define MSG_SOUND_GET_MASTER_VOLUME			77022	//"eee"       FX, music, speech volumes

//Sound management routines
#define MSG_SOUND_PLAY             			77003	//"sl[llllfff]" file_name, type, simple_cache?, looped?, cached?, fade_in_time, start_x, start_y, start_y
#define MSG_SOUND_STOP             			77004	//"ll"        id(0=all), fade_out_time
#define MSG_SOUND_RELEASE          			77005	//"l"         id(0=all)
#define MSG_SOUND_DUPLICATE        			77006	//"l"         id
#define MSG_SOUND_SET_3D_PARAM     			77007	//"llp"       id(0=all), param_type, pointer_to_operand
#define MSG_SOUND_SET_VOLUME        		77008	//"lf"        id(0=all), new_volume
#define MSG_SOUND_IS_PLAYING        		77009	//"l"         id
#define MSG_SOUND_GET_POSITION     			77010	//"l"         id
#define MSG_SOUND_RESTART          			77011	//"l"         id(0=all)
#define MSG_SOUND_RESUME           			77012	//"ll"         id(0=all), fade_in_time
//Sound schemes
#define MSG_SOUND_SCHEME_RESET				77013   //""
#define MSG_SOUND_SCHEME_SET				77014   //"s"         scheme_name
#define MSG_SOUND_SCHEME_ADD				77015   //"s"		  scheme_name
//Aliases
#define MSG_SOUND_ALIAS_ADD					77017   //"s"		  alias_name
//#20180815-03
#define MSG_SOUND_ENVIRONMENT				77100	//"ll"
//#20180824-01
#define MSG_SOUND_PLAY_NORET       			77150

//============================================================================================
//Animals messages
//============================================================================================
#define MSG_ANIMALS_SEAGULLS_SHOW			77100	//""
#define MSG_ANIMALS_SEAGULLS_HIDE			77101	//""
#define MSG_ANIMALS_SEAGULLS_FRIGHTEN			77102	//""
#define MSG_ANIMALS_SEAGULLS_ADD        		77103	//"fff"         x,y,z
#define MSG_ANIMALS_SHARKS_SHOW				77104	//""
#define MSG_ANIMALS_SHARKS_HIDE				77105	//""
#define MSG_ANIMALS_FISHSCHOOLS_SHOW			77106	//""
#define MSG_ANIMALS_FISHSCHOOLS_HIDE			77107	//""
#define MSG_ANIMALS_BUTTERFLIES_SHOW			77108	//""
#define MSG_ANIMALS_BUTTERFLIES_HIDE			77109	//""
#define MSG_ANIMALS_BUTTERFLIES_XYZ				77110	//""

//============================================================================================
//Ball splash messages
//============================================================================================
#define MSG_BALLSPLASH_ADD				77200	//"ffffff"    position, ball_vector
//============================================================================================

//============================================================================================
//Telescope messages
//============================================================================================
#define MSG_TELESCOPE_INIT_ARRAYS			77300	//"ee"
#define MSG_TELESCOPE_REQUEST				77301
#define MSG_TELESCOPE_SET_TYPE				77302 //"l", telescope_type

//============================================================================================
//Sea operator messages
//============================================================================================
#define MSG_SEA_OPERATOR_FIRE				77400 //"isfff"		shipID, bortName, x,y,z
#define MSG_SEA_OPERATOR_BALL_UPDATE			77401 //...fff...
#define MSG_SEA_OPERATOR_SHIP_HIT			77402 //fffi		ballX,ballY,ballZ, hitShipCharacter

//============================================================================================
//Peoples on ship
//============================================================================================
#define MSG_PEOPLES_ON_SHIP_MASTFALL		77500 //"ll"		characterIndex, mastNumber
#define MSG_PEOPLES_ON_SHIP_HULLHIT		    77600 //"lafff"

//============================================================================================
//Camera on ship
//============================================================================================
#define MSG_DECK_CAMERA_SET_VIEWPOINT			41800 //"fff"		point.x, point.y, point.z
#define MSG_WORLDMAP_FLAG_SET				31140 // Иконка нации на глобалке

#endif
