/****************************************************************************
** Meta object code from reading C++ file 'receiverobject.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../receiverobject.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'receiverobject.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14ReceiverObjectE_t {};
} // unnamed namespace

template <> constexpr inline auto ReceiverObject::qt_create_metaobjectdata<qt_meta_tag_ZN14ReceiverObjectE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ReceiverObject",
        "serverStatusChanged",
        "",
        "message",
        "warning",
        "sendMessage",
        "text",
        "startServerScreencast",
        "stopServerScreencast",
        "startScreencast",
        "stopScreencast",
        "setUdpAddress",
        "addr",
        "getUdpAddress",
        "onNewConnection",
        "onReadyRead",
        "onUdpDataReceived",
        "onClientDisconnected",
        "hasActiveClient",
        "sendPacket",
        "type",
        "data",
        "writeUdpDatagram",
        "QByteArray&",
        "sendChunks",
        "QList<DataChunk>",
        "chunks",
        "writeUdpTest"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'serverStatusChanged'
        QtMocHelpers::SignalData<void(QString)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'warning'
        QtMocHelpers::SignalData<void(QString)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'sendMessage'
        QtMocHelpers::SlotData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Slot 'startServerScreencast'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'stopServerScreencast'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'startScreencast'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'stopScreencast'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setUdpAddress'
        QtMocHelpers::SlotData<void(QString)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
        // Slot 'getUdpAddress'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onNewConnection'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onReadyRead'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onUdpDataReceived'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onClientDisconnected'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'hasActiveClient'
        QtMocHelpers::SlotData<bool()>(18, 2, QMC::AccessPrivate, QMetaType::Bool),
        // Slot 'sendPacket'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 20 }, { QMetaType::QString, 21 },
        }}),
        // Slot 'sendPacket'
        QtMocHelpers::SlotData<void(const QString &)>(19, 2, QMC::AccessPrivate | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 20 },
        }}),
        // Slot 'writeUdpDatagram'
        QtMocHelpers::SlotData<void(QByteArray &)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 23, 21 },
        }}),
        // Slot 'sendChunks'
        QtMocHelpers::SlotData<void(const QVector<DataChunk> &)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 25, 26 },
        }}),
        // Slot 'writeUdpTest'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ReceiverObject, qt_meta_tag_ZN14ReceiverObjectE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ReceiverObject::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ReceiverObjectE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ReceiverObjectE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14ReceiverObjectE_t>.metaTypes,
    nullptr
} };

void ReceiverObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ReceiverObject *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->serverStatusChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->warning((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->sendMessage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->startServerScreencast(); break;
        case 4: _t->stopServerScreencast(); break;
        case 5: _t->startScreencast(); break;
        case 6: _t->stopScreencast(); break;
        case 7: _t->setUdpAddress((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->getUdpAddress(); break;
        case 9: _t->onNewConnection(); break;
        case 10: _t->onReadyRead(); break;
        case 11: _t->onUdpDataReceived(); break;
        case 12: _t->onClientDisconnected(); break;
        case 13: { bool _r = _t->hasActiveClient();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->sendPacket((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 15: _t->sendPacket((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->writeUdpDatagram((*reinterpret_cast<std::add_pointer_t<QByteArray&>>(_a[1]))); break;
        case 17: _t->sendChunks((*reinterpret_cast<std::add_pointer_t<QList<DataChunk>>>(_a[1]))); break;
        case 18: _t->writeUdpTest(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ReceiverObject::*)(QString )>(_a, &ReceiverObject::serverStatusChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ReceiverObject::*)(QString )>(_a, &ReceiverObject::warning, 1))
            return;
    }
}

const QMetaObject *ReceiverObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReceiverObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ReceiverObjectE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ReceiverObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void ReceiverObject::serverStatusChanged(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ReceiverObject::warning(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP
