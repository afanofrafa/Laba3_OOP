#ifndef WEAPONTYPES_H
#define WEAPONTYPES_H
#pragma once
#include "weapon.h"
class Firearm : public Weapon {
private:
    int ammoType;
    QString modelName;
    const QString WeaponType = "огнестрельное оружие";
    int PistolsCapacity;
    int CurrentPistolsCapacity;
    QVector<QPoint> genShoot(int i);
public:
    Firearm();
    Firearm(int AmmoType, QString ModelName, int PistolCapacity, int CurrentPistolCapacity, int shootSpeed, int reloadSpeed, int cleanSpeed);

    QString operator [] (int index) override;

    static void playSound(QString Url, QMediaPlayer *mediaPlayer);

    void SetPistolCapacity(int PistolsCapacity);
    int GetPistolCapacity();

    void SetCurrentPistolCapacity(int CurrentPistolsCapacity);
    int GetCurrentPistolCapacity();

    int GetAmmoType();
    void SetAmmoType(int ammoType);

    QString GetModelName();
    void SetModelName(QString modelName);

    void SetInfo(int AmmoType, QString ModelName, int PistolCapacity, int CurrentPistolCapacity, int shootSpeed, int reloadSpeed, int cleanSpeed);

    int get_attackSpeed(int action) override;
    void set_attackSpeed(int value, int action) override;
    int get_MKUSpeed(int action) override;
    void set_MKUSpeed(int value, int action) override;

    //virtual void accept(Visitor* visitor, QString actionName) override = 0;
    QVector<QPoint> Attack(int action) override;
    QVector<QPoint> MakeWeaponUsable(int action) override;
    virtual QVector<QPoint> Shoot(int action, QString Url);
    virtual QVector<QPoint> Reload(QString Url);
    virtual QVector<QPoint> Clean(QString Url);

protected:
    int shootSpeed;
    int reloadSpeed;
    int cleanSpeed;
public:
    int get_shootSpeed();
    void set_shootSpeed(int value);

    int get_reloadSpeed();
    void set_reloadSpeed(int value);

    int get_cleanSpeed();
    void set_cleanSpeed(int value);

    ~Firearm() override;
};

#endif // WEAPONTYPES_H
