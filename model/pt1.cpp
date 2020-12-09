// Stefan SCHÖFEGGER: 26.4.2015

#include <QTimer>

#include "pt1.h"

Pt1::Pt1(float K, int T, int dT, QObject *parent) :
	QObject(parent),
	_K(K),
	_in(0),
	_out(0)
{
	_T = 1/((float)T / dT + 1.0);
	//qDebug("T* = %f", _T);

	QTimer *timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(calc()));
	timer->start(dT * 1000);
}


void Pt1::calc() {
	_out = _T * (_K * _in - _out) + _out;
	//qDebug("OUT: %f", _out);
}


void Pt1::set_input(int i) {
	_in = i;
}


float Pt1::out() {
	return _out;
}
