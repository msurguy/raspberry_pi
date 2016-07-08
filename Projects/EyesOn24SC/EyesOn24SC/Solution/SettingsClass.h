#ifndef SETTINGSCLASS_H
#define SETTINGSCLASS_H
#include <QString>

class SettingsClass
{
public:
    QString configFilePath;
    QString currentImagePath;
    int resolutionWidth;
    int resolutionHeight;
    int frameRate;
    QString monitorOnlyConfPath;
    QString motionConfPath;
};
#endif // SETTINGSCLASS_H
