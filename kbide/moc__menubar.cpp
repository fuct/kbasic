/****************************************************************************
** Meta object code from reading C++ file '_menubar.h'
**
** Created: Sat May 2 08:01:58 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_menubar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_menubar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__qmenubar[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      18,   11,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__qmenubar[] = {
    "_qmenubar\0\0action\0hovered(QAction*)\0"
};

const QMetaObject _qmenubar::staticMetaObject = {
    { &QMenuBar::staticMetaObject, qt_meta_stringdata__qmenubar,
      qt_meta_data__qmenubar, 0 }
};

const QMetaObject *_qmenubar::metaObject() const
{
    return &staticMetaObject;
}

void *_qmenubar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__qmenubar))
        return static_cast<void*>(const_cast< _qmenubar*>(this));
    return QMenuBar::qt_metacast(_clname);
}

int _qmenubar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenuBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: hovered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__menubar[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__menubar[] = {
    "_menubar\0"
};

const QMetaObject _menubar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__menubar,
      qt_meta_data__menubar, 0 }
};

const QMetaObject *_menubar::metaObject() const
{
    return &staticMetaObject;
}

void *_menubar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__menubar))
        return static_cast<void*>(const_cast< _menubar*>(this));
    return QWidget::qt_metacast(_clname);
}

int _menubar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
