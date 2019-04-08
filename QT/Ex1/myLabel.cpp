#include "myLabel.h"


myLabel::myLabel(QWidget* parent) : QLabel(parent)
{
	this->setAutoFillBackground(true);

	set_autopista(true);
	
	n_Cotxe = 0;
	n_Moto = 0;
	n_Camio = 0;
	diners = 0;
	
}

void myLabel::canvia_autopista()
{
	if(autopista == false)set_autopista(true);
	else set_autopista(false);
}
void myLabel::set_autopista(bool arg)
{
	autopista = arg;
	
	QColor color;
	
	if(autopista == true)
	{
		color = Qt::green;
	}else
	{
		color = Qt::red;
	}
	QPalette pal = palette();

	pal.setColor(QPalette::Background, color);
	
	this->setPalette(pal);
}
void myLabel::tracta_buto_cotxe()
{
	if(autopista)
	{
		setCotxe(++n_Cotxe);
		diners++;
	}
	QString aux = QString::number(diners)+" €";
	
	setDiners(aux);
}
void myLabel::tracta_buto_moto()
{
	if(autopista)
	{
		setMoto(++n_Moto);
		diners++;
	}
	QString aux = QString::number(diners)+" €";
	
	setDiners(aux);
}
void myLabel::tracta_buto_camio()
{
	if(autopista)
	{
		setCamio(++n_Camio);
		diners+=4;
	}
	QString aux = QString::number(diners)+" €";
	
	setDiners(aux);

}
