#include <QLineEdit>

class myLineEdit : public QLineEdit
{
	Q_OBJECT
	
	private:
	
	public:	
	myLineEdit(QWidget*);
	
	public slots:
	void afegirChar(QChar);
	void Bloqueig(QString);
	
	signals:
	
}
;
