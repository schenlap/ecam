#ifndef FAULT_OFF_BUTTON_H
#define FAULT_OFF_BUTTON_H

#include <QAbstractButton>

class QLabel;

namespace Ui {
class FaultOffButton;
}

class FaultOffButton : public QAbstractButton
{
	Q_OBJECT

public:
	explicit FaultOffButton(QWidget *parent = 0);
	~FaultOffButton();
	void set_fault(bool f);
	void set_off(bool f);

private:
	void set_label_color(QLabel *l, QColor c);
	Ui::FaultOffButton *ui;
	bool _fault;
	bool _off;

protected:
	void paintEvent(QPaintEvent *event);
	QSize sizeHint() const;
};

#endif // FAULT_OFF_BUTTON_H
