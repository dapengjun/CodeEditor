#include "CEFile.h"
#include <string.h>

using namespace std;

CEFile::CEFile()
{
    // 初始化文件为未保存状态
    mIsUntitled = true;
    // 初始化文件名为"未命名.txt"
    mFileName = "untitled";
}

CEFile::~CEFile()
{
    if (mfs.is_open())
    {
        mfs.close();
    }
}

string &CEFile::getFileName()
{
    return this->mFileName;
}

void CEFile::setFileName(string &fileName)
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

string &CEFile::getText()
{
    return mText;
}

void CEFile::setText(const string &text)
{
    mText = text;
}

bool CEFile::save()
{
    if (mfs.is_open())
    {
        mfs.close();
    }
    mfs.open(mFileName.c_str(), ios::trunc|ios::out);
    if (!mfs.is_open())
    {
        return false;
    }
    mfs << mText;
    mfs.close();
    return true;
}


bool CEFile::loadFile()
{
    char buf[256];
    if (mfs.is_open())
    {
        mfs.close();
    }
    mText.clear();
    mfs.open(mFileName.c_str(), ios::in);
    if (!mfs.is_open())
    {
        return false;
    }
    if (!mfs.eof())
    {
        memset(buf, 0, sizeof(buf));
        mfs.read(buf, sizeof(buf)-1);
        mText.append(buf);
    }
    mfs.close();
    return true;
}
