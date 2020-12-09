#ifndef ENGINECFM56_H
#define ENGINECFM56_H

#include <QObject>

#include "model/pt1.h"

class EngineCFM56 : public QObject
{
	Q_OBJECT
public:
	explicit EngineCFM56(QObject *parent = 0);
	void set_thrust(int t);
	float n1() { return _n1_pt1->out(); }
	float n2() { return _n2_pt1->out(); }
	float egt() { return _egt_pt1->out(); }
	float epr() { return _epr_pt1->out() + 1; }
	float ff(); // g/s

signals:

public slots:

private:
	int _thrust;
	Pt1 *_n1_pt1;
	Pt1 *_n2_pt1;
	Pt1 *_egt_pt1;
	Pt1 *_epr_pt1;
};

#endif // ENGINECFM56_H
