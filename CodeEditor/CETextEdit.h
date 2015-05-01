#ifndef CETEXTEDIT_H
#define CETEXTEDIT_H

#include <QTextEdit>
#include <QTabWidget>
#include "CEFile.h"

class CETextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit CETextEdit(QWidget *parent = 0);
    ~CETextEdit();

    bool save();      // 保存操作
    bool loadFile();

    QString &getFileName();
    void setFileName(QString &fileName);
    bool isUntitled();
    void setUntitled(bool is);

    QString &getTabTitle();

signals:

public slots:
    void textChanged();

private:
    QTabWidget *mTabWidget;
    CEFile mFile;
    QString mTabTitle;
};

#endif // CETEXTEDIT_H
