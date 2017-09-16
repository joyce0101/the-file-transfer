#include "tcpsender.h"
#include <QFileDialog>
#include <QList>
#include <QtNetwork/QHostAddress>
#include <QCryptographicHash>//���ļ�����md5У��
tcpSender::tcpSender(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	tcpSender::setWindowTitle("FileTransfer_Lan");
	
	//�ͻ��˹��캯����
	loadSize = 4 * 1024;
	totalBytes = 0;
	bytesWritten = 0;
	bytesToWrite = 0;
	tcpClient = new QTcpSocket(this);
	//�����ӷ������ɹ�ʱ������connected()�źţ����ǿ�ʼ�����ļ�
	connect(tcpClient, SIGNAL(connected()), this, SLOT(startTransfer()));
	//�������ݷ��ͳɹ�ʱ�����Ǹ��½�����
	connect(tcpClient, SIGNAL(bytesWritten(qint64)), this,
		SLOT(updateClientProgress(qint64)));
	connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this,
		SLOT(displayError(QAbstractSocket::SocketError)));
	connect(ui.openButton, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(send()));
	//��ʼʹ�����͡���ť������
	getIP();
	ui.sendButton->setEnabled(false);

	//�������˹��캯��
	totalBytesR = 0;
	bytesReceived = 0;
	fileNameSize = 0;
	//������������ʱ����newConnection()�ź�
	connect(&tcpServer, SIGNAL(newConnection()), this,
		SLOT(acceptConnection()));
	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(start()));
}
/**************************************/
//�ͻ�����غ���
tcpSender::~tcpSender()
{

}
//ʵ�ִ��ļ������ļ�����md5У��
void tcpSender::openFile()
{
	fileName = QFileDialog::getOpenFileName(this);
	QFile theFile(fileName);
	if (theFile.open(QFile::ReadOnly))
	{
		QCryptographicHash hash(QCryptographicHash::Md5);
		hash.addData(&theFile);
		md5 = hash.result().toHex();
		theFile.close();
		//ui.clientStatusLabel->setText(tr(md5));
	}
	else
	{
		qDebug() << "open the file False!";
	}
	if (!fileName.isEmpty())
	{
		ui.sendButton->setEnabled(true);
		ui.clientStatusLabel->setText(tr("open %1 successful!")
			.arg(fileName));
	}
}
//ʵ�����Ӻ���
void tcpSender::send()
{
	ui.sendButton->setEnabled(false);
	bytesWritten = 0;
	//��ʼ���ѷ����ֽ�Ϊ0
	ui.clientStatusLabel->setText(("connecting..."));
	tcpClient->connectToHost(ui.hostLineEdit->text(),
		ui.portLineEdit->text().toInt());//����
}
void tcpSender::startTransfer()  //ʵ���ļ���С����Ϣ�ķ���
{
	localFile = new QFile(fileName);
	if (!localFile->open(QFile::ReadOnly))
	{
		qDebug() << "open file error!";
		return;
	}

	//�ļ��ܴ�С
	totalBytes = localFile->size();

	QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_0);
	QString currentFileName = fileName.right(fileName.size()
		- fileName.lastIndexOf('/') - 1);

	//����д���ܴ�С��Ϣ�ռ䣬�ļ�����С��Ϣ�ռ䣬md5ֵ,�ļ���
	sendOut << qint64(0) << qint64(0) << md5<<currentFileName;

	//������ܴ�С���ļ�����С����Ϣ��ʵ���ļ���С���ܺ�
	totalBytes += outBlock.size();

	sendOut.device()->seek(0);
	//����outBolock�Ŀ�ʼ����ʵ�ʵĴ�С��Ϣ��������qint64(0)�ռ�
	sendOut << totalBytes << qint64((outBlock.size() - sizeof(qint64) * 2));

	//������ͷ���ݺ�ʣ�����ݵĴ�С
	bytesToWrite = totalBytes - tcpClient->write(outBlock);

	ui.clientStatusLabel->setText(tr("connect already"));
	outBlock.resize(0);
	
}
//���½�������ʵ���ļ��Ĵ���
void tcpSender::updateClientProgress(qint64 numBytes)
{
	//�Ѿ��������ݵĴ�С
	bytesWritten += (int)numBytes;

	if (bytesToWrite > 0) //����Ѿ�����������
	{
		//ÿ�η���loadSize��С�����ݣ���������Ϊ4KB�����ʣ������ݲ���4KB��
		//�ͷ���ʣ�����ݵĴ�С
		outBlock = localFile->read(qMin(bytesToWrite, loadSize));

		//������һ�����ݺ�ʣ�����ݵĴ�С
		bytesToWrite -= (int)tcpClient->write(outBlock);

		//��շ��ͻ�����
		outBlock.resize(0);

	}
	else {
		localFile->close(); //���û�з����κ����ݣ���ر��ļ�
	}

	//���½�����
	ui.clientProgressBar->setMaximum(totalBytes);
	ui.clientProgressBar->setValue(bytesWritten);

	if (bytesWritten == totalBytes) //�������
	{
		ui.clientStatusLabel->setText(tr("send %1 successful!")
			.arg(fileName));
		localFile->close();
		delete localFile;
		tcpClient->close();
		tcpClient->abort();
	}
	ui.clientProgressBar->reset();
	
}
void tcpSender::displayError(QAbstractSocket::SocketError) //��ʾ����
{
	qDebug() << tcpClient->errorString();
	tcpClient->close();
	ui.clientProgressBar->reset();
	ui.clientStatusLabel->setText(tr("client ready!"));
	ui.sendButton->setEnabled(true);
}
void tcpSender::getIP()
{
	QList<QHostAddress> list = QNetworkInterface::allAddresses();
	foreach (QHostAddress address, list)
	{
		if (address.protocol()==QAbstractSocket::IPv4Protocol)
		{
			if (address.toString().contains("127.0."))
			{
				continue;
			}
			ui.ipLable->setText(address.toString());
		}

	}
}
/**************************************************/
//����������غ���
void tcpSender::start() //��ʼ����
{
	ui.startButton->setEnabled(false);
	bytesReceived = 0;
	if (!tcpServer.listen(QHostAddress::AnyIPv4, 6666))//��������׽��ְ󶨵��󶨵�IPv4
	{
		qDebug() << tcpServer.errorString();
		close();
		return;
	}
	ui.serverStatusLabel->setText(tr("listen"));
}

void tcpSender::acceptConnection()  //��������
{
	tcpServerConnection = tcpServer.nextPendingConnection();
	connect(tcpServerConnection, SIGNAL(readyRead()), this,
		SLOT(updateServerProgress()));
	connect(tcpServerConnection,
		SIGNAL(error(QAbstractSocket::SocketError)), this,
		SLOT(displayError(QAbstractSocket::SocketError)));
	ui.serverStatusLabel->setText(tr("accept connect"));
	tcpServer.close();
	
}
void tcpSender::updateServerProgress()//���½���������������
{
	QDataStream in(tcpServerConnection);
	in.setVersion(QDataStream::Qt_5_0);
	if (bytesReceived<=sizeof(qint64)*2)
	{
		//������ܵ�������С��16���ֽڣ���ô�Ǹտ�ʼ�������ݣ����Ǳ���ͷ�ļ���Ϣ
		if ((tcpServerConnection->bytesAvailable()>=sizeof(qint64)*2)&&(fileNameSize==0))
			//�����ļ����������ļ�
		{//���������ܴ�С��Ϣ���ļ�����С��Ϣ
			in >> totalBytesR >> fileNameSize>>md5R;
			bytesReceived += sizeof(qint64) * 2;
		}
		if ((tcpServerConnection->bytesAvailable()>=fileNameSize)&&(fileNameSize!=0))
		{//�����ļ����������ļ�
			in >> fileNameR;
			qDebug() << "�����Ϣ";
			qDebug() << totalBytesR<<fileNameSize<<md5R<<fileNameR;
			ui.serverStatusLabel->setText(tr("accept %1...").arg(fileNameR));
			bytesReceived += fileNameSize;
			localFileR = new QFile(fileNameR);
			if (!localFileR->open(QFile::WriteOnly))//���մ���
			{
				qDebug() << "open the error!";
				return;
			}
			
		}
		else
		{
			return;
		}
	}
	if (bytesReceived<totalBytesR)
	{
		bytesReceived += tcpServerConnection->bytesAvailable();
		inBlock = tcpServerConnection->readAll();
		localFileR->write(inBlock);
		inBlock.resize(0);
	}
	//���½�����
	ui.serverProgressBar->setMaximum(totalBytesR);
	ui.serverProgressBar->setValue(bytesReceived);
	//�ƺ�����һ���ļ�������ر��ļ�����ɾ��ָ�룡���������´δ������bug
	if (bytesReceived==totalBytesR)//���ݽ�����ϲ������ļ�md5ֵ
	{
		tcpServerConnection->close();
		localFileR->close();
		QFile theFile(fileNameR);//�����յ����ļ��رպ����md5У��
		if (theFile.exists()&& theFile.open(QFile::ReadOnly))
		{
			QCryptographicHash hashR(QCryptographicHash::Md5);
			hashR.addData(&theFile);
			if (md5R==hashR.result().toHex())
			{
				ui.serverStatusLabel->setText(tr("accept %1 successful!").arg(fileNameR));
			}
			else
			{
				ui.serverStatusLabel->setText(tr("accept %1 failed!").append(fileNameR));
			}
			qDebug() << hashR.result().toHex();
		}
		else
			ui.serverStatusLabel->setText("error!");
		ui.startButton->setEnabled(true);
		ui.serverProgressBar->reset();
		localFileR->close();
		totalBytesR = 0;
		fileNameSize=0;
		//md5R = "";
		delete localFileR;

		
		
		/*if (md5R == hashR.result().toHex())
		{
			ui.serverStatusLabel->setText(tr("md5 correct!"));
		}
		else
		{
			ui.serverStatusLabel->setText("md5 incorrect!");
		}*/

	}

}
void tcpSender::displayErrorR(QAbstractSocket::SocketError socketError)
{
	qDebug ()<< tcpServerConnection->errorString();
	tcpServerConnection->close();
	ui.serverProgressBar->reset();
	ui.serverStatusLabel->setText(tr("sever ready!"));
	ui.startButton->setEnabled(true);
}

