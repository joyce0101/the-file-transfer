#include "tcpsender.h"
#include <QFileDialog>
#include <QList>
#include <QtNetwork/QHostAddress>
#include <QCryptographicHash>//对文件进行md5校验
tcpSender::tcpSender(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	tcpSender::setWindowTitle("FileTransfer_Lan");
	
	//客户端构造函数：
	loadSize = 4 * 1024;
	totalBytes = 0;
	bytesWritten = 0;
	bytesToWrite = 0;
	tcpClient = new QTcpSocket(this);
	//当连接服务器成功时，发出connected()信号，我们开始传送文件
	connect(tcpClient, SIGNAL(connected()), this, SLOT(startTransfer()));
	//当有数据发送成功时，我们更新进度条
	connect(tcpClient, SIGNAL(bytesWritten(qint64)), this,
		SLOT(updateClientProgress(qint64)));
	connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this,
		SLOT(displayError(QAbstractSocket::SocketError)));
	connect(ui.openButton, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(send()));
	//开始使”发送“按钮不可用
	getIP();
	ui.sendButton->setEnabled(false);

	//服务器端构造函数
	totalBytesR = 0;
	bytesReceived = 0;
	fileNameSize = 0;
	//当发现新连接时发出newConnection()信号
	connect(&tcpServer, SIGNAL(newConnection()), this,
		SLOT(acceptConnection()));
	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(start()));
}
/**************************************/
//客户端相关函数
tcpSender::~tcpSender()
{

}
//实现打开文件并对文件进行md5校验
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
//实现连接函数
void tcpSender::send()
{
	ui.sendButton->setEnabled(false);
	bytesWritten = 0;
	//初始化已发送字节为0
	ui.clientStatusLabel->setText(("connecting..."));
	tcpClient->connectToHost(ui.hostLineEdit->text(),
		ui.portLineEdit->text().toInt());//连接
}
void tcpSender::startTransfer()  //实现文件大小等信息的发送
{
	localFile = new QFile(fileName);
	if (!localFile->open(QFile::ReadOnly))
	{
		qDebug() << "open file error!";
		return;
	}

	//文件总大小
	totalBytes = localFile->size();

	QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_0);
	QString currentFileName = fileName.right(fileName.size()
		- fileName.lastIndexOf('/') - 1);

	//依次写入总大小信息空间，文件名大小信息空间，md5值,文件名
	sendOut << qint64(0) << qint64(0) << md5<<currentFileName;

	//这里的总大小是文件名大小等信息和实际文件大小的总和
	totalBytes += outBlock.size();

	sendOut.device()->seek(0);
	//返回outBolock的开始，用实际的大小信息代替两个qint64(0)空间
	sendOut << totalBytes << qint64((outBlock.size() - sizeof(qint64) * 2));

	//发送完头数据后剩余数据的大小
	bytesToWrite = totalBytes - tcpClient->write(outBlock);

	ui.clientStatusLabel->setText(tr("connect already"));
	outBlock.resize(0);
	
}
//更新进度条，实现文件的传送
void tcpSender::updateClientProgress(qint64 numBytes)
{
	//已经发送数据的大小
	bytesWritten += (int)numBytes;

	if (bytesToWrite > 0) //如果已经发送了数据
	{
		//每次发送loadSize大小的数据，这里设置为4KB，如果剩余的数据不足4KB，
		//就发送剩余数据的大小
		outBlock = localFile->read(qMin(bytesToWrite, loadSize));

		//发送完一次数据后还剩余数据的大小
		bytesToWrite -= (int)tcpClient->write(outBlock);

		//清空发送缓冲区
		outBlock.resize(0);

	}
	else {
		localFile->close(); //如果没有发送任何数据，则关闭文件
	}

	//更新进度条
	ui.clientProgressBar->setMaximum(totalBytes);
	ui.clientProgressBar->setValue(bytesWritten);

	if (bytesWritten == totalBytes) //发送完毕
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
void tcpSender::displayError(QAbstractSocket::SocketError) //显示错误
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
//服务器端相关函数
void tcpSender::start() //开始监听
{
	ui.startButton->setEnabled(false);
	bytesReceived = 0;
	if (!tcpServer.listen(QHostAddress::AnyIPv4, 6666))//将服务端套接字绑定到绑定到IPv4
	{
		qDebug() << tcpServer.errorString();
		close();
		return;
	}
	ui.serverStatusLabel->setText(tr("listen"));
}

void tcpSender::acceptConnection()  //接受连接
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
void tcpSender::updateServerProgress()//更新进度条，接收数据
{
	QDataStream in(tcpServerConnection);
	in.setVersion(QDataStream::Qt_5_0);
	if (bytesReceived<=sizeof(qint64)*2)
	{
		//如果接受到的数据小于16个字节，那么是刚开始接收数据，我们保存头文件信息
		if ((tcpServerConnection->bytesAvailable()>=sizeof(qint64)*2)&&(fileNameSize==0))
			//接收文件名并建立文件
		{//接收数据总大小信息和文件名大小信息
			in >> totalBytesR >> fileNameSize>>md5R;
			bytesReceived += sizeof(qint64) * 2;
		}
		if ((tcpServerConnection->bytesAvailable()>=fileNameSize)&&(fileNameSize!=0))
		{//接收文件名并建立文件
			in >> fileNameR;
			qDebug() << "输出信息";
			qDebug() << totalBytesR<<fileNameSize<<md5R<<fileNameR;
			ui.serverStatusLabel->setText(tr("accept %1...").arg(fileNameR));
			bytesReceived += fileNameSize;
			localFileR = new QFile(fileNameR);
			if (!localFileR->open(QFile::WriteOnly))//接收错误
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
	//更新进度条
	ui.serverProgressBar->setMaximum(totalBytesR);
	ui.serverProgressBar->setValue(bytesReceived);
	//善后工作，一个文件收完则关闭文件流，删除指针！！！否则下次传输出现bug
	if (bytesReceived==totalBytesR)//数据接收完毕并计算文件md5值
	{
		tcpServerConnection->close();
		localFileR->close();
		QFile theFile(fileNameR);//将接收到的文件关闭后进行md5校验
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

