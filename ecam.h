#ifndef ECAM_H_
#define ECAM_H_

#include <QObject>

#include "ui_ecam.h"

class EwdPage;
class FuelPage;
class BleedPage;
class CondPage;
class AnalogClock;
class QStackedWidget;
class QVBoxLayout;
class TmpTime;
class FgFs;
class Simulation;

class Ecam : public QMainWindow
{
	Q_OBJECT

public:
	enum Pages {
		EWD,
		BLEED,
		COND,
		SD,
		FUEL
	};
	Ecam(QWidget *parent = 0);
	~Ecam();

private:
	Ui::EcamClass _ui;
#ifdef __arm	
	GESys::SysFile _brightness;
#endif
	QVBoxLayout *_mainlayout;
	QStackedWidget *_sw;
	EwdPage *_ewd;
	FuelPage *_fuel;
	BleedPage *_bleed;
	CondPage *_cond;
	AnalogClock *_analogclock;
	AnalogClock *_analogclock2;
	Pages _curpage;

	TmpTime *_tmp_time;
	Simulation *_sim;
	FgFs *_fg;

private slots:
	void mousePressEvent(QMouseEvent *e);
	void switchpage(int p);
	void set_testdata();
};

#endif // ECAM_H_
