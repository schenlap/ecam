
#include <QTextCodec>
#include <QUdpSocket>

#include "ecam.h"
#include "pages/ewd_page.h"
#include "pages/fuel_page.h"

#include "model/tmp_time.h"
#include "fgfs.h"

FgFs::FgFs(QObject *parent, EwdPage *e, FuelPage *f, TmpTime *t) :
	QThread(parent),
	_e(e),
	_f(f),
	_t(t),
	_online(false)
{
	int port = 6789;
	qDebug("Connect to Port %d", port);

	_udp_socket_get  = new QUdpSocket(this);

	QHostAddress host  = QHostAddress("127.0.0.1");
	if (!_udp_socket_get->bind(host, port)) {
		qDebug ("Could not connect to port %d", port);
		return;
	}

	connect(_udp_socket_get,SIGNAL(readyRead()),this,SLOT(readData()));
}

void FgFs::run()
{
}


bool FgFs::parse_ewd_data(QStringList *sl) {
	if (sl->size() != (2 * 5 + 1 + 1)) {
		qDebug("ENGx: Got incorrect data size %d", sl->size());

		return false;
	}
	_e->set_value(EwdPage::N1RPM1, sl->at(0).toInt());
	_e->set_value(EwdPage::N2RPM1, sl->at(1).toInt());
	_e->set_value(EwdPage::EGT1, sl->at(2).toInt());
	_e->set_value(EwdPage::EPR1, sl->at(3).toFloat());
	//_e->set_value(EwdPage::E1STARTED, !!(sl->at(4).toInt()));
	_e->set_value(EwdPage::E1STARTED, true);

	_e->set_value(EwdPage::N1RPM2, sl->at(5).toInt());
	_e->set_value(EwdPage::N2RPM2, sl->at(6).toInt());
	_e->set_value(EwdPage::EGT2, sl->at(7).toInt());
	_e->set_value(EwdPage::EPR2, sl->at(8).toFloat());
	//_e->set_value(EwdPage::E2STARTED, !!(sl->at(9).toInt()));
	_e->set_value(EwdPage::E2STARTED, true);

	_e->set_value(EwdPage::FLAPS, sl->at(10).toInt());

	return true;
}


bool FgFs::parse_fuel_data(QStringList *sl) {
	if (sl->size() != (7+1)) {
		qDebug("Fuel: Got incorrect data size %d", sl->size());

		return false;
	}
	_f->set_value(FuelPage::FOB, sl->at(0).toInt());
	_f->set_value(FuelPage::LL_FUEL_QUANT, sl->at(1).toInt());
	_f->set_value(FuelPage::LC_FUEL_QUANT, sl->at(2).toInt());
	_f->set_value(FuelPage::CC_FUEL_QUANT, sl->at(3).toInt());
	_f->set_value(FuelPage::RC_FUEL_QUANT, sl->at(4).toInt());
	_f->set_value(FuelPage::RR_FUEL_QUANT, sl->at(5).toInt());
	_f->set_value(FuelPage::LL_FUEL_TEMP, sl->at(6).toInt());
	_f->set_value(FuelPage::LC_FUEL_TEMP, sl->at(6).toInt());
	_f->set_value(FuelPage::RC_FUEL_TEMP, sl->at(6).toInt());
	_f->set_value(FuelPage::RR_FUEL_TEMP, sl->at(6).toInt());

	return true;
}


bool FgFs::parse_sd_data(QStringList *sl) {
	if (sl->size() != 3) {
		qDebug("SD: Got incorrect data size %d", sl->size());

		return false;
	}
	_t->set_value(TmpTime::TAT, sl->at(0).toInt());
	_t->set_value(TmpTime::SAT, sl->at(0).toInt());


	return true;
}


bool FgFs::parse(const QString *d) {
	enum Ecam::Pages message_type;
	QString s = *d;

	qDebug() << "Datagram: " << s;

	if (s.startsWith("ENGx"))
		message_type = Ecam::EWD;
	else if (s.startsWith("FUEL"))
		message_type = Ecam::FUEL;
	else if (s.startsWith("STAT"))
		message_type = Ecam::SD;
	else
		return false;

	s.remove(0,4);
	QStringList vals = s.split('\t');

	switch(message_type) {
	case Ecam::EWD:
		return parse_ewd_data(&vals);
	case Ecam::FUEL:
		return parse_fuel_data(&vals);
	case Ecam::SD:
		return parse_sd_data(&vals);
	default:
		return false;
	}

	return false;
}

void FgFs::readData() {
		while (_udp_socket_get->hasPendingDatagrams()) {
			QByteArray datagram;
			datagram.resize(_udp_socket_get->pendingDatagramSize());
			QHostAddress sender;
			quint16 senderPort;

			_udp_socket_get->readDatagram(datagram.data(), datagram.size(),
				&sender, &senderPort);

			QString s = QString::fromAscii(datagram.data());
			//qDebug() <<"Rx: " << s;
			QStringList sl = s.split(':');
			for (int i = 0; i < sl.size(); i++) {
				if (sl.at(i).size() < 4)
					continue;
				if (!parse(&sl.at(i))) {
					qDebug() << "Uncorrect formatted String: " << sl.at(i).constData()->toAscii();
					qDebug("------------");
				} else {
					_online = true;
				}
			}
		}
	}
