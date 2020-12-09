#ifndef EWD_H_
#define EWD_H_

#include <QWidget>
#include <QLabel>

class Flaps;
class Arcwidget;
class MemoPage;

namespace Ui {
class EwdPage;
}

class EwdPage : public QWidget
{
	Q_OBJECT

public:
	enum ValueType {
		EPR1,
		EPR2,
		EGT1,
		EGT2,
		N1RPM1,
		N1RPM2,
		N2RPM1,
		N2RPM2,
		FLAPS,
		E1STARTED,
		E2STARTED,
	};

	EwdPage(QWidget *parent = 0);
	void set_value(ValueType t, float v);
	~EwdPage();

private:
	int _epr1;
	int _epr2;
	int _egt1;
	int _egt2;
	int _n1rpm1;
	int _n1rpm2;
	int _eprtext1;
	int _eprtext2;
	int _n2rpm1;
	int _n2rpm2;
	int _flaps;
	bool _n2rmp1_started;
	bool _n2rmp2_started;
	Ui::EwdPage *ui;
	bool set_new_value(Arcwidget *w, float v);
	bool set_new_started(Arcwidget *w, bool v);
	bool set_new_started(bool *w, bool v);
	bool set_new_value(Flaps *w, int v);
	bool set_new_value(QLabel *w, int v);
	bool set_new_value(int *w, int n);
	void set_label_color(QLabel *l, bool alert);
	MemoPage *_mp;

private slots:
		virtual QSize sizeHint() const;

protected:
	void paintEvent(QPaintEvent *event);
};

#endif // EWD_H_
