#include <QLabel>
#include <QPainter>

#include "widgets/flaps.h"
#include "memopage.h"
#include "structures/memo.h"
#include "ewd_page.h"
#include "ui_ewd_page.h"

EwdPage::EwdPage(QWidget *parent) :
	QWidget(parent),
	_n2rmp1_started(false),
	_n2rmp2_started(false),
	ui(new Ui::EwdPage)
{
	ui->setupUi(this);
	_mp = new MemoPage(ui);
	/*
	_mp->add_memo(new Memo(new QString("T.O. AUTO BRK.................."), new QString("MAX"), Memo::MEMO));
	_mp->add_memo(new Memo(new QString("     SIGNS......................"), new QString("ON"), Memo::MEMO));
	_mp->add_memo(new Memo(new QString("     CABIN..................."), new QString("CHECK"), Memo::MEMO));
	_mp->add_memo(new Memo(new QString("     SPLRS....................."), new QString("ARM"), Memo::MEMO, true));
	_mp->add_memo(new Memo(new QString("     FLAPS....................."), new QString("T.O"), Memo::MEMO, false));
	_mp->add_memo(new Memo(new QString("     T.O CONFIG..............."), new QString("TEST"), Memo::MEMO));*/
}


void EwdPage::paintEvent(QPaintEvent *) {
	//_mp->disp();

	QPainter painter(this);
	painter.setRenderHint((QPainter::Antialiasing));

	painter.setPen(QPen(Qt::white, 2));


	if (_n2rmp1_started == false) {
		set_label_color(ui->disp_n2rpm1, true);
		ui->disp_n2rpm1->setText("XX");
		//ui->disp_n2rpm1->setFont();
	} else {
		set_label_color(ui->disp_n2rpm1, false);
		set_new_value(ui->disp_n2rpm1, _n2rpm1);
		//ui->disp_n2rpm1->setFont();
	}
	painter.drawLine(127,329, 89, 336);


	if (_n2rmp2_started == false) {
		set_label_color(ui->disp_n2rpm2, true);
		ui->disp_n2rpm2->setText("XX");
		//ui->disp_n2rpm2->setFont();
	} else {
		set_label_color(ui->disp_n2rpm2, false);
		set_new_value(ui->disp_n2rpm2, _n2rpm2);
		//ui->disp_n2rpm2->setFont();
	}
	painter.drawLine(159,330,201,338);
}


bool EwdPage::set_new_value(QLabel *w, int v) {
	QString s = QString::number(v);
	if (QString::compare(w->text(), s)) {
		w->setText(s);
		return true;
	}
	return false;
}


bool EwdPage::set_new_value(Flaps *w, int v) {
	if (w->value() !=  v) {
		w->set_value(v);
		return true;
	}
	return false;
}


bool EwdPage::set_new_value(Arcwidget *w, float v) {
	if (w->value() !=  v) {
		w->set_value(v);
		return true;
	}
	return false;
}


bool EwdPage::set_new_value(int *w, int n) {
	if (*w !=  n) {
		*w = n;
		return true;
	}
	return false;
}


bool EwdPage::set_new_started(Arcwidget *w, bool v) {
	if (w->started() !=  v) {
		w->set_engine_started(v);
		return true;
	}
	return false;
}


bool EwdPage::set_new_started(bool *w, bool v) {
	if (*w !=  v) {
		*w = v;
		return true;
	}
	return false;
}


void EwdPage::set_value(ValueType t, float v) {
	bool newval = false;

	switch(t) {
	case EPR1: newval = set_new_value(ui->epr1, v); break;
	case EPR2: newval = set_new_value(ui->epr2, v); break;
	case EGT1: newval = set_new_value(ui->egt1, v); break;
	case EGT2: newval = set_new_value(ui->egt2, v); break;
	case N1RPM1: newval = set_new_value(ui->n1rpm1, v); break;
	case N1RPM2: newval = set_new_value(ui->n1rpm2, v); break;
	case N2RPM1: newval = set_new_value(&_n2rpm1, v); break;
	case N2RPM2: newval = set_new_value(&_n2rpm2, v); break;
	case FLAPS: newval = set_new_value(ui->flaps, v); break;
	case E1STARTED: newval = set_new_started(ui->epr1, !!v);
					newval |= set_new_started(ui->egt1, !!v);
					newval |= set_new_started(ui->n1rpm1, !!v);
					newval |= set_new_started(&_n2rmp1_started, !!v); break;
	case E2STARTED: newval = set_new_started(ui->epr2, !!v);
					newval |= set_new_started(ui->egt2, !!v);
					newval |= set_new_started(ui->n1rpm2, !!v);
					newval |= set_new_started(&_n2rmp2_started, !!v); break;
	}

	if (newval)
		update();
}


void EwdPage::set_label_color(QLabel *l, bool alert) {
	QPalette palette = l->palette();
	if (alert)
		palette.setColor(l->foregroundRole(), QColor( 0xFF, 0xA0, 0x00));
	else
		palette.setColor(l->foregroundRole(), Qt::green);
	l->setPalette(palette);
}


QSize EwdPage::sizeHint() const
{
	return QSize(480, 480);
}


EwdPage::~EwdPage()
{
	delete ui;
}
