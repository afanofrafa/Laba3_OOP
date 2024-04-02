#ifndef ENCRYPTION_H
#define ENCRYPTION_H
//#include "Encryption_global.h"
#include <QString>
#include <QByteArray>

class __declspec(dllexport) Encryption
{
public:
    Encryption();
    void encrypt();
    void decrypt();
    void set_key(QByteArray key);
    void set_filePath(QString path);
private:
    QString filePath;
    QByteArray key;
    QByteArray byteArray;
    QByteArray Column_Improved(int tt_length, int tk_length, QByteArray true_text, QByteArray true_key, bool IsCypher);
    QByteArray Stolb_encryption(int tk_length, int tt_length, QByteArray true_text, int arr_ind[]);
    QByteArray Stolb_decryption(int tk_length, int tt_length, QByteArray true_text, int arr_ind[]);
    int findMin(QByteArray str, int arr[], int len);
    bool IsUsed(int arr[], int ind, int len);
    void execute(bool isCypher);
};

extern "C" __declspec(dllexport) Encryption *createEncryptionInstance();
extern "C" __declspec(dllexport) void destroyEncryptionInstance(Encryption* instance);

#endif // ENCRYPTION_H
