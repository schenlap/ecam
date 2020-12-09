#include <QPainter>

#include "faultoffbutton.h"
#include "ui_faultoffbutton.h"

FaultOffButton::FaultOffButton(QWidget *parent) :
	QAbstractButton(parent),
	ui(new Ui::FaultOffButton),
	_fault(true),
	_off(true)
{
	ui->setupUi(this);
}


void FaultOffButton::set_fault(bool f) {
	_fault = f;
	update();
}


void FaultOffButton::set_off(bool f) {
	_off = f;
	update();
}


void FaultOffButton::set_label_color(QLabel *l, QColor c) {
	QPalette palette = l->palette();
	palette.setColor(l->foregroundRole(), c);
	l->setPalette(palette);
}


void FaultOffButton::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setPen(QPen(Qt::white, 1));
	//painter.drawLine(13, 43, 67, 43);
	painter.setPen(QPen(Qt::white, 2));
	painter.drawRect(40 - 42 / 2, 23, 42 + 1, 42);

	if (_off) {
		set_label_color(ui->label_3, Qt::white);
		painter.setPen(QPen(Qt::white, 1));
	} else {
		set_label_color(ui->label_3, Qt::darkGray);
		painter.setPen(QPen(Qt::darkGray, 1));
	}
	painter.drawRect(40 - 38/2, 43, 38, 18);

	if (_fault)
		set_label_color(ui->label_2, QColor( 0xFF, 0xA0, 0x00));
	else
		set_label_color(ui->label_2, Qt::darkGray);
}


QSize FaultOffButton::sizeHint() const
{
	return QSize(80, 70);
}


FaultOffButton::~FaultOffButton()
{
	delete ui;
}
