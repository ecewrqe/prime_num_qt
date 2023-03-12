/**
 * prime number cplus main window
 *
 * @author			euewrqe
 * @version        v1.1
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QTableWidget>
#include <QStringList>
#include <QString>
#include <QAbstractItemView>
#include <QHeaderView>
#include <Qt>
#include<QtCore/QDebug>
#include <QProgressBar>
#include<list>
#include <algorithm>
#include<QMessageBox>
#include<iostream>


#include <iterator>

#include "prime_num.h"
#include "ProgessBarThread.h"
#include "TableMakeThread.h"
#include "NumTransfer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void make_table();

public slots:
    void toggle_prime(int);
    void judge_onclick();
    void toRomanOnclick();
    void toggle_happy(int);
    void make_data();
    void proSendValue(long long prime_size, long long min_num, long long max_num);
    void makeHeadItem(long long row, QString item);
    void makeBodyItem(long long row, long long col, QString item);
    void setRenderValue(long long renderValue);
    void setPrimeValue(long long primeValue);

signals:
    void clicked();
    void getRenderTotalNum(int total);
    void sendValueToMakeTable(long long, long long, bool, bool);

public slots:
    

    void onProgress(int);

private:
    Ui::MainWindow *ui;
    QWidget *widget;
    QVBoxLayout *layout;

    bool happy;
    bool prime;

    QLabel *label;
    // 最大数＆最小数
    QLineEdit *min_num_edit;
    QLineEdit *max_num_edit;

    // checkbox row
    QHBoxLayout *checkbox_layout;
    // 素数？
    QCheckBox *is_prime_check;
    // happy?
    QCheckBox *is_happy_check;

    // 素数二次元表
    QPushButton *tableOkButton;
    QLabel *tableMsg;
    QLabel *tableTitle;

    // プログレス
    QHBoxLayout* renderLayout;
    QProgressBar* renderProBar;
    
    QHBoxLayout* primeLayout;
    QProgressBar* primeProBar;
    QLabel* renderTotal;
    QLabel* renderLabel;
    QLabel* renderCount;
    QLabel* primeTotal;
    QLabel* primeLabel;
    QLabel* primeCount;

    int renderedCount;
    ProgressBarThread probarT;
    QMetaObject::Connection emit_value;

    TableMakeThread *tableMakeThread;

    QTableWidget *table;
    QTableWidgetItem* bodyItem;
    QTableWidgetItem* headerItem;

    // 素数判定
    QLineEdit *judge_edit;
    QPushButton *judgeOkButton;
    QLabel *judgeMsg;

    // ローマ数字へ転換
    QLineEdit *arabicNumEdit;
    QPushButton *toRomanButton;
    QLabel *romanNumOutput;
};
#endif // MAINWINDOW_H
