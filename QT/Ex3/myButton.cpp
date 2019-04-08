#include "myButton.h"

myButton::myButton(QWidget* parent) : QPushButton(parent)
{
	this->setAutoFillBackground(true);
	vColors = {QColor(0xFF00FF), QColor(0x00FF00), QColor(0x0000FF), QColor((unsigned int)0x000000)};
	set_N();
}

void myButton::set_Despl(int n)
{
	Despl = n;
	actualitzar();
}

void myButton::set_N()
{
	N = rand()%MIDA;
	actualitzar();
}

void myButton::actualitzar()
{
	QPalette Pal(palette());
	Pal.setColor(QPalette::Button, vColors[(N+Despl)%MIDA]);
	this->setPalette(Pal);

}
