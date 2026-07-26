/****************************************************************************
** Meta object code from reading C++ file 'screenhandler.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../screenhandler.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'screenhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13ScreenHandlerE_t {};
} // unnamed namespace

template <> constexpr inline auto ScreenHandler::qt_create_metaobjectdata<qt_meta_tag_ZN13ScreenHandlerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ScreenHandler",
        "frameCaptured",
        "",
        "QList<DataChunk>",
        "chunks",
        "errorOccurred",
        "error",
        "captureStarted",
        "captureStopped",
        "onCaptureTimer"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'frameCaptured'
        QtMocHelpers::SignalData<void(const QVector<DataChunk> &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'captureStarted'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'captureStopped'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onCaptureTimer'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ScreenHandler, qt_meta_tag_ZN13ScreenHandlerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ScreenHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<ScreenBase::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ScreenHandlerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ScreenHandlerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13ScreenHandlerE_t>.metaTypes,
    nullptr
} };

void ScreenHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ScreenHandler *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->frameCaptured((*reinterpret_cast<std::add_pointer_t<QList<DataChunk>>>(_a[1]))); break;
        case 1: _t->errorOccurred((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->captureStarted(); break;
        case 3: _t->captureStopped(); break;
        case 4: _t->onCaptureTimer(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ScreenHandler::*)(const QVector<DataChunk> & )>(_a, &ScreenHandler::frameCaptured, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScreenHandler::*)(const QString & )>(_a, &ScreenHandler::errorOccurred, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScreenHandler::*)()>(_a, &ScreenHandler::captureStarted, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ScreenHandler::*)()>(_a, &ScreenHandler::captureStopped, 3))
            return;
    }
}

const QMetaObject *ScreenHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScreenHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ScreenHandlerE_t>.strings))
        return static_cast<void*>(this);
    return ScreenBase::qt_metacast(_clname);
}

int ScreenHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ScreenBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ScreenHandler::frameCaptured(const QVector<DataChunk> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ScreenHandler::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ScreenHandler::captureStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ScreenHandler::captureStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
