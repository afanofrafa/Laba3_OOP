#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include <QTimer>
Ui::MainWindow *u;
bool action;
extern QTimer *timerA;
extern QTimer *timerB;
QTimer *timerZ;
QTimer *timer_notAttack;
QTimer *timerStart;
extern QMediaPlayer *mediaPlayer;
extern QMediaPlayer *mediaPlayer2;
extern bool Aim;
bool moveRight = true;
bool isAttack;
bool fl;
QString button_action;
QPointF widgetPos;
int pixmapX = 0;
int pixmapY = 0;
unordered_map<QString, int> actNum;
list<QPushButton*> listButtons;
void SetButtonsEnabled() {
    if (u->pushButton_Meth_2->isEnabled() != fl) {
        u->pushButton_Meth_1->setEnabled(fl);
        u->pushButton_Meth_2->setEnabled(fl);
        u->pushButton_start->setEnabled(fl);
        u->listWidget_Info->setEnabled(fl);
        u->label_Info->setEnabled(fl);
    }
}
void SetButtonsVisible() {
    if (u->pushButton_Meth_2->isEnabled() != fl) {
        u->pushButton_Meth_1->setVisible(fl);
        u->pushButton_Meth_2->setVisible(fl);
        u->pushButton_start->setVisible(fl);
        u->listWidget_Info->setVisible(fl);
        u->label_Info->setVisible(fl);
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white); // Заливаем фон виджета белым цветом
    painter.drawPixmap(pixmapX, pixmapY, pixmap); // Рисуем pixmap по заданным координатам
    painter.drawRect(QRect(280, 10, 930, 700));
}

void DrawVisitor::drawFigureFire(QPixmap& pixmap, QVector<QPoint>& points) {
    QPainter painter(&pixmap);
    int count = points.size();
    painter.setRenderHint(QPainter::Antialiasing); // Устанавливаем сглаживание для лучшего качества рисунка
    painter.setPen(Qt::black); // Устанавливаем цвет линии
    // Создаем путь, используя переданные точки
    QPainterPath path;
    path.moveTo(points.at(0));
    for (int i = 1; i < count; ++i)
        path.lineTo(points.at(i));
    path.closeSubpath();
    // Закрашиваем область, ограниченную путем, в белый цвет
    painter.fillPath(path, Qt::white);
    // Рисуем линии
    for (int i = 0; i < count - 1; ++i)
        painter.drawLine(points.at(i), points.at(i + 1));
    painter.drawLine(points.last(), points.first());
    painter.end();
    mainWindow->setPixmap(pixmap);
}

void Soldier::show_action(void (DrawVisitor::*drawFunc)(QPixmap& pixmap, QVector<QPoint>& points), QVector<QPoint> figure) {
    if (!figure.empty()) {
        (this->*drawFunc)(mainWindow->pixmap, figure);
    }
}
template<typename WeaponType>
void getButtonNames(unordered_map<QString, pair<QVector<QPoint> (WeaponType::*)(int), QString>>& actionMap) {
    auto actionIter = actionMap.begin();
    auto buttonIter = listButtons.begin();
    for (; (buttonIter != listButtons.end()) && (actionIter != actionMap.end()); buttonIter++, actionIter++) {
        (*buttonIter)->setText(actionIter->first);
    }
}
template<typename WeaponType>
QVector<QPoint> Soldier::useWeapon(WeaponType* weapon, QString actionName, unordered_map<QString, pair<QVector<QPoint> (WeaponType::*)(int), QString>>& actionMap) {
    fl = true;
    SetButtonsVisible();
    SetButtonsEnabled();
    getButtonNames(actionMap);
    QVector<QPoint> figure;
    auto it = actionMap.find(actionName);
    if (it != actionMap.end()) {
        if (it->second.second == Attack)
            isAttack = true;
        else
            isAttack = false;
        figure = (weapon->*(it->second.first))(actNum[actionName]);
    }
    int len = weapon->GetInfoSize();
    u->listWidget_Info->clear();
    for (int i = 0; i < len; i++) {
        QListWidgetItem *listItem = new QListWidgetItem;
        listItem->setText((*weapon)[i]);
        u->listWidget_Info->addItem(listItem);
    }
    return figure;
}

QString Soldier::get_attack_str()
{
    return Attack;
}

QString Soldier::get_make_weapon_usable_str()
{
    return MakeWeaponUsable;
}

void Soldier::useWeapon(Firearm* weapon, QString actionName) {
    show_action(&DrawVisitor::drawFigureFire, useWeapon(weapon, actionName, fireMap));
};

void DrawVisitor::visit(Firearm* firearm, QString actionName) {
    mainWindow->soldier.useWeapon(firearm, actionName);
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), soldier(this)
{
    ui->setupUi(this);
    u = ui;
    update();
    timerA = new QTimer(this);
    timerB = new QTimer(this);
    timerZ = new QTimer(this);
    timerStart = new QTimer(this);
    listButtons.push_back(ui->pushButton_Meth_1);
    listButtons.push_back(ui->pushButton_Meth_2);
    connect(timerA, SIGNAL(timeout()), this, SLOT(doAction()));
    connect(timerStart, SIGNAL(timeout()), this, SLOT(drawTarget()));
    QScreen *screen = QGuiApplication::primaryScreen();
    QSize screenSize = screen->size();
    this->setFixedSize(screenSize);
    this->move(0, 0);
    actNum["Стрелять"] = 0;
    actNum["Перезарядить"] = 1;
    actNum["Почистить"] = 2;

    ui->label_BuyNum->setText("0");
    wepMap[0] = {"Автомат", ":/img/AKM.png", []() { return new MachineGun; }};
    wepMap[1] = {"Пистолет", ":/img/Deagle.jpg", []() { return new Gun; }};
    wepMap[2] = {"Дробовик", ":/img/Drobovik.png", []() { return new ShotGun; }};
    wepMap[3] = {"Винтовка", ":/img/Vintovka.jpg", []() { return new Rifle; }};
    ui->comboBox_ChooseWeapon->setIconSize(QSize(iconSize, iconSize));
    ui->comboBox_WeaponList->setIconSize(QSize(iconSize, iconSize));
    for (int i = 0; i < WeaponTypesCount; i++) {
        ui->comboBox_ChooseWeapon->addItem(QIcon(wepMap[i].wepImgPath), wepMap[i].wepName);
    }
    fl = false;
    SetButtonsVisible();
    SetButtonsEnabled();
}

MainWindow::~MainWindow()
{
    u->listWidget_Info->clear();
    delete mediaPlayer;
    delete mediaPlayer2;
    delete timerA;
    delete timerB;
    delete timerZ;
    delete timerStart;
    delete ui;
}
void MainWindow::drawTarget() {
    int sp = ui->spinBox_speed->value();
    if (moveRight) {
        setPixmapPosition(pixmapX, pixmapY);
        pixmapX += sp;
        if (pixmapX >= 1110)
            moveRight = false;
    }
    else {
        setPixmapPosition(pixmapX, pixmapY);
        pixmapX -= sp;
        if (pixmapX <= 280)
            moveRight = true;
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && timerStart->isActive() && !action && !timerA->isActive() && !weapon_vect.empty()) {
        QPointF globalPos = event->globalPosition();
        widgetPos = mapFromGlobal(globalPos);
        if (widgetPos.x() >= 280 && widgetPos.y() >= 10 && widgetPos.x() <= 1210 && widgetPos.y() <= 710) {
            button_action = "Стрелять";
            action = true;
            doAction();
        }
        else
            doAfterAction();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (button_action == "Стрелять")
        doAfterAction();
}

void MainWindow::setPixmapPosition(int x, int y)
{
    pixmapX = x;
    pixmapY = y;
    update(); // Перерисовываем виджет
}

void MainWindow::setPixmap(const QPixmap &newPixmap)
{
    pixmap = newPixmap;
    update(); // Перерисовываем виджет
}


void MainWindow::on_pushButton_Buy_clicked()
{
    auto iterator = wepMap.find(ui->comboBox_ChooseWeapon->currentIndex());
    if (iterator != wepMap.end()) {
        auto weapon = iterator->second.wepType();
        weapon_vect.push_back(weapon);
        ui->comboBox_WeaponList->addItem(QIcon(iterator->second.wepImgPath), iterator->second.wepName);
        ui->label_BuyNum->setText(QString::number(weapon->GetCount()));
    }
}


void MainWindow::on_pushButton_Throw_clicked()
{
    if (!weapon_vect.empty()) {
        int index = ui->comboBox_WeaponList->currentIndex();
        auto weapon = weapon_vect.at(index);
        int count = weapon->GetCount() - 1;
        ui->label_BuyNum->setText(QString::number(count));
        weapon_vect.erase(weapon_vect.begin() + index);
        ui->comboBox_WeaponList->removeItem(index);
        delete weapon;
    }
}

void MainWindow::on_comboBox_WeaponList_currentIndexChanged(int index)
{
    if (!weapon_vect.empty()) {
        auto weapon = weapon_vect.at(index);
        weapon->accept(&soldier, "");
    }
    else {
        fl = false;
        SetButtonsVisible();
        SetButtonsEnabled();
    }
}
bool MainWindow::checkActionAttack() {
    auto it = soldier.fireMap.find(button_action);
    if (it == soldier.fireMap.end())
        return false;
    if (it->second.second != "Attack")
        return true;
    if (widgetPos.x() < 280 || widgetPos.x() > 1210 || widgetPos.y() < 10 || widgetPos.y() > 710)
        return false;
    else
        return true;
}
void MainWindow::doAction() {
    QPoint globalPos = QCursor::pos();
    widgetPos = mapFromGlobal(globalPos);
    if (checkActionAttack()) {
        auto weapon = weapon_vect.at(ui->comboBox_WeaponList->currentIndex());
        weapon->accept(&soldier, button_action);
    }
    else
        mouseReleaseEvent(nullptr);
}
void allow_attack() {
    action = false;
}
void MainWindow::doAfterAction() {
    fl = false;
    QTimer *timer = nullptr;
    if (!isAttack)
        timer = timerB;
    else
        timer = timerA;
    SetButtonsEnabled();
    fl = true;
    timerZ->singleShot(timer->remainingTime(), this, SetButtonsEnabled);
    timer_notAttack->singleShot(timer->remainingTime(), this, allow_attack);
    timer->stop();
}


void MainWindow::stopShooting() {
    timerStart->stop();
    setPixmap(QPixmap());
    ui->pushButton_start->setText("Старт");
}
void MainWindow::on_pushButton_start_clicked()
{
    if (timerStart->isActive()) {
        stopShooting();
    }
    else {
        setPixmap(QPixmap(":/img/target4.jpg"));
        setPixmapPosition(280, 50);
        timerStart->start(1);
        moveRight = true;
        ui->pushButton_start->setText("Завершить");
    }
}


void MainWindow::on_pushButton_Meth_1_clicked()
{
    button_action = ui->pushButton_Meth_1->text();
    action = true;
    doAction();
    doAfterAction();
}


void MainWindow::on_pushButton_Meth_2_clicked()
{
    button_action = ui->pushButton_Meth_2->text();
    action = true;
    doAction();
    doAfterAction();
}

