/********************************************************************************
** Form generated from reading UI file 'tcpsender.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSENDER_H
#define UI_TCPSENDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tcpSenderClass
{
public:
    QLabel *label_3;
    QLabel *ipLable;
    QGroupBox *groupBox;
    QPushButton *sendButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QProgressBar *clientProgressBar;
    QLabel *clientStatusLabel;
    QPushButton *openButton;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *hostLineEdit;
    QLineEdit *portLineEdit;
    QGroupBox *groupBox_2;
    QLabel *serverStatusLabel;
    QPushButton *startButton;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QProgressBar *serverProgressBar;

    void setupUi(QWidget *tcpSenderClass)
    {
        if (tcpSenderClass->objectName().isEmpty())
            tcpSenderClass->setObjectName(QStringLiteral("tcpSenderClass"));
        tcpSenderClass->resize(652, 593);
        label_3 = new QLabel(tcpSenderClass);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 10, 81, 31));
        label_3->setScaledContents(false);
        ipLable = new QLabel(tcpSenderClass);
        ipLable->setObjectName(QStringLiteral("ipLable"));
        ipLable->setGeometry(QRect(130, 20, 441, 16));
        groupBox = new QGroupBox(tcpSenderClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 50, 611, 331));
        sendButton = new QPushButton(groupBox);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(480, 280, 93, 28));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 150, 531, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        clientProgressBar = new QProgressBar(layoutWidget);
        clientProgressBar->setObjectName(QStringLiteral("clientProgressBar"));
        clientProgressBar->setValue(0);

        horizontalLayout_2->addWidget(clientProgressBar);

        clientStatusLabel = new QLabel(groupBox);
        clientStatusLabel->setObjectName(QStringLiteral("clientStatusLabel"));
        clientStatusLabel->setGeometry(QRect(40, 200, 531, 31));
        openButton = new QPushButton(groupBox);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(40, 270, 93, 28));
        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(40, 30, 531, 91));
        horizontalLayout = new QHBoxLayout(layoutWidget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(layoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        hostLineEdit = new QLineEdit(layoutWidget_2);
        hostLineEdit->setObjectName(QStringLiteral("hostLineEdit"));

        verticalLayout_2->addWidget(hostLineEdit);

        portLineEdit = new QLineEdit(layoutWidget_2);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));

        verticalLayout_2->addWidget(portLineEdit);


        horizontalLayout->addLayout(verticalLayout_2);

        groupBox_2 = new QGroupBox(tcpSenderClass);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 400, 611, 161));
        serverStatusLabel = new QLabel(groupBox_2);
        serverStatusLabel->setObjectName(QStringLiteral("serverStatusLabel"));
        serverStatusLabel->setGeometry(QRect(40, 20, 521, 41));
        startButton = new QPushButton(groupBox_2);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(40, 110, 93, 28));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 70, 531, 25));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_5->addWidget(label_8);

        serverProgressBar = new QProgressBar(layoutWidget1);
        serverProgressBar->setObjectName(QStringLiteral("serverProgressBar"));
        serverProgressBar->setValue(0);

        horizontalLayout_5->addWidget(serverProgressBar);


        retranslateUi(tcpSenderClass);

        QMetaObject::connectSlotsByName(tcpSenderClass);
    } // setupUi

    void retranslateUi(QWidget *tcpSenderClass)
    {
        tcpSenderClass->setWindowTitle(QApplication::translate("tcpSenderClass", "tcpSender", Q_NULLPTR));
        label_3->setText(QApplication::translate("tcpSenderClass", "\346\234\254\346\234\272IP\357\274\232", Q_NULLPTR));
        ipLable->setText(QString());
        groupBox->setTitle(QApplication::translate("tcpSenderClass", "\345\217\221\351\200\201\346\226\207\344\273\266", Q_NULLPTR));
        sendButton->setText(QApplication::translate("tcpSenderClass", "\345\217\221\351\200\201", Q_NULLPTR));
        label_4->setText(QApplication::translate("tcpSenderClass", "\345\217\221\351\200\201\351\200\237\347\216\207\357\274\232", Q_NULLPTR));
        clientStatusLabel->setText(QApplication::translate("tcpSenderClass", "\347\255\211\345\276\205\346\211\223\345\274\200\346\226\207\344\273\266\357\274\201\357\274\201\357\274\201", Q_NULLPTR));
        openButton->setText(QApplication::translate("tcpSenderClass", "\346\211\223\345\274\200", Q_NULLPTR));
        label->setText(QApplication::translate("tcpSenderClass", "   \344\270\273\346\234\272\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("tcpSenderClass", "   \347\253\257\345\217\243\357\274\232", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("tcpSenderClass", "\346\216\245\346\224\266\346\226\207\344\273\266", Q_NULLPTR));
        serverStatusLabel->setText(QApplication::translate("tcpSenderClass", "\346\234\215\345\212\241\345\231\250\347\253\257", Q_NULLPTR));
        startButton->setText(QApplication::translate("tcpSenderClass", "\345\274\200\345\247\213\347\233\221\345\220\254", Q_NULLPTR));
        label_8->setText(QApplication::translate("tcpSenderClass", "\346\216\245\346\224\266\351\200\237\347\216\207\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class tcpSenderClass: public Ui_tcpSenderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSENDER_H
