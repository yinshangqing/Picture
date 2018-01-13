#include "picture.h"

Picture::Picture(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.widget->setStyleSheet("QWidget{\
							   border-width: 1px;\
							   border-color: rgb(135, 135, 135);\
							   border-style: solid;\
							   border-radius: 5px;\
							   background-color: rgba(0,0,0,0);\
							   color: rgb(200, 200, 200);}\
							   QWidget:hover,QWidget:press,QWidget:checked{\
							   border-color: rgb(214, 152, 45);}");
	//ui.widget_2->setStyleSheet("QWidget{\
	//						 border-width: 1px;\
	//						 border-color: rgb(135, 135, 135);\
	//						 border-style: solid;\
	//						 border-radius: 5px;\
	//						 background-color: rgba(0,0,0,0);\
	//						 color: rgb(200, 200, 200);}\
	//						 QWidget:hover,QWidget:press,QWidget:checked{\
	//						 border-color: rgb(214, 152, 45);}");
	QString qstr_border_normal = "QPushButton{\
								 background-color: rgb(61,61,61);\
								 border-style: solid;\
								 border-width: 2px;\
								 border-radius: 10px;\
								 border-color: rgb(30, 30, 30);\
								 min-width: 5em;\
								 padding: 4px;\
								 color: rgb(200,200,200);}\
								 QPushButton:hover,QPushButton:press,QPushButton:checked{\
								 background-color: rgb(0,0,0);\
								 color: rgb(214, 152, 45);\
								 border-color: rgb(214, 152, 45);}";
	ui.SaveBtn->setStyleSheet(qstr_border_normal);
	ui.ChooseBtn->setStyleSheet(qstr_border_normal);
	ui.labWidget->setFixedHeight(50);
	ui.widget_3->setFixedHeight(150);
	ui.widget_4->setFixedHeight(430);
	connect(ui.ChooseBtn,SIGNAL(clicked()),this,SLOT(OnSlotChoosePhoto()));
	connect(ui.SaveBtn,SIGNAL(clicked()),this,SLOT(OnSlotSavePhoto()));

	//QFont ft;
	//ft.setPointSize(22);
	//ui.label_4->setFont(ft);
	//ui.label->setFont(ft);
	////设置颜色
	//QPalette pa;
	//pa.setColor(QPalette::WindowText,Qt::black);
	//ui.label_4->setPalette(pa);
	//ui.label->setPalette(pa);
	
}

Picture::~Picture()
{

}

void Picture::OnSlotChoosePhoto()
{
	QString qstrPhotoPath = QFileDialog::getOpenFileName(NULL,tr("choose photo"),".",tr("Images (*.png *.bmp *.jpg *.jpeg)"));
	if(qstrPhotoPath.isEmpty())  
		return;  
	//m_photoOper->SetPhotoPath(m_qstrPhotoPath);
	//if(!(m_qimage.load(m_qstrPhotoPath))) //加载图像  
	//{  
	//	QMessageBox::information(this, tr("is fail"),tr("photo is fails!"));  
	//	return;  
	//}  
	m_qstrPhotoPath = qstrPhotoPath;
	m_qimage = QPixmap(m_qstrPhotoPath).toImage();//绝对路径
	QPixmap pixmap(m_qstrPhotoPath);
	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(pixmap.scaled(ui.showPhoto->size(), Qt::IgnoreAspectRatio,
		Qt::SmoothTransformation)));
	ui.showPhoto->setPalette(palette);
	ui.showPhoto->setAutoFillBackground(true);
	int index = qstrPhotoPath.lastIndexOf("/");
	qstrPhotoPath = qstrPhotoPath.remove(0,index).remove(0,1);
	
	m_qstrPhotoName = qstrPhotoPath;
	if (m_qstrPhotoName.endsWith(".jpeg"))
	{
		m_qstrPhotoName.remove(".jpeg");
		m_qstrPhotoType = "jpeg";
	}
	else if (m_qstrPhotoName.endsWith(".jpg"))
	{
		m_qstrPhotoName.remove(".jpg");
		m_qstrPhotoType = "jpg";
	}
	else if (m_qstrPhotoName.endsWith(".png"))
	{
		m_qstrPhotoName.remove(".png");
		m_qstrPhotoType = "png";
	}
	else if (m_qstrPhotoName.endsWith(".bmp"))
	{
		m_qstrPhotoName.remove(".bmp");
		m_qstrPhotoType = "bmp";
	}
	else
	{
		return;
	}

	
	ui.label_4->setText(m_qstrPhotoName);
	ui.label->setText(m_qstrPhotoName);
	
}

void Picture::OnSlotSavePhoto()
{
	QString qstrPhotoPath = QString("Photo_2") + m_qstrPhotoPath;
	//QString filename1 = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg *.jpeg)")); //选择路径  
	QScreen *screen = QGuiApplication::primaryScreen();  
	screen->grabWindow(ui.widget_2->winId()).save(qstrPhotoPath,m_qstrPhotoType.toLatin1().data(),100); 
	int nWidget = m_qimage.width();
	int nHeight = (m_qimage.height()) * 11 / 10;
	QImage *subImg = new QImage(nWidget,nHeight,QImage::Format_ARGB32); 
	subImg->fill(QColor(255, 255, 255, 255));
	QPainter painter(subImg); //为这个QImage构造一个QPainter
	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);//注意这一行代码
	QPen pen = painter.pen();
	pen.setColor(Qt::black);
	QFont font = painter.font();
	font.setBold(true);//加粗
	font.setPixelSize(m_qimage.height() / 12);//改变字体大小
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(subImg->rect(),Qt::AlignHCenter|Qt::AlignBottom,m_qstrPhotoName);

	//painter.drawImage(318,12,m_qimage,318,12,ui.photoWidget->width(),ui.photoWidget->height()); 
	painter.drawImage(318,12,m_qimage,0,0);
	m_qstrPhotoPath = QString("Photo") + m_qstrPhotoPath;
	if(subImg->save(m_qstrPhotoPath,m_qstrPhotoType.toLatin1().data(),100))
	{
		QMessageBox::information(NULL,"tip",tr("save is success!"));
		return;
	}
	QMessageBox::information(NULL,"tip",tr("save is fails!"));
}

void Picture::paintEvent(QPaintEvent *)
{
	QPainter p(this);	
	p.fillRect(rect(),QBrush(QColor(65,66,69))); 

	QPixmap pix;
	pix.load(m_qstrPhotoPath);
	p.drawPixmap(318,12,ui.photoWidget->width(),ui.photoWidget->height(),pix);
	

}
