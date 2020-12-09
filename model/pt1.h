#ifndef PT1_H
#define PT1_H

#include <QObject>

class QObject;

class Pt1 : public QObject
{
	Q_OBJECT

public:
	Pt1(float K, int T, int dT, QObject *parent = 0); // Times in sec
	float out();
	void set_input(int i);

private slots:
	void calc();

private:
	float _K;
	float _T;
	float _in;
	float _out;
};

#endif // PT1_H
