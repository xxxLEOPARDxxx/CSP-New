#define SAILS_COLOR_QUANTITY				9
#define SHIP_TYPES_QUANTITY					137
#define SHIP_TYPES_QUANTITY_WITH_FORT		138	// must be (SHIP_TYPES_QUANTITY + 1)

//====================================================================================================================================================================================================================
//7											(�������� �������)		�����: �-��(������)														(���������)		(���. ��������������)	(��� ���: ����|����)
#define SHIP_TARTANE				0		// �������:					Gun: 0(0�)  | HP: 100 | ����: 50  | Crew: 12 | Speed: 7.0 | Turn: 50| FW: 8.0 |		|���:���,���,���,���,���|		[Trade]
#define SHIP_PLOT					1		// ����:					Gun: 5(8�)  | HP: 100 | ����: 210 | Crew: 10 | Speed: 3.0 | Turn: 10| FW: 7.0 |		|���:���,���,���,���,���|		[Trade]
#define SHIP_WAR_TARTANE			2		// ������:					Gun: 8(8�)  | HP: 210 | ����: 210 | Crew: 20 | Speed: 14.0| Turn: 70| FW: 7.0 |		|���:���,���,���,���,���|		[Trade]
//====================================================================================================================================================================================================================
//6 �����(8-12)
#define SHIP_BERMSLOOP 				3		// ˸�. ����:				Gun: 8(12�) | HP: 700 | ����: 600 | Crew: 45 | Speed: 15.8| Turn: 55| FW: 9.0 |		|���:���,���,���,���|			[Trade|WAR]
#define SHIP_EMPRESS				4		// �����������:				Gun: 10(8�) | HP: 1750| ����: 1200| Crew: 94 | Speed: 13.3| Turn: 50| FW: 7.0 |		|���:���,���,���,���|			[Trade]
#define SHIP_PINK					5		// ˸�. ����:				Gun: 12(12�)| HP: 800 | ����: 700 | Crew: 55 | Speed: 15.0| Turn: 50| FW: 8.5 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_LUGGER					6		// ������:					Gun: 12(12�)| HP: 600 | ����: 600 | Crew: 40 | Speed: 16.5| Turn: 60| FW: 10.0|		|���:���,���,���,���,���|		[WAR]
#define SHIP_LUGGER_H				7		// ���. ������:				Gun: 12(12�)| HP: 850 | ����: 900 | Crew: 50 | Speed: 15.5| Turn: 50| FW: 10.0|		|���:���,���,���,���,���|		[WAR]
#define SHIP_SPEEDY					8		// ��. ����:				Gun: 14(12�)| HP: 1150| ����: 1000| Crew: 70 | Speed: 15.0| Turn: 45| FW: 3.3 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_FR_SLOOP				9		// ���. ����:				Gun: 14(12�)| HP: 1500| ����: 800 | Crew: 72 | Speed: 15.3| Turn: 55| FW: 8.0 |		|���:���|						[WAR]
#define SHIP_GALEOTH_H				10		// ������:					Gun: 16(12�)| HP: 1800| ����: 1950| Crew: 90 | Speed: 12.0| Turn: 47| FW: 8.0 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_SLOOP					11		// ����:					Gun: 16(12�)| HP: 900 | ����: 800 | Crew: 75 | Speed: 13.8| Turn: 39| FW: 8.0 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_SLOOP_B				12		// ������ ����: 			Gun: 16(12�)| HP: 1450| ����: 1200| Crew: 95 | Speed: 14.0| Turn: 42| FW: 4.3 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_NEPTUNUS        	 	13		// ����. ����:				Gun: 16(12�)| HP: 1700| ����: 950 | Crew: 110| Speed: 13.5| Turn: 45| FW: 2.8 |		|���:���,���,���|				[WAR]
#define SHIP_SOPHIE					14		// ���. ����: 				Gun: 18(12�)| HP: 1450| ����: 1600| Crew: 125| Speed: 13.3| Turn: 35| FW: 3.3 |		|���:���,���,���,���,���|		[Trade|WAR]
//====================================================================================================================================================================================================================
//5 �����(8-12-16)
#define SHIP_POLACCA				15		// �������:					Gun: 14(12�)| HP: 2100| ����: 2250| Crew: 150| Speed: 11.0| Turn: 30| FW: 7.2 |		|���:���,���,���,���|			[Trade]
#define SHIP_BARQUE					16		// ����:					Gun: 16(16�)| HP: 1500| ����: 2200| Crew: 105| Speed: 9.0 | Turn: 25| FW: 3.6 |		|���:���,���,���,���|			[Trade]
#define SHIP_FR_POSTILLIONEN		17		// ���. ������: 			Gun: 20(12�)| HP: 2300| ����: 1200| Crew: 140| Speed: 14.8| Turn: 44| FW: 7.5 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_SCHOONER				18		// �����: 					Gun: 20(12�)| HP: 1550| ����: 1400| Crew: 120| Speed: 14.2| Turn: 35| FW: 7.5 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_COLONIALSCHOONER		19		// ���. �����: 				Gun: 20(12�)| HP: 1100| ����: 1100| Crew: 100| Speed: 15.5| Turn: 45| FW: 8.0 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_XEBEC					20		// ������: 					Gun: 20(12�)| HP: 1850| ����: 1800| Crew: 140| Speed: 14.5| Turn: 35| FW: 9.6 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_BATTLEXEBEC			21		// ����. ������:			Gun: 20(12�)| HP: 2400| ����: 1300| Crew: 140| Speed: 14.0| Turn: 35| FW: 9.2 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_XEBECLIGHT				22		// ���. ������: 			Gun: 22(8�) | HP: 1800| ����: 1600| Crew: 120| Speed: 15.3| Turn: 46| FW: 10.0|		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_SCHOONERLIGHT			23		// ��. �����: 				Gun: 22(12�)| HP: 1700| ����: 1000| Crew: 130| Speed: 14.0| Turn: 40| FW: 7.5 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_MIRAGE					24		// ���. �����: 				Gun: 22(12�)| HP: 2150| ����: 1300| Crew: 150| Speed: 13.5| Turn: 45| FW: 5.4 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_POLACRE			    25		// ������: 					Gun: 22(12�)| HP: 2550| ����: 1450| Crew: 135| Speed: 14.5| Turn: 25| FW: 7.6 |		|���:���,���,���|				[WAR]
#define SHIP_ENSLAVER				26		// ���. ����������: 		Gun: 22(12�)| HP: 2000| ����: 1300| Crew: 150| Speed: 16.0| Turn: 40| FW: 9.1 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_SHNYAVA				27		// �����: 					Gun: 22(8�) | HP: 2300| ����: 1950| Crew: 150| Speed: 14.0| Turn: 25| FW: 6.6 |		|���:���,���,���|				[Trade|WAR]
//====================================================================================================================================================================================================================
//4 �����(16-24)
#define SHIP_BRIG					28		// ����: 					Gun: 16(16�)| HP: 2700| ����: 1800| Crew: 160| Speed: 14.5| Turn: 45| FW: 3.3 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_BRIGHEAVY				29		// ���. ����: 				Gun: 16(16�)| HP: 3000| ����: 2000| Crew: 180| Speed: 14.0| Turn: 40| FW: 3.0 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_BARKENTINE				30		// ����������: 				Gun: 16(16�)| HP: 2400| ����: 2200| Crew: 180| Speed: 10.4| Turn: 40| FW: 8.5 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_BRIGANTINE				31		// ����������: 				Gun: 16(16�)| HP: 2300| ����: 1400| Crew: 140| Speed: 15.5| Turn: 50| FW: 9.1 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_CASTELF				32		// ���. ����������: 		Gun: 16(16�)| HP: 2550| ����: 1600| Crew: 150| Speed: 15.0| Turn: 50| FW: 6.1 |		|���:���,���|					[Trade|WAR]
#define SHIP_DERFFLINGER			33		// ����. �����:				Gun: 16(16�)| HP: 2700| ����: 2600| Crew: 240| Speed: 13.0| Turn: 30| FW: 4.0 |		|���:���,���,���,���|			[Trade|WAR]
#define SHIP_INTERCEPTOR			34		// ���-�����: 				Gun: 18(16�)| HP: 2800| ����: 1900| Crew: 160| Speed: 15.0| Turn: 40| FW: 4.3 |		|���:���,���,���|				[WAR]
#define SHIP_FLEUT					35		// �����: 					Gun: 18(16�)| HP: 3100| ����: 3000| Crew: 170| Speed: 12.0| Turn: 35| FW: 4.0 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_PO_FLEUT50				36		// ����. �����: 			Gun: 20(16�)| HP: 3600| ����: 3200| Crew: 160| Speed: 12.0| Turn: 35| FW: 4.0 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_GALEON_L				37		// ������: 					Gun: 20(16�)| HP: 3800| ����: 3400| Crew: 320| Speed: 11.0| Turn: 30| FW: 3.2 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_GREYHOUND				38		// ���. ������: 			Gun: 22(16�)| HP: 2400| ����: 1600| Crew: 150| Speed: 17.5| Turn: 30| FW: 4.0 |		|���:���,���,���|				[WAR]
#define SHIP_CORVETTELIGHT			39		// ���. ������: 			Gun: 22(16�)| HP: 2700| ����: 1400| Crew: 170| Speed: 16.8| Turn: 60| FW: 5.8 |		|���:���,���,���|				[WAR]
#define SHIP_PACKET_BRIG			40		// ����. ����: 				Gun: 22(16�)| HP: 3000| ����: 1900| Crew: 170| Speed: 14.5| Turn: 40| FW: 3.0 |		|���:���,���,���|				[WAR]
#define SHIP_PDN					41		// ���. ����: 				Gun: 24(16�)| HP: 3750| ����: 1700| Crew: 190| Speed: 14.0| Turn: 30| FW: 4.5 |		|���:���,���,���|				[WAR]
#define SHIP_ENTERPRISE				42		// ����. ���-�����: 		Gun: 24(16�)| HP: 2800| ����: 1700| Crew: 180| Speed: 14.5| Turn: 50| FW: 4.3 |		|���:���,���,���|				[WAR]
#define SHIP_POLACRE_H				43		// ���. ������: 			Gun: 24(16�)| HP: 3800| ����: 2200| Crew: 170| Speed: 14.0| Turn: 30| FW: 5.0 |		|���:���,���,���|				[WAR]
#define SHIP_CARAVEL				44		// ���������: 				Gun: 30(16�)| HP: 2300| ����: 3000| Crew: 195| Speed: 10.0| Turn: 29| FW: 4.0 |		|���:���,���,���,���|			[Trade]
#define SHIP_FRIGATEMEDIUM			45		// ��. ������: 				Gun: 30(16�)| HP: 4000| ����: 2300| Crew: 220| Speed: 13.5| Turn: 40| FW: 4.5 |		|���:���,���|					[WAR]
#define SHIP_RAAFRIGATE				46		// ��. ������: 				Gun: 32(16�)| HP: 3500| ����: 2000| Crew: 250| Speed: 14.0| Turn: 40| FW: 4.5 |		|���:���,���|					[WAR]
#define SHIP_CARAVEL2				47		// ����. ���������: 		Gun: 32(24�)| HP: 2700| ����: 2800| Crew: 280| Speed: 10.6| Turn: 32| FW: 4.0 |		|���:���,���,���,���|			[Trade|WAR]
#define SHIP_FLEUTWAR				48		// ���. ����. �����: 		Gun: 34(16�)| HP: 4500| ����: 3000| Crew: 200| Speed: 11.0| Turn: 35| FW: 4.0 |		|���:���,���,���,���|			[Trade|WAR]
#define SHIP_FLEUTWARSAT			49		// ���. ���. �����: 		Gun: 34(16�)| HP: 4000| ����: 2700| Crew: 230| Speed: 12.5| Turn: 25| FW: 4.0 |		|���:���|						[Trade|WAR]
#define SHIP_GALEONTRADER			50		// ����. �������: 			Gun: 34(24�)| HP: 2000| ����: 5000| Crew: 250| Speed: 8.0 | Turn: 25| FW: 2.6 |		|���:���,���,���,���|			[Trade]
#define SHIP_LYDIA					51		// ����. �������: 			Gun: 36(16�)| HP: 2700| ����: 4200| Crew: 170| Speed: 12.5| Turn: 35| FW: 2.6 |		|���:���,���,���,���|			[Trade]
//====================================================================================================================================================================================================================
//3 �����(16-24-32)
#define SHIP_PINNACE				52		// �����: 					Gun: 18(16�)| HP: 4950| ����: 4000| Crew: 270| Speed: 13.0| Turn: 30| FW: 6.0 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_DUTCHPINNACE			53		// ����. �����: 			Gun: 20(24�)| HP: 5000| ����: 3600| Crew: 310| Speed: 12.5| Turn: 30| FW: 6.0 |		|���:���,���,���|				[WAR]
#define SHIP_PINNACELIGHT			54		// ���������. �����: 		Gun: 30(16�)| HP: 5500| ����: 3000| Crew: 290| Speed: 13.0| Turn: 25| FW: 6.0 |		|���:���,���,���|				[Trade|WAR]
#define SHIP_XEBEKVT				55		// ���. ����. ������: 		Gun: 30(24�)| HP: 4600| ����: 2600| Crew: 240| Speed: 14.5| Turn: 45| FW: 8.8 |		|���:���,���,���,���|			[WAR]
#define SHIP_FELIPE					56		// ����. ������: 			Gun: 30(32�)| HP: 7000| ����: 4950| Crew: 440| Speed: 7.7 | Turn: 25| FW: 2.6 |		|���:���,���,���,���|			[Trade|WAR]
#define SHIP_CRIMSONBLOOD			57		// ���. ������: 			Gun: 30(16�)| HP: 4200| ����: 2000| Crew: 250| Speed: 16.8| Turn: 55| FW: 4.8 |		|���:���|						[WAR]
#define SHIP_CORVETTE				58		// ������: 					Gun: 32(24�)| HP: 4450| ����: 2250| Crew: 200| Speed: 16.2| Turn: 55| FW: 4.8 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_FRIGATE_l				59		// ���. ������: 			Gun: 32(24�)| HP: 4700| ����: 2000| Crew: 260| Speed: 15.7| Turn: 45| FW: 4.5 |		|���:���,���,���|				[WAR]
#define SHIP_BATTLECORVETTE			60		// ���. ������: 			Gun: 32(24�)| HP: 4800| ����: 2500| Crew: 230| Speed: 16.0| Turn: 45| FW: 3.8 |		|���:���,���,���|				[WAR]
#define SHIP_BLACKANGEL				61		// ������ ������: 			Gun: 32(32�)| HP: 4000| ����: 2000| Crew: 200| Speed: 15.5| Turn: 50| FW: 4.8 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_COASTALFRIGATE			62		// ��������� ������: 		Gun: 32(24�)| HP: 4800| ����: 3200| Crew: 290| Speed: 15.0| Turn: 45| FW: 4.5 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_FR_FRIGATE				63		// ���������� ������: 		Gun: 36(24�)| HP: 5800| ����: 2400| Crew: 330| Speed: 14.5| Turn: 35| FW: 4.6 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_JAMAICASHIP			64		// ���. �����: 				Gun: 36(16�)| HP: 5000| ����: 4500| Crew: 300| Speed: 12.0| Turn: 30| FW: 2.6 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_THEBLACKPEARL			65		// ���. ������: 			Gun: 36(24�)| HP: 6500| ����: 4000| Crew: 390| Speed: 9.0 | Turn: 25| FW: 2.6 |		|���:���|						[WAR]
#define SHIP_GALEON_H				66		// ���. ������: 			Gun: 36(32�)| HP: 6200| ����: 4650| Crew: 400| Speed: 8.0 | Turn: 25| FW: 2.6 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_GALEON1				67		// ���. ���. ������: 		Gun: 38(24�)| HP: 7800| ����: 5950| Crew: 520| Speed: 7.5 | Turn: 20| FW: 2.6 |		|���:���|						[Trade|WAR]
#define SHIP_LA_MARIANNA			68		// ���������� ������: 		Gun: 38(24�)| HP: 5600| ����: 4800| Crew: 380| Speed: 9.0 | Turn: 25| FW: 4.6 |		|���:���|						[WAR]
#define SHIP_PIRATFASTGAL			69		// ���. ������� ������: 	Gun: 38(24�)| HP: 6300| ����: 4000| Crew: 350| Speed: 10.5| Turn: 20| FW: 3.6 |		|���:���|						[WAR]
#define SHIP_UNICORN				70		// ������������ ������: 	Gun: 38(32�)| HP: 6300| ����: 3300| Crew: 360| Speed: 13.5| Turn: 35| FW: 5.5 |		|���:���,���,���|				[WAR]
#define SHIP_REVENGE				71		// ������ ������: 			Gun: 40(32�)| HP: 7000| ����: 4000| Crew: 400| Speed: 8.0 | Turn: 25| FW: 2.6 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_LINEFRIGATE			72		// ���. ������: 			Gun: 40(32�)| HP: 5000| ����: 3500| Crew: 380| Speed: 14.0| Turn: 35| FW: 3.6 |		|���:���,���|					[WAR]
#define SHIP_LIGHTFRIGATE			73		// ����. �������: 			Gun: 40(24�)| HP: 6500| ����: 4000| Crew: 420| Speed: 13.7| Turn: 30| FW: 2.6 |		|���:���,���,���,���|			[WAR]
#define SHIP_BOUSSOLE				74		// ���. ����. ������: 		Gun: 42(32�)| HP: 5150| ����: 2300| Crew: 280| Speed: 15.2| Turn: 30| FW: 4.5 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_SURPRISE				75		// ���. ������: 			Gun: 42(24�)| HP: 5600| ����: 3300| Crew: 320| Speed: 14.0| Turn: 35| FW: 4.5 |		|���:���|						[WAR]
#define SHIP_SALAMANDER				76		// ���. ������: 			Gun: 44(24�)| HP: 5400| ����: 2700| Crew: 300| Speed: 15.0| Turn: 45| FW: 3.6 |		|���:���|						[WAR]
#define SHIP_FRIGATE_SAT			77		// ���. ������: 			Gun: 44(24�)| HP: 6000| ����: 3600| Crew: 300| Speed: 13.5| Turn: 30| FW: 3.6 |		|���:���|						[WAR]
#define SHIP_BATTLEFRIGATE			78		// ���. ������: 			Gun: 44(24�)| HP: 5800| ����: 2500| Crew: 350| Speed: 14.0| Turn: 45| FW: 3.6 |		|���:���|						[WAR]
#define SHIP_NIGHTMARE				79		// ���. ������: 			Gun: 44(24�)| HP: 5000| ����: 2800| Crew: 330| Speed: 15.0| Turn: 35| FW: 3.6 |		|���:���|						[WAR]
#define SHIP_MORDAUNT				80		// ������ ��������: 		Gun: 46(32�)| HP: 5800| ����: 2100| Crew: 310| Speed: 15.0| Turn: 30| FW: 3.6 |		|���:���,���|	SPOINTS			[WAR]
#define SHIP_FRIGATE				81		// ������: 					Gun: 46(24�)| HP: 5400| ����: 3000| Crew: 300| Speed: 14.3| Turn: 38| FW: 3.6 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_AMSTERDAM				82		// ������ 3-�� ������: 		Gun: 50(32�)| HP: 4900| ����: 2800| Crew: 350| Speed: 12.5| Turn: 35| FW: 3.6 |		|���:���,���,���,���,���|		[Trade|WAR]
#define SHIP_CARRACA				83		// �������: 				Gun: 56(16�)| HP: 7200| ����: 6500| Crew: 550| Speed: 7.0 | Turn: 25| FW: 2.6 |		|���:���|						[Trade|WAR]
//====================================================================================================================================================================================================================
//2 �����(24-32)
#define SHIP_GALEON50				84		// ������������� ������: 	Gun: 40(32�)| HP: 7000| ����: 7500| Crew: 540| Speed: 8.8 | Turn: 25| FW: 3.0 |		|���:���,���|	SPOINTS			[Trade|WAR]
#define SHIP_FASTFRIGATE			85		// ������ ������: 			Gun: 42(32�)| HP: 6000| ����: 3200| Crew: 320| Speed: 15.5| Turn: 35| FW: 5.0 |		|���:���,���|					[WAR]
#define SHIP_FR_ESSEX				86		// ���. ������: 			Gun: 46(24�)| HP: 7000| ����: 3700| Crew: 350| Speed: 15.0| Turn: 40| FW: 3.6 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_FRIGATE_H			    87		// ���. ������: 			Gun: 50(32�)| HP: 6400| ����: 3500| Crew: 320| Speed: 14.5| Turn: 35| FW: 4.4 |		|���:���,���|					[WAR]
#define SHIP_WARGALLEON2			88		// ���. ����. ������: 		Gun: 52(32�)| HP: 7500| ����: 5500| Crew: 510| Speed: 8.5 | Turn: 30| FW: 2.6 |		|���:���,���,���|				[Trade|WAR]
#define SHIP_NL_PINNACEOFWAR47		89		// ���. ����. �����: 		Gun: 54(24�)| HP: 6500| ����: 5000| Crew: 400| Speed: 13.0| Turn: 30| FW: 2.6 |		|���:���,���,���,���|			[WAR]
#define SHIP_HOLLGALEON_H			90		// ���. ����. ������: 		Gun: 54(32�)| HP: 6800| ����: 5300| Crew: 470| Speed: 9.2 | Turn: 25| FW: 3.0 |		|���:���|						[Trade|WAR]
#define SHIP_FEARLESS				91		// ����. ����. �������: 	Gun: 56(24�)| HP: 7000| ����: 4000| Crew: 400| Speed: 13.5| Turn: 35| FW: 3.6 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_LINESHIP				92		// ����. �������: 			Gun: 56(32�)| HP: 8800| ����: 4350| Crew: 420| Speed: 13.0| Turn: 30| FW: 1.7 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_NL_FWZP				93		// ���. ����. ������: 		Gun: 56(32�)| HP: 8500| ����: 5500| Crew: 550| Speed: 8.0 | Turn: 25| FW: 1.7 |		|���:���|						[Trade|WAR]
#define SHIP_CONSTITUTION			94		// ���. ���. ������: 		Gun: 56(32�)| HP: 7700| ����: 3000| Crew: 340| Speed: 14.0| Turn: 35| FW: 3.5 |		|���:���,���|					[WAR]
#define SHIP_OXFORD                 95		// ������ �������: 			Gun: 58(24�)| HP: 7000| ����: 3300| Crew: 380| Speed: 14.5| Turn: 35| FW: 3.6 |		|���:���,���|	SPOINTS			[WAR]
#define SHIP_DUTCHLINESHIP			96		// ��. ����. �������: 		Gun: 60(32�)| HP: 7000| ����: 3800| Crew: 380| Speed: 13.5| Turn: 35| FW: 1.7 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_DUTCHSHIP				97		// ����. ������: 			Gun: 60(32�)| HP: 9900| ����: 4500| Crew: 450| Speed: 12.0| Turn: 30| FW: 2.5 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_NL_CONVOISHIP			98		// ���������� �������: 		Gun: 60(32�)| HP: 8200| ����: 4000| Crew: 420| Speed: 13.0| Turn: 30| FW: 2.7 |		|���:���,���,���,���|			[WAR]
#define SHIP_COURONNE				99		// ���. ����. ������: 		Gun: 64(32�)| HP: 9900| ����: 6500| Crew: 580| Speed: 7.5 | Turn: 25| FW: 1.5 |		|���:���|						[Trade|WAR]
#define SHIP_ALEXIS					100		// ������ 2-�� ������: 		Gun: 64(32�)| HP: 11500| ����: 4400| Crew: 470| Speed: 11.5| Turn: 25| FW: 1.7 |	|���:���,���,���,���,���|		[WAR]
#define SHIP_LINESHIPHEAVY			101		// ���. ����. �������: 		Gun: 64(32�)| HP: 10000| ����: 5300| Crew: 420| Speed: 12.0| Turn: 30| FW: 1.7 |	|���:���,���,���|				[WAR]
#define SHIP_WARSHIP				102		// �������� �������: 		Gun: 66(32�)| HP: 8900| ����: 5000| Crew: 500| Speed: 12.5| Turn: 35| FW: 1.5 |		|���:���,���,���,���,���|		[WAR]
#define SHIP_HEAVYWARSHIP			103		// ������: 					Gun: 74(24�)| HP: 9000| ����: 4800| Crew: 460| Speed: 13.5| Turn: 25| FW: 2.5 |		|���:���,���,���|				[Trade|WAR]
#define SHIP_HEAVYLINESHIP			104		// ���. ���. �����: 		Gun: 82(24�)| HP: 6000| ����: 5400| Crew: 480| Speed: 11.5| Turn: 25| FW: 1.0 |		|���:���,���,���,���,���|		[Trade|WAR]
//====================================================================================================================================================================================================================
//1 �����(42)
#define SHIP_POSEIDON				105		// ������: 					Gun: 66(42�) | HP: 8200 | ����: 3400| Crew: 420 | Speed: 13.5| Turn: 45| FW: 2.0 |	|���:���,���|					[WAR]
#define SHIP_HMS_CENTURION			106		// ������: 					Gun: 68(42�) | HP: 9000 | ����: 3900| Crew: 400 | Speed: 12.7| Turn: 38| FW: 1.8 |	|���:���,���|					[WAR]
#define SHIP_RESOLUTION             107		// ������ ���������: 		Gun: 70(42�) | HP: 7000 | ����: 4400| Crew: 450 | Speed: 13.5| Turn: 30| FW: 3.6 |	|���:���,���|					[WAR]
#define SHIP_FR_SUPERIORWARSHIP1	108		// ������ �������: 			Gun: 74(42�) | HP: 11500| ����: 4000| Crew: 540 | Speed: 13.0| Turn: 25| FW: 1.0 |	|���:���,���,���|				[WAR]
#define SHIP_LINK					109		// ���. ������: 			Gun: 78(42�) | HP: 10000| ����: 6000| Crew: 650 | Speed: 11.0| Turn: 30| FW: 1.0 |	|���:���,���,���|				[WAR]
#define SHIP_SUPERBE				110		// ���. ������: 			Gun: 78(42�) | HP: 11000| ����: 4500| Crew: 600 | Speed: 12.5| Turn: 25| FW: 2.0 |	|���:���,���,���|				[WAR]
#define SHIP_BATTLESHIP				111		// ������ �������: 			Gun: 80(42�) | HP: 12000| ����: 4900| Crew: 600 | Speed: 11.5| Turn: 32| FW: 1.0 |	|���:���,���,���,���,���|		[WAR]
#define SHIP_LINK2					112		// ���. ������: 			Gun: 82(42�) | HP: 15000| ����: 5500| Crew: 850 | Speed: 9.5 | Turn: 25| FW: 1.8 |	|���:���,���|					[WAR]
#define SHIP_BELLONA				113		// ������ 1-�� ������: 		Gun: 84(42�) | HP: 8500 | ����: 4500| Crew: 500 | Speed: 12.0| Turn: 30| FW: 1.0 |	|���:���,���|					[WAR]
#define SHIP_LINEARSHIP				114		// ���. ���. �������: 		Gun: 84(42�) | HP: 11000| ����: 4500| Crew: 650 | Speed: 11.8| Turn: 30| FW: 1.0 |	|���:���,���,���|				[WAR]
#define SHIP_SHARK					115		// ���. ���. �������: 		Gun: 84(42�) | HP: 10000| ����: 5500| Crew: 550 | Speed: 12.5| Turn: 30| FW: 1.0 |	|���:���,���,���|				[WAR]
#define SHIP_INTREPIDE				116		// ���. �������: 			Gun: 90(42�) | HP: 12000| ����: 5800| Crew: 650 | Speed: 11.0| Turn: 30| FW: 1.7 |	|���:���,���,���,���,���|		[WAR]
#define SHIP_FR_TRINITY				117		// ����. �������: 			Gun: 96(42�) | HP: 13000| ����: 6200| Crew: 720 | Speed: 10.0| Turn: 30| FW: 1.7 |	|���:���,���,���,���,���|		[WAR]
#define SHIP_MANOWAR_FAST			118		// ���. �������: 			Gun: 100(42�)| HP: 17000| ����: 6000| Crew: 850 | Speed: 9.5 | Turn: 20| FW: 1.0 |	|���:���|						[WAR]
#define SHIP_BATTLEMANOWAR			119		// ���. �������: 			Gun: 100(42�)| HP: 16000| ����: 6500| Crew: 950 | Speed: 9.0 | Turn: 20| FW: 1.0 |	|���:���|						[WAR]
#define SHIP_MANOWAR_GUB			120		// ���. �������: 			Gun: 100(42�)| HP: 15000| ����: 7000| Crew: 1050| Speed: 8.5 | Turn: 20| FW: 1.0 |	|���:���|						[WAR]
#define SHIP_PRINCE                 121		// ����������� ������: 		Gun: 100(42�)| HP: 12000| ����: 5000| Crew: 750 | Speed: 11.0| Turn: 25| FW: 1.0 |	|���:���|						[WAR]
#define SHIP_MANOWAR				122		// ���. �������: 			Gun: 102(42�)| HP: 13000| ����: 6800| Crew: 800 | Speed: 9.5 | Turn: 25| FW: 0.7 |	|���:���|						[WAR]
#define SHIP_HMS_VICTORY			123		// ������� ��������: 		Gun: 104(42�)| HP: 14000| ����: 6000| Crew: 900 | Speed: 9.8 | Turn: 22| FW: 1.0 |	|���:���|						[WAR]
#define SHIP_SP_SANFELIPE			124		// ���. �������: 			Gun: 108(42�)| HP: 13000| ����: 7500| Crew: 750 | Speed: 9.5 | Turn: 25| FW: 1.0 |	|���:���|						[WAR]
//====================================================================================================================================================================================================================
// QuestShip					(10 ��������)
#define SHIP_LUGGERQUEST     	   	125		// ���������� ������: 		Gun: 12(16�) | HP: 1100 | ����: 990 | Crew: 96  | Speed: 17.5| Turn: 60| FW: 11.0|		6 �����
#define SHIP_XEBEKVML				126		// ������: 					Gun: 22(16�) | HP: 2500 | ����: 1800| Crew: 180 | Speed: 17.5| Turn: 55| FW: 7.5 |		4 �����
#define SHIP_BRIGQEEN				127		// ����: 					Gun: 24(16�) | HP: 2800 | ����: 2000| Crew: 200 | Speed: 16.5| Turn: 45| FW: 6.0 |		4 �����
#define SHIP_BRIGSW					128		// ����:					Gun: 24(16�) | HP: 3200 | ����: 2100| Crew: 130 | Speed: 16.5| Turn: 50| FW: 7.5 |		4 �����
#define SHIP_CORVETTE_QUEST			129		// ������: 					Gun: 40(24�) | HP: 3800 | ����: 2700| Crew: 250 | Speed: 18.0| Turn: 60| FW: 5.5 |		3 �����
#define SHIP_ARABELLA				130		// ������: 					Gun: 52(32�) | HP: 6000 | ����: 3700| Crew: 350 | Speed: 16.0| Turn: 42| FW: 4.0 |		2 �����
#define SHIP_FRIGATEQUEEN			131		// ������: 					Gun: 52(32�) | HP: 5500 | ����: 3200| Crew: 300 | Speed: 17.0| Turn: 45| FW: 4.5 |		2 �����
#define SHIP_FLYINGDUTCHMAN			132		// ������: 					Gun: 60(42�) | HP: 7700 | ����: 5200| Crew: 444 | Speed: 15.0| Turn: 40| FW: 3.0 |		2 �����
#define SHIP_SANTISIMA		 	   	133		// ������� �������: 		Gun: 106(42�)| HP: 10700| ����: 5750| Crew: 800 | Speed: 13.0| Turn: 32| FW: 1.2 |		1 �����
#define SHIP_SOLEYRU				134		// ����� ������: 			Gun: 112(42�)| HP: 18000| ����: 6800| Crew: 1200| Speed: 10.6| Turn: 29| FW: 1.3 |		1 �����
//====================================================================================================================================================================================================================

//	����� + ����
#define SHIP_BOAT          	  	   135
#define SHIP_FORT           	   136


#define SHIP_NOTUSED			 1000
#define SHIP_NOTUSED_TYPE_NAME	"Not Used"
#define SHIP_NAME_NOTUSED		"Noname"

object  ShipsTypes[SHIP_TYPES_QUANTITY_WITH_FORT];  // RealShips
object	SailsColors[SAILS_COLOR_QUANTITY];


ref GetShipByType(int iType) { return &ShipsTypes[iType]; }  // ���������� GetRealShip