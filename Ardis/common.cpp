#include "common.h"

Common* Common::m_instance = nullptr;

Common::Common(QObject *parent)
    : QObject{parent}
{
}
Common* Common::instance(){
    if(!m_instance){
        m_instance = new Common();
    }
    return m_instance;
}

void Common::debug(const QString& message){
    emit debugSignal(message);
}
