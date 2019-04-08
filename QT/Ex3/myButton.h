#include <QPushButton>
#include <iostream>

#define MIDA 4
class myButton : public QPushButton
{
	Q_OBJECT
	int Despl;
	int N;
	std::vector<QColor> vColors;
		
	private:
	void actualitzar();

	public:
	myButton(QWidget*);
	
	public slots:
	void set_Despl(int);
	void set_N();
	signals:
	
	
}
;
