// Stefan SCHÖFEGGER: 4.4.2015
// TODO: Display valve transit (45 degree)

#include <QPainter>

#include "valve.h"

static int linewidth = 10;

Valve::Valve(QWidget *parent, bool vertical, bool apu) :
	QWidget(parent),
	_parent(parent),
	_is_apu(apu),
	_desired(CLOSE),
	_actual(CLOSE),
	_vertical(vertical),
	_color_man_alert(-1)
{

}


void Valve::set_vertical(bool vertical) {
	_vertical = vertical;
}


void Valve::set_apu(bool apu) {
	_is_apu = apu;
}


void Valve::set_color_man_alert(int man) {
	_color_man_alert = man;
}


Valve::~Valve()
{

}


void Valve::set_value(Valvestate s) {
	_desired = s;
	_actual = s;
}


void Valve::paintEvent(QPaintEvent *) {
	QPainter painter(this);

	int side = qMin(width(), height());
	painter.setRenderHint((QPainter::Antialiasing));
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);

	if (!_vertical)
		painter.rotate(90);

	painter.setPen(QPen(Qt::green, linewidth));

	if (_color_man_alert == -1) {
		if (_desired == OPEN) {
			painter.drawLine(0, -100, 0, 100); // verticel
		} else {
			if (!is_moving()) {
				if (_is_apu)
					painter.setPen(QPen(Qt::green, linewidth));
				else
					painter.setPen(QPen(QColor( 0xFF, 0xA0, 0x00), linewidth));
			} else {
				painter.setPen(QPen(QColor( 0xFF, 0xA0, 0x00), linewidth / 2));
			}

			painter.drawLine(-100, 0, 100, 0); // horizontal
		}
	} else {
		if (_color_man_alert == 0) {
			painter.setPen(QPen(Qt::green, linewidth));
		} else {
			painter.setPen(QPen(QColor( 0xFF, 0xA0, 0x00), linewidth));
		}
		if (_desired == OPEN)
			painter.drawLine(0, -100, 0, 100); // verticel
		else
			painter.drawLine(-100, 0, 100, 0); // horizontal
	}

	painter.drawEllipse(QPointF(0, 0), 100 - linewidth / 2, 100 - linewidth / 2);
}


QPoint Valve::inlet_pos() {
	QPoint in;
	if (_vertical)
		in = QPoint(width() / 2, height());
	else
		in = QPoint(0, height() / 2);

	QPoint windowPoint = pos() + in;
	return windowPoint;
}


QPoint Valve::outlet_pos() {
	QPoint out;
	if (_vertical)
		out = QPoint(width() / 2, 0);
	else
		out = QPoint(height(), height() / 2);

	QPoint windowPoint = pos() + out;
	return windowPoint;
}


bool Valve::is_moving() {
	return _desired != _actual;
}

QSize Valve::sizeHint() const
{
	return QSize(30, 30);
}
