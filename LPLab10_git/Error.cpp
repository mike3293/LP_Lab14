#include "stdafx.h"
namespace Error
{
	/*Ñåğèè îøèáîê   0-99		 ñèñòåìíûå îøèáêè ÑÀÍß
					 100-109	 îøèáêè ïàğàìåòğîâ
					 110-119	 îøèáêè îòêğûòèÿ è ÷òåíèÿ ôàéëîâ
	*/
	ERROR errors[ERROR_MAX_ENTRY] =  //òàáëèöà îøèáîê
	{
		ERROR_ENTRY(0,"Íåäîïóñòèìûé êîä îøèáêè"), //êîä îøèáêè âíå äèàïàçîíà 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1,"Ñèñòåìíûé ñáîé"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY(5,"IT maxsize = 4096"),
		ERROR_ENTRY(6,"Òàáëèöà èäåíòèôèêàòîğîâ ïåğåïîëíåíà"),ERROR_ENTRY(7,"LT maxsize = 4096"),ERROR_ENTRY(8,"Òàáëèöà ëåêñåì ïåğåïîëíåíà"), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"Ïàğàìåòğ -in äîëæåí áûòü çàäàí"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"Ïğåâûøåíà äëèííà âõîäíîãî ïàğàìàòğà"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Îøèáêà ïğè îòêğûòèè ôàéëà ñ èñõîäíûì êîäîì (-in)"),
		ERROR_ENTRY(111,"Íåäîïóñòèìûé ñèìâîë â èñõîäíîì ôàéëå (-in)"),
		ERROR_ENTRY(112,"Îøèáêà ïğè ñîçäàíèè ôàéëà ïğîòîêîëà (-log)"),
		ERROR_ENTRY_NODEF(113),ERROR_ENTRY_NODEF(114),ERROR_ENTRY(115, "Îøèáêà ëåêñè÷åñêîãî àíàëèçà"),
		ERROR_ENTRY(116, "Äëèíà èäåíòèôèêàòîğà áîëüøå 5"),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY_NODEF100(600),ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900),
	};
	ERROR geterror(int id)
	{
		ERROR error_info ;												// ñîçäàíèå ñòğóêòóğû êîòîğóş íàäî áóäåò âåğíóòü
		if (id > 0 && id < ERROR_MAXSIZE_MESSAGE)						// ñğàâíèâàíèå äèàïàçîíà
		{ 
			error_info.id = errors[id].id;
			strcpy_s(error_info.message, errors[id].message);
			error_info.inext.col = -1;
			error_info.inext.line = -1;
		}
		else
		{
			error_info.id = errors[0].id;
			strcpy_s(error_info.message, errors[0].message);
		}
		return error_info;
	}

	ERROR geterrorin(int id, int line, int col)
	{
		ERROR error_info;												//	ñîçäàíèå ñòğóêòóğó êîòîğóş íàäî áóäåò âåğíóòü
		if (id > 0 && id < ERROR_MAXSIZE_MESSAGE)						// ñğàâíåíèå äèàïàçîíà
		{
			error_info.id = errors[id].id;
			error_info.inext.col = col;
			error_info.inext.line = line;
			strcpy_s(error_info.message, errors[id].message);
			return error_info;
		}
		else
		{
			error_info.id = 0; // çàíîøó
			error_info.inext.col = -1;
			error_info.inext.line = -1;
			strcpy_s(error_info.message, errors[0].message);
			return error_info;
		}
	}
	;
};