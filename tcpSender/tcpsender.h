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

	//��������˽�����Ա��
	QTcpServer tcpServer;
	QTcpSocket *tcpServerConnection;
	qint64 totalBytesR;  //����ܴ�С��Ϣ
	qint64 bytesReceived;  //���յ����ݵĴ�С
	qint64 fileNameSize;  //�ļ����Ĵ�С��Ϣ
	QString fileNameR;   //����ļ���
	QFile *localFileR;   //�����ļ�
	QByteArray inBlock;   //���ݻ�����
	QByteArray md5R;  //���յ����ļ���md5ֵ

	//�ͻ���˽�����Ա��
	QTcpSocket *tcpClient;
	QFile *localFile;  //Ҫ���͵��ļ�
	qint64 totalBytes;  //�����ܴ�С
	qint64 bytesWritten;  //�Ѿ��������ݴ�С
	qint64 bytesToWrite;   //ʣ�����ݴ�С
	qint64 loadSize;   //ÿ�η������ݵĴ�С
	QString fileName;  //�����ļ�·��
	QByteArray outBlock;  //���ݻ������������ÿ��Ҫ���͵�����
	QByteArray md5;    //�����ļ�ǰ���ļ�����md5У���ֵ
private slots:

	//�ͻ��˲ۺ���
	void send();  //���ӷ�����
	void startTransfer();  //�����ļ���С����Ϣ
	void updateClientProgress(qint64); //�������ݣ����½�����
	void displayError(QAbstractSocket::SocketError); //��ʾ����
	void openFile();  //���ļ�
	void getIP();//��ȡ����IP

	//�������˲ۺ���
	void start();   //��ʼ����
	void acceptConnection();  //��������
	void updateServerProgress();  //���½���������������
	void displayErrorR(QAbstractSocket::SocketError socketError);//��ʾ����
};

#endif // TCPSENDER_H
