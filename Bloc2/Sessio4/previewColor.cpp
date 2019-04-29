#include "previewColor.h"


previewColor::previewColor(QWidget* parent) : QLabel(parent)
{
	R = 255;
	G = 255;
	B = 255;
	
}

void previewColor::actualitzaColor()
{
	QPalette Pal(palette());
	
	QColor color;
	
	color.setRgb(R, G, B, 255);
	
	Pal.setColor(QPalette::Window, color);
	
	this->setPalette(Pal);
}

void previewColor::canviaR(int arg)
{
	R = arg;
	actualitzaColor();
	canviaTerra(R,G,B);
}

void previewColor::canviaG(int arg)
{
	G = arg;
	actualitzaColor();
	canviaTerra(R,G,B);
}

void previewColor::canviaB(int arg)
{
	B = arg;
	actualitzaColor();
	canviaTerra(R,G,B);
}
