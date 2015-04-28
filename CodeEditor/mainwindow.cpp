#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "CETextEdit.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString fileName;
    ui->setupUi(this);
    ui->tabWidget->setMovable(true);
    ui->tabWidget->setTabsClosable(false);
    fileName = "untitled";
    loadFile(fileName, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loadFile(QString &fileName, bool isNew)
{
    QString tabTitle;
    int index = 0;
    CETextEdit *textEdit = NULL;

    if (isNew)
    {
        tabTitle = fileName;
        textEdit = new CETextEdit(ui->tabWidget);
        index = ui->tabWidget->addTab(textEdit, tabTitle);
        ui->tabWidget->setCurrentIndex(index);
        ui->tabWidget->setTabEnabled(index, true);
        ui->tabWidget->setTabToolTip(index, fileName);
        setWindowTitle(fileName);
    }
    else
    {
        textEdit = new CETextEdit(ui->tabWidget);
        textEdit->setFileName(fileName);
        tabTitle = textEdit->getTabTitle();
        index = ui->tabWidget->addTab(textEdit, tabTitle);
        ui->tabWidget->setCurrentIndex(index);
        ui->tabWidget->setTabEnabled(index, true);
        ui->tabWidget->setTabToolTip(index, fileName);
        setWindowTitle(fileName);
    }
    return true;
}

bool MainWindow::maybeSave()
{
    CETextEdit *textEdit = NULL;

    textEdit = (CETextEdit *)ui->tabWidget->currentWidget();
    // 如果文档被更改了
    if (textEdit && textEdit->document()->isModified()) {
        // 自定义一个警告对话框
        QMessageBox box;
        box.setWindowTitle(tr("warning"));
        box.setIcon(QMessageBox::Warning);
        box.setText(textEdit->getTabTitle() + tr(" is not save. save?"));
        QPushButton *yesBtn = box.addButton(tr("yes(&Y)"),
                         QMessageBox::YesRole);
        box.addButton(tr("no(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBut = box.addButton(tr("cancel"),
                         QMessageBox::RejectRole);
        box.exec();
        if ((QPushButton *)box.clickedButton() == yesBtn)
             return save();
        else if ((QPushButton *)box.clickedButton() == cancelBut)
             return false;
    }
    // 如果文档没有被更改，则直接返回true
    return true;
}

void MainWindow::newFile()
{
    if (maybeSave())
    {
        QString fileName;
        fileName = "untitled";
        loadFile(fileName, true);
    }
}

bool MainWindow::saveAs()
{
    bool ret = true;
    CETextEdit *textEdit = NULL;

    QString fileName = QFileDialog::getSaveFileName(this,
                                          tr("Save As"));
    textEdit = (CETextEdit *)ui->tabWidget->currentWidget();
    textEdit->setFileName(fileName);
    textEdit->setUntitled(false);
    save();
    return ret;
}

bool MainWindow::save()
{
    bool ret = true;
    CETextEdit *textEdit = NULL;

    textEdit = (CETextEdit *)ui->tabWidget->currentWidget();
    if (textEdit->isUntitled())
    {
        QString fileName = QFileDialog::getSaveFileName(this,
                                              tr("Save As"));
        if (fileName.isEmpty())
        {
            return false;
        }
        textEdit->setFileName(fileName);
        textEdit->setUntitled(false);
    }

    // 鼠标指针变为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ret = textEdit->save();
    // 鼠标指针恢复原来的状态
    QApplication::restoreOverrideCursor();

    setWindowTitle(textEdit->getTabTitle());
    return ret;
}

bool MainWindow::closeTab(int index)
{
    if (maybeSave())
    {
        QTextEdit *textEdit = NULL;
        textEdit = (QTextEdit *)ui->tabWidget->widget(index);
        ui->tabWidget->removeTab(index);
        delete textEdit;
    }
    return true;
}

void MainWindow::setApp(QApplication *app)
{
    mApp = app;
}

void MainWindow::on_aNewFile_triggered()
{
    newFile();
}

void MainWindow::on_aSave_triggered()
{
    save();
}

void MainWindow::on_aSaveAs_triggered()
{
    saveAs();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    closeTab(index);
}

void MainWindow::on_tabWidget_tabBarDoubleClicked(int index)
{
    closeTab(index);
}

void MainWindow::on_aCloseFile_triggered()
{
    int index;

    index = ui->tabWidget->currentIndex();
    closeTab(index);
}

void MainWindow::on_aCloseAllFile_triggered()
{
    int count = ui->tabWidget->count();

    for (int i=count-1;i>=0;i--)
    {
        closeTab(i);
    }
}

void MainWindow::on_aQuit_triggered()
{
    on_aCloseAllFile_triggered();
    mApp->quit();
}
