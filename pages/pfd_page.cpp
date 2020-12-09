// 9.12.2020
// http://www.a320dp.com/A320_DP/flight-instruments/sys-8.3.0.html

#include <QPainter>
#include <QtSvg/QSvgRenderer>
#include <QLabel>

#include "pfd_page.h"
#include "ui_pfd_page.h"

static int linewidth = 2;

PfdPage::PfdPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PfdPage)
{
	ui->setupUi(this);

	QString fn = QString("../ui/pfd_with_background.svg");
	//QString fn = QString("../ui/pfd.svg");
	_svgr = new QSvgRenderer(fn);// (&fn, parent);
	_pm = new QPixmap(480, 600);
	_pm->fill(Qt::green);
	//QPainter painter(&pm);


}


void PfdPage::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint((QPainter::Antialiasing));

	if(_svgr->elementExists("text1517")) {
		qDebug("Element found");
	}
	_svgr->render(&painter, _pm->rect());
	//painter.setPen(QPen(Qt::green, linewidth));


}


void PfdPage::set_value(ValueType t, int v) {
	bool newval = false;

	if (newval)
		update();
}


PfdPage::~PfdPage()
{
	//delete ui;
}
