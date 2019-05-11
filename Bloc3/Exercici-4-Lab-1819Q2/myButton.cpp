#include "myButton.h"

myButton::myButton(QWidget* parent) : QPushButton(parent)
{
	index = 0;
	vLabels.push_back(QString("Focus de camera"));
	vLabels.push_back(QString("Focus sobre Patricio"));
	vLabels.push_back(QString("Focus sobre arbre"));
} 
void myButton::tractaClick()
{
	index = (index+1)%3;
	emit  canviaLabel(vLabels[index]);
		
}
