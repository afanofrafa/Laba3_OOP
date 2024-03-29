#include "weapon.h"
#include <random>
int getRandomInt(int min_value, int max_value) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min_value, max_value);
    return dis(gen);
}
QVector<QPoint> generatePointsAroundCenter(int n, float radius, float centerX, float centerY) {
    QVector<QPoint> points;
    float angleIncrement = 2 * M_PI / n;
    float angle = 0.0;

    for (int i = 0; i < n; ++i) {
        float randomAngle = ((float)rand() / RAND_MAX) * 0.7 - 0.2;
        float currentAngle = angle + randomAngle;

        QPoint p;
        p.setX(centerX + radius * cos(currentAngle));
        p.setY(centerY + radius * sin(currentAngle));
        points.push_back(p);
        angle += angleIncrement;
    }

    return points;
}
vector<QString> Weapon::GetInfo() {
    return Info;
}
QString Weapon::GetInfoByIndex(int index) {
    if (!Info.empty()) {
        int size = Info.size();
        if (index < 0)
            return Info[0];
        if (index >= size)
            return Info[size - 1];
        return Info[index];
    }
    else
        return "Error. Data is empty";
}
void Weapon::SetInfoByIndex(int index, QString strInfo) {
    if (index < Info.size() && index >= 0)
        Info[index] = strInfo;
}
void Weapon::SetNewInfo(QString strInfo) {
    Info.push_back(strInfo);
}
Weapon::Weapon()
{
    if (createNum == INT32_MAX)
        createNum = 0;
    else
        id = createNum++;
    if (count == INT32_MAX)
        count = 0;
    else
        count++;
}
unsigned int Weapon::GetInfoSize() {
    return Info.size();
}
Weapon::~Weapon()
{
    count--;
}

int Weapon::GetID()
{
    return id;
}

int Weapon::GetCount()
{
    return count;
}
int Weapon::count = 0;
int Weapon::createNum = 0;
