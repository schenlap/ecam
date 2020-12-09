#include <QTimer>
#include <QPushButton>
#include <QSignalMapper>
#include <QLayout>

#include "widgets/faultoffbutton.h"

#include "sys_stat_panel.h"

SysStatPanel::SysStatPanel(QWidget *parent) :
	QWidget(parent)
{
	QGridLayout *layout = new QGridLayout;

	QPalette palette1 = QPalette();
	palette1.setColor(QPalette::ButtonText,Qt::white);

	QSignalMapper *signalMapper = new QSignalMapper(this);
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(handleButtons(int)));

	QPushButton *ewd_but = new QPushButton("ENG");
	ewd_but->setPalette(palette1);
	signalMapper->setMapping(ewd_but, 0);
	connect(ewd_but, SIGNAL(released()), signalMapper, SLOT(map()));

	QPushButton *fuel_but = new QPushButton("FUEL");
	fuel_but->setPalette(palette1);
	signalMapper->setMapping(fuel_but, 1);
	connect(fuel_but, SIGNAL(released()), signalMapper, SLOT(map()));

	QPushButton *bleed_but = new QPushButton("BLEED");
	bleed_but->setPalette(palette1);
	signalMapper->setMapping(bleed_but, 2);
	connect(bleed_but, SIGNAL(released()), signalMapper, SLOT(map()));

	QPushButton *cond_but = new QPushButton("COND");
	cond_but->setPalette(palette1);
	signalMapper->setMapping(cond_but, 3);
	connect(cond_but, SIGNAL(released()), signalMapper, SLOT(map()));

	QPushButton *to_but = new QPushButton("T.O\nConfig");
	to_but->setPalette(palette1);
	signalMapper->setMapping(to_but, 10);
	connect(to_but, SIGNAL(released()), this, SLOT(to_config()));

	FaultOffButton *ha = new FaultOffButton(this);
	ha->show();

	layout->addWidget(ewd_but, 0, 0);
	layout->addWidget(fuel_but, 0, 1);
	layout->addWidget(bleed_but, 0, 2);
	layout->addWidget(cond_but, 0, 3);
	layout->addWidget(ha, 1, 0);
	layout->addWidget(to_but, 1, 1);

	QWidget *wid = new QWidget(this);
	wid->setLayout(layout);
}


void SysStatPanel::handleButtons(int p) {
	qDebug("Switch to page %d", p);
	emit switchpage(p);
}


void SysStatPanel::to_config() {
	qDebug("T.O. Config pressed");
}


QSize SysStatPanel::sizeHint() const
{
	return QSize(480, 640 - 480);
}


SysStatPanel::~SysStatPanel()
{
}
