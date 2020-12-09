#ifndef FUEL_PAGE_H
#define FUEL_PAGE_H

#include <QWidget>

class QLabel;
class Pump;
class Valve;

namespace Ui {
class FuelPage;
}

class FuelPage : public QWidget
{
	Q_OBJECT

public:
	enum ValueType {
		FOB = 1,
		LL_FUEL_QUANT,
		LC_FUEL_QUANT,
		CC_FUEL_QUANT,
		RC_FUEL_QUANT,
		RR_FUEL_QUANT,
		LL_FUEL_TEMP,
		LC_FUEL_TEMP,
		RC_FUEL_TEMP,
		RR_FUEL_TEMP,
		TAT,
		SAT,
		HH,
		MM,
		GW,
		PUMP_LL,
		PUMP_LC,
		PUMP_CL,
		PUMP_CR,
		PUMP_RC,
		PUMP_RR,
		VALVE_ENG1,
		VALVE_APU,
		VALVE_XFEED,
		VALVE_ENG2,
		FF_ENG1,
		FF_ENG2
	};

	explicit FuelPage(QWidget *parent = 0);
	void set_value(ValueType t, int v);
	~FuelPage();

private:
	bool set_new_value(QLabel *w, int v);
	bool set_new_value(Pump *w, int v);
	bool set_new_value(Valve *w, int v);
	Ui::FuelPage *ui;

protected:
	void paintEvent(QPaintEvent *event);
};

#endif // FUEL_PAGE_H
