/****************************************************************************
** Meta object code from reading C++ file '_timebox.h'
**
** Created: Sat May 2 08:07:24 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_timebox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_timebox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__timebox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      27,    9,    9,    9, 0x0a,
      42,    9,    9,    9, 0x0a,
      58,    9,    9,    9, 0x0a,
      77,    9,    9,    9, 0x0a,
      95,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__timebox[] = {
    "_timebox\0\0EVENT_OnEvent2()\0SoundOnEvent()\0"
    "EVENT_OnEvent()\0EVENT_OnSQLEvent()\0"
    "frameChanged(int)\0cursoranimation_frameChanged(int)\0"
};

const QMetaObject _timebox::staticMetaObject = {
    { &QTimeEdit::staticMetaObject, qt_meta_stringdata__timebox,
      qt_meta_data__timebox, 0 }
};

const QMetaObject *_timebox::metaObject() const
{
    return &staticMetaObject;
}

void *_timebox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__timebox))
        return static_cast<void*>(const_cast< _timebox*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _timebox*>(this));
    return QTimeEdit::qt_metacast(_clname);
}

int _timebox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTimeEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: EVENT_OnEvent2(); break;
        case 1: SoundOnEvent(); break;
        case 2: EVENT_OnEvent(); break;
        case 3: EVENT_OnSQLEvent(); break;
        case 4: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
