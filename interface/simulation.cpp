#include "pages/ewd_page.h"
#include "model/enginecfm56.h"

#include "simulation.h"

Simulation::Simulation(QObject *parent, EwdPage *e) :
	QObject(parent),
	_e(e)
{
	_eng1 = new EngineCFM56();
	_eng2 = new EngineCFM56();
}

void Simulation::set_data() {
		_eng1->set_thrust(80);
		_e->set_value(EwdPage::E1STARTED, true);
		_e->set_value(EwdPage::EPR1, _eng1->epr());
		_e->set_value(EwdPage::EGT1, _eng1->egt());
		_e->set_value(EwdPage::N1RPM1, _eng1->n1());
		_e->set_value(EwdPage::N2RPM1, _eng1->n2());
}
