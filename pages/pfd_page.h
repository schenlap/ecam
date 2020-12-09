#ifndef PFD_PAGE_H
#define PFD_PAGE_H

#include <QtSvg/QSvgRenderer>
#include <QWidget>

class QLabel;
class Pump;
class Valve;

namespace Ui {
class PfdPage;
}

class PfdPage : public QWidget
{
	Q_OBJECT

public:
	enum ValueType {
		IP_TEMP1,
		IP_PRESS1,
		TEMPIN1,
	};

	explicit PfdPage(QWidget *parent = 0);
	void set_value(ValueType t, int v);
	~PfdPage();

private:
	Ui::PfdPage *ui;
	QSvgRenderer *_svgr;
	QPixmap *_pm;


protected:
	void paintEvent(QPaintEvent *event);
};

#endif // PFD_PAGE_H
