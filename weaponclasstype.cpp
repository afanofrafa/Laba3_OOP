#include "weaponclasstype.h"
#include <QTimer>
QTimer *timerA = nullptr;
QTimer *timerB = nullptr;
Gun::Gun() : Firearm(6, "Пистолет", 9, 9, 190, 2500, 2500, 0, 0)
{
}
Gun::~Gun()
{
}
QVector<QPoint> Gun::Shoot(int action, QString Url) {
    QVector<QPoint> v = Firearm::Shoot(GetAmmoType(), "qrc:/sounds/DeagleShot.mp3");
    timerA->start(shootSpeed);
    return v;
}
QVector<QPoint> Gun::Reload(QString Url) {
    Firearm::Reload("qrc:/sounds/DeagleReload.mp3");
    timerB->start(reloadSpeed);
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> Gun::Clean(QString Url) {
    Firearm::Clean("qrc:/sounds/DeagleClean.mp3");
    timerB->start(cleanSpeed);
    QVector<QPoint> v;
    return v;
}
void Gun::accept(Visitor* visitor, QString actionName) {
    visitor->visit(this, actionName);
}
MachineGun::MachineGun() : Firearm(5, "Автомат", 100, 100, 100, 3000, 2500, 0, 0)
{
}
MachineGun::~MachineGun()
{
}
void MachineGun::accept(Visitor* visitor, QString actionName) {
    visitor->visit(this, actionName);
}
QVector<QPoint> MachineGun::Shoot(int action, QString Url) {
    QVector<QPoint> v = Firearm::Shoot(GetAmmoType(), "qrc:/sounds/MachineGunShot.mp3");
    timerA->start(shootSpeed);
    return v;
}
QVector<QPoint> MachineGun::Reload(QString Url) {
    Firearm::Reload("qrc:/sounds/MachineGunReload.mp3");
    timerB->start(reloadSpeed);
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> MachineGun::Clean(QString Url) {
    Firearm::Clean("qrc:/sounds/MachineGunClean.mp3");
    timerB->start(cleanSpeed);
    QVector<QPoint> v;
    return v;
}
Rifle::Rifle() :  Firearm(8, "Винтовка", 9, 9, 1500, 5000, 2500, 0, 0)
    {
    };
Rifle::~Rifle()
    {
    };
void Rifle::accept(Visitor* visitor, QString actionName) {
    visitor->visit(this, actionName);
}
QVector<QPoint> Rifle::Shoot(int action, QString Url) {
    QVector<QPoint> v = Firearm::Shoot(GetAmmoType(), "qrc:/sounds/VintovkaShot.mp3");
    timerA->start(shootSpeed);
    return v;
}
QVector<QPoint> Rifle::Reload(QString Url) {
    Firearm::Reload("qrc:/sounds/RifleReload.mp3");
    timerB->start(reloadSpeed);
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> Rifle::Clean(QString Url) {
    Firearm::Clean("qrc:/sounds/RifleClean.mp3");
    timerB->start(cleanSpeed);
    QVector<QPoint> v;
    return v;
}
ShotGun::ShotGun() : Firearm(13, "Дробовик", 7, 7, 1950, 5000, 2500, 0, 0)
{
}

ShotGun::~ShotGun()
{
}
void ShotGun::accept(Visitor* visitor, QString actionName) {
    visitor->visit(this, actionName);
}
QVector<QPoint> ShotGun::Shoot(int action, QString Url) {
    QVector<QPoint> v = Firearm::Shoot(GetAmmoType(), "qrc:/sounds/ShotGunShot.mp3");
    timerA->start(shootSpeed);
    return v;
}
QVector<QPoint> ShotGun::Reload(QString Url) {
    Firearm::Reload("qrc:/sounds/ShotGunReload.mp3");
    timerB->start(reloadSpeed);
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> ShotGun::Clean(QString Url) {
    Firearm::Clean("qrc:/sounds/ShotGunClean.mp3");
    timerB->start(cleanSpeed);
    QVector<QPoint> v;
    return v;
}
