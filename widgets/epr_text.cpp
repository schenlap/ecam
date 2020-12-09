#include <QPainter>
#include <QResizeEvent>
#include <QWidget>

#include "arcwidget.h"
#include "epr_text.h"

const int arcwidth = 5;

EprText::EprText(QWidget *parent, QString str1, QString str2, bool pointer) :
	QWidget(parent),
	_str1(str1),
	_str2(str2),
	_pointer(pointer),
	_font_scale(1)
{
	setFixedSize(50,50);
}

void EprText::paintEvent(QPaintEvent *)
{
	int side = qMin(width(), height());
	QPainter painter(this);
	painter.setRenderHint((QPainter::Antialiasing));
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);
	painter.setPen(QPen(Qt::white, arcwidth));
	//painter.drawRect(-100,-100,200,200);

	QFont font;
	font.setPixelSize(label_font_sz * _font_scale);
	font.setBold(1);
	painter.setFont(font);

	painter.drawText(QRect(-40,-25,80,30), Qt::AlignCenter, _str1);

	painter.setPen(QPen(Qt::cyan, arcwidth));
	painter.drawText(QRect(-30,20,60,30), Qt::AlignCenter, _str2);

	if(!_pointer)
		return;

	int width = 100;
	int heigth = 15;
	painter.setPen(QPen(Qt::gray, arcwidth + 2));
	painter.drawLine(-35, 10, -25 - width, 10 + heigth);
	painter.drawLine(35, 10, 25 + width, 10 + heigth);
}


void EprText::resizeEvent(QResizeEvent *event) {
		_font_scale = 100.0 / event->size().width();
	//	qDebug("EPR: font scale %f, new width %d", _font_scale, event->size().width());
}


QSize EprText::sizeHint() const
{
	return QSize(50, 50);
}
