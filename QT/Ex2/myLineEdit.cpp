#include "myLineEdit.h"
#define MIDA_PARAULA 10
myLineEdit::myLineEdit(QWidget* parent) : QLineEdit(parent)
{
	inicialitzar();
	
	//this->setAutoFillBackground(true);

}
void myLineEdit::inicialitzar()
{
	N_errors = 5;
	N_trobades = 0;
	paraula = "diccionari";
	paraula_mostrada = "**********";
	poder_escriure = true;
	setN_errors(N_errors);
	setParaula_mostrada(paraula_mostrada);
	
	QPalette pal = palette();
	pal.setColor(QPalette::Base, Qt::white);
	this->setPalette(pal);

}
void myLineEdit::tracta_change_text(QString text_changed)
{
	if(text_changed.size() > 1)text_changed.truncate(1);
	else if(text_changed.size() == 1 && (text_changed[0] < 'a' || text_changed[0] > 'z'))text_changed.truncate(0);

	if(poder_escriure == false)text_changed.truncate(0);
	
	setText(text_changed);
}

void myLineEdit::tracta_return()
{
	bool fallo = true;

	for(int i = 0; i<MIDA_PARAULA; i++)
	{
		if(text()[0] == paraula[i])
		{
			fallo = false;
			swap_paraula(i);
		}
	}
	setParaula_mostrada(paraula_mostrada);
	
	QPalette pal = palette();
	
	if(N_trobades >= MIDA_PARAULA)
	{	
		pal.setColor(QPalette::Base, Qt::green);
		this->setPalette(pal);
		poder_escriure = false;
	}

	
	if(text().size() == 1 && fallo)setN_errors(--N_errors);
	
	if(N_errors == 0)
	{
		pal.setColor(QPalette::Base, Qt::red);
		this->setPalette(pal);
		poder_escriure = false;
	}
	
	setText(QString());
}
void myLineEdit::swap_paraula(int index)
{
	paraula_mostrada[index] = paraula[index];

	paraula[index] = '*';
	
	N_trobades++;
}
void myLineEdit::Reiniciar()
{
	inicialitzar();
}
