/****************************************************************************
** Meta object code from reading C++ file '_textbox.h'
**
** Created: Fri May 1 19:14:52 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_textbox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_textbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__textbox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      25,    9,    9,    9, 0x0a,
      43,   41,    9,    9, 0x0a,
      82,    9,    9,    9, 0x0a,
     108,    9,    9,    9, 0x0a,
     132,    9,    9,    9, 0x0a,
     159,    9,    9,    9, 0x0a,
     188,    9,    9,    9, 0x0a,
     216,    9,    9,    9, 0x0a,
     235,    9,    9,    9, 0x0a,
     253,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__textbox[] = {
    "_textbox\0\0SoundOnEvent()\0EVENT_OnEvent()\0"
    ",\0EVENT_OnCursorPositionChanged(int,int)\0"
    "EVENT_OnEditingFinished()\0"
    "EVENT_OnReturnPressed()\0"
    "EVENT_OnSelectionChanged()\0"
    "EVENT_OnTextChanged(QString)\0"
    "EVENT_OnTextEdited(QString)\0"
    "EVENT_OnSQLEvent()\0frameChanged(int)\0"
    "cursoranimation_frameChanged(int)\0"
};

const QMetaObject _textbox::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata__textbox,
      qt_meta_data__textbox, 0 }
};

const QMetaObject *_textbox::metaObject() const
{
    return &staticMetaObject;
}

void *_textbox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__textbox))
        return static_cast<void*>(const_cast< _textbox*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _textbox*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int _textbox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SoundOnEvent(); break;
        case 1: EVENT_OnEvent(); break;
        case 2: EVENT_OnCursorPositionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: EVENT_OnEditingFinished(); break;
        case 4: EVENT_OnReturnPressed(); break;
        case 5: EVENT_OnSelectionChanged(); break;
        case 6: EVENT_OnTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: EVENT_OnTextEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: EVENT_OnSQLEvent(); break;
        case 9: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
