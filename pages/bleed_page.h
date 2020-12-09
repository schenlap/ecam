#ifndef BLEED_PAGE_H
#define BLEED_PAGE_H

#include <QWidget>

class QLabel;
class Pump;
class Valve;

namespace Ui {
class BleedPage;
}

class BleedPage : public QWidget
{
	Q_OBJECT

public:
	enum ValueType {
		IP_TEMP1,
		IP_PRESS1,
		TEMPIN1,
		BYPASS1,
		TEMPOUT1,
		FLOW1,
		IP_TEMP2,
		IP_PRESS2,
		TEMPIN2,
		BYPASS2,
		TEMPOUT2,
		FLOW2,
		ANTI_ICE1,
		ANTI_ICE2,
		GND,
		OUT1,
		OUT2,
		OUT3,
		TAT,
		SAT,
		HH,
		MM,
		GW,
		VALVE_ENG1,
		VALVE_APU,
		VALVE_XFEED,
		VALVE_ENG2,
		VALVE_IP1,
		VALVE_IP2,
		VALVE_HP1,
		VALVE_HP2
	};

	explicit BleedPage(QWidget *parent = 0);
	void set_value(ValueType t, int v);
	~BleedPage();

private:
	bool set_new_value(QLabel *w, int v);
	bool set_new_value(Pump *w, int v);
	bool set_new_value(Valve *w, int v);
	bool set_new_value(int *s, int v);
	bool set_new_value(bool *s, bool v);
	void paint_simple_arc(QPainter *p, int x, int y, int min, int max, int val);
	void paint_simple_triangle(QPainter *p, int x, int y, int rot);
	void set_label_color(QLabel *l, bool alert);
	void display_label_warning(QLabel *l, int min, int max, int val);
	Ui::BleedPage *ui;
	bool _anti_ice1;
	bool _anti_ice2;
	bool _gnd;
	bool _out1;
	bool _out2;
	bool _out3;
	int _ip_temp1;
	int _ip_press1;
	int _tempin1;
	int _bypass1;
	int _tempout1;
	int _flow1;
	int _ip_temp2;
	int _ip_press2;
	int _tempin2;
	int _bypass2;
	int _tempout2;
	int _flow2;


protected:
	void paintEvent(QPaintEvent *event);
};

#endif // BLEED_PAGE_H
