#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QWidget>

#include "arcwidget.h"

const int arcwidth = 5;
const int arcmaker_length = 10;
const int arc_rad = 80;

Arcwidget::Arcwidget(QWidget *parent, int startangle, int endangle, int ticpoints, int endnotics) :
	QWidget(parent),
	_value(1.0),
	_started(false),
	_max_normal(1.0),
	_min_normal(0),
	_max(1.0),
	_min(0),
	_arc_startangle(startangle),
	_arc_endangle(endangle),
	_arc_ticpoints(ticpoints),
	_arc_endnotics(endnotics),
	_font_scale(1)
{

}


bool Arcwidget::is_normalvalue() {
	if (_value >= _min_normal && _value <= _max_normal)
		return true;
	else
		return false;
}


float Arcwidget::to_displayvalue(float value) {
	if (value < _min)
		return _min;
	if (value > _max)
		return _max;
	return value;
}


void Arcwidget::set_value(float value) {
	if (_value != value) {
		_value = to_displayvalue(value);
		update();
	}
}


int Arcwidget::tickrotate() {
	return (_arc_endangle - _arc_endnotics - _arc_startangle) / (_arc_ticpoints - 1);
}


int Arcwidget::value_torot(float val) {
	return -(int)(_arc_endangle -(_arc_endangle - _arc_startangle - _arc_endnotics) / (_max - _min) * (val - _min));
}


int Arcwidget::value_torot() {
	return value_torot(value());
}

