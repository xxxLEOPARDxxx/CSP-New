// Philippe, de AoP1
//Таблица слухов, и их состояние. "active" - слух включен в поле случаного выбора слуха, "passive" - слух исключен из поля
#define MAX_RUMOURS 7
object	Rumour[MAX_RUMOURS];


void SetRumourDefaults()
{
	Rumour[0].text = GlobalStringConvert("Rumour_1");
	Rumour[0].state = "active";

	Rumour[1].text = GlobalStringConvert("Rumour_2");
	Rumour[1].state = "active";

	Rumour[2].text = GlobalStringConvert("Rumour_3");
	Rumour[2].state = "active";

	Rumour[3].text = GlobalStringConvert("Rumour_4");
	Rumour[3].state = "active";

	Rumour[4].text = GlobalStringConvert("Rumour_5");
	Rumour[4].state = "active";

	Rumour[5].text = GlobalStringConvert("Rumour_6");
	Rumour[5].state = "active";

	Rumour[6].text = GlobalStringConvert("Rumour_7");
	Rumour[6].state = "active";

}
