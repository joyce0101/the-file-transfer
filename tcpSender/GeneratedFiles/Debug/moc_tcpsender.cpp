/****************************************************************************
** Meta object code from reading C++ file 'tcpsender.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tcpsender.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpsender.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcpSender_t {
    QByteArrayData data[14];
    char stringdata0[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcpSender_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcpSender_t qt_meta_stringdata_tcpSender = {
    {
QT_MOC_LITERAL(0, 0, 9), // "tcpSender"
QT_MOC_LITERAL(1, 10, 4), // "send"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 13), // "startTransfer"
QT_MOC_LITERAL(4, 30, 20), // "updateClientProgress"
QT_MOC_LITERAL(5, 51, 12), // "displayError"
QT_MOC_LITERAL(6, 64, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(7, 93, 8), // "openFile"
QT_MOC_LITERAL(8, 102, 5), // "getIP"
QT_MOC_LITERAL(9, 108, 5), // "start"
QT_MOC_LITERAL(10, 114, 16), // "acceptConnection"
QT_MOC_LITERAL(11, 131, 20), // "updateServerProgress"
QT_MOC_LITERAL(12, 152, 13), // "displayErrorR"
QT_MOC_LITERAL(13, 166, 11) // "socketError"

    },
    "tcpSender\0send\0\0startTransfer\0"
    "updateClientProgress\0displayError\0"
    "QAbstractSocket::SocketError\0openFile\0"
    "getIP\0start\0acceptConnection\0"
    "updateServerProgress\0displayErrorR\0"
    "socketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcpSender[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    1,   66,    2, 0x08 /* Private */,
       5,    1,   69,    2, 0x08 /* Private */,
       7,    0,   72,    2, 0x08 /* Private */,
       8,    0,   73,    2, 0x08 /* Private */,
       9,    0,   74,    2, 0x08 /* Private */,
      10,    0,   75,    2, 0x08 /* Private */,
      11,    0,   76,    2, 0x08 /* Private */,
      12,    1,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,   13,

       0        // eod
};

void tcpSender::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcpSender *_t = static_cast<tcpSender *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send(); break;
        case 1: _t->startTransfer(); break;
        case 2: _t->updateClientProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 3: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->openFile(); break;
        case 5: _t->getIP(); break;
        case 6: _t->start(); break;
        case 7: _t->acceptConnection(); break;
        case 8: _t->updateServerProgress(); break;
        case 9: _t->displayErrorR((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject tcpSender::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_tcpSender.data,
      qt_meta_data_tcpSender,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *tcpSender::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcpSender::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_tcpSender.stringdata0))
        return static_cast<void*>(const_cast< tcpSender*>(this));
    return QWidget::qt_metacast(_clname);
}

int tcpSender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
