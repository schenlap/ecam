// 4.4.2015
// TODO: unreachable fuel quantity in cyan
// TODO: x feed valve in out tanks
// TODO: Fuel Uses Number in amber if engine is on idle
// TODO: Pump low pressure indication

#include <QPainter>
#include <QLabel>

#include "widgets/valve.h"
#include "widgets/pump.h"
#include "fuel_page.h"
#include "ui_fuel_page.h"

static int linewidth = 2;

FuelPage::FuelPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FuelPage)
{
	ui->setupUi(this);

	ui->val_apu->set_apu(true);
	ui->val_xfeed->set_vertical(false);
	ui->val_xfeed->set_apu(true);
}


void FuelPage::paintEvent(QPaintEvent *) {
	//qDebug("-");
	QPainter painter(this);
	painter.setRenderHint((QPainter::Antialiasing));

	painter.setPen(QPen(Qt::green, linewidth));

	QPoint apu_val_in = ui->val_apu->inlet_pos();
	QPoint eng1_val_in = ui->val_eng1->inlet_pos();
	QPoint eng2_val_in = ui->val_eng2->inlet_pos();
	QPoint xfeed_val_in = ui->val_xfeed->inlet_pos();
	QPoint xfeed_val_out = ui->val_xfeed->outlet_pos();
	QPoint pump_ll_out = ui->pump_left_left->outlet_pos();
	QPoint pump_lc_out = ui->pump_left_center->outlet_pos();
	QPoint pump_cl_out = ui->pump_center_left->outlet_pos();
	QPoint pump_cr_out = ui->pump_center_right->outlet_pos();
	QPoint pump_rc_out = ui->pump_right_center->outlet_pos();
	QPoint pump_rr_out = ui->pump_right_right->outlet_pos();

	QPoint xfeed_left = QPoint(eng1_val_in.x(), xfeed_val_in.y()); // Xfeed Y - Position

	/* horizontal lines */
	painter.drawLine(pump_ll_out, eng1_val_in); // Left Left
	painter.drawLine(pump_lc_out.x(), pump_lc_out.y(), pump_lc_out.x(), pump_lc_out.y()-10); // Left Center

	painter.drawLine(eng1_val_in.x(), xfeed_left.y() ,pump_cl_out.x() , xfeed_left.y()); // horiz. X Feed
	painter.drawLine(eng2_val_in.x(), xfeed_left.y() ,pump_cr_out.x() , xfeed_left.y()); // horit. X Feed

	painter.drawLine(apu_val_in.x(), apu_val_in.y(), apu_val_in.x(), xfeed_left.y()); // APU

	painter.drawLine(pump_cl_out.x(), xfeed_val_in.y(), pump_cl_out.x(), pump_cl_out.y()); // Center left
	painter.drawLine(pump_cr_out.x(), xfeed_val_in.y(), pump_cr_out.x(), pump_cr_out.y()); // Center right

	painter.drawLine(pump_rc_out.x(), pump_rc_out.y(), pump_rc_out.x(), pump_rc_out.y()-10); // Right Center
	painter.drawLine(pump_rr_out, eng2_val_in); // Right

	//painter.drawLine(ui->pump_right_right->outlet_pos(), ui->val_eng2->inlet_pos());
	/* vertical lines */
	painter.save();
	painter.setPen(QPen(Qt::blue, linewidth));
	painter.drawLine(pump_ll_out.x() - 10, pump_ll_out.y()-10, pump_lc_out.x() + 10, pump_lc_out.y()-10); // Left
	painter.drawLine(pump_cl_out.x() - 10, pump_cl_out.y()-10, pump_cl_out.x() + 10, pump_cl_out.y()-10); // Center Left
	painter.drawLine(pump_cr_out.x() - 10, pump_cr_out.y()-10, pump_cr_out.x() + 10, pump_cr_out.y()-10); // Center Right
	painter.drawLine(pump_rc_out.x() - 10, pump_rc_out.y()-10, pump_rr_out.x() + 10, pump_rr_out.y()-10); // Right
	painter.restore();

	/* x fedd vertical lines */
	if (ui->val_xfeed->value() == Valve::OPEN) {
		painter.drawLine(pump_cl_out.x(), xfeed_val_in.y(), xfeed_val_in.x() , xfeed_val_in.y());
		painter.drawLine(pump_cr_out.x(), xfeed_val_out.y(), xfeed_val_out.x() , xfeed_val_out.y());
	}

	painter.setPen(QPen(Qt::blue, 1));
	static const int fyo = 83;
	static const int fxo = 198;
	static const int fdx = 63;
	static const int fdy = 18;
	static const QPoint fr[4] = {
		QPoint(fxo, fyo),
		QPoint(fxo + fdx, fyo),
		QPoint(fxo + fdx, fyo + fdy),
		QPoint(fxo, fyo + fdy),
	};
	painter.drawConvexPolygon(fr, 4);
	static const QPoint fr2[4] = {
		QPoint(fxo-3, fyo-3),
		QPoint(fxo + fdx+3, fyo-3),
		QPoint(fxo + fdx+3, fyo + fdy+3),
		QPoint(fxo-3, fyo + fdy+3),
	};
	painter.drawConvexPolygon(fr2, 4);

	static const int yofs = 260 + 45;
	static const int dy = 40;
	static const int yc = 5;
	static const QPoint fl[8] = {
		QPoint(10, yofs),
		QPoint(90, yofs + yc),
		QPoint(390, yofs + yc),
		QPoint(470, yofs),
		QPoint(470, yofs + dy),
		QPoint(410, yofs + dy + yc),
		QPoint(90, yofs + dy + yc),
		QPoint(10, yofs + dy)
	};
	painter.drawConvexPolygon(fl, 8);
	static const QPoint fl2[8] = {
		QPoint(10-3, yofs-3),
		QPoint(90, yofs + yc-3),
		QPoint(390, yofs + yc-3),
		QPoint(470+3, yofs-3),
		QPoint(470+3, yofs + dy+3),
		QPoint(390, yofs + dy + yc+3),
		QPoint(90, yofs + dy + yc+3),
		QPoint(10-3, yofs + dy+3)
	};
	painter.drawConvexPolygon(fl2, 8);
	painter.drawLine(pump_cl_out.x()-15, yofs + yc, pump_cl_out.x()-15, yofs + yc + dy); // cl
	painter.drawLine(pump_cl_out.x()-15 + 3, yofs + yc, pump_cl_out.x()-15 + 3, yofs + yc + dy);
	painter.drawLine(pump_cr_out.x()+15, yofs + yc, pump_cr_out.x()+15, yofs + yc + dy); // cr
	painter.drawLine(pump_cr_out.x()+15 - 3, yofs + yc, pump_cr_out.x()+15 - 3, yofs + yc + dy);
	painter.setPen(QPen(Qt::green, linewidth));
	painter.drawLine(90, yofs - 3 - 1, 90, yofs + yc + dy + 3 + 1); // ll
	painter.drawLine(390, yofs - 3 - 1, 390, yofs + yc + dy + 3 + 1); // rr
}


bool FuelPage::set_new_value(QLabel *w, int v) {
	QString s = QString::number(v);
	if (QString::compare(w->text(), s)) {
		w->setText(s);
		return true;
	}
	return false;
}


bool FuelPage::set_new_value(Pump *w, int v) {
	if (w->value() !=  !!v) {
		w->set_value(v ? Pump::ON : Pump::OFF);
		return true;
	}
	return false;
}


bool FuelPage::set_new_value(Valve *w, int v) {
	if (w->value() !=  !!v) {
		w->set_value(v ? Valve::OPEN : Valve::CLOSE);
		return true;
	}
	return false;
}


void FuelPage::set_value(ValueType t, int v) {
	bool newval = false;
	switch(t) {
	case FOB: newval = set_new_value(ui->disp_fob, v); break;
	case LL_FUEL_QUANT : newval = set_new_value(ui->disp_ll, v); break;
	case LC_FUEL_QUANT : newval = set_new_value(ui->disp_cl, v); break;
	case CC_FUEL_QUANT : newval = set_new_value(ui->disp_cc, v); break;
	case RC_FUEL_QUANT : newval = set_new_value(ui->disp_cr, v); break;
	case RR_FUEL_QUANT : newval = set_new_value(ui->disp_rr, v); break;
	case LL_FUEL_TEMP : newval = set_new_value(ui->disp_temp_ll, v); break;
	case LC_FUEL_TEMP : newval = set_new_value(ui->disp_temp_cl, v); break;
	case RC_FUEL_TEMP : newval = set_new_value(ui->disp_temp_cr, v); break;
	case RR_FUEL_TEMP : newval = set_new_value(ui->disp_temp_rr, v); break;
	case TAT : newval = set_new_value(ui->disp_tat, v); break;
	case SAT : newval = set_new_value(ui->disp_sat, v); break;
	case HH : newval = set_new_value(ui->disp_hh, v); break;
	case MM : newval = set_new_value(ui->disp_mm, v); break;
	case GW : newval = set_new_value(ui->disp_gw, v); break;
	case PUMP_LL : newval = set_new_value(ui->pump_left_left, v); break;
	case PUMP_LC : newval = set_new_value(ui->pump_left_center, v); break;
	case PUMP_CL : newval = set_new_value(ui->pump_center_left, v); break;
	case PUMP_CR : newval = set_new_value(ui->pump_center_right, v); break;
	case PUMP_RC : newval = set_new_value(ui->pump_right_center, v);break;
	case PUMP_RR : newval = set_new_value(ui->pump_right_right, v);break;
	case VALVE_ENG1 : newval = set_new_value(ui->val_eng1, v); break;
	case VALVE_APU : newval = set_new_value(ui->val_apu, v);break;
	case VALVE_XFEED : newval = set_new_value(ui->val_xfeed, v); break;
	case VALVE_ENG2 : newval = set_new_value(ui->val_eng2, v);break;
	case FF_ENG1 : newval = set_new_value(ui->disp_ff_eng1, v);break;
	case FF_ENG2 : newval = set_new_value(ui->disp_ff_eng2, v);break;
	}
	if (newval)
		update();
}


FuelPage::~FuelPage()
{
	//delete ui;
}
