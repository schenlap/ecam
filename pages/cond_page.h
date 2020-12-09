#ifndef COND_PAGE_H
#define COND_PAGE_H

#include <QWidget>

class QLabel;
class Pump;
class Valve;

namespace Ui {
class CondPage;
}

class CondPage : public QWidget
{
	Q_OBJECT

public:
	enum ValueType {
		VALVE_HOT_AIR,
		VALVE_CARG_HOT_AIR,
		VALVE_CARG_OUT_ISO,
		VALVE_CARG_IN_ISO,
		CKPT_TRIM,
		FWD_TRIM,
		AFT_TRIM,
		CKPT_TMP,
		FWD_TMP,
		AFT_TMP,
		CKPT_DUCT,
		FWD_DUCT,
		AFT_DUCT,
		CARG_TMP,
		CARG_DUCT,
		CARG_TRIM,
		TAT,
		SAT,
		HH,
		MM,
		GW,
	};

	explicit CondPage(QWidget *parent = 0);
	void set_value(ValueType t, int v);
	~CondPage();

private:
	bool set_new_value(QLabel *w, int v);
	bool set_new_value(Pump *w, int v);
	bool set_new_value(Valve *w, int v);
	bool set_new_value(int *s, int v);
	bool set_new_value(bool *s, bool v);
	void paint_simple_arc(QPainter *p, int x, int y, int min, int max, int val);
	void set_label_color(QLabel *l, bool alert);
	void display_label_warning(QLabel *l, int min, int max, int val);
	void paint_silhoute(QPainter *p);
	void paint_cargo(QPainter *p);
	Ui::CondPage *ui;
	int _ckpt_trim;
	int _fwd_trim;
	int _aft_trim;
	int _ckpt_tmp;
	int _fwd_tmp;
	int _aft_tmp;
	int _ckpt_duct;
	int _fwd_duct;
	int _aft_duct;
	int _carg_tmp;
	int _carg_duct;
	int _carg_trim;


protected:
	void paintEvent(QPaintEvent *event);
};

#endif // COND_PAGE_H
