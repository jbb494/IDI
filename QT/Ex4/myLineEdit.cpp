#include "myLineEdit.h"


myLineEdit::myLineEdit(QWidget* parent) : QLineEdit(parent)
{
	
}

void myLineEdit::afegirChar(QChar Charg)
{
	setText(text()+Charg);
}

void myLineEdit::Bloqueig(QString Str_arg)
{
	Str_arg.truncate(Str_arg.size()-1);
	
	setText(Str_arg);
}
