// Stefan SCHÖFEGGER: 26.4.2015
// Simulate CFM56-5B

#include "model/pt1.h"

#include "enginecfm56.h"

EngineCFM56::EngineCFM56(QObject *parent) :
	QObject(parent),
	_thrust(0)
{
	_n1_pt1 = new Pt1(1, 52/3, 1);
	_n2_pt1 = new Pt1(1, 45/3, 1);
	_egt_pt1 = new Pt1(6, 90/3, 1);
	_epr_pt1 = new Pt1(0.45 / 100, 46 / 3, 1);
}


void EngineCFM56::set_thrust(int t) {
	if (t > 100)
		t = 100;
	if (t < 0)
		t = 0;
	_thrust = t;
	_n1_pt1->set_input(t);
	_n2_pt1->set_input(t);
	_egt_pt1->set_input(t);
	_epr_pt1->set_input(t);
}


float EngineCFM56::ff() {
	float ff = (float)_thrust / 100 * 137.9 /* kN */ * 0.58 /* lb / lbf*h */ * 14.24 /* lb/lbfh -> g/kN*s */;
	return ff;
}
