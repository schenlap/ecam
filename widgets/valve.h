#ifndef VALVE_H
#define VALVE_H

#include <QWidget>

class Valve : public QWidget
{
	Q_OBJECT

public:
	enum Valvestate {
		CLOSE = 0,
		OPEN
	};

	explicit Valve(QWidget *parent = 0, bool vertical = true, bool apu = false);
	void set_value(Valvestate s);
	void set_vertical(bool vertical);
	void set_apu(bool apu);
	void set_color_man_alert(int man);
	QPoint inlet_pos();
	QPoint outlet_pos();
	Valvestate value() {return _desired; }
	~Valve();

private:
	bool is_moving();

	QWidget *_parent;
	bool _is_apu;
	Valvestate _desired;
	Valvestate _actual;
	bool _vertical;
	int _color_man_alert; // 0 = green, 1 = amber (orange), -1 = no man color

protected:
	void paintEvent(QPaintEvent *event);
	QSize sizeHint() const;
};

#endif // VALVE_H
