#include "picture.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Picture w;
	w.show();
	return a.exec();
}
