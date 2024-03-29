#ifndef WEAPON_H
#define WEAPON_H
#pragma once
#include <iostream>
#include <QPushButton>
#include <QtMultimedia>
using namespace std;
int getRandomInt(int min_value, int max_value);
QVector<QPoint> generatePointsAroundCenter(int n, float radius, float centerX, float centerY);
class Firearm;
class BladedWeapon;
class Visitor {
public:
    virtual void visit(Firearm* firearm, QString actionName) = 0;
};
class Weapon {
private:
    static int count;
    static int createNum;
    int id;
    vector<QString> Info;
public:
    Weapon();
    virtual ~Weapon();
    virtual int get_attackSpeed(int action) = 0;
    virtual void set_attackSpeed(int value, int action) = 0;
    virtual int get_MKUSpeed(int action) = 0;
    virtual void set_MKUSpeed(int value, int action) = 0;
    int GetID();
    static int GetCount();
    vector<QString> GetInfo();
    unsigned int GetInfoSize();
    virtual QString operator [] (int index) = 0;
    QString GetInfoByIndex(int index);
    void SetInfoByIndex(int index, QString strInfo);
    void SetNewInfo(QString strInfo);
    virtual QVector<QPoint> Attack(int action) = 0;
    virtual QVector<QPoint> MakeWeaponUsable(int action) = 0;
    virtual void accept(Visitor* visitor, QString actionName) = 0;

};
#endif // WEAPON_H
