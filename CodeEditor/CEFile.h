#ifndef CEFILE_H
#define CEFILE_H

#include <QString>
#include <QFile>

class CEFile
{
public:
    CEFile();
    ~CEFile();

    bool save();      // 保存操作

    QString &getFileName();
    void setFileName(QString &fileName);
    bool isUntitled();
    void setUntitled(bool is);
    QString &getText();
    void setText(const QString &text);

private:
    // 为真表示文件没有保存过，为假表示文件已经被保存过了
    bool mIsUntitled;
    // 保存当前文件的路径
    QString mFileName;
    QString mText;

    QFile *mFile;
};

#endif // CEFILE_H
