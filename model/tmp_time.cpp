
#include <QTime>
#include <QTimer>

#include "pages/ewd_page.h"
#include "pages/fuel_page.h"
#include "pages/bleed_page.h"
#include "pages/cond_page.h"
#include "panels/sys_stat_panel.h"
#include "widgets/analogclock.h"

#include "tmp_time.h"




TmpTime::TmpTime(QObject *parent, FuelPage *fuel, BleedPage *bleed, CondPage *cond) :
	QObject(parent),
	_fuel(fuel),
	_bleed(bleed),
	_cond(cond)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(set_time()));
	timer->start(1000);
}


TmpTime::TmpTime(QObject *parent) :
	QObject(parent)
{

}


void TmpTime::set_time() {
	QTime time = QTime::currentTime();
	_fuel->set_value(FuelPage::HH, time.hour() );
	_fuel->set_value(FuelPage::MM, time.minute());

	_bleed->set_value(BleedPage::HH, time.hour() );
	_bleed->set_value(BleedPage::MM, time.minute());

	_cond->set_value(CondPage::HH, time.hour() );
	_cond->set_value(CondPage::MM, time.minute());
}


void TmpTime::set_value(ValueType t, int v) {

	if (t == TAT) {
		_fuel->set_value(FuelPage::TAT, v);
		_bleed->set_value(BleedPage::TAT, v);
		_cond->set_value(CondPage::TAT, v);
	} else if (t == SAT) {
		_fuel->set_value(FuelPage::SAT, v);
		_bleed->set_value(BleedPage::SAT, v);
		_cond->set_value(CondPage::SAT, v);
	} else if (t == GW) {
		_fuel->set_value(FuelPage::GW, v);
		_bleed->set_value(BleedPage::GW, v);
		_cond->set_value(CondPage::GW, v);
	}
}


TmpTime::~TmpTime()
{
}
