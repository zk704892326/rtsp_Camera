/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../newDJ/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      41,   11,   11,   11, 0x08,
      71,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,
     127,   11,   11,   11, 0x08,
     156,   11,   11,   11, 0x08,
     186,   11,   11,   11, 0x08,
     216,   11,   11,   11, 0x08,
     247,   11,   11,   11, 0x08,
     288,   11,  275,   11, 0x08,
     305,   11,   11,   11, 0x08,
     324,   11,   11,   11, 0x08,
     343,   11,   11,   11, 0x08,
     366,   11,   11,   11, 0x08,
     389,   11,   11,   11, 0x0a,
     471,  408,   11,   11, 0x0a,
     521,   11,   11,   11, 0x0a,
     541,   11,   11,   11, 0x0a,
     560,   11,   11,   11, 0x0a,
     580,   11,   11,   11, 0x0a,
     599,   11,   11,   11, 0x0a,
     619,   11,   11,   11, 0x0a,
     638,   11,   11,   11, 0x0a,
     658,   11,   11,   11, 0x0a,
     677,   11,   11,   11, 0x0a,
     697,   11,   11,   11, 0x0a,
     716,   11,   11,   11, 0x0a,
     736,   11,   11,   11, 0x0a,
     755,   11,   11,   11, 0x0a,
     775,   11,   11,   11, 0x0a,
     794,   11,   11,   11, 0x0a,
     814,   11,   11,   11, 0x0a,
     833,   11,   11,   11, 0x0a,
     853,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_pushButton_open_clicked()\0"
    "on_pushButton_close_clicked()\0"
    "on_pushButton_up_clicked()\0"
    "on_pushButton_down_clicked()\0"
    "on_pushButton_stop_clicked()\0"
    "on_pushButton_local_clicked()\0"
    "on_pushButton_reset_clicked()\0"
    "on_pushButton_socket_clicked()\0"
    "on_pushButton_set_clicked()\0QHostAddress\0"
    "getLocalHostIP()\0on_goto1_clicked()\0"
    "on_goto2_clicked()\0on_getValue1_clicked()\0"
    "on_getValue2_clicked()\0slot_read_my_com()\0"
    "count1,count2,count3,count4,comcount,com1,com2,com3,com4,speed\0"
    "SendMess(int,int,int,int,int,int,int,int,int,int)\0"
    "slotConnectClient()\0slotReadTcpData0()\0"
    "slotDisconnected0()\0slotReadTcpData1()\0"
    "slotDisconnected1()\0slotReadTcpData2()\0"
    "slotDisconnected2()\0slotReadTcpData3()\0"
    "slotDisconnected3()\0slotReadTcpData4()\0"
    "slotDisconnected4()\0slotReadTcpData5()\0"
    "slotDisconnected5()\0slotReadTcpData6()\0"
    "slotDisconnected6()\0slotReadTcpData7()\0"
    "slotDisconnected7()\0update_mess()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_open_clicked(); break;
        case 1: _t->on_pushButton_close_clicked(); break;
        case 2: _t->on_pushButton_up_clicked(); break;
        case 3: _t->on_pushButton_down_clicked(); break;
        case 4: _t->on_pushButton_stop_clicked(); break;
        case 5: _t->on_pushButton_local_clicked(); break;
        case 6: _t->on_pushButton_reset_clicked(); break;
        case 7: _t->on_pushButton_socket_clicked(); break;
        case 8: _t->on_pushButton_set_clicked(); break;
        case 9: { QHostAddress _r = _t->getLocalHostIP();
            if (_a[0]) *reinterpret_cast< QHostAddress*>(_a[0]) = _r; }  break;
        case 10: _t->on_goto1_clicked(); break;
        case 11: _t->on_goto2_clicked(); break;
        case 12: _t->on_getValue1_clicked(); break;
        case 13: _t->on_getValue2_clicked(); break;
        case 14: _t->slot_read_my_com(); break;
        case 15: _t->SendMess((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])),(*reinterpret_cast< int(*)>(_a[9])),(*reinterpret_cast< int(*)>(_a[10]))); break;
        case 16: _t->slotConnectClient(); break;
        case 17: _t->slotReadTcpData0(); break;
        case 18: _t->slotDisconnected0(); break;
        case 19: _t->slotReadTcpData1(); break;
        case 20: _t->slotDisconnected1(); break;
        case 21: _t->slotReadTcpData2(); break;
        case 22: _t->slotDisconnected2(); break;
        case 23: _t->slotReadTcpData3(); break;
        case 24: _t->slotDisconnected3(); break;
        case 25: _t->slotReadTcpData4(); break;
        case 26: _t->slotDisconnected4(); break;
        case 27: _t->slotReadTcpData5(); break;
        case 28: _t->slotDisconnected5(); break;
        case 29: _t->slotReadTcpData6(); break;
        case 30: _t->slotDisconnected6(); break;
        case 31: _t->slotReadTcpData7(); break;
        case 32: _t->slotDisconnected7(); break;
        case 33: _t->update_mess(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
