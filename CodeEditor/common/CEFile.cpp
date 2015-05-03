#include "CEFile.h"

CEFile::CEFile()
{
    // 初始化文件为未保存状态
    mIsUntitled = true;
    // 初始化文件名为"未命名.txt"
    mFileName = "untitled";
    mFile = NULL;
}

CEFile::~CEFile()
{
    if (mFile)
    {
        mFile->close;
        delete mFile;
        mFile = NULL;
    }
}

QString &CEFile::getFileName()
{
    return this->mFileName;
}

void CEFile::setFileName(QString &fileName)
{
    this->mFileName = fileName;
}

bool CEFile::isUntitled()
{
    return this->mIsUntitled;
}

void CEFile::setUntitled(bool is)
{
    this->mIsUntitled = is;
}

QString &CEFile::getText()
{
    return mText;
}

void CEFile::setText(const QString &text)
{
    mText = text;
}

bool CEFile::save()
{
    if (mFile)
    {
        mFile->close();
        delete mFile;
        mFile = NULL;
    }
    mFile = new QFile(mFileName);
    if (!mFile->open(QFile::WriteOnly | QFile::Text))
    {
        delete mFile;
        mFile = NULL;
        return false;
    }
    QTextStream out(mFile);
    out << mText;
    mFile->close();
    delete mFile;
    mFile = NULL;
    return true;
}


bool CEFile::loadFile()
{
    if (mFile)
    {
        mFile->close();
        delete mFile;
        mFile = NULL;
    }
    mFile = new QFile(mFileName);
    if (!mFile->open(QFile::ReadOnly | QFile::Text))
    {
        delete mFile;
        mFile = NULL;
        return false;
    }
    QTextStream in(mFile);
    mText = QString(in.readAll());
    mFile->close();
    delete mFile;
    mFile = NULL;
    return true;
}
