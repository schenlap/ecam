#include <QPainter>
#include <QResizeEvent>
#include <qmath.h>
#include <QTimer>
#include <QWidget>

#include "arcwidget.h"
#include "flaps.h"

//const int arcwidth = 5;
//const int arcmaker_length = 10;
//const int arc_rad = 80;

Flaps::Flaps(QWidget *parent) :
	QWidget(parent) ,
	_desired(0),
	_actual(0),
	_started(false),
	_font_scale(1)
{
	setFixedSize(125,125);
	_timer = new QTimer;
	_timer->setSingleShot(true);
	connect(_timer, SIGNAL(timeout()), this, SLOT(transit_done()));

	set_value(2);
}

void Flaps::paintEvent(QPaintEvent *)
{
	int side = qMin(width(), height());
	QPainter painter(this);
	painter.setRenderHint((QPainter::Antialiasing));
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);
	painter.setPen(Qt::blue);
	//painter.drawRect(-100,-100,200,200);

	QFont font;
	font.setPixelSize(label_font_sz * _font_scale);
	font.setBold(1);
	painter.setFont(font);

	// Value Rectangle
	//painter.setPen(QPen(QColor(Qt::gray), arcwidth));
	//painter.drawRect(-25, 25, 70 , -40);

	print_aleron(&painter);
	print_flaps(&painter);
	return;

	if (!started()) {
		//print_not_started(&painter, &font);
		return;
	}

}


void Flaps::resizeEvent(QResizeEvent *event) {
		_font_scale = 100.0 / event->size().width();
		//qDebug("EGT: font scale %f, new width %d", _font_scale, event->size().width());
}


void Flaps::print_aleron(QPainter *p) {
	p->save();
	const int yoff = -20;
	static const QPoint aleron[4] = {
		QPoint(5, 0 + yoff),
		QPoint(1, 7 + yoff),
		QPoint(-21, 7 + yoff),
		QPoint(-25, 0 + yoff)
	};
	p->setPen(Qt::cyan);
	p->setBrush(Qt::cyan);
	p->drawConvexPolygon(aleron, 4);
	p->restore();
}


void Flaps::print_flaps(QPainter *p) {
	p->save();
	p->setPen(Qt::white);

	QFont font;
	font.setPixelSize(label_font_sz);
	font.setBold(0);
	p->setFont(font);

	p->drawText(-70, -50, "S");
	p->drawText(-20, -50, "Flaps");
	p->drawText(50, -50, "F");

	static int yoff = -10;
	static const QPoint flapend[7] = {
		QPoint(45, 0 + yoff), // Flaps 1
		QPoint(60, 20 + yoff),
		QPoint(70, 40 + yoff),
		QPoint(70, 60 + yoff),  // Flaps 4
		QPoint(-65, 10 + yoff),  // Slats 1
		QPoint(-83, 30 + yoff),
		QPoint(-90, 50 + yoff)  // Slats 3
	};

	QPen linepen(Qt::white);
	linepen.setCapStyle(Qt::RoundCap);
	linepen.setWidth(8);
	p->setPen(linepen);

	for (int i = 0; i < 7; i++) {
		p->drawPoint(flapend[i]);
	}

	QPoint start = QPoint(5, -13);
	QPoint mid = QPoint(35, -5);
	if (_desired == 0) {
		QPoint end = QPoint(17, 7 - 20);
		print_flap(p, &start, &end, 0);
	} else if (_desired == 1) {
		print_flap(p, &start, &flapend[_desired - 1], 0);
	} else {
		print_flap(p, &start, &flapend[_desired - 1], &mid);
	}

	QPoint end_slat = QPoint(-35, 7 - 20);
	QPoint start_slat = QPoint(-25, -13);
	QPoint mid_slat = QPoint(-45, -5);
	if (_desired <= 1)
		print_slat(p, &start_slat, &end_slat, 0);
	else if (_desired == 2)
		print_slat(p, &start_slat, &flapend[_desired -1 + 3], 0);
	else
		print_slat(p, &start_slat, &flapend[_desired - 1 + 3], &mid_slat); // slat begin driving at des = 1 not 0, so -3

	p->restore();
}


void Flaps::print_flap(QPainter *p, const QPoint *start, const QPoint *end, const QPoint *middle) {
	p->save();

	if (is_moving())
		p->setPen(QPen(Qt::cyan, 3));
	else
		p->setPen(QPen(Qt::green, 3));


	static const QPoint flapp[3] = {
		QPoint(5, 0 -20),
		QPoint(17, 7 - 20),
		QPoint(1, 7 -20)
	};


	if (_desired == 0) {
		p->drawPolygon(flapp, 3);
		p->restore();
		return;
	}

	QPoint endnew = *end;
	endnew.setX(end->x() - 5);

	float rot;
	if (middle == 0) {
		p->drawLine(*start, endnew);
		rot = atan2(end->y() - start->y(), endnew.x() - start->x()) * 180 / M_PI;
		//qDebug("Winkel %f", rot);
	} else {
		p->drawLine(*start, *middle);
		p->drawLine(*middle, endnew);
		rot = atan2(end->y() - middle->y(), endnew.x() - middle->x()) * 180 / M_PI;
		//qDebug("Winkel %f", -rot);
	}

	QPoint flapnew[3];
	for (int i=0; i < 3; i++){
		flapnew[i] = flapp[i] - flapp[1] + endnew;
	}

	p->translate(endnew);
	p->rotate(rot);

	for (int i=0; i < 3; i++){
		flapnew[i] -= endnew;
	}

	p->drawPolygon(flapnew, 3);
	p->restore();
}


void Flaps::print_slat(QPainter *p, const QPoint *start, const QPoint *end, const QPoint *middle ) {
	p->save();

	if (is_moving())
		p->setPen(QPen(Qt::cyan, 3));
	else
		p->setPen(QPen(Qt::green, 3));


	static const QPoint slatpp[3] = {
		QPoint(-21, 7 -20),
		QPoint(-38, 7 - 20),
		QPoint(-25, 0 -20)

	};

	if (_desired <= 1) {
		p->drawPolygon(slatpp, 3);
		p->restore();
		return;
	}

	QPoint endnew = *end;
	endnew.setX(end->x() + 5);

	float rot;
	if (middle == 0 || _desired == 2) {
		p->drawLine(*start, endnew);
		rot = atan2(start->y() - end->y(), start->x() - endnew.x()) * 180 / M_PI;
		//qDebug("Winkel %f", rot);
	} else {
		p->drawLine(*start, *middle);
		p->drawLine(*middle, endnew);
		rot = atan2(middle->y() - end->y(), middle->x() - endnew.x()) * 180 / M_PI;
		//qDebug("Winkel %f", -rot);
	}

	QPoint slatnew[3];
	for (int i=0; i < 3; i++){
		slatnew[i] = slatpp[i] - slatpp[1] + endnew;
	}

	p->translate(endnew);
	p->rotate(rot);

	for (int i=0; i < 3; i++){
		slatnew[i] -= endnew;
	}

	p->drawPolygon(slatnew, 3);
	p->restore();
}


void Flaps::set_value(int flap) {
	if (flap > 4)
		flap = 4;
	else if (flap < 0)
		flap = 0;
	_desired = flap;
	//qDebug ("desired flap: %d", _desired);
	int steps = _desired - _actual;
	if (steps < 0)
		steps = (-1) * steps;
	_timer->start(3000 * steps);
	update();
}


bool Flaps::is_moving() {
	return _desired != _actual;
}


void Flaps::transit_done() {
	_actual = _desired;
	update();
}


QSize Flaps::sizeHint() const
{
	return QSize(125, 125);
}
