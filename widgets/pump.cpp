#include <QPainter>

#include "pump.h"

static int linewidth = 10;

Pump::Pump(QWidget *parent) :
	QWidget(parent),
	_parent(parent),
	_actual(OFF),
	_vertical(true),
	_lowpress(false)
{

}


void Pump::set_vertical(bool vertical) {
	_vertical = vertical;
}


void Pump::lowpressure(bool press) {
	_lowpress = press;
}


Pump::~Pump()
{

}


void Pump::set_value(Pumpstate s) {
	_actual = s;
}


void Pump::paintEvent(QPaintEvent *) {
	QPainter painter(this);

	int side = qMin(width(), height());
	painter.setRenderHint((QPainter::Antialiasing));
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);

	if (!_vertical)
		painter.rotate(90);

	if (_actual == ON) {
		painter.setPen(QPen(Qt::green, linewidth));
		painter.drawLine(0, -100, 0, 100); // verticel

	} else {
		painter.setPen(QPen(QColor( 0xFF, 0xA0, 0x00), linewidth)); // Orange
		painter.drawLine(-50, 0, 50, 0); // horizontal
	}
	painter.drawRect(-100 + linewidth / 2, -100 + linewidth / 2, 200 - linewidth, 200 - linewidth);
}


/*
QPoint Pump::inlet_pos() {
	QPoint in;
	if (_vertical)
		in = QPoint(width() / 2, height());
	else
		in = QPoint(0, height() / 2);

	QPoint windowPoint = pos() + in;
	qDebug("Inlet: x=%d, y=%d", windowPoint.x(), windowPoint.y());
	return windowPoint;
}
*/


QPoint Pump::outlet_pos() {
	QPoint out;
	if (_vertical)
		out = QPoint(width() / 2, 0);
	else
		out = QPoint(height(), height() / 2);

	QPoint windowPoint = pos() + out;
	return windowPoint;
}



QSize Pump::sizeHint() const
{
	return QSize(30, 30);
}
