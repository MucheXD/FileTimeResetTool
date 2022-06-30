#pragma once

#include <QtWidgets/QWidget>
#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <vector>
#include <QMouseEvent>
#include <QMimedata>
#include <QProcess>
#include <Windows.h>

#include "global.h" 
#include "ui_ResetterW.h"
#include "ui_fullWindowInfo.h"


class Resetter : public QWidget
{
    Q_OBJECT

public:
    Resetter(QWidget* parent = nullptr);
    void getAllFileList(int argc, char* argv[]);
    ~Resetter();

private:
    Ui::ResetterClass ui_resetter;
    QStringList fileList;
    std::vector<WORKINFO> workList;
    //bool isTopBarDown = false;
    POSITION slideWindowCenter;

    void setWindowHeightMode(bool isDetailed);
    QStringList getAllFilesInList(QStringList list, uint depth = 0);
    void methodChanged();
    void modeChanged();
    void selectAllMode();
    QDateTime randDateTime();
    void setRandomTime();
    FILETIME qDateTimeToFileTime(QDateTime dateTime);
    void startReset();
    void mouseMoveEvent(QMouseEvent* mouseEvent);
    void mouseReleaseEvent(QMouseEvent* mouseEvent);
};

//#############################################################################

class fullWindowInfo : public QWidget
{
    Q_OBJECT

public:
    fullWindowInfo(QWidget* parent = nullptr);
    void setInfo(QString mode, QString subText);
    ~fullWindowInfo();

private:
    Ui::fullWindowInfoClass ui_fwi;
};

