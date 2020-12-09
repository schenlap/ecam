#ifndef N2RPM_H
#define N2RPM_H

#include "arcwidget.h"

#include <QWidget>

class N2Rpm : public Arcwidget
{
	Q_OBJECT

public:
	N2Rpm(QWidget *parent = 0);


public slots:


private:
	void paint_needle(QPainter *p, int length, int rot);
	void print_arc(QPainter *p);
	void print_arc_ns(QPainter *p);
	void print_not_started(QPainter *p, QFont *f);
	void print_tics_and_label(QPainter *p);
	void print_value(QPainter *p);

	float font_scale;


protected:
	void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *event);
	QSize sizeHint() const;
};

#endif
