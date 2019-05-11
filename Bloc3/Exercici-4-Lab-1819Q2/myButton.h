#include <QPushButton> 

class myButton : public QPushButton
{
	Q_OBJECT

private:
	std::vector<QString> vLabels;
	int index;
	
	public:
	myButton(QWidget*);

	public slots:
	void tractaClick();
//<<>>
	signals:
	void canviaLabel(QString);
}
;
