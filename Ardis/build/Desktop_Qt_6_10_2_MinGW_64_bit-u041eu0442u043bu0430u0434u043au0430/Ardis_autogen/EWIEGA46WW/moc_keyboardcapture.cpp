/****************************************************************************
** Meta object code from reading C++ file 'keyboardcapture.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../keyboardcapture.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QSet>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keyboardcapture.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN15KeyboardCaptureE_t {};
} // unnamed namespace

template <> constexpr inline auto KeyboardCapture::qt_create_metaobjectdata<qt_meta_tag_ZN15KeyboardCaptureE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "KeyboardCapture",
        "keyPressed",
        "",
        "keyCode",
        "ctrl",
        "shift",
        "alt",
        "keyReleased",
        "keyCombination",
        "QSet<int>",
        "keys",
        "keyHold",
        "durationMS",
        "captureStarted",
        "captureStopped",
        "error",
        "er",
        "onKeyHoldTimer",
        "onKeyReleaseTimer"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'keyPressed'
        QtMocHelpers::SignalData<void(int, bool, bool, bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::Bool, 4 }, { QMetaType::Bool, 5 }, { QMetaType::Bool, 6 },
        }}),
        // Signal 'keyReleased'
        QtMocHelpers::SignalData<void(int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'keyCombination'
        QtMocHelpers::SignalData<void(const QSet<int> &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'keyHold'
        QtMocHelpers::SignalData<void(int, int)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::Int, 12 },
        }}),
        // Signal 'captureStarted'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'captureStopped'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'error'
        QtMocHelpers::SignalData<void(const QString &)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 16 },
        }}),
        // Slot 'onKeyHoldTimer'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onKeyReleaseTimer'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<KeyboardCapture, qt_meta_tag_ZN15KeyboardCaptureE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject KeyboardCapture::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15KeyboardCaptureE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15KeyboardCaptureE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15KeyboardCaptureE_t>.metaTypes,
    nullptr
} };

void KeyboardCapture::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<KeyboardCapture *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->keyPressed((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[4]))); break;
        case 1: _t->keyReleased((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->keyCombination((*reinterpret_cast<std::add_pointer_t<QSet<int>>>(_a[1]))); break;
        case 3: _t->keyHold((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->captureStarted(); break;
        case 5: _t->captureStopped(); break;
        case 6: _t->error((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->onKeyHoldTimer(); break;
        case 8: _t->onKeyReleaseTimer(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QSet<int> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (KeyboardCapture::*)(int , bool , bool , bool )>(_a, &KeyboardCapture::keyPressed, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (KeyboardCapture::*)(int )>(_a, &KeyboardCapture::keyReleased, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (KeyboardCapture::*)(const QSet<int> & )>(_a, &KeyboardCapture::keyCombination, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (KeyboardCapture::*)(int , int )>(_a, &KeyboardCapture::keyHold, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (KeyboardCapture::*)()>(_a, &KeyboardCapture::captureStarted, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (KeyboardCapture::*)()>(_a, &KeyboardCapture::captureStopped, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (KeyboardCapture::*)(const QString & )>(_a, &KeyboardCapture::error, 6))
            return;
    }
}

const QMetaObject *KeyboardCapture::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KeyboardCapture::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15KeyboardCaptureE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int KeyboardCapture::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void KeyboardCapture::keyPressed(int _t1, bool _t2, bool _t3, bool _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 1
void KeyboardCapture::keyReleased(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void KeyboardCapture::keyCombination(const QSet<int> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void KeyboardCapture::keyHold(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}

// SIGNAL 4
void KeyboardCapture::captureStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void KeyboardCapture::captureStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void KeyboardCapture::error(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}
QT_WARNING_POP
