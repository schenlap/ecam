#include <QtGui>
#include "ecam.h"
#include "widgets/epr.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setApplicationName("ecam");
	Ecam w;
	w.setFixedSize(480, 640);
	w.show();
	return app.exec();
}
