#include <QPushButton>
#include <QStackedWidget>
#include <QTime>
#include <QTimer>
#include <QLayout>
#include <QMouseEvent>

#include "pages/ewd_page.h"
#include "pages/fuel_page.h"
#include "pages/bleed_page.h"
#include "pages/cond_page.h"
#include "pages/pfd_page.h"

#include "panels/sys_stat_panel.h"
#include "widgets/analogclock.h"

#include "model/tmp_time.h"
#include "model/pt1.h"

#include "interface/simulation.h"
#include "interface/fgfs.h"

#include "ecam.h"




Ecam::Ecam(QWidget *parent) :
	QMainWindow(parent),
	_curpage(EWD)
{
	_ui.setupUi(this);
#ifdef __arm__
	setWindowState(windowState() | Qt::WindowFullScreen);
#endif
	setStyleSheet("background-color: black;");
	_mainlayout = new QVBoxLayout;

	_sw = new QStackedWidget;
	_analogclock = new AnalogClock;
	_analogclock2 = new AnalogClock;

	_ewd = new EwdPage;
	_fuel = new FuelPage;
	_bleed = new BleedPage;
	_cond = new CondPage;
	_pfd = new PfdPage;

	_tmp_time = new TmpTime(parent, _fuel, _bleed, _cond);

	_sw->addWidget(_ewd);
	_sw->addWidget(_fuel);
	_sw->addWidget(_bleed);
	_sw->addWidget(_cond);
	_sw->addWidget(_pfd);
	_sw->addWidget(_analogclock);
	_sw->setCurrentWidget(_cond);

	SysStatPanel *sys_panel = new SysStatPanel;

	_mainlayout->addWidget(_sw);
	_mainlayout->addWidget(sys_panel);
	_mainlayout->addStretch(1);

	QWidget *wid = new QWidget(this);
	wid->setLayout(_mainlayout);
	setCentralWidget(wid);
	//setCentralWidget(sys_panel);
	show();
	switchpage(4);

	connect(sys_panel, SIGNAL(switchpage(int)), this, SLOT(switchpage(int)));

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(set_testdata()));
	timer->start(1000);

	_sim = new Simulation(0, _ewd);
	_fg = new FgFs(0, _ewd, _fuel, _tmp_time);
	_fg->start();

}


void Ecam::switchpage(int p) {
	if (p == 0)
		_sw->setCurrentWidget(_ewd);
	else if (p == 1)
		_sw->setCurrentWidget(_fuel);
	else if (p == 2)
		_sw->setCurrentWidget(_bleed);
	else if (p == 3)
		_sw->setCurrentWidget(_cond);
	else if (p == 4)
		_sw->setCurrentWidget(_pfd);
}


void Ecam::set_testdata() {
	_fuel->set_value(FuelPage::VALVE_ENG1, 1);
	_fuel->set_value(FuelPage::VALVE_XFEED, 0);
	_fuel->set_value(FuelPage::PUMP_LL, 1);
	_fuel->set_value(FuelPage::PUMP_LC, 1);
	_fuel->set_value(FuelPage::FF_ENG1, 20);
	_fuel->set_value(FuelPage::FF_ENG2, 0);

	_bleed->set_value(BleedPage::ANTI_ICE1, false);
	_bleed->set_value(BleedPage::ANTI_ICE2, false);
	_bleed->set_value(BleedPage::GND, false);
	_bleed->set_value(BleedPage::OUT1, true);
	_bleed->set_value(BleedPage::OUT2, true);
	_bleed->set_value(BleedPage::OUT3, true);
	_bleed->set_value(BleedPage::IP_TEMP1, 180);
	_bleed->set_value(BleedPage::IP_PRESS1, 35);
	_bleed->set_value(BleedPage::TEMPIN1, 65);
	_bleed->set_value(BleedPage::TEMPOUT1, 30);
	_bleed->set_value(BleedPage::FLOW1, 40);
	_bleed->set_value(BleedPage::BYPASS1, 40);
	_bleed->set_value(BleedPage::IP_TEMP2, 28);
	_bleed->set_value(BleedPage::IP_PRESS2, 12);
	_bleed->set_value(BleedPage::TEMPIN2, 70);
	_bleed->set_value(BleedPage::BYPASS2, 100);
	_bleed->set_value(BleedPage::TEMPOUT2, 29);
	_bleed->set_value(BleedPage::FLOW2, 0);
	_bleed->set_value(BleedPage::VALVE_IP1, 1);
	_bleed->set_value(BleedPage::VALVE_IP2, 0);
	_bleed->set_value(BleedPage::VALVE_ENG1, 1);
	_bleed->set_value(BleedPage::VALVE_ENG2, 0);

	_cond->set_value(CondPage::CKPT_TMP, 23);
	_cond->set_value(CondPage::FWD_TMP, 24);
	_cond->set_value(CondPage::AFT_TMP, 24);
	_cond->set_value(CondPage::CARG_TMP, 15);
	_cond->set_value(CondPage::CKPT_DUCT, 18);
	_cond->set_value(CondPage::FWD_DUCT, 30);
	_cond->set_value(CondPage::AFT_DUCT, 28);
	_cond->set_value(CondPage::CARG_DUCT, 19);
	_cond->set_value(CondPage::CKPT_TRIM, 0);
	_cond->set_value(CondPage::FWD_TRIM, 20);
	_cond->set_value(CondPage::AFT_TRIM, 0);
	_cond->set_value(CondPage::CARG_TRIM, 0);
	_cond->set_value(CondPage::VALVE_CARG_HOT_AIR, true);
	_cond->set_value(CondPage::VALVE_CARG_IN_ISO, true);
	_cond->set_value(CondPage::VALVE_CARG_OUT_ISO, true);
	_cond->set_value(CondPage::VALVE_HOT_AIR, true);

	_tmp_time->set_value(TmpTime::GW, 74800);

	if (_fg->is_online())
		return;

	_tmp_time->set_value(TmpTime::SAT, 15);
	_tmp_time->set_value(TmpTime::TAT, 15);

	_fuel->set_value(FuelPage::FOB, 11900);
	_fuel->set_value(FuelPage::LL_FUEL_QUANT, 650);
	_fuel->set_value(FuelPage::LC_FUEL_QUANT, 4290);
	_fuel->set_value(FuelPage::CC_FUEL_QUANT, 2010);
	_fuel->set_value(FuelPage::RC_FUEL_QUANT, 4300);
	_fuel->set_value(FuelPage::RR_FUEL_QUANT, 650);
	_fuel->set_value(FuelPage::LL_FUEL_TEMP, 15);
	_fuel->set_value(FuelPage::LC_FUEL_TEMP, 15);
	_fuel->set_value(FuelPage::RC_FUEL_TEMP, 15);
	_fuel->set_value(FuelPage::RR_FUEL_TEMP, 15);

	_sim->set_data();

	static int tmp = 0;
	static int flappos = 1;
	if (++tmp == 20) {
		tmp = 0;
		//_flaps->set_value(flappos++);
		_ewd->set_value(EwdPage::FLAPS, flappos++);
		if (flappos > 4)
			flappos = 0;
	}

//	static float ff = 0;
//	ff += _eng1->ff() / 1000; // kg/s
//	ff += _eng2->ff() / 1000;
//	qDebug("FF: %f", ff);
}


void Ecam::mousePressEvent(QMouseEvent *e)

{
	QPoint point=e->pos();
	qDebug("Ecam: QPoint(%d,%d)", point.x(), point.y() );

	QMainWindow::mousePressEvent(e);

}


Ecam::~Ecam()
{
}
