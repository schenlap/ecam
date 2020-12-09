#ifndef EPR_TEXT_H
#define EPR_TEXT_H

#include <QWidget>

class EprText : public QWidget
{
	Q_OBJECT

public:
	EprText(QWidget *parent, QString str1, QString str2, bool pointer = false);


public slots:


private:
	QString _str1;
	QString _str2;
	bool _pointer;
	float _font_scale;

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	QSize sizeHint() const;
};

#endif
