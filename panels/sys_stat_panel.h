#ifndef SYSSTATPANEL_H_
#define SYSSTATPANEL_H_

#include <QWidget>


class SysStatPanel : public QWidget
{
	Q_OBJECT

public:
	SysStatPanel(QWidget *parent = 0);
	~SysStatPanel();

signals:
	void switchpage(int);

private:

private slots:
		virtual QSize sizeHint() const;
		void handleButtons(int p);
		void to_config();
};

#endif // SYSSTATPANEL_H_
