#include <QPainter>
#include <QResizeEvent>
#include <QWidget>

#include "egt.h"

const int arcwidth = 5;
const int arcmaker_length = 10;
const int arc_rad = 80;

Egt::Egt(QWidget *parent) :
	Arcwidget(parent, 45, 45 + 180, 3, 0)
{
	setFixedSize(100,100);

	set_min(0);
	set_min_normal(0);
	set_max(800);
	set_max_normal(635);

	set_value(25);
	_value_max = 0;
}

void Egt::paintEvent(QPaintEvent *)
{
	float val = value();
	if (val > _value_max)
		_value_max = val;

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

	if (!started()) {
		print_not_started(&painter, &font);
		return;
	}

	painter.setPen(QPen(Qt::white, arcwidth));
	print_arc(&painter);
	print_tics_and_label(&painter);

	print_value(&painter);
	paint_needle(&painter, arc_rad + 10, value_torot());

	if (_value_max > _max_normal)
		paint_peak(&painter);
}


void Egt::resizeEvent(QResizeEvent *event) {
		_font_scale = 100.0 / event->size().width();
		//qDebug("EGT: font scale %f, new width %d", _font_scale, event->size().width());
}


void Egt::print_arc_ns(QPainter *p) {
	p->save();
	p->translate(-1 * arc_rad ,-1 * arc_rad);
	p->drawArc(0, 0,2 * arc_rad, 2 * arc_rad, (_arc_startangle + 45) * 16 , (_arc_endangle - 45) * 16);
	p->drawArc(0, 0, 2 * arc_rad, 2 * (arc_rad ), _arc_startangle * 16 , (45) * 16);
	p->restore();
}

void Egt::print_arc(QPainter *p) {
	p->save();
	p->translate(-1 * arc_rad ,-1 * arc_rad);
	p->drawArc(0, 0,2 * arc_rad, 2 * arc_rad, (_arc_startangle + 45) * 16 , (_arc_endangle - _arc_startangle - 45) * 16);
	p->setPen(QPen(Qt::red, arcwidth));
	p->drawArc(0, 0, 2 * arc_rad, 2 * (arc_rad ), _arc_startangle * 16 , (45) * 16);
	p->drawArc(10, 10, 2 * (arc_rad - 10), 2 * (arc_rad - 10), _arc_startangle * 16 , (45) * 16);
	p->restore();
}


void Egt::print_not_started(QPainter *p, QFont *f) {
	p->save();
	p->setPen(QPen(QColor(0xFF, 0xA0, 0x00), arcwidth));
	print_arc_ns(p);
	f->setPixelSize(value_font_sz * _font_scale);
	f->setBold(0);
	p->setFont(*f);
	p->drawText(-20,40,"xx");
	p->restore();
}


void Egt::print_tics_and_label(QPainter *p) {
	p->save();
	p->rotate(_arc_endangle);
	for(int i = 0; i < (_arc_ticpoints - 1); i++) {
		if (i == 1) {
			p->save();
			p->setPen(QPen(Qt::red, arcwidth));
			p->drawLine(arc_rad - arcmaker_length , 0, arc_rad, 0);
			p->restore();
		} else {
			p->drawLine(arc_rad - arcmaker_length , 0, arc_rad, 0);
		}
		p->rotate(tickrotate());
	}
	p->restore();

	p->save();
	QTransform f = QTransform().translate(-10, -2).rotate(-_arc_endangle);
	QPoint po = QPoint(arc_rad - arcmaker_length - 25, 0);
	QPoint pf;

	float epr = 0;
	for(int i = 0; i < 3; i++) {
		pf = f.map(po);
		if (i == 1 || i == 2)
			p->drawText(pf, QString().number(epr));
		f.rotate(tickrotate());
		epr += 4;
	}
	p->restore();
}


void Egt::print_value(QPainter *p) {
	p->setPen(QPen(Qt::cyan, arcwidth));
	p->drawRect(-22, 15, 52, 30);
	if (is_normalvalue())
		p->setPen(QPen(Qt::green, arcwidth));
	else
		p->setPen(QPen(Qt::red, arcwidth));
	p->drawText(-20,40,QString().number(value(), 'f', 0));
}


void Egt::paint_needle(QPainter *p, int length, int rot) {
	p->save();
	p->rotate(rot);
	if (is_normalvalue())
		p->setPen(QPen(Qt::green, 5));
	else
		p->setPen(QPen(Qt::red, 5));
	p->drawLine(0, 0, length, 0);
	p->restore();
}


void Egt::paint_peak(QPainter *p) {
	p->save();
	p->rotate(value_torot(_value_max));
	p->setPen(QPen(QColor(0xFF, 0xA0, 0x00), 2 * arcwidth));
	p->drawLine(arc_rad + 5, 0, arc_rad + 10, 0);
	p->restore();
}


QSize Egt::sizeHint() const
{
	return QSize(100, 100);
}
