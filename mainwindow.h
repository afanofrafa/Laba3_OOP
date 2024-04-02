#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <functional>
#include <map>
#include <QMainWindow>
#include "weaponclasstype.h"
#include <windows.h>
#include <QScreen>
#include <QSize>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>
#include <QEvent>
#include <QByteArray>
#define WeaponTypesCount 4
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow;
class DrawVisitor : public Visitor {
public:
    MainWindow *mainWindow;
    DrawVisitor(MainWindow *mainWindow) {
        this->mainWindow = mainWindow;
    };
    ~DrawVisitor() {};

    void drawFigureFire(QPixmap& pixmap, QVector<QPoint>& points);

    void visit(Firearm* firearm, QString actionName) override;
};
class Soldier : public DrawVisitor {
private:
    vector<Weapon*> weapons;
    QString Attack = "Attack";
    QString MakeWeaponUsable = "MakeWeaponUsable";
public:
    QString get_attack_str();
    QString get_make_weapon_usable_str();
    unordered_map<QString, pair<QVector<QPoint> (Firearm::*)(int), QString>> fireMap;
    Soldier(MainWindow *mainWindow) : DrawVisitor(mainWindow) {
        fireMap["Стрелять"] = {&Firearm::Attack, Attack};
        fireMap["Перезарядить"] = {&Firearm::MakeWeaponUsable, MakeWeaponUsable};
        fireMap["Почистить"] = {&Firearm::MakeWeaponUsable, MakeWeaponUsable};
    }

    void useWeapon(Firearm* weapon, QString actionName);
private:
    template<typename WeaponType>
    QVector<QPoint> useWeapon(WeaponType* weapon, QString actionName, unordered_map<QString, pair<QVector<QPoint> (WeaponType::*)(int), QString>>& actionMap);
    void show_action(void (DrawVisitor::*drawFunc)(QPixmap& pixmap, QVector<QPoint>& points), QVector<QPoint> figure);
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Soldier soldier;
    //DrawVisitor drawVisitor;
    QPixmap pixmap;
    void setPixmapPosition(int x, int y);
    void setPixmap(const QPixmap &newPixmap);
    void setLibraries(const vector<pair<HINSTANCE, QString>> &libs);
    bool checkLibraries(vector<pair<HINSTANCE, QString>> &libs);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void doAfterAction();

    void doAction();

    void on_pushButton_Buy_clicked();

    void on_pushButton_Throw_clicked();

    void on_comboBox_WeaponList_currentIndexChanged(int index);

    void on_pushButton_start_clicked();

    void drawTarget();

    void stopShooting();

    bool checkActionAttack();

    void on_pushButton_Meth_1_clicked();

    void on_pushButton_Meth_2_clicked();

private:
    Ui::MainWindow *ui;
    vector<pair<HINSTANCE, QString>> libraries;
    int const iconSize = 150;
    struct wepData {
        QString wepName;
        QString wepImgPath;
        function<Weapon*()> wepType;
    };
    //QPushButton button;
    map<int, wepData> wepMap;
    vector<Weapon*> weapon_vect;
    map<QString, QString> map_verify;
    QString generateSignature(const QString filePath);
    bool verifySignature(const QString filePath, QString expectedSignature);
};
#endif // MAINWINDOW_H
