#pragma once

#include <QObject>

class TPerson : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("author", "wang") // 定义类的附加信息
    Q_CLASSINFO("company", "GNU")
    Q_CLASSINFO("version", "1.0.0.0")
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged) // 定义属性age
    Q_PROPERTY(QString name MEMBER m_name)                      // 定义属性name
    Q_PROPERTY(int score MEMBER m_score)                        // 定义属性score
public:
    explicit TPerson(QString name, QObject *parent = nullptr);
    int age();
    void setAge(int val);
    void incAge(); // increase age
signals:
    void ageChanged(int val);

private:
    int m_age = 10;
    int m_score = 79;
    QString m_name;
};

