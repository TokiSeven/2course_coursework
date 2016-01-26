/****************************************************************************
** Meta object code from reading C++ file 'launcher.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client_v01/launcher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'launcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Launcher_t {
    QByteArrayData data[9];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Launcher_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Launcher_t qt_meta_stringdata_Launcher = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Launcher"
QT_MOC_LITERAL(1, 9, 9), // "connected"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 12), // "disconnected"
QT_MOC_LITERAL(4, 33, 14), // "nick_incorrect"
QT_MOC_LITERAL(5, 48, 13), // "signal_closed"
QT_MOC_LITERAL(6, 62, 15), // "slot_game_close"
QT_MOC_LITERAL(7, 78, 15), // "readUdpDiagrams"
QT_MOC_LITERAL(8, 94, 7) // "timeOut"

    },
    "Launcher\0connected\0\0disconnected\0"
    "nick_incorrect\0signal_closed\0"
    "slot_game_close\0readUdpDiagrams\0timeOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Launcher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,
       5,    0,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Launcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Launcher *_t = static_cast<Launcher *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->nick_incorrect(); break;
        case 3: _t->signal_closed(); break;
        case 4: _t->slot_game_close(); break;
        case 5: _t->readUdpDiagrams(); break;
        case 6: _t->timeOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Launcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Launcher::connected)) {
                *result = 0;
            }
        }
        {
            typedef void (Launcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Launcher::disconnected)) {
                *result = 1;
            }
        }
        {
            typedef void (Launcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Launcher::nick_incorrect)) {
                *result = 2;
            }
        }
        {
            typedef void (Launcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Launcher::signal_closed)) {
                *result = 3;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Launcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Launcher.data,
      qt_meta_data_Launcher,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Launcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Launcher::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Launcher.stringdata0))
        return static_cast<void*>(const_cast< Launcher*>(this));
    return QObject::qt_metacast(_clname);
}

int Launcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Launcher::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Launcher::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Launcher::nick_incorrect()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Launcher::signal_closed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
