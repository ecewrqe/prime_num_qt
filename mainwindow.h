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
#include<list>
#include <algorithm>


#include <iterator>

#include "prime_num.h"
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
    void toggle_prime();
    void toggle_prime(int);
    void judge_onclick();
    void toggle_happy(int);
    void make_data();


signals:
    void clicked();

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

    QTableWidget *table;

    // 素数判定
    QLineEdit *judge_edit;
    QPushButton *judgeOkButton;
    QLabel *judgeMsg;

};
#endif // MAINWINDOW_H
