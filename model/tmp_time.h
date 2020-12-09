#ifndef TMP_TIME_H_
#define TMP_TIME_H_

#include <QObject>

class FuelPage;
class BleedPage;
class CondPage;

class TmpTime : public QObject
{
	Q_OBJECT

public:
	enum ValueType {
		TAT,
		SAT,
		GW
	};
	TmpTime(QObject *parent, FuelPage *fuel, BleedPage *bleed, CondPage *cond);
	TmpTime(QObject *parent);
	~TmpTime();
	void set_value(ValueType t, int v);

private slots:
	void set_time();

private:
	FuelPage *_fuel;
	BleedPage *_bleed;
	CondPage *_cond;
};

#endif // TMP_TIME_H_
