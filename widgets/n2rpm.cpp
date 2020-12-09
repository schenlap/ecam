#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QWidget>
#include <QTransform>
#include <QResizeEvent>

#include "n2rpm.h"

const int arcwidth = 5;

N2Rpm::N2Rpm(QWidget *parent) :
	Arcwidget(parent, 20, 20 + 200, 6, 30) ,
	font_scale(1)
{
	setFixedSize(60,60);

	set_min(0);
	set_min_normal(0);
	set_max(130);
	set_max_normal(100);

	set_value(0);
}


void N2Rpm::paintEvent(QPaintEvent *)
{
	int side = qMin(width(), height());
	QPainter painter(this);
	QFont font;

	font.setPixelSize(value_font_sz * font_scale);
	font.setBold(1);
	painter.setFont(font);

	painter.setRenderHint((QPainter::Antialiasing));
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);
	//painter.setWindow(-100, -100, 200, 200);

	painter.setPen(Qt::blue);
	//painter.drawRect(-100,-100,200,200);

	// Value Rectangle
	//painter.setPen(QPen(QColor(Qt::gray), arcwidth));
	//painter.drawRect(-25, 25, 70 , -40);

	if (!started()) {
		print_not_started(&painter, &font);
		return;
	}

	print_value(&painter);
}


void N2Rpm::resizeEvent(QResizeEvent *event) {
		_font_scale = 100.0 / event->size().width();
	//	qDebug("EPR: font scale %f, new width %d", _font_scale, event->size().width());
}


void N2Rpm::print_not_started(QPainter *p, QFont *f) {
	p->save();
	p->setPen(QPen(QColor(0xFF, 0xA0, 0x00), arcwidth));
	f->setPixelSize(value_font_sz * font_scale);
	f->setBold(0);
	p->setFont(*f);
	p->drawText(QRect(-50,-10, 100, 80), Qt::AlignCenter, "xx");
	p->restore();

}


void N2Rpm::print_value(QPainter *p) {
	//p->setPen(QPen(Qt::cyan, arcwidth));
	//p->drawRect(-22, 15, 52, 30);
	if (is_normalvalue())
		p->setPen(QPen(Qt::green, arcwidth));
	else
		p->setPen(QPen(Qt::red, arcwidth));
	p->drawText(QRect(-30,-10,60,20), Qt::AlignCenter, QString().number(value(), 'f', 1));
}


QSize N2Rpm::sizeHint() const
{
	return QSize(60, 60);
}
