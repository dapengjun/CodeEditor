#ifndef CEFILE_H
#define CEFILE_H

#include <string>
#include <iostream>
#include <fstream>

class CEFile
{
public:
    CEFile();
    ~CEFile();

    bool save();      // 保存操作
    bool loadFile();

    string &getFileName();
    void setFileName(string &fileName);
    bool isUntitled();
    void setUntitled(bool is);
    string &getText();
    void setText(const string &text);

private:
    // 为真表示文件没有保存过，为假表示文件已经被保存过了
    bool mIsUntitled;
    // 保存当前文件的路径
    string mFileName;
    string mText;

    fstream *mFile;
};

#endif // CEFILE_H
