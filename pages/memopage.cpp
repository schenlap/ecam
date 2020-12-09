#include <QVector>

#include "structures/memo.h"
#include "ui_ewd_page.h"
#include "memopage.h"

MemoPage::MemoPage(Ui::EwdPage *ui, QWidget *parent) :
	QWidget(parent),
	_ui(ui)
{
	_disp.append(_ui->disp_memo_1);
	_disp.append(_ui->disp_memo_2);
	_disp.append(_ui->disp_memo_3);
	_disp.append(_ui->disp_memo_4);
	_disp.append(_ui->disp_memo_5);
	_disp.append(_ui->disp_memo_6);

	add_memo(TO_AUTOBRK, new Memo(new QString("T.O. AUTO BRK.................."), new QString("MAX"), Memo::MEMO));
	add_memo(TO_SIGNS, new Memo(new QString("     SIGNS......................"), new QString("ON"), Memo::MEMO));
	add_memo(TO_CABIN, new Memo(new QString("     CABIN..................."), new QString("CHECK"), Memo::MEMO));
	add_memo(TO_SPLRS, new Memo(new QString("     SPLRS....................."), new QString("ARM"), Memo::MEMO));
	add_memo(TO_FLAPS, new Memo(new QString("     FLAPS....................."), new QString("T.O"), Memo::MEMO, false));
	add_memo(TO_CONFIG, new Memo(new QString("     T.O CONFIG..............."), new QString("TEST"), Memo::MEMO));
	add_memo(LDG_LDG_GEAR, new Memo(new QString("LDG. LDG GEAR..................."), new QString("DN"), Memo::MEMO));
	add_memo(LDG_SIGNS,    new Memo(new QString("     SIGN......................."), new QString("ON"), Memo::MEMO));
	add_memo(LDG_CABIN,    new Memo(new QString("     CABIN..................."), new QString("CHECK"), Memo::MEMO));
	add_memo(LDG_SPLRS,    new Memo(new QString("     SPLRS....................."), new QString("ARM"), Memo::MEMO, false));
	add_memo(LDG_FLAPS,    new Memo(new QString("     FLAPS...................."), new QString("FULL"), Memo::MEMO));

	_predef_page.insert(PREDEF_TO_CONFIG, new QPoint(TO_AUTOBRK, TO_CONFIG));
	_predef_page.insert(PREDEF_LDG_CONFIG, new QPoint(LDG_LDG_GEAR, LDG_FLAPS));

	dispPage(PREDEF_LDG_CONFIG);
	//dispPage(PREDEF_TO_CONFIG);
}


void MemoPage::set_label_color(QLabel *l) {
	QPalette palette = l->palette();
	//palette.setColor(l->foregroundRole(), QColor( 0xFF, 0xA0, 0x00));
	palette.setColor(l->foregroundRole(), Qt::green);
	l->setPalette(palette);
}


void MemoPage::add_memo(MemoList pos, Memo *m) {
	_memo_vec.insert(pos, m);
}


void MemoPage::set_active(MemoList pos, bool a) {
	_memo_vec.at(pos)->set_active(a);
}


void MemoPage::dispPage(MemoPredefConfig p) {
	if (p > _predef_page.size())
		return;

	dispPage((enum MemoList)_predef_page.at(p)->x(), (enum MemoList)_predef_page.at(p)->y());
}


void MemoPage::dispPage(MemoList pos, MemoList end) {

	if (end > _memo_vec.size())
		return;

	int cnt = end - pos + 1;
	if (cnt > _disp.size())
		cnt = _disp.size();

	for (int i= 0; i < cnt; i++) {
		set_label_color(_disp.at(i));
		if (_memo_vec.at(i+pos)->is_active())
			_disp.at(i)->setText(_memo_vec.at(i+pos)->name() + _memo_vec.at(i+pos)->val());
		else {
			QString s = ("&nbsp;&nbsp;&nbsp;&nbsp;" + _memo_vec.at(i+pos)->name() + "<font color=\"cyan\">" + _memo_vec.at(i+pos)->val() + "</font>");
			_disp.at(i)->setText(s);
		}
	}
}

void MemoPage::paintEvent(QPaintEvent *) {
	qDebug("Paintevent MemoPage");
}
