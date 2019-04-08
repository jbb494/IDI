#include <QLineEdit>
#include <iostream>

class myLineEdit : public QLineEdit
{
	Q_OBJECT
	
	private:
	int N_errors, N_trobades;
	QString paraula;
	QString paraula_mostrada;
	bool poder_escriure;
	void inicialitzar();
	void swap_paraula(int );
	
	public:
	myLineEdit(QWidget *parent);
	public slots:
	void tracta_change_text(QString);
	void tracta_return();
	void Reiniciar();
	signals:
	void setN_errors(int);
	void setParaula_mostrada(const QString&);
}
;
