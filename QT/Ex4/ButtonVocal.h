#include <QPushButton>

class ButtonVocal : public QPushButton
{
	Q_OBJECT
		
	private:
	bool Majuscules;

	private:
	void set_Text_clase();
	
	public:
	ButtonVocal (QWidget*);
	
	public slots:
	void toggleMajuscules();
	void TractaClick();
	
	signals:
	void EnviaVocal(QChar);
}
;
