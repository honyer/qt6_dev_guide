#include "tperson.h"

TPerson::TPerson(QString name, QObject *parent)
{
    m_name = name;
}

int TPerson::age()
{
    return m_age;
}

void TPerson::setAge(int val)
{
    if (m_age != val) {
        m_age = val;
        emit ageChanged(m_age);
    }
}

void TPerson::incAge()
{
    m_age++;
    emit ageChanged(m_age);
}
