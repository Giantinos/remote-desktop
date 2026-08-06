/****************************************************************************
** Meta object code from reading C++ file 'senderclient.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../senderclient.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'senderclient.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12SenderClientE_t {};
} // unnamed namespace

template <> constexpr inline auto SenderClient::qt_create_metaobjectdata<qt_meta_tag_ZN12SenderClientE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SenderClient",
        "connectionChanged",
        "",
        "status",
        "warning",
        "message",
        "clientEvent",
        "disconnectFromHost",
        "sendMessage",
        "text",
        "startServerScreencast",
        "stopServerScreencast",
        "startScreencast",
        "stopScreencast",
        "setUdpAddress",
        "address",
        "setUdpPort",
        "port",
        "SHOWMES",
        "s",
        "getUdpAddress",
        "onSocketError",
        "QAbstractSocket::SocketError",
        "socketError",
        "onDisconnected",
        "onTcpConnected",
        "onReadyRead",
        "stopUdpListening"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'connectionChanged'
        QtMocHelpers::SignalData<void(const int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'warning'
        QtMocHelpers::SignalData<void(const QString)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Signal 'clientEvent'
        QtMocHelpers::SignalData<void(const QString)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Slot 'disconnectFromHost'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'sendMessage'
        QtMocHelpers::SlotData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'startServerScreencast'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'stopServerScreencast'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'startScreencast'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'stopScreencast'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setUdpAddress'
        QtMocHelpers::SlotData<void(QString)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Slot 'setUdpPort'
        QtMocHelpers::SlotData<void(int)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 17 },
        }}),
        // Slot 'SHOWMES'
        QtMocHelpers::SlotData<void(QString)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 },
        }}),
        // Slot 'getUdpAddress'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onSocketError'
        QtMocHelpers::SlotData<void(QAbstractSocket::SocketError)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 22, 23 },
        }}),
        // Slot 'onDisconnected'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTcpConnected'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onReadyRead'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'stopUdpListening'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SenderClient, qt_meta_tag_ZN12SenderClientE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SenderClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12SenderClientE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12SenderClientE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12SenderClientE_t>.metaTypes,
    nullptr
} };

void SenderClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SenderClient *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->connectionChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->warning((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->clientEvent((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->disconnectFromHost(); break;
        case 4: _t->sendMessage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->startServerScreencast(); break;
        case 6: _t->stopServerScreencast(); break;
        case 7: _t->startScreencast(); break;
        case 8: _t->stopScreencast(); break;
        case 9: _t->setUdpAddress((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->setUdpPort((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->SHOWMES((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->getUdpAddress(); break;
        case 13: _t->onSocketError((*reinterpret_cast<std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 14: _t->onDisconnected(); break;
        case 15: _t->onTcpConnected(); break;
        case 16: _t->onReadyRead(); break;
        case 17: _t->stopUdpListening(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SenderClient::*)(const int )>(_a, &SenderClient::connectionChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SenderClient::*)(const QString )>(_a, &SenderClient::warning, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (SenderClient::*)(const QString )>(_a, &SenderClient::clientEvent, 2))
            return;
    }
}

const QMetaObject *SenderClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SenderClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12SenderClientE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SenderClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void SenderClient::connectionChanged(const int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void SenderClient::warning(const QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void SenderClient::clientEvent(const QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
