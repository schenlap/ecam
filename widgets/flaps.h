#ifndef FLAPS_H
#define FLAPS_H

#include <QWidget>

class Flaps : public QWidget
{
	Q_OBJECT

public:
	Flaps(QWidget *parent = 0);
	void set_value(int);
	int value() {return _desired; }


public slots:


private:
	bool is_moving();
	virtual bool started() {return _started; }
	void print_aleron(QPainter *p);
	void print_flaps(QPainter *p);
	void print_flap(QPainter *p, const QPoint *start, const QPoint *end, const QPoint *middle);
	void print_slat(QPainter *p, const QPoint *start, const QPoint *end, const QPoint *middle);

	int _desired;
	int _actual;
	bool _started;
	float _font_scale;
	QTimer *_timer;


private slots:
	void transit_done();


protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	QSize sizeHint() const;
};

#endif
