// 5.4.2015
// TODO Grey backgrounds
// TODO Anti ice text
// TODO Color on overvalue

#include <QPainter>
#include <QLabel>

#include "widgets/valve.h"
#include "widgets/pump.h"
#include "bleed_page.h"
#include "ui_bleed_page.h"

static int linewidth = 2;

BleedPage::BleedPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::BleedPage),
	_anti_ice1(false),
	_anti_ice2(false),
	_gnd(false),
	_out1(false),
	_out2(false),
	_out3(false),
	_ip_temp1(0),
	_ip_press1(0),
	_tempin1(0),
	_bypass1(0),
	_tempout1(0),
	_flow1(0),
	_ip_temp2(0),
	_ip_press2(0),
	_tempin2(0),
	_bypass2(0),
	_tempout2(0),
	_flow2(0)
{
	ui->setupUi(this);

	ui->val_apu->set_apu(true);
	ui->val_xfeed->set_vertical(false);
	ui->val_hp1->set_vertical(false);
	ui->val_hp1->set_color_man_alert(0);
	ui->val_hp2->set_vertical(false);
	ui->val_hp2->set_color_man_alert(0);
	ui->val_xfeed->set_apu(true);
	ui->val_ram->set_apu(true);
	ui->val_ip1->set_color_man_alert(0);
	ui->val_ip2->set_color_man_alert(0);
}


void BleedPage::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint((QPainter::Antialiasing));

	painter.setPen(QPen(Qt::green, linewidth));

	QPoint apu_val_in = ui->val_apu->inlet_pos();
	QPoint apu_val_out = ui->val_apu->outlet_pos();
	QPoint eng1_val_in = ui->val_eng1->inlet_pos();
	QPoint eng1_val_out = ui->val_eng1->outlet_pos();
	QPoint eng2_val_in = ui->val_eng2->inlet_pos();
	QPoint eng2_val_out = ui->val_eng2->outlet_pos();
	QPoint xfeed_val_in = ui->val_xfeed->inlet_pos();
	QPoint xfeed_val_out = ui->val_xfeed->outlet_pos();
	QPoint ip1_val_out = ui->val_ip1->outlet_pos();
	QPoint ip1_val_in = ui->val_ip1->inlet_pos();
	QPoint ip2_val_out = ui->val_ip2->outlet_pos();
	QPoint ip2_val_in = ui->val_ip2->inlet_pos();
	QPoint hp1_val_out = ui->val_hp1->outlet_pos();
	QPoint hp1_val_in = ui->val_hp1->inlet_pos();
	QPoint hp2_val_out = ui->val_hp2->outlet_pos();
	QPoint hp2_val_in = ui->val_hp2->inlet_pos();
	QPoint ram_val_in = ui->val_ram->inlet_pos();

	painter.drawLine(eng1_val_in.x(), 50, eng2_val_in.x(), 50); // Main outlets
	painter.drawLine(eng1_val_in.x(), 50, eng1_val_in.x(), 50+5); // Main outlets in eng 1
	painter.drawLine(eng2_val_in.x(), 50, eng2_val_in.x(), 50+5); // Main outlets in eng 2

	painter.drawLine(apu_val_out.x(), apu_val_out.y(), apu_val_out.x(), xfeed_val_in.y()); // APU above
	painter.drawLine(apu_val_in.x(), apu_val_in.y(), apu_val_in.x(), apu_val_in.y() + 10); // APU below

	// if XFEED
	painter.drawLine(xfeed_val_in.x(), xfeed_val_in.y(), eng1_val_in.x(), xfeed_val_in.y()); // XFeed - Eng1
	painter.drawLine(xfeed_val_out.x(), xfeed_val_out.y(), eng2_val_in.x(), xfeed_val_out.y()); // XFeed - Eng2
	// }

	// HP1
	if (ui->val_hp1->value() == Valve::OPEN)
		painter.drawLine(hp1_val_in.x(), hp1_val_in.y(), eng1_val_in.x(), hp1_val_in.y()); // HP1 -> IP

	// HP2
	if (ui->val_hp1->value() == Valve::OPEN)
		painter.drawLine(hp2_val_out.x(), hp2_val_out.y(), eng2_val_in.x(), hp2_val_out.y()); // HP2 -> IP


	/* ENG 1 */
	painter.drawLine(ip1_val_in.x(), ip1_val_in.y(), ip1_val_in.x(), hp1_val_in.y() + 15); // IP
	painter.drawLine(ip1_val_out.x(), ip1_val_out.y(), eng1_val_in.x(), eng1_val_in.y()); // IP - Eng
	painter.drawLine(hp1_val_out.x(), hp1_val_out.y(), hp1_val_out.x()+15, hp1_val_out.y()); // HP
	painter.drawLine(hp1_val_out.x()+15, hp1_val_out.y(), hp1_val_out.x()+15, hp1_val_out.y()+15); // HP

	paint_simple_arc(&painter, eng1_val_out.x(), 85, 0, 100, _bypass1); // tempout
	set_new_value(ui->disp_tempout1, _tempout1);
	paint_simple_arc(&painter, eng1_val_out.x(), eng1_val_out.y() - 30 + 15, 0, 100, _flow1); // tempin
	set_new_value(ui->disp_tempin1, _tempin1);

	/* ENG 2 */
	painter.drawLine(ip2_val_in.x(), ip2_val_in.y(), ip2_val_in.x(), hp2_val_in.y() + 15); // IP
	painter.drawLine(ip2_val_out.x(), ip2_val_out.y(), eng2_val_in.x(), eng2_val_in.y()); // IP - Eng
	painter.drawLine(hp2_val_in.x(), hp2_val_in.y(), hp2_val_in.x()-15, hp2_val_in.y()); // HP
	painter.drawLine(hp2_val_in.x()-15, hp2_val_in.y(), hp2_val_in.x()-15, hp2_val_in.y()+15); // HP

	paint_simple_arc(&painter, eng2_val_out.x(), 85, 0, 100, _bypass2); // tempout
	set_new_value(ui->disp_tempout2, _tempout2);
	paint_simple_arc(&painter, eng2_val_out.x(), eng2_val_out.y() - 30 + 15, 0, 100, _flow2); // tempin
	set_new_value(ui->disp_tempin2, _tempin2);

	/* RAM */
	painter.drawLine(ram_val_in.x(), ram_val_in.y(), ram_val_in.x(), ram_val_in.y()+10);

	/* x fedd vertical lines */
	if (ui->val_xfeed->value() == Valve::OPEN) {
	}

	//painter.save();
	//painter.fillRect(QRect(QPoint(71,262), QPoint(151,303)), QBrush(QColor(Qt::lightGray)));
	//painter.restore();

	/* TOP */
	painter.save();
	if (!_out1)
		painter.setPen(QPen(QColor( 0xFF, 0xA0, 0x00), linewidth)); // Orange
	paint_simple_triangle(&painter, 145, 35, 0);
	painter.restore();
	painter.save();
	if (!_out2)
		painter.setPen(QPen(QColor( 0xFF, 0xA0, 0x00), linewidth)); // Orange
	paint_simple_triangle(&painter, 240, 35, 0);
	painter.restore();
	painter.save();
	if (!_out3)
		painter.setPen(QPen(QColor( 0xFF, 0xA0, 0x00), linewidth)); // Orange
	paint_simple_triangle(&painter, 335, 35, 0);
	painter.restore();

	/* Anti Ice */
	if (_anti_ice1) {
		paint_simple_triangle(&painter, eng1_val_in.x() - 15, xfeed_val_in.y(), -90);
	}

	if (_anti_ice2) {
		paint_simple_triangle(&painter, eng2_val_in.x() + 15, xfeed_val_in.y(), 90);
	}

	/* GND */
	if (_gnd)
		paint_simple_triangle(&painter, 185, xfeed_val_in.y() + 1, 0);
	ui->disp_symb_gnd->setVisible(_gnd);

	/* Warnings */
	display_label_warning(ui->disp_ip_press1, 4, 60, _ip_press1);
	display_label_warning(ui->disp_ip_press2, 4, 60, _ip_press2);
	display_label_warning(ui->disp_ip_temp1, 150, 240, _ip_temp1); // TODO: time - temp indication
	display_label_warning(ui->disp_ip_temp2, 150, 240, _ip_temp2);
}


void BleedPage::set_label_color(QLabel *l, bool alert) {
	QPalette palette = l->palette();
	if (alert)
		palette.setColor(l->foregroundRole(), Qt::red);
	else
		palette.setColor(l->foregroundRole(), Qt::green);
	l->setPalette(palette);
}


void BleedPage::display_label_warning(QLabel *l, int min, int max, int val) {
	if (val <= min || val >= max)
		set_label_color(l, true);
	else
		set_label_color(l, false);
}


void BleedPage::paint_simple_triangle(QPainter *p, int x, int y, int rot) {
	const int size = 10;
	const QPoint t[3] = {
		QPoint(0, 0),
		QPoint(size / 2, size),
		QPoint(- size / 2, size)
	};
	p->save();
	p->translate(x, y);
	p->rotate(rot);
	p->drawConvexPolygon(t, 3);
	p->resetMatrix();
	p->restore();
}


void BleedPage::paint_simple_arc(QPainter *p, int x, int y, int min, int max, int val) {
	if (val > max)
			val = max;
	if (val < min)
			val = min;
	int winkel = 140.0 / (max - min) * val + 20;
	p->save();
	p->setPen(QPen(Qt::white, 2));
	p->drawArc(x - 30, y, 60, 60, 20 * 16, 140 * 16);
	p->restore();
	p->save();
	p->translate(x,y + 30); // Drehpunkt
	p->rotate(winkel);
	if (val == min || val == max)
		p->setPen(QPen(QColor( 0xFF, 0xA0, 0x00), linewidth)); // Orange
	p->drawLine(-35, 0, -15, 0);
	p->restore();
}


bool BleedPage::set_new_value(QLabel *w, int v) {
	QString s = QString::number(v);
	if (QString::compare(w->text(), s)) {
		w->setText(s);
		return true;
	}
	return false;
}


bool BleedPage::set_new_value(Pump *w, int v) {
	if (w->value() !=  !!v) {
		w->set_value(v ? Pump::ON : Pump::OFF);
		return true;
	}
	return false;
}


bool BleedPage::set_new_value(Valve *w, int v) {
	if (w->value() !=  !!v) {
		w->set_value(v ? Valve::OPEN : Valve::CLOSE);
		return true;
	}
	return false;
}


bool BleedPage::set_new_value(int *s, int v) {
	if (*s !=  v) {
		*s = v;
		return true;
	}
	return false;
}


bool BleedPage::set_new_value(bool *s, bool v) {
	if (*s !=  v) {
		*s = v;
		return true;
	}
	return false;
}


void BleedPage::set_value(ValueType t, int v) {
	bool newval = false;

	switch(t) {
	case IP_TEMP1: _ip_temp1 = v; set_new_value(ui->disp_ip_temp1, _ip_temp1); break;
	case IP_PRESS1: _ip_press1 = v; set_new_value(ui->disp_ip_press1, _ip_press1); break;
	case TEMPIN1: set_new_value(&_tempin1, v);  break;
	case BYPASS1: set_new_value(&_bypass1, v);  break;
	case TEMPOUT1: set_new_value(&_tempout1, v); break;
	case FLOW1: set_new_value(&_flow1, v);  break;
	case IP_TEMP2: _ip_temp2 = v; set_new_value(ui->disp_ip_temp2, _ip_temp2); break;
	case IP_PRESS2: _ip_press2 = v; set_new_value(ui->disp_ip_press2, _ip_press2); break;
	case TEMPIN2: set_new_value(&_tempin2, v); break;
	case BYPASS2: set_new_value(&_bypass2, v);  break;
	case TEMPOUT2: set_new_value(&_tempout2, v); break;
	case FLOW2: set_new_value(&_flow2, v);  break;
	case ANTI_ICE1: set_new_value(&_anti_ice1, !!v); break;
	case ANTI_ICE2: set_new_value(&_anti_ice1, !!v); break;
	case GND: set_new_value(&_gnd, !!v); break;
	case OUT1: set_new_value(&_out1, !!v); break;
	case OUT2: set_new_value(&_out2, !!v); break;
	case OUT3: set_new_value(&_out3, !!v); break;
	case TAT : newval = set_new_value(ui->disp_tat, v); break;
	case SAT : newval = set_new_value(ui->disp_sat, v); break;
	case HH : newval = set_new_value(ui->disp_hh, v); break;
	case MM : newval = set_new_value(ui->disp_mm, v); break;
	case GW : newval = set_new_value(ui->disp_gw, v); break;
	case VALVE_ENG1 : newval = set_new_value(ui->val_eng1, v); break;
	case VALVE_APU : newval = set_new_value(ui->val_apu, v);break;
	case VALVE_XFEED : newval = set_new_value(ui->val_xfeed, v); break;
	case VALVE_ENG2 : newval = set_new_value(ui->val_eng2, v);break;
	case VALVE_IP1 : newval = set_new_value(ui->val_ip1, v); break;
	case VALVE_IP2 : newval = set_new_value(ui->val_ip2, v); break;
	case VALVE_HP1 : newval = set_new_value(ui->val_hp1, v); break;
	case VALVE_HP2 : newval = set_new_value(ui->val_hp2, v); break;
	}

	if (newval)
		update();
}


BleedPage::~BleedPage()
{
	//delete ui;
}
