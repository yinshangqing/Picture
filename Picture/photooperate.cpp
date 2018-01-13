#include "photooperate.h"

PhotoOperate::PhotoOperate(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

PhotoOperate::~PhotoOperate()
{

}

void PhotoOperate::SetPhotoPath(QString qstrPhotoPath)
{
	m_qstrPhotoPath = qstrPhotoPath;
	update();
}

void PhotoOperate::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	//ui.photolabname->setText(m_qstrTextName);
	QPixmap pix;
	pix.load(m_qstrPhotoPath);
	painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

