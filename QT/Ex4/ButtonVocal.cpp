#include "ButtonVocal.h"	
	
	
ButtonVocal::ButtonVocal (QWidget* parent) : QPushButton(parent)
{
	Majuscules = false;
}


void ButtonVocal::toggleMajuscules()
{
	if(Majuscules == true)Majuscules = false;
	else Majuscules = true;
	
	set_Text_clase();
}

void ButtonVocal::set_Text_clase()
{
	if(Majuscules == true)setText(text().toUpper());
	else setText(text().toLower());
}

void ButtonVocal::TractaClick()
{
	QChar Vocal = text()[0];
	
	if(Majuscules == true)Vocal = Vocal.toUpper();
	else Vocal = Vocal.toLower();
	EnviaVocal(Vocal);
}
