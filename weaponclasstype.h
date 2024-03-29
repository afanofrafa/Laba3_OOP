#ifndef WEAPONCLASSTYPE_H
#define WEAPONCLASSTYPE_H
#pragma once
#include "weapontypes.h"
class Gun : public Firearm {
private:
    QVector<QPoint> Shoot(int action, QString Url) override;
    QVector<QPoint> Reload(QString Url) override;
    QVector<QPoint> Clean(QString Url) override;
public:
    Gun();
    ~Gun() override;
    void accept(Visitor* visitor, QString actionName) override;
};
class MachineGun : public Firearm {
private:
    QVector<QPoint> Shoot(int action, QString Url) override;
    QVector<QPoint> Reload(QString Url) override;
    QVector<QPoint> Clean(QString Url) override;
public:
    MachineGun();
    ~MachineGun() override;
    void accept(Visitor* visitor, QString actionName) override;
};
class Rifle : public Firearm {
private:
    QVector<QPoint> Shoot(int action, QString Url) override;
    QVector<QPoint> Reload(QString Url) override;
    QVector<QPoint> Clean(QString Url) override;
public:
    Rifle();
    ~Rifle() override;
    void accept(Visitor* visitor, QString actionName) override;
};
class ShotGun : public Firearm {
private:
    QVector<QPoint> Shoot(int action, QString Url) override;
    QVector<QPoint> Reload(QString Url) override;
    QVector<QPoint> Clean(QString Url) override;
public:
    ShotGun();
    ~ShotGun() override;
    void accept(Visitor* visitor, QString actionName) override;
};
#endif // WEAPONCLASSTYPE_H
