// 9.12.2020
// http://www.a320dp.com/A320_DP/flight-instruments/sys-8.3.0.html

#include <QPainter>
#include <QtSvg/QSvgRenderer>
#include <QLabel>
#include <QGraphicsSvgItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "pfd_page.h"
#include "ui_pfd_page.h"

static int linewidth = 2;

PfdPage::PfdPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PfdPage)
{
	ui->setupUi(this);

	_scene = new QGraphicsScene();
	_view = new QGraphicsView();

	_scene->setSceneRect(this->_view->rect());
	_view->setScene(this->_scene);

	//_svgr = new QSvgRenderer(QString("../ui/pfd_with_background.svg"));
	_svgr = new QSvgRenderer(QString("../ui/pfd.svg"));
	_svgh = new QSvgRenderer(QString("../ui/pfd_horizont.svg"));
	_pmh = new QPixmap(300, 600);
	_pm = new QPixmap(480, 480);
	_pm->fill(Qt::green);

}


void PfdPage::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint((QPainter::Antialiasing));

	_svgh->render(&painter, QRectF(80,-50-3,300,600)); // level
	_svgr->render(&painter, _pm->rect());
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
