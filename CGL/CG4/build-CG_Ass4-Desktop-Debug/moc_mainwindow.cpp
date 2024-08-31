/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CG_Ass4/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "on_label_linkActivated"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 4), // "link"
QT_MOC_LITERAL(4, 40, 3), // "dda"
QT_MOC_LITERAL(5, 44, 2), // "x1"
QT_MOC_LITERAL(6, 47, 2), // "y1"
QT_MOC_LITERAL(7, 50, 2), // "x2"
QT_MOC_LITERAL(8, 53, 2), // "y2"
QT_MOC_LITERAL(9, 56, 6), // "signfn"
QT_MOC_LITERAL(10, 63, 6), // "matMul"
QT_MOC_LITERAL(11, 70, 11), // "float[2][3]"
QT_MOC_LITERAL(12, 82, 4), // "arr1"
QT_MOC_LITERAL(13, 87, 11), // "float[3][3]"
QT_MOC_LITERAL(14, 99, 4), // "arr2"
QT_MOC_LITERAL(15, 104, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(16, 126, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(17, 150, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(18, 174, 23) // "on_pushButton_4_clicked"

    },
    "MainWindow\0on_label_linkActivated\0\0"
    "link\0dda\0x1\0y1\0x2\0y2\0signfn\0matMul\0"
    "float[2][3]\0arr1\0float[3][3]\0arr2\0"
    "on_pushButton_clicked\0on_pushButton_2_clicked\0"
    "on_pushButton_3_clicked\0on_pushButton_4_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       4,    4,   57,    2, 0x08 /* Private */,
       9,    2,   66,    2, 0x08 /* Private */,
      10,    2,   71,    2, 0x08 /* Private */,
      15,    0,   76,    2, 0x08 /* Private */,
      16,    0,   77,    2, 0x08 /* Private */,
      17,    0,   78,    2, 0x08 /* Private */,
      18,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    5,    6,    7,    8,
    QMetaType::Int, QMetaType::Float, QMetaType::Float,    2,    2,
    QMetaType::Float, 0x80000000 | 11, 0x80000000 | 13,   12,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_label_linkActivated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->dda((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 2: { int _r = _t->signfn((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { float _r = _t->matMul((*reinterpret_cast< float(*)[2][3]>(_a[1])),(*reinterpret_cast< float(*)[3][3]>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->on_pushButton_2_clicked(); break;
        case 6: _t->on_pushButton_3_clicked(); break;
        case 7: _t->on_pushButton_4_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
