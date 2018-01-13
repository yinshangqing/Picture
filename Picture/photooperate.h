#ifndef PHOTOOPERATE_H
#define PHOTOOPERATE_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QMouseEvent>
#include "ui_photooperate.h"

class PhotoOperate : public QWidget
{
	Q_OBJECT

public:
	PhotoOperate(QWidget *parent = 0);
	~PhotoOperate();

	void SetPhotoPath(QString qstrPhotoPath);
	//void SetPhotoName(QString qstrTextName);

signals:
	void SignalShow();

	public slots:
protected:
	void paintEvent(QPaintEvent *);
	//void mouseDoubleClickEvent(QMouseEvent *);

private:
	Ui::PhotoOperate ui;
	bool    m_bShow;
	QString m_qstrPhotoPath;
	//QString m_qstrTextName;
	QImage  m_newImage;
};

#endif // PHOTOOPERATE_H
