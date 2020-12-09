#ifndef PUMP_H
#define PUMP_H

#include <QWidget>

class Pump : public QWidget
{
	Q_OBJECT

public:
	enum Pumpstate {
		OFF = 0,
		ON
	};

	explicit Pump(QWidget *parent = 0);
	void set_value(Pumpstate s);
	void set_vertical(bool vertical);
	void lowpressure(bool press);
	Pumpstate value() {return _actual; }
//	QPoint inlet_pos();
	QPoint outlet_pos();
	~Pump();

private:
	bool is_moving();

	QWidget *_parent;
	Pumpstate _actual;
	bool _vertical;
	bool _lowpress;

protected:
	void paintEvent(QPaintEvent *event);
	QSize sizeHint() const;
};

#endif // VALVE_H
