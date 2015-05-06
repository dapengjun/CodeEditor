#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CEFile.h"
#include <QMap>
#include <QTextEdit>
#include <QCloseEvent>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void newFile();   // 新建操作
    bool loadFile(QString &fileName, bool isNew);
    bool save(int index = -1);      // 保存操作
    bool saveAs();    // 另存为操作
    bool maybeSave();
    bool closeTab(int index);

    void setApp(QApplication *app);

protected:
    void closeEvent(QCloseEvent *event); // 关闭事件

private slots:
    void on_aNewFile_triggered();

    void on_aSave_triggered();

    void on_aSaveAs_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_tabBarDoubleClicked(int index);

    void on_aCloseFile_triggered();

    void on_aCloseAllFile_triggered();

    void on_aQuit_triggered();

    void on_aOpenFile_triggered();

    void on_aSaveAll_triggered();

    void on_aOpenFolder_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel mTvModel;
    QApplication *mApp;
};

#endif // MAINWINDOW_H
