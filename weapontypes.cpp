#include "weapontypes.h"
QMediaPlayer *mediaPlayer = nullptr;
QMediaPlayer *mediaPlayer2 = nullptr;
extern QPointF widgetPos;
extern int pixmapX;
extern int pixmapY;
bool Aim;
double count_distance(int x, int y, int cx, int cy) {
    return sqrt(pow(x - cx, 2) + pow(y - cy, 2));
}
QVector<QPoint> Firearm::genShoot(int n) {
    double r = n;
    QVector<QPoint> small = generatePointsAroundCenter(n, r, widgetPos.x() - pixmapX, widgetPos.y() - pixmapY);
    QVector<QPoint> big = generatePointsAroundCenter(n, r * 2, widgetPos.x() - pixmapX, widgetPos.y() - pixmapY);
    QVector<QPoint> vect;
    for (int i = 0; i < n; i++) {
        vect.push_back(small.at(i));
        vect.push_back(big.at(i));
    }
    return vect;
}
void Firearm::playSound(QString Url, QMediaPlayer *mediaPlayer) {
    if (mediaPlayer != nullptr && mediaPlayer->isPlaying()) {
        mediaPlayer->stop();
        delete mediaPlayer;
    }
    mediaPlayer = new QMediaPlayer;
    mediaPlayer->setSource(QUrl(Url));
    mediaPlayer->setAudioOutput(new QAudioOutput);
    mediaPlayer->play();
}
Firearm::Firearm()
{
    SetInfo(93, "Flamethrower", 40, 40, 1000, 2000, 1000);
}
Firearm::Firearm(int AmmoType, QString ModelName, int PistolCapacity, int CurrentPistolCapacity, int shootSpeed, int reloadSpeed, int cleanSpeed) {
    SetInfo(AmmoType, ModelName, PistolCapacity, CurrentPistolCapacity, shootSpeed, reloadSpeed, cleanSpeed);
}
void Firearm::SetInfo(int AmmoType, QString ModelName, int PistolCapacity, int CurrentPistolCapacity, int shootSpeed, int reloadSpeed, int cleanSpeed) {
    this->ammoType = AmmoType;
    this->modelName = ModelName;
    this->PistolsCapacity = PistolCapacity;
    this->CurrentPistolsCapacity = CurrentPistolCapacity;
    this->shootSpeed = shootSpeed;
    this->reloadSpeed = reloadSpeed;
    this->cleanSpeed = cleanSpeed;

    SetNewInfo("Калибр: " + QString::number(GetAmmoType()) + "мм");
    SetNewInfo(GetModelName());
    SetNewInfo("Вместимость магазина: " + QString::number(GetPistolCapacity()));
    SetNewInfo("Количество оставшихся патронов: " + QString::number(GetCurrentPistolCapacity()));
    SetNewInfo("Тип оружия: " + this->WeaponType);
    SetNewInfo("Выстрелов в секунду: " + QString::number(1000.0 / shootSpeed, 'f', 2));
    SetNewInfo("Время перезарядки: " + QString::number(reloadSpeed / 1000.0, 'f', 2) + "с");
    SetNewInfo("Время чистки: " + QString::number(cleanSpeed / 1000.0, 'f', 2) + "с");
}
QString Firearm::operator [] (int index) { //Не ипользую ссылку для лишения возможности присваивания через индекс
    return Weapon::GetInfoByIndex(index);
}
int Firearm::GetAmmoType()
{
    return ammoType;
}
int Firearm::get_cleanSpeed() {
    return cleanSpeed;
}

void Firearm::set_cleanSpeed(int value) {
    this->cleanSpeed = value;
}
int Firearm::get_reloadSpeed() {
    return reloadSpeed;
}

void Firearm::set_reloadSpeed(int value) {
    this->reloadSpeed = value;
}
int Firearm::get_shootSpeed() {
    return shootSpeed;
}

void Firearm::set_shootSpeed(int value) {
    this->shootSpeed = value;
}
void Firearm::SetAmmoType(int ammoType)
{
    this->ammoType = ammoType;
}
QString Firearm::GetModelName()
{
    return modelName;
}
void Firearm::SetModelName(QString modelName)
{
    this->modelName = modelName;
}
QVector<QPoint> Firearm::Clean(QString Url) {
    playSound(Url, mediaPlayer);
    QVector<QPoint> v;
    return v;
}
void Firearm::SetPistolCapacity(int PistolsCapacity) {
    this->PistolsCapacity = PistolsCapacity;
}
int Firearm::GetPistolCapacity() {
    return PistolsCapacity;
}
void Firearm::SetCurrentPistolCapacity(int CurrentPistolsCapacity) {
    this->CurrentPistolsCapacity = CurrentPistolsCapacity;
}
int Firearm::GetCurrentPistolCapacity() {
    return CurrentPistolsCapacity;
}
QVector<QPoint> Firearm::Reload(QString Url) {
    CurrentPistolsCapacity = PistolsCapacity;
    playSound(Url, mediaPlayer);
    SetInfoByIndex(3, "Количество оставшихся патронов: " + QString::number(CurrentPistolsCapacity));
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> Firearm::Shoot(int action, QString Url) {
    QVector<QPoint> vect;
    if (CurrentPistolsCapacity > 0) {
        CurrentPistolsCapacity--;
        playSound(Url, mediaPlayer);
        if (count_distance(widgetPos.x(), widgetPos.y(), pixmapX + 50, pixmapY + 50) <= 50.001) {
            playSound("qrc:/sounds/Penetration.mp3", mediaPlayer2);
            vect = genShoot(action);
        }
    }
    SetInfoByIndex(3, "Количество оставшихся патронов: " + QString::number(CurrentPistolsCapacity));
    return vect;
}
QVector<QPoint> Firearm::Attack(int action) {
    switch (action) {
    case 0:
        return Shoot(action, "");

        break;
    default:
        break;
    }
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> Firearm::MakeWeaponUsable(int action) {
    switch (action) {
    case 1:
        return Reload("");

        break;
    case 2:
        return Clean("");

        break;
    default:
        break;
    }
    QVector<QPoint> v;
    return v;
}
int Firearm::get_attackSpeed(int action) {
    return get_shootSpeed();
}
void Firearm::set_attackSpeed(int value, int action) {
    set_shootSpeed(value);
}

int Firearm::get_MKUSpeed(int action) {
    switch (action) {
    case 1:
        return get_reloadSpeed();
        break;
    case 2:
        return get_cleanSpeed();
        break;
    default:
        break;
    }
    return -1;
}
void Firearm::set_MKUSpeed(int value, int action) {
    switch (action) {
    case 1:
        set_reloadSpeed(value);
        break;
    case 2:
        set_cleanSpeed(value);
        break;
    default:
        break;
    }
}
Firearm::~Firearm() {

}
