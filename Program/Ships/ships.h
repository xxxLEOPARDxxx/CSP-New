#define SAILS_COLOR_QUANTITY				9
#define SHIP_TYPES_QUANTITY					137
#define SHIP_TYPES_QUANTITY_WITH_FORT		138	// must be (SHIP_TYPES_QUANTITY + 1)

//====================================================================================================================================================================================================================
//7											(Название корабля)		Пушки: к-во(калибр)														(Бейдевинд)		(Нац. принадлежность)	(Тип кор: торг|воен)
#define SHIP_TARTANE				0		// Тартана:					Gun: 0(0ф)  | HP: 100 | трюм: 50  | Crew: 12 | Speed: 7.0 | Turn: 50| FW: 8.0 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade]
#define SHIP_PLOT					1		// Плот:					Gun: 5(8ф)  | HP: 100 | трюм: 210 | Crew: 10 | Speed: 3.0 | Turn: 10| FW: 7.0 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade]
#define SHIP_WAR_TARTANE			2		// Баркас:					Gun: 8(8ф)  | HP: 210 | трюм: 210 | Crew: 20 | Speed: 14.0| Turn: 70| FW: 7.0 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade]
//====================================================================================================================================================================================================================
//6 пушки(8-12)
#define SHIP_BERMSLOOP 				3		// Лёг. Шлюп:				Gun: 8(12ф) | HP: 700 | трюм: 600 | Crew: 45 | Speed: 15.8| Turn: 55| FW: 9.0 |		|Нац:Анг,Фра,Гол,Исп|			[Trade|WAR]
#define SHIP_EMPRESS				4		// Императрица:				Gun: 10(8ф) | HP: 1750| трюм: 1200| Crew: 94 | Speed: 13.3| Turn: 50| FW: 7.0 |		|Нац:Анг,Фра,Гол,Исп|			[Trade]
#define SHIP_PINK					5		// Лёг. Шлюп:				Gun: 12(12ф)| HP: 800 | трюм: 700 | Crew: 55 | Speed: 15.0| Turn: 50| FW: 8.5 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_LUGGER					6		// Люггер:					Gun: 12(12ф)| HP: 600 | трюм: 600 | Crew: 40 | Speed: 16.5| Turn: 60| FW: 10.0|		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_LUGGER_H				7		// Тяж. Люггер:				Gun: 12(12ф)| HP: 850 | трюм: 900 | Crew: 50 | Speed: 15.5| Turn: 50| FW: 10.0|		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_SPEEDY					8		// Ср. Шлюп:				Gun: 14(12ф)| HP: 1150| трюм: 1000| Crew: 70 | Speed: 15.0| Turn: 45| FW: 3.3 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_FR_SLOOP				9		// Пир. Шлюп:				Gun: 14(12ф)| HP: 1500| трюм: 800 | Crew: 72 | Speed: 15.3| Turn: 55| FW: 8.0 |		|Нац:Пир|						[WAR]
#define SHIP_GALEOTH_H				10		// Галеот:					Gun: 16(12ф)| HP: 1800| трюм: 1950| Crew: 90 | Speed: 12.0| Turn: 47| FW: 8.0 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_SLOOP					11		// Шлюп:					Gun: 16(12ф)| HP: 900 | трюм: 800 | Crew: 75 | Speed: 13.8| Turn: 39| FW: 8.0 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_SLOOP_B				12		// Боевой Шлюп: 			Gun: 16(12ф)| HP: 1450| трюм: 1200| Crew: 95 | Speed: 14.0| Turn: 42| FW: 4.3 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_NEPTUNUS        	 	13		// Усил. Шлюп:				Gun: 16(12ф)| HP: 1700| трюм: 950 | Crew: 110| Speed: 13.5| Turn: 45| FW: 2.8 |		|Нац:Фра,Гол,Пир|				[WAR]
#define SHIP_SOPHIE					14		// Тяж. Шлюп: 				Gun: 18(12ф)| HP: 1450| трюм: 1600| Crew: 125| Speed: 13.3| Turn: 35| FW: 3.3 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
//====================================================================================================================================================================================================================
//5 пушки(8-12-16)
#define SHIP_POLACCA				15		// Полакка:					Gun: 14(12ф)| HP: 2100| трюм: 2250| Crew: 150| Speed: 11.0| Turn: 30| FW: 7.2 |		|Нац:Анг,Фра,Гол,Исп|			[Trade]
#define SHIP_BARQUE					16		// Барк:					Gun: 16(16ф)| HP: 1500| трюм: 2200| Crew: 105| Speed: 9.0 | Turn: 25| FW: 3.6 |		|Нац:Анг,Фра,Гол,Исп|			[Trade]
#define SHIP_FR_POSTILLIONEN		17		// Лег. Фрегат: 			Gun: 20(12ф)| HP: 2300| трюм: 1200| Crew: 140| Speed: 14.8| Turn: 44| FW: 7.5 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_SCHOONER				18		// Шхуна: 					Gun: 20(12ф)| HP: 1550| трюм: 1400| Crew: 120| Speed: 14.2| Turn: 35| FW: 7.5 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_COLONIALSCHOONER		19		// Лег. Шхуна: 				Gun: 20(12ф)| HP: 1100| трюм: 1100| Crew: 100| Speed: 15.5| Turn: 45| FW: 8.0 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_XEBEC					20		// Щебека: 					Gun: 20(12ф)| HP: 1850| трюм: 1800| Crew: 140| Speed: 14.5| Turn: 35| FW: 9.6 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_BATTLEXEBEC			21		// Усил. Щебека:			Gun: 20(12ф)| HP: 2400| трюм: 1300| Crew: 140| Speed: 14.0| Turn: 35| FW: 9.2 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_XEBECLIGHT				22		// Лег. Щебека: 			Gun: 22(8ф) | HP: 1800| трюм: 1600| Crew: 120| Speed: 15.3| Turn: 46| FW: 10.0|		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_SCHOONERLIGHT			23		// Ср. Шхуна: 				Gun: 22(12ф)| HP: 1700| трюм: 1000| Crew: 130| Speed: 14.0| Turn: 40| FW: 7.5 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_MIRAGE					24		// Тяж. Шхуна: 				Gun: 22(12ф)| HP: 2150| трюм: 1300| Crew: 150| Speed: 13.5| Turn: 45| FW: 5.4 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_POLACRE			    25		// Полакр: 					Gun: 22(12ф)| HP: 2550| трюм: 1450| Crew: 135| Speed: 14.5| Turn: 25| FW: 7.6 |		|Нац:Анг,Фра,Пир|				[WAR]
#define SHIP_ENSLAVER				26		// Пир. Бригантина: 		Gun: 22(12ф)| HP: 2000| трюм: 1300| Crew: 150| Speed: 16.0| Turn: 40| FW: 9.1 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_SHNYAVA				27		// Шнява: 					Gun: 22(8ф) | HP: 2300| трюм: 1950| Crew: 150| Speed: 14.0| Turn: 25| FW: 6.6 |		|Нац:Фра,Гол,Исп|				[Trade|WAR]
//====================================================================================================================================================================================================================
//4 пушки(16-24)
#define SHIP_BRIG					28		// Бриг: 					Gun: 16(16ф)| HP: 2700| трюм: 1800| Crew: 160| Speed: 14.5| Turn: 45| FW: 3.3 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_BRIGHEAVY				29		// Тяж. Бриг: 				Gun: 16(16ф)| HP: 3000| трюм: 2000| Crew: 180| Speed: 14.0| Turn: 40| FW: 3.0 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_BARKENTINE				30		// Баркентина: 				Gun: 16(16ф)| HP: 2400| трюм: 2200| Crew: 180| Speed: 10.4| Turn: 40| FW: 8.5 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_BRIGANTINE				31		// Бригантина: 				Gun: 16(16ф)| HP: 2300| трюм: 1400| Crew: 140| Speed: 15.5| Turn: 50| FW: 9.1 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_CASTELF				32		// Тяж. Бригантина: 		Gun: 16(16ф)| HP: 2550| трюм: 1600| Crew: 150| Speed: 15.0| Turn: 50| FW: 6.1 |		|Нац:Анг,Гол|					[Trade|WAR]
#define SHIP_DERFFLINGER			33		// Воен. Флейт:				Gun: 16(16ф)| HP: 2700| трюм: 2600| Crew: 240| Speed: 13.0| Turn: 30| FW: 4.0 |		|Нац:Анг,Фра,Гол,Исп|			[Trade|WAR]
#define SHIP_INTERCEPTOR			34		// Ост-индец: 				Gun: 18(16ф)| HP: 2800| трюм: 1900| Crew: 160| Speed: 15.0| Turn: 40| FW: 4.3 |		|Нац:Анг,Исп,Пир|				[WAR]
#define SHIP_FLEUT					35		// Флейт: 					Gun: 18(16ф)| HP: 3100| трюм: 3000| Crew: 170| Speed: 12.0| Turn: 35| FW: 4.0 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_PO_FLEUT50				36		// Усил. Флейт: 			Gun: 20(16ф)| HP: 3600| трюм: 3200| Crew: 160| Speed: 12.0| Turn: 35| FW: 4.0 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_GALEON_L				37		// Галеон: 					Gun: 20(16ф)| HP: 3800| трюм: 3400| Crew: 320| Speed: 11.0| Turn: 30| FW: 3.2 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_GREYHOUND				38		// Лег. Корвет: 			Gun: 22(16ф)| HP: 2400| трюм: 1600| Crew: 150| Speed: 17.5| Turn: 30| FW: 4.0 |		|Нац:Фра,Гол,Пир|				[WAR]
#define SHIP_CORVETTELIGHT			39		// Лег. Корвет: 			Gun: 22(16ф)| HP: 2700| трюм: 1400| Crew: 170| Speed: 16.8| Turn: 60| FW: 5.8 |		|Нац:Анг,Пир,Исп|				[WAR]
#define SHIP_PACKET_BRIG			40		// Воен. Бриг: 				Gun: 22(16ф)| HP: 3000| трюм: 1900| Crew: 170| Speed: 14.5| Turn: 40| FW: 3.0 |		|Нац:Анг,Гол,Пир|				[WAR]
#define SHIP_PDN					41		// Лин. Бриг: 				Gun: 24(16ф)| HP: 3750| трюм: 1700| Crew: 190| Speed: 14.0| Turn: 30| FW: 4.5 |		|Нац:Фра,Пир,Исп|				[WAR]
#define SHIP_ENTERPRISE				42		// Воен. Ост-индец: 		Gun: 24(16ф)| HP: 2800| трюм: 1700| Crew: 180| Speed: 14.5| Turn: 50| FW: 4.3 |		|Нац:Фра,Гол,Пир|				[WAR]
#define SHIP_POLACRE_H				43		// Тяж. Полакр: 			Gun: 24(16ф)| HP: 3800| трюм: 2200| Crew: 170| Speed: 14.0| Turn: 30| FW: 5.0 |		|Нац:Анг,Пир,Исп|				[WAR]
#define SHIP_CARAVEL				44		// Каравелла: 				Gun: 30(16ф)| HP: 2300| трюм: 3000| Crew: 195| Speed: 10.0| Turn: 29| FW: 4.0 |		|Нац:Анг,Фра,Гол,Исп|			[Trade]
#define SHIP_FRIGATEMEDIUM			45		// Ср. Фрегат: 				Gun: 30(16ф)| HP: 4000| трюм: 2300| Crew: 220| Speed: 13.5| Turn: 40| FW: 4.5 |		|Нац:Анг,Исп|					[WAR]
#define SHIP_RAAFRIGATE				46		// Ср. Фрегат: 				Gun: 32(16ф)| HP: 3500| трюм: 2000| Crew: 250| Speed: 14.0| Turn: 40| FW: 4.5 |		|Нац:Фра,Гол|					[WAR]
#define SHIP_CARAVEL2				47		// Воен. Каравелла: 		Gun: 32(24ф)| HP: 2700| трюм: 2800| Crew: 280| Speed: 10.6| Turn: 32| FW: 4.0 |		|Нац:Анг,Фра,Гол,Исп|			[Trade|WAR]
#define SHIP_FLEUTWAR				48		// Тяж. Боев. Флейт: 		Gun: 34(16ф)| HP: 4500| трюм: 3000| Crew: 200| Speed: 11.0| Turn: 35| FW: 4.0 |		|Нац:Анг,Фра,Гол,Исп|			[Trade|WAR]
#define SHIP_FLEUTWARSAT			49		// Пир. Тяж. Флейт: 		Gun: 34(16ф)| HP: 4000| трюм: 2700| Crew: 230| Speed: 12.5| Turn: 25| FW: 4.0 |		|Нац:Пир|						[Trade|WAR]
#define SHIP_GALEONTRADER			50		// Торг. Корабль: 			Gun: 34(24ф)| HP: 2000| трюм: 5000| Crew: 250| Speed: 8.0 | Turn: 25| FW: 2.6 |		|Нац:Анг,Фра,Гол,Исп|			[Trade]
#define SHIP_LYDIA					51		// Торг. Корабль: 			Gun: 36(16ф)| HP: 2700| трюм: 4200| Crew: 170| Speed: 12.5| Turn: 35| FW: 2.6 |		|Нац:Анг,Фра,Гол,Исп|			[Trade]
//====================================================================================================================================================================================================================
//3 пушки(16-24-32)
#define SHIP_PINNACE				52		// Пинас: 					Gun: 18(16ф)| HP: 4950| трюм: 4000| Crew: 270| Speed: 13.0| Turn: 30| FW: 6.0 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_DUTCHPINNACE			53		// Воен. Пинас: 			Gun: 20(24ф)| HP: 5000| трюм: 3600| Crew: 310| Speed: 12.5| Turn: 30| FW: 6.0 |		|Нац:Анг,Фра,Гол|				[WAR]
#define SHIP_PINNACELIGHT			54		// Двухпалуб. Пинас: 		Gun: 30(16ф)| HP: 5500| трюм: 3000| Crew: 290| Speed: 13.0| Turn: 25| FW: 6.0 |		|Нац:Анг,Пир,Исп|				[Trade|WAR]
#define SHIP_XEBEKVT				55		// Тяж. Воен. Щебека: 		Gun: 30(24ф)| HP: 4600| трюм: 2600| Crew: 240| Speed: 14.5| Turn: 45| FW: 8.8 |		|Нац:Анг,Фра,Гол,Исп|			[WAR]
#define SHIP_FELIPE					56		// Воен. Галеон: 			Gun: 30(32ф)| HP: 7000| трюм: 4950| Crew: 440| Speed: 7.7 | Turn: 25| FW: 2.6 |		|Нац:Анг,Фра,Гол,Исп|			[Trade|WAR]
#define SHIP_CRIMSONBLOOD			57		// Пир. Корвет: 			Gun: 30(16ф)| HP: 4200| трюм: 2000| Crew: 250| Speed: 16.8| Turn: 55| FW: 4.8 |		|Нац:Пир|						[WAR]
#define SHIP_CORVETTE				58		// Корвет: 					Gun: 32(24ф)| HP: 4450| трюм: 2250| Crew: 200| Speed: 16.2| Turn: 55| FW: 4.8 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_FRIGATE_l				59		// Тяж. Корвет: 			Gun: 32(24ф)| HP: 4700| трюм: 2000| Crew: 260| Speed: 15.7| Turn: 45| FW: 4.5 |		|Нац:Анг,Гол,Пир|				[WAR]
#define SHIP_BATTLECORVETTE			60		// Тяж. Корвет: 			Gun: 32(24ф)| HP: 4800| трюм: 2500| Crew: 230| Speed: 16.0| Turn: 45| FW: 3.8 |		|Нац:Фра,Пир,Исп|				[WAR]
#define SHIP_BLACKANGEL				61		// Боевой Корвет: 			Gun: 32(32ф)| HP: 4000| трюм: 2000| Crew: 200| Speed: 15.5| Turn: 50| FW: 4.8 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_COASTALFRIGATE			62		// Береговой Фрегат: 		Gun: 32(24ф)| HP: 4800| трюм: 3200| Crew: 290| Speed: 15.0| Turn: 45| FW: 4.5 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_FR_FRIGATE				63		// Корсарский Фрегат: 		Gun: 36(24ф)| HP: 5800| трюм: 2400| Crew: 330| Speed: 14.5| Turn: 35| FW: 4.6 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_JAMAICASHIP			64		// Тяж. Пинас: 				Gun: 36(16ф)| HP: 5000| трюм: 4500| Crew: 300| Speed: 12.0| Turn: 30| FW: 2.6 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_THEBLACKPEARL			65		// Пир. Галеон: 			Gun: 36(24ф)| HP: 6500| трюм: 4000| Crew: 390| Speed: 9.0 | Turn: 25| FW: 2.6 |		|Нац:Пир|						[WAR]
#define SHIP_GALEON_H				66		// Тяж. Галеон: 			Gun: 36(32ф)| HP: 6200| трюм: 4650| Crew: 400| Speed: 8.0 | Turn: 25| FW: 2.6 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_GALEON1				67		// Исп. Тяж. Галеон: 		Gun: 38(24ф)| HP: 7800| трюм: 5950| Crew: 520| Speed: 7.5 | Turn: 20| FW: 2.6 |		|Нац:Исп|						[Trade|WAR]
#define SHIP_LA_MARIANNA			68		// Призрачный Галеон: 		Gun: 38(24ф)| HP: 5600| трюм: 4800| Crew: 380| Speed: 9.0 | Turn: 25| FW: 4.6 |		|Нац:Пир|						[WAR]
#define SHIP_PIRATFASTGAL			69		// Пир. Быстрый Галеон: 	Gun: 38(24ф)| HP: 6300| трюм: 4000| Crew: 350| Speed: 10.5| Turn: 20| FW: 3.6 |		|Нац:Пир|						[WAR]
#define SHIP_UNICORN				70		// Приватирский Фрегат: 	Gun: 38(32ф)| HP: 6300| трюм: 3300| Crew: 360| Speed: 13.5| Turn: 35| FW: 5.5 |		|Нац:Анг,Гол,Пир|				[WAR]
#define SHIP_REVENGE				71		// Боевой Галеон: 			Gun: 40(32ф)| HP: 7000| трюм: 4000| Crew: 400| Speed: 8.0 | Turn: 25| FW: 2.6 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_LINEFRIGATE			72		// Лин. Фрегат: 			Gun: 40(32ф)| HP: 5000| трюм: 3500| Crew: 380| Speed: 14.0| Turn: 35| FW: 3.6 |		|Нац:Фра,Гол|					[WAR]
#define SHIP_LIGHTFRIGATE			73		// Патр. Корабль: 			Gun: 40(24ф)| HP: 6500| трюм: 4000| Crew: 420| Speed: 13.7| Turn: 30| FW: 2.6 |		|Нац:Анг,Фра,Гол,Исп|			[WAR]
#define SHIP_BOUSSOLE				74		// Тяж. Воен. Корвет: 		Gun: 42(32ф)| HP: 5150| трюм: 2300| Crew: 280| Speed: 15.2| Turn: 30| FW: 4.5 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_SURPRISE				75		// Фра. фрегат: 			Gun: 42(24ф)| HP: 5600| трюм: 3300| Crew: 320| Speed: 14.0| Turn: 35| FW: 4.5 |		|Нац:Фра|						[WAR]
#define SHIP_SALAMANDER				76		// Анг. фрегат: 			Gun: 44(24ф)| HP: 5400| трюм: 2700| Crew: 300| Speed: 15.0| Turn: 45| FW: 3.6 |		|Нац:Анг|						[WAR]
#define SHIP_FRIGATE_SAT			77		// Исп. фрегат: 			Gun: 44(24ф)| HP: 6000| трюм: 3600| Crew: 300| Speed: 13.5| Turn: 30| FW: 3.6 |		|Нац:Исп|						[WAR]
#define SHIP_BATTLEFRIGATE			78		// Гол. фрегат: 			Gun: 44(24ф)| HP: 5800| трюм: 2500| Crew: 350| Speed: 14.0| Turn: 45| FW: 3.6 |		|Нац:Гол|						[WAR]
#define SHIP_NIGHTMARE				79		// Пир. фрегат: 			Gun: 44(24ф)| HP: 5000| трюм: 2800| Crew: 330| Speed: 15.0| Turn: 35| FW: 3.6 |		|Нац:Пир|						[WAR]
#define SHIP_MORDAUNT				80		// Фрегат Мордаунт: 		Gun: 46(32ф)| HP: 5800| трюм: 2100| Crew: 310| Speed: 15.0| Turn: 30| FW: 3.6 |		|Нац:Фра,Гол|	SPOINTS			[WAR]
#define SHIP_FRIGATE				81		// Фрегат: 					Gun: 46(24ф)| HP: 5400| трюм: 3000| Crew: 300| Speed: 14.3| Turn: 38| FW: 3.6 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_AMSTERDAM				82		// Линкор 3-го класса: 		Gun: 50(32ф)| HP: 4900| трюм: 2800| Crew: 350| Speed: 12.5| Turn: 35| FW: 3.6 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
#define SHIP_CARRACA				83		// Каракка: 				Gun: 56(16ф)| HP: 7200| трюм: 6500| Crew: 550| Speed: 7.0 | Turn: 25| FW: 2.6 |		|Нац:Гол|						[Trade|WAR]
//====================================================================================================================================================================================================================
//2 пушки(24-32)
#define SHIP_GALEON50				84		// Императорский Галеон: 	Gun: 40(32ф)| HP: 7000| трюм: 7500| Crew: 540| Speed: 8.8 | Turn: 25| FW: 3.0 |		|Нац:Гол,Исп|	SPOINTS			[Trade|WAR]
#define SHIP_FASTFRIGATE			85		// Боевой Фрегат: 			Gun: 42(32ф)| HP: 6000| трюм: 3200| Crew: 320| Speed: 15.5| Turn: 35| FW: 5.0 |		|Нац:Анг,Исп|					[WAR]
#define SHIP_FR_ESSEX				86		// Тяж. Фрегат: 			Gun: 46(24ф)| HP: 7000| трюм: 3700| Crew: 350| Speed: 15.0| Turn: 40| FW: 3.6 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_FRIGATE_H			    87		// Тяж. Фрегат: 			Gun: 50(32ф)| HP: 6400| трюм: 3500| Crew: 320| Speed: 14.5| Turn: 35| FW: 4.4 |		|Нац:Фра,Гол|					[WAR]
#define SHIP_WARGALLEON2			88		// Тяж. Воен. Галеон: 		Gun: 52(32ф)| HP: 7500| трюм: 5500| Crew: 510| Speed: 8.5 | Turn: 30| FW: 2.6 |		|Нац:Гол,Пир,Исп|				[Trade|WAR]
#define SHIP_NL_PINNACEOFWAR47		89		// Тяж. Воен. Пинас: 		Gun: 54(24ф)| HP: 6500| трюм: 5000| Crew: 400| Speed: 13.0| Turn: 30| FW: 2.6 |		|Нац:Анг,Фра,Гол,Исп|			[WAR]
#define SHIP_HOLLGALEON_H			90		// Гол. Воен. Галеон: 		Gun: 54(32ф)| HP: 6800| трюм: 5300| Crew: 470| Speed: 9.2 | Turn: 25| FW: 3.0 |		|Нац:Гол|						[Trade|WAR]
#define SHIP_FEARLESS				91		// Усил. Патр. Корабль: 	Gun: 56(24ф)| HP: 7000| трюм: 4000| Crew: 400| Speed: 13.5| Turn: 35| FW: 3.6 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_LINESHIP				92		// Воен. Корабль: 			Gun: 56(32ф)| HP: 8800| трюм: 4350| Crew: 420| Speed: 13.0| Turn: 30| FW: 1.7 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_NL_FWZP				93		// Анг. Воен. Галеон: 		Gun: 56(32ф)| HP: 8500| трюм: 5500| Crew: 550| Speed: 8.0 | Turn: 25| FW: 1.7 |		|Нац:Анг|						[Trade|WAR]
#define SHIP_CONSTITUTION			94		// Тяж. Лин. фрегат: 		Gun: 56(32ф)| HP: 7700| трюм: 3000| Crew: 340| Speed: 14.0| Turn: 35| FW: 3.5 |		|Нац:Фра,Исп|					[WAR]
#define SHIP_OXFORD                 95		// Фрегат Оксфорд: 			Gun: 58(24ф)| HP: 7000| трюм: 3300| Crew: 380| Speed: 14.5| Turn: 35| FW: 3.6 |		|Нац:Анг,Гол|	SPOINTS			[WAR]
#define SHIP_DUTCHLINESHIP			96		// Ср. Воен. Корабль: 		Gun: 60(32ф)| HP: 7000| трюм: 3800| Crew: 380| Speed: 13.5| Turn: 35| FW: 1.7 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_DUTCHSHIP				97		// Усил. Фрегат: 			Gun: 60(32ф)| HP: 9900| трюм: 4500| Crew: 450| Speed: 12.0| Turn: 30| FW: 2.5 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_NL_CONVOISHIP			98		// Сторожевой Корабль: 		Gun: 60(32ф)| HP: 8200| трюм: 4000| Crew: 420| Speed: 13.0| Turn: 30| FW: 2.7 |		|Нац:Анг,Фра,Гол,Исп|			[WAR]
#define SHIP_COURONNE				99		// Фра. Воен. Галеон: 		Gun: 64(32ф)| HP: 9900| трюм: 6500| Crew: 580| Speed: 7.5 | Turn: 25| FW: 1.5 |		|Нац:Фра|						[Trade|WAR]
#define SHIP_ALEXIS					100		// Линкор 2-го класса: 		Gun: 64(32ф)| HP: 11500| трюм: 4400| Crew: 470| Speed: 11.5| Turn: 25| FW: 1.7 |	|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_LINESHIPHEAVY			101		// Тяж. Воен. Корабль: 		Gun: 64(32ф)| HP: 10000| трюм: 5300| Crew: 420| Speed: 12.0| Turn: 30| FW: 1.7 |	|Нац:Анг,Фра,Пир|				[WAR]
#define SHIP_WARSHIP				102		// Линейный Корабль: 		Gun: 66(32ф)| HP: 8900| трюм: 5000| Crew: 500| Speed: 12.5| Turn: 35| FW: 1.5 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_HEAVYWARSHIP			103		// Варшип: 					Gun: 74(24ф)| HP: 9000| трюм: 4800| Crew: 460| Speed: 13.5| Turn: 25| FW: 2.5 |		|Нац:Гол,Пир,Исп|				[Trade|WAR]
#define SHIP_HEAVYLINESHIP			104		// Тяж. Лин. Пинас: 		Gun: 82(24ф)| HP: 6000| трюм: 5400| Crew: 480| Speed: 11.5| Turn: 25| FW: 1.0 |		|Нац:Анг,Фра,Гол,Пир,Исп|		[Trade|WAR]
//====================================================================================================================================================================================================================
//1 пушки(42)
#define SHIP_POSEIDON				105		// Линкор: 					Gun: 66(42ф) | HP: 8200 | трюм: 3400| Crew: 420 | Speed: 13.5| Turn: 45| FW: 2.0 |	|Нац:Фра,Исп|					[WAR]
#define SHIP_HMS_CENTURION			106		// Линкор: 					Gun: 68(42ф) | HP: 9000 | трюм: 3900| Crew: 400 | Speed: 12.7| Turn: 38| FW: 1.8 |	|Нац:Анг,Гол|					[WAR]
#define SHIP_RESOLUTION             107		// Фрегат Резолюция: 		Gun: 70(42ф) | HP: 7000 | трюм: 4400| Crew: 450 | Speed: 13.5| Turn: 30| FW: 3.6 |	|Нац:Фра,Гол|					[WAR]
#define SHIP_FR_SUPERIORWARSHIP1	108		// Боевой Корабль: 			Gun: 74(42ф) | HP: 11500| трюм: 4000| Crew: 540 | Speed: 13.0| Turn: 25| FW: 1.0 |	|Нац:Анг,Фра,Пир|				[WAR]
#define SHIP_LINK					109		// Тяж. Линкор: 			Gun: 78(42ф) | HP: 10000| трюм: 6000| Crew: 650 | Speed: 11.0| Turn: 30| FW: 1.0 |	|Нац:Анг,Гол,Пир|				[WAR]
#define SHIP_SUPERBE				110		// Тяж. Линкор: 			Gun: 78(42ф) | HP: 11000| трюм: 4500| Crew: 600 | Speed: 12.5| Turn: 25| FW: 2.0 |	|Нац:Фра,Пир,Исп|				[WAR]
#define SHIP_BATTLESHIP				111		// Боевой Корабль: 			Gun: 80(42ф) | HP: 12000| трюм: 4900| Crew: 600 | Speed: 11.5| Turn: 32| FW: 1.0 |	|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_LINK2					112		// Тяж. Варшип: 			Gun: 82(42ф) | HP: 15000| трюм: 5500| Crew: 850 | Speed: 9.5 | Turn: 25| FW: 1.8 |	|Нац:Анг,Исп|					[WAR]
#define SHIP_BELLONA				113		// Линкор 1-го класса: 		Gun: 84(42ф) | HP: 8500 | трюм: 4500| Crew: 500 | Speed: 12.0| Turn: 30| FW: 1.0 |	|Нац:Фра,Гол|					[WAR]
#define SHIP_LINEARSHIP				114		// Тяж. Лин. Корабль: 		Gun: 84(42ф) | HP: 11000| трюм: 4500| Crew: 650 | Speed: 11.8| Turn: 30| FW: 1.0 |	|Нац:Анг,Фра,Пир|				[WAR]
#define SHIP_SHARK					115		// Тяж. Лин. Корабль: 		Gun: 84(42ф) | HP: 10000| трюм: 5500| Crew: 550 | Speed: 12.5| Turn: 30| FW: 1.0 |	|Нац:Гол,Пир,Исп|				[WAR]
#define SHIP_INTREPIDE				116		// Лег. Мановар: 			Gun: 90(42ф) | HP: 12000| трюм: 5800| Crew: 650 | Speed: 11.0| Turn: 30| FW: 1.7 |	|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_FR_TRINITY				117		// Воен. Мановар: 			Gun: 96(42ф) | HP: 13000| трюм: 6200| Crew: 720 | Speed: 10.0| Turn: 30| FW: 1.7 |	|Нац:Анг,Фра,Гол,Пир,Исп|		[WAR]
#define SHIP_MANOWAR_FAST			118		// Фра. Мановар: 			Gun: 100(42ф)| HP: 17000| трюм: 6000| Crew: 850 | Speed: 9.5 | Turn: 20| FW: 1.0 |	|Нац:Фра|						[WAR]
#define SHIP_BATTLEMANOWAR			119		// Анг. Мановар: 			Gun: 100(42ф)| HP: 16000| трюм: 6500| Crew: 950 | Speed: 9.0 | Turn: 20| FW: 1.0 |	|Нац:Анг|						[WAR]
#define SHIP_MANOWAR_GUB			120		// Пир. Мановар: 			Gun: 100(42ф)| HP: 15000| трюм: 7000| Crew: 1050| Speed: 8.5 | Turn: 20| FW: 1.0 |	|Нац:Пир|						[WAR]
#define SHIP_PRINCE                 121		// Королевский Фрегат: 		Gun: 100(42ф)| HP: 12000| трюм: 5000| Crew: 750 | Speed: 11.0| Turn: 25| FW: 1.0 |	|Нац:Фра|						[WAR]
#define SHIP_MANOWAR				122		// Гол. Мановар: 			Gun: 102(42ф)| HP: 13000| трюм: 6800| Crew: 800 | Speed: 9.5 | Turn: 25| FW: 0.7 |	|Нац:Гол|						[WAR]
#define SHIP_HMS_VICTORY			123		// Мановар Виктория: 		Gun: 104(42ф)| HP: 14000| трюм: 6000| Crew: 900 | Speed: 9.8 | Turn: 22| FW: 1.0 |	|Нац:Анг|						[WAR]
#define SHIP_SP_SANFELIPE			124		// Исп. Мановар: 			Gun: 108(42ф)| HP: 13000| трюм: 7500| Crew: 750 | Speed: 9.5 | Turn: 25| FW: 1.0 |	|Нац:Исп|						[WAR]
//====================================================================================================================================================================================================================
// QuestShip					(10 кораблей)
#define SHIP_LUGGERQUEST     	   	125		// Курьерский Люггер: 		Gun: 12(16ф) | HP: 1100 | трюм: 990 | Crew: 96  | Speed: 17.5| Turn: 60| FW: 11.0|		6 класс
#define SHIP_XEBEKVML				126		// Щебека: 					Gun: 22(16ф) | HP: 2500 | трюм: 1800| Crew: 180 | Speed: 17.5| Turn: 55| FW: 7.5 |		4 класс
#define SHIP_BRIGQEEN				127		// Бриг: 					Gun: 24(16ф) | HP: 2800 | трюм: 2000| Crew: 200 | Speed: 16.5| Turn: 45| FW: 6.0 |		4 класс
#define SHIP_BRIGSW					128		// Бриг:					Gun: 24(16ф) | HP: 3200 | трюм: 2100| Crew: 130 | Speed: 16.5| Turn: 50| FW: 7.5 |		4 класс
#define SHIP_CORVETTE_QUEST			129		// Фрегат: 					Gun: 40(24ф) | HP: 3800 | трюм: 2700| Crew: 250 | Speed: 18.0| Turn: 60| FW: 5.5 |		3 класс
#define SHIP_ARABELLA				130		// Фрегат: 					Gun: 52(32ф) | HP: 6000 | трюм: 3700| Crew: 350 | Speed: 16.0| Turn: 42| FW: 4.0 |		2 класс
#define SHIP_FRIGATEQUEEN			131		// Фрегат: 					Gun: 52(32ф) | HP: 5500 | трюм: 3200| Crew: 300 | Speed: 17.0| Turn: 45| FW: 4.5 |		2 класс
#define SHIP_FLYINGDUTCHMAN			132		// Варшип: 					Gun: 60(42ф) | HP: 7700 | трюм: 5200| Crew: 444 | Speed: 15.0| Turn: 40| FW: 3.0 |		2 класс
#define SHIP_SANTISIMA		 	   	133		// Быстрый мановар: 		Gun: 106(42ф)| HP: 10700| трюм: 5750| Crew: 800 | Speed: 13.0| Turn: 32| FW: 1.2 |		1 класс
#define SHIP_SOLEYRU				134		// Сулей Руаяль: 			Gun: 112(42ф)| HP: 18000| трюм: 6800| Crew: 1200| Speed: 10.6| Turn: 29| FW: 1.3 |		1 класс
//====================================================================================================================================================================================================================

//	ЛОДКА + ФОРТ
#define SHIP_BOAT          	  	   135
#define SHIP_FORT           	   136


#define SHIP_NOTUSED			 1000
#define SHIP_NOTUSED_TYPE_NAME	"Not Used"
#define SHIP_NAME_NOTUSED		"Noname"

object  ShipsTypes[SHIP_TYPES_QUANTITY_WITH_FORT];  // RealShips
object	SailsColors[SAILS_COLOR_QUANTITY];


ref GetShipByType(int iType) { return &ShipsTypes[iType]; }  // пользовать GetRealShip