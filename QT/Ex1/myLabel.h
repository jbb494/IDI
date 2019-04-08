#include <QLabel>

class myLabel : public QLabel
{
	Q_OBJECT
	private:
	bool autopista;
	
	int n_Cotxe;
	int n_Moto;
	int n_Camio;
	
	int diners;
	
	void set_autopista(bool);
	 public:
	 myLabel(QWidget *parent);
	 public slots:
	 void canvia_autopista();
	 
	 //Buttons
	 void tracta_buto_cotxe();
	 void tracta_buto_moto();
	 void tracta_buto_camio();
	 signals:
	 
	 //QLCD Number
	 void setCotxe(int);
	 void setMoto(int);
	 void setCamio(int);
	 void setDiners(const QString&);

} 
;
