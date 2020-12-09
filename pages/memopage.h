#ifndef MEMOPAGE_H
#define MEMOPAGE_H

#include <QWidget>
#include <QVector>

#include "ui_ewd_page.h"
#include "structures/memo.h"

class Memo;

class MemoPage : public QWidget
{
	Q_OBJECT
public:
	enum MemoList {
		TO_AUTOBRK = 0,
		TO_SIGNS,
		TO_CABIN,
		TO_SPLRS,
		TO_FLAPS,
		TO_CONFIG,
		LDG_LDG_GEAR,
		LDG_SIGNS,
		LDG_CABIN,
		LDG_SPLRS,
		LDG_FLAPS
	};
	enum MemoPredefConfig {
		PREDEF_TO_CONFIG = 0,
		PREDEF_LDG_CONFIG
	};

	explicit MemoPage(Ui::EwdPage *ui, QWidget *parent = 0);
	void add_memo(MemoList pos, Memo *m);
	void set_active(MemoList pos, bool a);
	void dispPage(MemoList pos, MemoList end);
	void dispPage(MemoPredefConfig p);

signals:

public slots:

private:
	void set_label_color(QLabel *l);
	Ui::EwdPage *_ui;
	QVector<Memo *> _memo_vec;
	QVector<QLabel *> _disp;
	QVector<QPoint *> _predef_page;

protected:
	void paintEvent(QPaintEvent *event);
};

#endif // MEMOPAGE_H
