// 11.4.2015

#include <QPainter>
#include <QLabel>

#include "widgets/valve.h"
#include "widgets/pump.h"
#include "cond_page.h"
#include "ui_cond_page.h"

static int linewidth = 2;

CondPage::CondPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CondPage),
	_ckpt_trim(0),
	_fwd_trim(0),
	_aft_trim(0),
	_ckpt_tmp(0),
	_fwd_tmp(0),
	_aft_tmp(0),
	_ckpt_duct(0),
	_fwd_duct(0),
	_aft_duct(0),
	_carg_tmp(0),
	_carg_duct(0),
	_carg_trim(0)
{
	ui->setupUi(this);

	ui->val_carg_out_iso->set_vertical(false);
	ui->val_ha_press_cab->set_vertical(false);
	ui->val_cargo_ha_press->set_vertical(false);

	//ui->val_hp2->set_color_man_alert(0);
	//ui->val_ip2->set_color_man_alert(0);
}


void CondPage::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint((QPainter::Antialiasing));

	painter.setPen(QPen(Qt::green, linewidth));

	paint_silhoute(&painter);
	QPoint trim_ckpt_p = QPoint(127-30,170);
	QPoint trim_fwd_p = QPoint(257-30,170);
	QPoint trim_aft_p = QPoint(367-30,170);
	paint_simple_arc(&painter, trim_ckpt_p.x(), trim_ckpt_p.y(), 0, 100, _ckpt_trim);
	paint_simple_arc(&painter, trim_fwd_p.x(), trim_fwd_p.y(), 0, 100, _fwd_trim);
	paint_simple_arc(&painter, trim_aft_p.x(), trim_aft_p.y(), 0, 100, _aft_trim);

	QPoint press_cab = ui->val_ha_press_cab->inlet_pos();
	QPoint press_cab_out = ui->val_ha_press_cab->outlet_pos();
	painter.drawLine(press_cab.x(), press_cab.y(), trim_ckpt_p.x(), press_cab.y()); // horz line
	painter.drawLine(trim_ckpt_p.x(), press_cab.y(), trim_ckpt_p.x(), trim_ckpt_p.y() + 30);
	painter.drawLine(trim_fwd_p.x(), press_cab.y(), trim_fwd_p.x(), trim_fwd_p.y() + 30);
	painter.drawLine(trim_aft_p.x(), press_cab.y(), trim_aft_p.x(), trim_aft_p.y() + 30);
	painter.drawLine(press_cab_out.x(), press_cab_out.y(), press_cab_out.x() + 10, press_cab_out.y());

	paint_cargo(&painter);
	paint_simple_arc(&painter, 288, 338, 0, 100, _carg_trim);

//		painter.setPen(QPen(QColor( 0xFF, 0xA0, 0x00), linewidth)); // Orange


	/* Warnings */
	display_label_warning(ui->disp_ckpt_duct, -99, 80, _ckpt_duct);
	display_label_warning(ui->disp_fwd_duct, -99, 80, _fwd_duct);
	display_label_warning(ui->disp_aft_duct, -99, 80, _aft_duct);
	display_label_warning(ui->disp_carg_duct, -99, 80, _carg_duct);
}


void CondPage::paint_cargo(QPainter *p) {
	QPoint out_tmp = ui->val_carg_out_iso->outlet_pos();
	QPoint out = QPoint(out_tmp.x() - 15, out_tmp.y() -15);
	QPoint in_tmp = ui->val_carg_out_iso->inlet_pos();
	QPoint in = QPoint(in_tmp.x() + 15, in_tmp.y() + 15);

	p->save();
	p->setPen(QPen(Qt::blue, 2));
	p->drawLine(in.x(), in.y(), in.x(), in.y() + 9);
	p->drawLine(in.x(), in.y() + 9, in.x() - 50, in.y() + 9);
	p->drawLine(274, in.y() + 9, 212, in.y() + 9);
	p->drawLine(212, in.y() + 9, 212, out.y() - 9);
	p->drawLine(212, out.y() - 9, out.x(), out.y() - 9);
	p->drawLine(out.x(), out.y() - 9, out.x(), out.y());
	p->restore();

	QPoint carg_in_inlet = ui->val_cargo_inlet_iso->inlet_pos();
	QPoint carg_in_oulet = ui->val_cargo_inlet_iso->outlet_pos();
	QPoint carg_ha_press_inlet = ui->val_cargo_ha_press->inlet_pos();
	p->drawLine(carg_in_inlet.x(), carg_in_inlet.y(), carg_in_inlet.x(), 338);
	p->drawLine(288, 338 + 30, 288, carg_ha_press_inlet.y());
	p->drawLine(288, carg_ha_press_inlet.y(), carg_ha_press_inlet.x(), carg_ha_press_inlet.y());
	p->drawLine(carg_in_oulet.x(), carg_in_oulet.y(), carg_in_oulet.x(), carg_in_oulet.y() - 5);
	QPoint carg_ha_press_outlet = ui->val_cargo_ha_press->outlet_pos();
	p->drawLine(carg_ha_press_outlet.x(), carg_ha_press_outlet.y(), carg_ha_press_outlet.x() + 10, carg_ha_press_outlet.y());
}


void CondPage::paint_silhoute(QPainter *p) {
	p->save();
	p->setPen(QPen(Qt::blue, 2));
	const int yu = 160;
	p->drawLine(QPoint(105-30,104), QPoint(380-30,104));
	p->drawLine(QPoint(143-30,yu), QPoint(237-30,yu));
	p->drawLine(QPoint(277-30,yu), QPoint(351-30,yu));
	p->drawLine(QPoint(187-30,yu), QPoint(187-30,105));
	p->drawLine(QPoint(307-30,yu), QPoint(307-30,132));

	p->drawArc(105 - 18-30, 104, 2 * 18, 2 * 18, 90 * 16, 60 * 16); // Top Ckpt
	p->drawArc(380 - 50-30, 104, 2 * 50, 2 * 50, 60 * 16, 30 * 16); // Top Aft
	p->drawArc(338-30, yu - 2 * 45, 2 * 45, 2 * 45, 270 * 16, 25 * 16); // Bottom Aft

	/* Cockpit */
	p->drawArc(15-30, 112, 2 * 90, 2 * 90, 100 * 16, 25 * 16);
	p->drawArc(49-30, 129, 13, 13, 120 * 16, 110 * 16);
	p->drawArc(46-30, 83, 77, 77, 210 * 16, 60 * 16);
	p->drawLine(QPoint(86-30,yu), QPoint(112-30, yu));
	p->restore();
}


void CondPage::set_label_color(QLabel *l, bool alert) {
	QPalette palette = l->palette();
	if (alert)
		palette.setColor(l->foregroundRole(), Qt::red);
	else
		palette.setColor(l->foregroundRole(), Qt::green);
	l->setPalette(palette);
}


void CondPage::display_label_warning(QLabel *l, int min, int max, int val) {
	if (val <= min || val >= max)
		set_label_color(l, true);
	else
		set_label_color(l, false);
}


void CondPage::paint_simple_arc(QPainter *p, int x, int y, int min, int max, int val) {
	if (val > max)
			val = max;
	if (val < min)
			val = min;
	int winkel = 100.0 / (max - min) * val + 40;
	p->save();
	p->setPen(QPen(Qt::white, 2));
	p->drawArc(x - 30, y, 60, 60, 40 * 16, 100 * 16);
	p->restore();
	p->save();
	p->translate(x,y + 30); // Drehpunkt
	p->rotate(winkel);
//	if (val == min || val == max)
//		p->setPen(QPen(QColor( 0xFF, 0xA0, 0x00), linewidth)); // Orange
	p->drawLine(-30, 0, 0, 0);
	p->restore();
}


bool CondPage::set_new_value(QLabel *w, int v) {
	QString s = QString::number(v);
	if (QString::compare(w->text(), s)) {
		w->setText(s);
		return true;
	}
	return false;
}


bool CondPage::set_new_value(Pump *w, int v) {
	if (w->value() !=  !!v) {
		w->set_value(v ? Pump::ON : Pump::OFF);
		return true;
	}
	return false;
}


bool CondPage::set_new_value(Valve *w, int v) {
	if (w->value() !=  !!v) {
		w->set_value(v ? Valve::OPEN : Valve::CLOSE);
		return true;
	}
	return false;
}


bool CondPage::set_new_value(int *s, int v) {
	if (*s !=  v) {
		*s = v;
		return true;
	}
	return false;
}


bool CondPage::set_new_value(bool *s, bool v) {
	if (*s !=  v) {
		*s = v;
		return true;
	}
	return false;
}


void CondPage::set_value(ValueType t, int v) {
	bool newval = false;

	switch(t) {
	case VALVE_HOT_AIR: newval = set_new_value(ui->val_ha_press_cab, !!v); break;
	case VALVE_CARG_HOT_AIR: newval = set_new_value(ui->val_cargo_ha_press, !!v); break;
	case VALVE_CARG_OUT_ISO: newval = set_new_value(ui->val_carg_out_iso, !!v); break;
	case VALVE_CARG_IN_ISO: newval = set_new_value(ui->val_cargo_inlet_iso, !!v); break;
	case CKPT_TRIM: newval = set_new_value(&_ckpt_trim, v); break;
	case FWD_TRIM: newval = set_new_value(&_fwd_trim, v); break;
	case AFT_TRIM: newval = set_new_value(&_aft_trim, v); break;
	case CKPT_TMP: newval = set_new_value(ui->disp_ckpt_tmp, v); break;
	case FWD_TMP: newval = set_new_value(ui->disp_fwd_tmp, v); break;
	case AFT_TMP: newval = set_new_value(ui->disp_aft_tmp, v); break;
	case CKPT_DUCT: newval = set_new_value(ui->disp_ckpt_duct, v); break;
	case FWD_DUCT: newval = set_new_value(ui->disp_fwd_duct, v); break;
	case AFT_DUCT: newval = set_new_value(ui->disp_aft_duct, v); break;
	case CARG_TMP: newval = set_new_value(ui->disp_carg_tmp, v); break;
	case CARG_DUCT: newval = set_new_value(ui->disp_carg_duct, v); break;
	case CARG_TRIM: newval = set_new_value(&_carg_trim, v); break;
	case TAT : newval = set_new_value(ui->disp_tat, v); break;
	case SAT : newval = set_new_value(ui->disp_sat, v); break;
	case HH : newval = set_new_value(ui->disp_hh, v); break;
	case MM : newval = set_new_value(ui->disp_mm, v); break;
	case GW : newval = set_new_value(ui->disp_gw, v); break;
	}

	if (newval)
		update();
}


CondPage::~CondPage()
{
	delete ui;
}
