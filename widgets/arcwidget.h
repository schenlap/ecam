#ifndef ARCWIDGET_H
#define ARCWIDGET_H

#include <QWidget>

const int label_font_sz = 20;
const int value_font_sz = 50;

class Arcwidget : public QWidget
{
	Q_OBJECT

public:
	Arcwidget(QWidget *parent = 0, int startangle = 0, int endangle = 180, int ticpoints = 5, int endnotics = 0);
	void set_value(float epr);
	void set_engine_started(bool started = true) {_started = started; }
	float to_displayvalue(float value);
	float value() {return _value; }
	bool started() {return _started; }

public slots:


private:
	float _value;
	bool _started;
	
protected:
	bool is_normalvalue();
	void set_max_normal(float max) {_max_normal = max; }
	void set_max(float max) {_max = max; }
	void set_min_normal(float min) {_min_normal = min; }
	void set_min(float min) {_min = min; }
	int tickrotate();
	int value_torot();
	int value_torot(float val);

	float _max_normal;
	float _min_normal;
	float _max;
	float _min;

	const int _arc_startangle;
	const int _arc_endangle;
	const int _arc_ticpoints;
	const int _arc_endnotics;

	float _font_scale;
};

#endif
