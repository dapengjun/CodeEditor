#include "CETextEdit.h"
#include <QFileInfo>

CETextEdit::CETextEdit(QWidget *parent) :
    QTextEdit(parent)
{
    mTabWidget = (QTabWidget *)parent;
    mTabTitle = "untitled";
    connect(this, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

CETextEdit::~CETextEdit()
{
    mTabWidget = NULL;
}

void CETextEdit::textChanged()
{
    int index;
    QString tabTitle;

    index = mTabWidget->indexOf(this);
    tabTitle = mTabTitle;
    if (this->document()->isModified())
    {
        tabTitle.append("*");
    }
    mTabWidget->setTabText(index, tabTitle);
}

bool CETextEdit::save()
{
    int index;
    const QString &text = this->toPlainText();

    index = mTabWidget->indexOf(this);
    mTabWidget->setTabText(index, mTabTitle);
    mFile.setText(text.toStdString());
    this->document()->setModified(false);
    return mFile.save();
}

bool CETextEdit::loadFile()
{
    int index;

    mFile.loadFile();
    mFile.setUntitled(false);
    QString text;
    text = text.fromStdString(mFile.getText());
    this->setText(text);
    this->document()->setModified(false);
    index = mTabWidget->indexOf(this);
    mTabWidget->setTabText(index, mTabTitle);
    return true;
}

QString &CETextEdit::getFileName()
{
    static QString fileName;
    fileName.clear();
    fileName.fromStdString(mFile.getFileName());
    return fileName;
}

void CETextEdit::setFileName(QString &fileNameQ)
{
    string fileNameS;
    fileNameS = fileNameQ.toStdString();
    mFile.setFileName(fileNameS);
    mTabTitle = QFileInfo(fileNameQ).fileName();
}

bool CETextEdit::isUntitled()
{
    return mFile.isUntitled();
}

void CETextEdit::setUntitled(bool is)
{
    mFile.setUntitled(is);
}

QString &CETextEdit::getTabTitle()
{
    return mTabTitle;
}
