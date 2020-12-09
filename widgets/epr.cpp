#include <QPainter>
#include <QResizeEvent>
#include <QTime>
#include <QTimer>
#include <QWidget>

#include "epr.h"

const int arcwidth = 5;
const int arcmaker_length = 10;
const int arc_rad = 80;

Epr::Epr(QWidget *parent) :
	Arcwidget(parent, 0, 225, 7, 30)
{
	setFixedSize(100,100);

	set_min(1);
	set_min_normal(1);
	set_max(1.6);
	set_max_normal(1.7); // will never be reached
}

void Epr::paintEvent(QPaintEvent *)
{
	int side = qMin(width(), height());
	QPainter painter(this);
	painter.setRenderHint((QPainter::Antialiasing));
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);
	painter.setPen(Qt::blue);
	//painter.drawRect(-100,-100,200,200);

	QFont font;
	font.setPixelSize(label_font_sz);
	font.setBold(1);
	painter.setFont(font);

	if (!started()) {
		print_not_started(&painter, &font);
		return;
	}

	painter.setPen(QPen(Qt::white, arcwidth));
	print_arc(&painter);
	print_tics_and_label(&painter);

	print_value(&painter);
	paint_needle(&painter, arc_rad + 10, value_torot());
}


void Epr::resizeEvent(QResizeEvent *event) {
		_font_scale = 100.0 / event->size().width();
	//	qDebug("EPR: font scale %f, new width %d", _font_scale, event->size().width());
}


void Epr::print_arc(QPainter *p) {
	p->save();
	p->translate(-1 * arc_rad ,-1 * arc_rad);
	p->drawArc(0, 0,2 * arc_rad, 2 * arc_rad, _arc_startangle * 16 , (_arc_endangle - _arc_startangle) * 16);
	p->restore();
}


void Epr::print_not_started(QPainter *p, QFont *f) {
	p->save();
	p->setPen(QPen(QColor(0xFF, 0xA0, 0x00), arcwidth));
	print_arc(p);
	f->setPixelSize(value_font_sz * _font_scale);
	f->setBold(0);
	p->setFont(*f);
	p->drawText(-30,-20,"xx");
	p->drawText(0,30,"xx");
	p->restore();
}


void Epr::print_tics_and_label(QPainter *p) {
	p->save();
	p->rotate(-_arc_endangle);	// Set to stop marker (this is min value)

	for(int i = 0; i < _arc_ticpoints; i++) {
		p->drawLine(arc_rad - arcmaker_length , 0, arc_rad, 0);
		p->rotate(tickrotate());
	}
	p->restore();

	p->save();
	p->rotate(-60);
	p->setPen(QPen(Qt::yellow, 8));
	p->drawLine(arc_rad + 10, 0, arc_rad - 5, 0);
	p->restore();

	p->save();
	QTransform f = QTransform().translate(-18, 2).rotate(180 - _arc_endangle);
	QPoint po = QPoint(arc_rad - arcmaker_length - 25, 0);
	QPoint pf;

	float epr = _max;
	for(int i = 0; i < 7; i++) {
		pf = f.map(po);
		if (i % 2 == 0)
			p->drawText(pf, QString().number(epr));
		f.rotate(-30);
		epr -= 0.1;
	}
	p->restore();
}


void Epr::print_value(QPainter *p) {
	p->setPen(QPen(Qt::cyan, arcwidth));
	p->drawRect(-22, 15, 72, 30);
	if (is_normalvalue())
		p->setPen(QPen(Qt::green, arcwidth));
	else
		p->setPen(QPen(Qt::red, arcwidth));
	p->drawText(-20,40,QString().number(value(), 'f', 3));
}


void Epr::paint_needle(QPainter *p, int length, int rot) {
	p->save();
	p->rotate(rot);
	if (is_normalvalue())
		p->setPen(QPen(Qt::green, 5));
	else
		p->setPen(QPen(Qt::red, 5));
	p->drawLine(0, 0, length, 0);
	p->restore();
}


QSize Epr::sizeHint() const
{
	return QSize(100, 100);
}
