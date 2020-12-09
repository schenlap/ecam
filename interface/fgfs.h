#ifndef FGFS_H
#define FGFS_H

#include <QThread>

class QUdpSocket;
class EwdPage;
class FuelPage;
class TmpTime;

class FgFs : public QThread
{
	Q_OBJECT
public:
	explicit FgFs(QObject *parent, EwdPage *e, FuelPage *f, TmpTime *t);
	bool is_online() {return _online; }

signals:

public slots:

protected:
	void run();

private:
	EwdPage *_e;
	FuelPage *_f;
	TmpTime *_t;
	QUdpSocket * _udp_socket_get;
	bool _online;
	bool parse(const QString *d);
	bool parse_ewd_data(QStringList *sl);
	bool parse_fuel_data(QStringList *sl);
	bool parse_sd_data(QStringList *sl);

private slots:
	void readData(void);
	//void connected(void);
	//void disconnected(void);
};

#endif // FGFS_H
