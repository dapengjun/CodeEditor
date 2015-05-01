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
    mFile.setText(text);
    this->document()->setModified(false);
    return mFile.save();
}

bool CETextEdit::loadFile()
{
    int index;

    mFile.loadFile();
    mFile.setUntitled(false);
    const QString &text = mFile.getText();
    this->setText(text);
    this->document()->setModified(false);
    index = mTabWidget->indexOf(this);
    mTabWidget->setTabText(index, mTabTitle);
    return true;
}

QString &CETextEdit::getFileName()
{
    return mFile.getFileName();
}

void CETextEdit::setFileName(QString &fileName)
{
    mFile.setFileName(fileName);
    mTabTitle = QFileInfo(fileName).fileName();
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
