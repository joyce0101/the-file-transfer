#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QtWidgets/QWidget>
#include "ui_tcpsender.h"
#include <QtNetwork>
class tcpSender : public QWidget
{
	Q_OBJECT

public:
	tcpSender(QWidget *parent = 0);
	~tcpSender();

private:
	Ui::tcpSenderClass ui;

	//服务器端私有类成员：
	QTcpServer tcpServer;
	QTcpSocket *tcpServerConnection;
	qint64 totalBytesR;  //存放总大小信息
	qint64 bytesReceived;  //已收到数据的大小
	qint64 fileNameSize;  //文件名的大小信息
	QString fileNameR;   //存放文件名
	QFile *localFileR;   //本地文件
	QByteArray inBlock;   //数据缓冲区
	QByteArray md5R;  //接收到的文件的md5值

	//客户端私有类成员：
	QTcpSocket *tcpClient;
	QFile *localFile;  //要发送的文件
	qint64 totalBytes;  //数据总大小
	qint64 bytesWritten;  //已经发送数据大小
	qint64 bytesToWrite;   //剩余数据大小
	qint64 loadSize;   //每次发送数据的大小
	QString fileName;  //保存文件路径
	QByteArray outBlock;  //数据缓冲区，即存放每次要发送的数据
	QByteArray md5;    //发送文件前对文件进行md5校验的值
private slots:

	//客户端槽函数
	void send();  //连接服务器
	void startTransfer();  //发送文件大小等信息
	void updateClientProgress(qint64); //发送数据，更新进度条
	void displayError(QAbstractSocket::SocketError); //显示错误
	void openFile();  //打开文件
	void getIP();//获取本机IP

	//服务器端槽函数
	void start();   //开始监听
	void acceptConnection();  //建立连接
	void updateServerProgress();  //更新进度条，接收数据
	void displayErrorR(QAbstractSocket::SocketError socketError);//显示错误
};

#endif // TCPSENDER_H
