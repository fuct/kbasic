/****************************************************************************
** Meta object code from reading C++ file '_qbe_browser.h'
**
** Created: Sat May 2 07:54:48 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_qbe_browser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_qbe_browser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__qbe_browser[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__qbe_browser[] = {
    "_qbe_browser\0"
};

const QMetaObject _qbe_browser::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata__qbe_browser,
      qt_meta_data__qbe_browser, 0 }
};

const QMetaObject *_qbe_browser::metaObject() const
{
    return &staticMetaObject;
}

void *_qbe_browser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__qbe_browser))
        return static_cast<void*>(const_cast< _qbe_browser*>(this));
    return QTableView::qt_metacast(_clname);
}

int _qbe_browser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
