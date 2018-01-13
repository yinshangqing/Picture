#ifndef PICTURE_H
#define PICTURE_H

#include <QtWidgets/QWidget>
#include "ui_picture.h"
#include <QPainter>
#include <QPaintEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QScreen>
#include "photooperate.h"

class Picture : public QWidget
{
	Q_OBJECT

public:
	Picture(QWidget *parent = 0);
	~Picture();

signals:
	public slots:
		void OnSlotChoosePhoto();
		void OnSlotSavePhoto();

protected:
	void paintEvent(QPaintEvent *);

private:
	Ui::PictureClass ui;
	QImage  m_qimage;
	QString m_qstrPhotoPath;
	PhotoOperate *m_photoOper;
	QString m_qstrPhotoName;
	QString m_qstrPhotoType;
};

#endif // PICTURE_H
