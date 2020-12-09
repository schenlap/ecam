#ifndef MEMO_H
#define MEMO_H

#include <QObject>

class Memo : public QObject
{
	Q_OBJECT
public:
	enum MemoPrio {
		LEVEL3, // Highest
		LEVEL2,
		LEVEL1,
		ADVISORY,
		MEMO
	};
	Memo(QString *text, QString *textval, MemoPrio prio, bool active = true, QObject *parent = 0);
	QString name();
	QString val();
	void set_active(bool act);
	bool is_active() {return _active; }

signals:

public slots:

private:
	QString *_text;
	QString *_textval;
	MemoPrio _prio;
	bool _active;
};

#endif // MEMO_H
