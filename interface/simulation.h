#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>

class EwdPage;
class EngineCFM56;

class Simulation : public QObject
{
	Q_OBJECT
public:
	explicit Simulation(QObject *parent, EwdPage *e);
	void set_data();

signals:

public slots:

private:
	EwdPage *_e;
	EngineCFM56 *_eng1;
	EngineCFM56 *_eng2;

};

#endif // SIMULATION_H
