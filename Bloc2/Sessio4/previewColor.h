#include <QLabel>

class previewColor : public QLabel
{
	Q_OBJECT
	
	int R,G,B;
	
	public:
	previewColor(QWidget*);
	
	private:
	void actualitzaColor();
	
	public slots:
	void canviaR(int);
	void canviaG(int);
	void canviaB(int);
	
	signals:
	void canviaTerra(int, int, int);
}
;
