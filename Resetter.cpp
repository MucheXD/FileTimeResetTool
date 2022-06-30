#include "Resetter.h"

Resetter::Resetter(QWidget* parent)
    : QWidget(parent)
{
    ui_resetter.setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去除系统边框
    this->setWindowOpacity(0.8);//设置窗体透明度(80%)
    setWindowHeightMode(false);//设置短窗口
    //初始信号连接
    connect(ui_resetter.pushButton_close, &QPushButton::clicked, this, &QWidget::close);
    connect(ui_resetter.pushButton_setZero, &QPushButton::clicked, this, &Resetter::methodChanged);
    connect(ui_resetter.pushButton_setRandom, &QPushButton::clicked, this, &Resetter::methodChanged);
    connect(ui_resetter.pushButton_setInput, &QPushButton::clicked, this, &Resetter::methodChanged);
    connect(ui_resetter.pushButton_randomSet , &QPushButton::clicked, this, &Resetter::methodChanged);
    connect(ui_resetter.pushButton_created, &QPushButton::clicked, this, &Resetter::modeChanged);
    connect(ui_resetter.pushButton_modified, &QPushButton::clicked, this, &Resetter::modeChanged);
    connect(ui_resetter.pushButton_accessed, &QPushButton::clicked, this, &Resetter::modeChanged);
    connect(ui_resetter.pushButton_selectAll, &QPushButton::clicked, this, &Resetter::selectAllMode);
    connect(ui_resetter.pushButton_randomTime, &QPushButton::clicked, this, &Resetter::setRandomTime);
    connect(ui_resetter.pushButton_start, &QPushButton::clicked, this, &Resetter::startReset);
}

void Resetter::setWindowHeightMode(bool isDetailed)//设置窗体高度(展开与不展开)
{
    if (isDetailed == false)
    {
        ui_resetter.widget_background->setFixedHeight(180);
        ui_resetter.widget_inner->setFixedHeight(140);
        this->setFixedHeight(180);
    }
    else
    {
        ui_resetter.widget_background->setFixedHeight(220);
        ui_resetter.widget_inner->setFixedHeight(180);
        this->setFixedHeight(220);
    }
}

void Resetter::getAllFileList(int argc, char* argv[])//[公共]从main接过传参表并执行分析
{
    QStringList argFileList;
    int nPos = 1;//忽略0号位的自身目录
    while (nPos < argc)//建立文件表
    {
        argFileList.append(QDir::fromNativeSeparators(QString::fromLocal8Bit(argv[nPos])));
        nPos += 1;
    }
    if (argFileList.count() == 0)//无文件情况
    {
        fullWindowInfo* fwi = new fullWindowInfo;
        fwi->setParent(ui_resetter.widget_inner);
        fwi->setInfo("nofile", QString("Please use drag-launch or cmd-launch.").arg(workList.size()));
        fwi->show();
        return;
    }
    QStringList fileList = getAllFilesInList(argFileList);//开始递归遍历所有文件
    nPos = 0;
    while (nPos < fileList.count())//构建工作列表
	{
		WORKINFO work;
		work.fileName = fileList[nPos];
		workList.push_back(work);
        nPos += 1;
	}
    ui_resetter.label_topBar->setText(QString("Collected Files: %1").arg(workList.size()));
}

QStringList Resetter::getAllFilesInList(QStringList list , uint depth)//遍历获取一列文件(包括目录)下的全部子文件
{
    QFileInfo fileInfo;
    int nPos = 0;
    while (nPos < list.count())//循环列表中的每一项
    {
        fileInfo.setFile(list.at(nPos));//聚焦当前项
        if (fileInfo.isDir() == true)//如果是目录则展开操作
        {
            list.remove(nPos);
            nPos -= 1;
            QStringList filesInDir;
            QDir dir;
            dir.setPath(fileInfo.filePath());
            filesInDir = dir.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs);//遍历目录下的所有项
            int nAddPath = 0;
            while (nAddPath < filesInDir.count())//为遍历出的项补全路径
            {
                filesInDir[nAddPath] = fileInfo.filePath() + "/" + filesInDir.at(nAddPath);
                nAddPath += 1;
            }
            QStringList subList;
            if (depth >= 96)//深度过深(要么是程序BUG, 要么是用户在套娃)
            {
                fullWindowInfo* fwi = new fullWindowInfo;
                fwi->setParent(ui_resetter.widget_inner);
                fwi->setInfo("rtd", QString("Recursive went too deep. There might be too much folder."));
                fwi->show();
                return list;
            }
            subList = getAllFilesInList(filesInDir, depth + 1);//递归调用获取目录下...目录内的项
            int subNPos = 0;
            while (subNPos < subList.count())//收集归并到列表
            {
                list.insert(nPos + 1, subList.at(subNPos));
                subNPos += 1;
            }
            nPos += subList.count();
        }
        nPos += 1;
    }
    return list;
}

void Resetter::methodChanged(void)//方式(左选项)更改
{
    ui_resetter.widget_mode->setEnabled(true);
    ui_resetter.pushButton_next->setEnabled(true);
    if (ui_resetter.pushButton_setInput->isChecked())
        setWindowHeightMode(true);
    else
        setWindowHeightMode(false);
}

void Resetter::modeChanged(void)//应用模式(右选项)更改
{
    if (ui_resetter.pushButton_created->isChecked() && ui_resetter.pushButton_modified->isChecked() && ui_resetter.pushButton_accessed->isChecked())
        ui_resetter.pushButton_selectAll->setChecked(true);
    else
        ui_resetter.pushButton_selectAll->setChecked(false);
    if (ui_resetter.pushButton_created->isChecked() || ui_resetter.pushButton_modified->isChecked() || ui_resetter.pushButton_accessed->isChecked())
        ui_resetter.pushButton_start->setEnabled(true);
    else
        ui_resetter.pushButton_start->setEnabled(false);
}

void Resetter::selectAllMode(void)//全选应用模式(右选项)按钮按下
{
    if (ui_resetter.pushButton_selectAll->isChecked())
    {
        ui_resetter.pushButton_created->setChecked(true);
        ui_resetter.pushButton_modified->setChecked(true);
        ui_resetter.pushButton_accessed->setChecked(true);
    }
    else
    {
        ui_resetter.pushButton_created->setChecked(false);
        ui_resetter.pushButton_modified->setChecked(false);
        ui_resetter.pushButton_accessed->setChecked(false);
    }
    modeChanged();
}

QDateTime Resetter::randDateTime()//生成一个随机时间
{
    QDateTime dateTime;
    srand(QDateTime::currentDateTime().toMSecsSinceEpoch());
    dateTime.setMSecsSinceEpoch(__rdtsc() * rand() * (uint)(sin(clock() % 178 + 1) * 0xFFFF) % 0xE00000000000);
    return dateTime;
}

void Resetter::setRandomTime()//将日期时间编辑框置为随机时间
{
    ui_resetter.dateTimeEdit_timeInput->setDateTime(randDateTime());
}

FILETIME Resetter::qDateTimeToFileTime(QDateTime dateTime)//从QDateTime转换至FILETIME
{
    //FILETIME的值表示自1601年1月1日开始的100纳秒为单位的时间
    uint64_t hnsecs = 10000 * QDateTime(QDate(1601, 1, 1), QTime(0, 0, 0, 0), Qt::UTC).msecsTo(dateTime);
    FILETIME result;
    result.dwLowDateTime = hnsecs;//设置低位
    result.dwHighDateTime = (hnsecs >> 32);//移位至高位设置
    return result;
}

void Resetter::startReset()
{
    //禁用UI, 进入工作状态
    ui_resetter.pushButton_close->setEnabled(false);
    ui_resetter.pushButton_start->setEnabled(false);
    ui_resetter.pushButton_close->setText("Working");

    int nW = 0;//当前工作项
    int totalErr = 0;//总计错误数
    QDateTime dateTime;
    if (ui_resetter.pushButton_setZero->isChecked())//置零模式
        dateTime.setMSecsSinceEpoch(0);
    if (ui_resetter.pushButton_setInput->isChecked())//输入模式
        dateTime = ui_resetter.dateTimeEdit_timeInput->dateTime();
    
    while (nW < workList.size())
    {
        HANDLE hFile;//文件指针
        hFile = CreateFileW(workList.at(nW).fileName.toStdWString().c_str(),
            GENERIC_READ | GENERIC_WRITE,//打开方式: 读写
            FILE_SHARE_READ | FILE_SHARE_WRITE,//共享方式: 读写
            NULL,//安全指针: 空
            OPEN_EXISTING,//读取方式: 现有文件
            FILE_ATTRIBUTE_NORMAL,//属性方式: 一般
            NULL);//继承句柄: 否

        FILETIME fileTime;
        workList.at(nW).isSucceed = true;//先默认没有错误, 接下来只要有环节出现问题都会改为false
        if (ui_resetter.pushButton_randomSet->isChecked())//统一随机模式
            dateTime = randDateTime();
        if (ui_resetter.pushButton_setRandom->isChecked())//全随机模式(下面还有3段)
            dateTime = randDateTime();
        fileTime = qDateTimeToFileTime(dateTime);
        if (ui_resetter.pushButton_created->isChecked())//设置指定时间属性, 下同
            if (!SetFileTime(hFile, &fileTime, NULL, NULL))
            {
                workList.at(nW).isSucceed = false;
                totalErr += 1;
            }
        if (ui_resetter.pushButton_setRandom->isChecked())
            dateTime = randDateTime();
        fileTime = qDateTimeToFileTime(dateTime);
        if (ui_resetter.pushButton_modified->isChecked())
            if(!SetFileTime(hFile, NULL, NULL, &fileTime))
            {
                workList.at(nW).isSucceed = false;
                totalErr += 1;
            }
        if (ui_resetter.pushButton_setRandom->isChecked())
            dateTime = randDateTime();
        fileTime = qDateTimeToFileTime(dateTime);
        if (ui_resetter.pushButton_accessed->isChecked())//accessed必须在最后, 否则失效
            if (!SetFileTime(hFile, NULL, &fileTime, NULL))
            {
                workList.at(nW).isSucceed = false;
                totalErr += 1;
            }
        CloseHandle(hFile);//关闭文件
        nW += 1;//指针移动到下一个工作项
    }
    //恢复UI
    ui_resetter.pushButton_close->setEnabled(true);
    ui_resetter.pushButton_start->setEnabled(true);
    ui_resetter.pushButton_close->setText("Close");

    //进入完成窗口
    setWindowHeightMode(false);
    ui_resetter.pushButton_start->setText("Finish");
    ui_resetter.pushButton_close->setVisible(false);
    connect(ui_resetter.pushButton_start, &QPushButton::clicked, this, &QWidget::close);
    ui_resetter.label_topBar->setText("Finished");
    fullWindowInfo* fwi = new fullWindowInfo;
    fwi->setParent(ui_resetter.widget_inner);
    if (totalErr == 0)
        fwi->setInfo("finish", QString("%1 files successfully processed.").arg(workList.size()));
    else
    {
        int nW = 0;
        int failedFileCount = 0;
        while (nW < workList.size())
        {
            if (workList.at(nW).isSucceed == false)
                failedFileCount += 1;
            nW += 1;
        }
        fwi->setInfo("failed", QString("%2/%1 files went wrong, %3 Errs in total.").arg(workList.size()).arg(failedFileCount).arg(totalErr));
    }
    fwi->show();
}

void Resetter::mouseMoveEvent(QMouseEvent* mouseEvent)//鼠标拖动事件
{
	if (mouseEvent->y() <= ui_resetter.label_topBar->y() + ui_resetter.label_topBar->height())
	{
		if (slideWindowCenter.x == -1)//若无滑动中心则设置滑动中心
		{
			slideWindowCenter.x = mouseEvent->x();
			slideWindowCenter.y = mouseEvent->y();
		}
        //根据滑动中心动态设置窗口位置 滑动中心指首次移动是鼠标相对与窗口的位置
		this->setGeometry(mouseEvent->globalX() - slideWindowCenter.x, mouseEvent->globalY() - slideWindowCenter.y, this->width(), this->height());
	}
}

void Resetter::mouseReleaseEvent(QMouseEvent* mouseEvent)//鼠标释放事件
{
    //重置滑动中心
    slideWindowCenter.x = -1;
    slideWindowCenter.y = -1;
}

Resetter::~Resetter()
{}

//#############################################################################

fullWindowInfo::fullWindowInfo(QWidget* parent)
    : QWidget(parent)
{
    ui_fwi.setupUi(this);
}

void fullWindowInfo::setInfo(QString mode, QString subText)
{
    //设置全屏信息
	if (mode == "finish")
	{
		ui_fwi.pushButton_main->setIcon(QIcon(":/Res/finish.svg"));
		ui_fwi.pushButton_main->setText("  Finished");
		ui_fwi.label_sub->setText(subText);
	}
    if (mode == "failed")
    {
        ui_fwi.pushButton_main->setIcon(QIcon(":/Res/failed.svg"));
        ui_fwi.pushButton_main->setText("  Errs occurred");
        ui_fwi.label_sub->setText(subText);
    }
    if (mode == "nofile")
    {
        ui_fwi.pushButton_main->setIcon(QIcon(":/Res/failed.svg"));
        ui_fwi.pushButton_main->setText("  No File");
        ui_fwi.label_sub->setText(subText);
    }
    if (mode == "rtd")
    {
        ui_fwi.pushButton_main->setIcon(QIcon(":/Res/criticalErr.svg"));
        ui_fwi.pushButton_main->setText("  Critical Error");
        ui_fwi.label_sub->setText(subText);
    }
    if (mode == "crash")
    {
        ui_fwi.pushButton_main->setIcon(QIcon(":/Res/criticalErr.svg"));
        ui_fwi.pushButton_main->setText("  Crashed");
        ui_fwi.label_sub->setText(subText);
    }
}

fullWindowInfo::~fullWindowInfo()
{}