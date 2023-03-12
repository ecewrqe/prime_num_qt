/**
 * prime number cplus main window
 *
 * @author			euewrqe
 * @version        v1.1
 *
 */

#include "mainwindow.h"
#include "valueerror.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("素数の検証");
    this->setFixedSize(QSize(1200, 700));
    this->setWindowIcon(QIcon(":/new/prefix1/prime_num.ico"));

    this->widget = new QWidget();
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->layout = new QVBoxLayout();

    this->happy = false;
    this->prime = true;

    // 最大数＆最小数
    this->label = new QLabel("最小数：");
    this->layout->addWidget(this->label);
    this->min_num_edit = new QLineEdit();
    this->min_num_edit->setText("17610");
    this->layout->addWidget(this->min_num_edit);

    this->label = new QLabel("最大数：");
    this->layout->addWidget(this->label);
    this->max_num_edit = new QLineEdit();
    this->max_num_edit->setText("20024");
    this->layout->addWidget(this->max_num_edit);

    // 並べる
    this->checkbox_layout = new QHBoxLayout();
    this->is_prime_check = new QCheckBox("素数？");
    this->is_prime_check->setChecked(this->prime);
    this->checkbox_layout->addWidget(this->is_prime_check);
    connect(this->is_prime_check, &QCheckBox::clicked, this, [this]{toggle_prime(this->prime);});

    // connect a event
    this->is_happy_check = new QCheckBox("ハッピー？");
    this->is_happy_check->setChecked(this->happy);
    this->checkbox_layout->addWidget(this->is_happy_check);
    // connect a event
    this->layout->addLayout(this->checkbox_layout);
    connect(this->is_happy_check, &QCheckBox::clicked, this, [this]{toggle_happy(this->happy);});


    // button
    this->tableOkButton = new QPushButton("確定");
    this->layout->addWidget(this->tableOkButton);
    connect(this->tableOkButton, &QPushButton::clicked, this, [this]{make_data();});


    this->tableMsg = new QLabel("");
    this->tableMsg->setStyleSheet("color: black");
    this->layout->addWidget(this->tableMsg);

    this->tableTitle = new QLabel("素数表");
    this->tableTitle->setAlignment(Qt::AlignCenter);
    this->layout->addWidget(this->tableTitle);

    
    // pro make
    this->make_table();
    // render count
    this->renderLayout = new QHBoxLayout();
    this->renderLayout->setContentsMargins(0, 0, 20, 0);

    this->renderCount = new QLabel("0");
    this->renderLayout->addWidget(this->renderCount);

    this->renderLabel = new QLabel("総量");
    this->renderLabel->setAlignment(Qt::AlignCenter);
    this->renderLayout->addWidget(this->renderLabel);

    this->renderTotal = new QLabel("0");
    this->renderTotal->setAlignment(Qt::AlignRight);
    this->renderLayout->addWidget(this->renderTotal);

    this->layout->addLayout(this->renderLayout);


    // レンダー計数プログレスバー
    this->renderProBar = new QProgressBar();

    this->layout->addWidget(this->renderProBar);

    //QObject::connect(&probarT, SIGNAL(finished()), this, SLOT(quit()));
    //QObject::connect(this, SIGNAL(getRenderTotalNum(int)), &probarT, SLOT(setTotal(int)));
    //// スレッド
    //QObject::connect(&probarT, SIGNAL(progress(int)), this, SLOT(onProgress(int)));

    // prime count
    this->primeLayout = new QHBoxLayout();
    this->primeLayout->setContentsMargins(0, 0, 20, 0);

    this->primeCount = new QLabel("0");
    this->primeLayout->addWidget(this->primeCount);

    this->primeLabel = new QLabel("値の総量");
    this->primeLabel->setAlignment(Qt::AlignCenter);
    this->primeLayout->addWidget(this->primeLabel);

    this->primeTotal = new QLabel("0");
    this->primeTotal->setAlignment(Qt::AlignRight);
    this->primeLayout->addWidget(this->primeTotal);
    this->layout->addLayout(this->primeLayout);

    // 素数計数プログレスバー
    this->primeProBar = new QProgressBar();
    this->layout->addWidget(this->primeProBar);

    // 素数判定
    this->label = new QLabel("素数判定");
    this->layout->addWidget(this->label);
    this->judge_edit = new QLineEdit();
    this->layout->addWidget(this->judge_edit);
    this->judgeOkButton = new QPushButton("確定");
    connect(this->judgeOkButton, SIGNAL(clicked()), this, SLOT(judge_onclick()));

    this->layout->addWidget(this->judgeOkButton);

    this->judgeMsg = new QLabel("");
    this->judgeMsg->setStyleSheet("color:black");
    this->layout->addWidget(this->judgeMsg);

    // ローマン数字へ転換
    this->label = new QLabel("アラビア数字を入力し：");
    this->layout->addWidget(this->label);
    this->arabicNumEdit = new QLineEdit();
    this->layout->addWidget(this->arabicNumEdit);
    this->toRomanButton = new QPushButton("確定");
    connect(this->toRomanButton, SIGNAL(clicked()), this, SLOT(toRomanOnclick()));
    this->layout->addWidget(this->toRomanButton);
    this->romanNumOutput = new QLabel();
    this->romanNumOutput->setStyleSheet("color:black");
    this->layout->addWidget(this->romanNumOutput);

    this->widget->setLayout(this->layout);
    this->setCentralWidget(this->widget);

    tableMakeThread = new TableMakeThread();
    //tableMakeThread->moveToThread(tableMakeThread);



    // 作る前に準備
    QObject::connect(this, SIGNAL(sendValueToMakeTable(long long, long long, bool, bool)), tableMakeThread, SLOT(setValue(long long, long long, bool, bool)));
    QObject::connect(tableMakeThread, SIGNAL(proSendValue(long long, long long, long long)), this, SLOT(proSendValue(long long, long long, long long)));

    QObject::connect(tableMakeThread, SIGNAL(makeBodyItem(long long, long long, QString)), this, SLOT(makeBodyItem(long long, long long, QString)));
    QObject::connect(tableMakeThread, SIGNAL(makeBodyItem(long long, long long, QString)), this, SLOT(makeBodyItem(long long, long long, QString)));
    QObject::connect(tableMakeThread, SIGNAL(makeHeadItem(long long, QString)), this, SLOT(makeHeadItem(long long, QString)));

    QObject::connect(tableMakeThread, SIGNAL(getRenderValue(long long)), this, SLOT(setRenderValue(long long)));
    QObject::connect(tableMakeThread, SIGNAL(getPrimeValue(long long)), this, SLOT(setPrimeValue(long long)));



}

void MainWindow::make_table(){
    QStringList *column = new QStringList{"head", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    this->table = new QTableWidget();
    this->table->setColumnCount(column->size());
    this->table->setHorizontalHeaderLabels(*column);
    this->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Fixed);
    this->table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Fixed);
    this->layout->addWidget(this->table);
    this->table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->table->setColumnWidth(0,100);
          this->table->setColumnWidth(1,100);
          this->table->setColumnWidth(2,100);
          this->table->setColumnWidth(3,100);
}
#include <string>
void MainWindow::judge_onclick(){

    try{

        QString prime_num_str=this->judge_edit->text();
        bool ok;
        long long prime_num = prime_num_str.toLongLong(&ok);

        // throw error
        if(!ok){
            throw ValueError("数字ではない");
        }
        long long divitor;
        bool prime, happy;
        prime = is_prime_func(prime_num, divitor);
        happy = is_happy_func(prime_num);
        if(prime){
            this->judgeMsg->setText("素数");
            if(happy){
                this->judgeMsg->setText("素数且つハッピー素数");
            }
        }else{
            this->judgeMsg->setText(QString("素数ではない、少なくとも%1に割れる").arg(divitor));
            if(happy){
                this->judgeMsg->setText(QString("素数ではない、少なくとも%1に割れる、ハッピー数").arg(divitor));
            }
        }
        this->judgeMsg->setStyleSheet("color:black");

    }catch(ValueError ex){
        this->judgeMsg->setText("数字ではない");
        this->judgeMsg->setStyleSheet("color:red");
    }


}

void MainWindow::toRomanOnclick(){
    bool ok;
    long long num = (this->arabicNumEdit->text()).toLongLong(&ok);
    // throw error
    try{
        if(!ok){
            throw ValueError("数字を入力してください");
        }
        bool ok2;
        string result = to_roman_transfer(num, &ok2);
        cout << "ok?" << ok2 << endl;
        if(!ok2){
            throw NumLargeError("数字は十桁を超えた");
        }
        this->romanNumOutput->setText(QString::fromStdString(result));
        this->romanNumOutput->setStyleSheet("color:black");
    }
    catch(NumLargeError ex){
        this->romanNumOutput->setText("数字は十桁を超えた");
        this->romanNumOutput->setStyleSheet("color:red");
    }

    catch(ValueError ex){
        this->romanNumOutput->setText("数字を入力してください");
        this->romanNumOutput->setStyleSheet("color:red");
    }
}

void MainWindow::toggle_prime(int prime){
    this->prime = !prime;
    this->is_prime_check->setChecked(this->prime);

}
void MainWindow::toggle_happy(int happy){
    this->happy = !happy;
    this->is_happy_check->setChecked(this->happy);
}


void MainWindow::make_data(){
    
    this->table->clear();
    QStringList *column = new QStringList{"head", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

    this->table->setColumnCount(column->size());
    this->table->setHorizontalHeaderLabels(*column);

    if(this->happy && this->prime){
        this->tableTitle->setText("ハッピー素数表");
    }else if(this->prime){
        this->tableTitle->setText("素数表");
    }else if(this->happy){
        this->tableTitle->setText("ハッピー表");
    }
    bool oki = false, oka = false;

    QString min_num_str = this->min_num_edit->text();
    QString max_num_str = this->max_num_edit->text();
    try{
        long long min_num = min_num_str.toLongLong(&oki);
        long long max_num = max_num_str.toLongLong(&oka);
        if(!oki || !oka){
            throw ValueError("自然数しか受けない");
        }
        if(min_num > max_num){
            throw NumSmallError("");
        }
        if(!this->prime && !this->happy){
            throw PrimeCheckedError("");
        }
        this->tableMsg->setText("");
        this->tableMsg->setStyleSheet("color:black");

        // bar setting
        int renderSize = max_num - min_num;
        this->renderCount->setText("0");
        this->renderProBar->setMinimum(0);
        this->renderProBar->setMaximum(renderSize);
        this->renderTotal->setText(QString::number(renderSize));
        
        if (this->tableMakeThread->isRunning()) {
            this->tableMakeThread->terminate();
        }

        this->primeCount->setText("0");
        this->primeProBar->setMinimum(0);
        this->primeProBar->setMaximum(0);
        this->primeTotal->setText("0");

        //qDebug() << "send value" << max_num << min_num << happy << prime;
        emit sendValueToMakeTable(max_num, min_num, happy, prime);
        this->primeLabel->setText("値の総量、ローディング");
        
        
        this->tableMakeThread->start();

        
        
        

        
        
        

        // 素数取得してテーブルに表す、この段階はmultithread処理にする
        // 範囲説明を取得した後すぐにテーブル生成とプロバーをほかのスレッドにスタート合図を送る
        /*
        *                                      200   <-- レンダー数
          ||||||||||||||||||||||||||||||||||||||
                                               50    <-- 選出した数
        */

        // テーブル生成スタート合図を送る

        
        /*
        スレッド内：
        先ず素数リストを取得して素数量の合計をprime_totalに送る
        // プロバーレンダースタート合図を送る
        // テーブル生成始まる
        // テーブル生成の同時に例えば10000終わったら情報をテーブルに送る、
        同時に生成した量/総量の比例をプロバー監視しながらvalueに送る
        */
        // プロバー合図を送る、レンダー計数を準備する
        //this->renderedCount = 0;

        // 総数をスレッドに送る
        //emit getRenderTotalNum(this->renderTotal->text().toInt());
        // スレッドスタート合図を送る
        //probarT.start();
        
        

        // テーブルの値生成してからスレッドに合図する
        
        // 何か値を送る
        // QObject::connect(this, SIGNAL(sendValueToMakeTable), tableMakeThread, SLOT(setValues))
        // emit sendValueToMakeTable(xx,xx,xx)
        // 何を受ける
        /*qobject::connect(&tablemakethread, signal(makebodyitem), this, slot(makebodyitem));
        qobject::connect(&tablemakethread, signal(makeheaditem), this, slot(makeheaditem));*/
        // renderValue, primeValue
        /*QObject::connect(&tableMakeThread, SIGNAL(getRenderValue), this, SLOT(setRenderValue));
        QObject::connect(&tableMakeThread, SIGNAL(getPrimeValue), this, SLOT(setPrimeValue));*/
        // this->table->setItem(input_head,count % 10 + 1,bodyItem);

        //std::list<long long> prime_list = get_primenum_list(max_num, min_num, happy, prime);

        //int max_count_size = prime_list.size();
        //this->primeTotal->setText(QString::number(max_count_size));

        //long long count = min_num;
        //this->table->setRowCount((max_num + 10) / 10 - count / 10);

        //this->tableMakeThread.start();

        //std::list<long long>::iterator it = prime_list.begin();


        //long long head;
        //long long start_head;
        //long long input_head;
        //QTableWidgetItem* headerItem;
        //QTableWidgetItem* bodyItem;
        //head = min_num / 10;
        //start_head = min_num/10;
        //input_head = head - start_head;
        //count = head * 10;



        //// 間隔17609-17623, 176713-176741, 間隔 17610-17624
        //headerItem = new QTableWidgetItem(QString::number(head));
        //this->table->setItem(input_head,0, headerItem);

        //// 最小数行の最小数前の空欄を付ける
        //for(;count<min_num;count++){
        //    bodyItem = new QTableWidgetItem("-");
        //    this->table->setItem(input_head,count % 10 + 1,bodyItem);
        //}


        //while(count < max_num){
        //    
        //    if(it == prime_list.end()){
        //        for(;count < max_num; count++){
        //            
        //            bodyItem = new QTableWidgetItem("*");
        //            this->table->setItem(input_head,count % 10 + 1,bodyItem);
        //            if(count-head*10==10){
        //                head = count / 10;
        //                input_head = head - start_head;
        //                headerItem = new QTableWidgetItem(QString::number(head));
        //                this->table->setItem(input_head,0, headerItem);
        //            }
        //        }
        //        break;
        //    }
        //    // 空いた値を位置に付ける、結尾はheadか*itかの前は比較次第

        //    // headerすでに付けた、0-9をはんだんしつつ入れる
        //    for(;it != prime_list.end(); ){
        //        // 累加はちょうど*itと同じ場合は値を付ける、次は執行せずにitを次に進む
        //        if(count == *it){
        //            bodyItem = new QTableWidgetItem(QString::number(*it));
        //            // input_head, count % 10 + 1に置く
        //            this->table->setItem(input_head,count % 10 + 1,bodyItem);
        //            count++;
        //            it++;

        //            // 改行
        //            if(count-head*10==10){
        //                head = count / 10;
        //                input_head = head - start_head;
        //                headerItem = new QTableWidgetItem(QString::number(head));
        //                this->table->setItem(input_head,0, headerItem);
        //            }

        //            continue;
        //        }

        //        // tailは次のヘッドまたは*it
        //        int tail = *it;
        //        // head 数列の頭、input_head テーブルの頭、head - start_head = input_head
        //        // tail は 次の数列のヘッドより大きいの場合はまずこの行を補填する、故tailはこの行の末尾となる
        //        if(tail >= (head+1)*10){
        //            tail = (head+1)*10;
        //        }
        //        // countからtailまで空欄を付ける、付けずむとcountは次のhead相当
        //        for(;count<tail;count++){
        //            bodyItem = new QTableWidgetItem("*");
        //            this->table->setItem(input_head,count % 10 + 1,bodyItem);
        //        }
        //        // 付け済むと改行
        //        if(count-head*10==10){
        //            head = count / 10;
        //            input_head = head - start_head;
        //            headerItem = new QTableWidgetItem(QString::number(head));
        //            this->table->setItem(input_head,0, headerItem);
        //        }


        //    }
        //    // 最後の場合は、count
        //    // 最終の数から定義した最大範囲まで空いた値を付ける
        //    for(;count < max_num; count++){
        //        bodyItem = new QTableWidgetItem("*");
        //        this->table->setItem(input_head,count % 10 + 1,bodyItem);
        //        if(count-head*10==10){
        //            head = count / 10;
        //            input_head = head - start_head;
        //            headerItem = new QTableWidgetItem(QString::number(head));
        //            this->table->setItem(input_head,0, headerItem);
        //        }
        //    }

        //}


    }catch(ValueError ex){
        this->tableMsg->setText("自然数しか受けない");
        this->tableMsg->setStyleSheet("color:red");
    }catch(NumSmallError ex){
        this->tableMsg->setText("受けた数字が小さすぎる");
        this->tableMsg->setStyleSheet("color:red");
    }catch(PrimeCheckedError ex){
        this->tableMsg->setText("素数とハッピー少なくとも一種にチェックを付く");
        this->tableMsg->setStyleSheet("color:red");
    }
}

//int MainWindow::getRenderTotalNum() {
//    int n = this->renderTotal->text().toInt();
//    return n;
//}

void MainWindow::onProgress(int value){
    this->renderProBar->setValue(value);
    this->renderCount->setText(QString::number(this->renderedCount));
    if (value == this->renderTotal->text().toInt()) {
        QMessageBox msgBox;
        msgBox.setText("提示");
        msgBox.setInformativeText("二次元表作成！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
    }
}
void MainWindow::proSendValue(long long prime_size, long long min_num, long long max_num) {
    qDebug() << "get proSendValue" << prime_size << min_num << max_num;

    /*this->renderProBar->setValue(0);
    this->renderCount->setText("0");*/
    this->table->setRowCount((max_num + 10) / 10 - min_num / 10);
    this->primeTotal->setText(QString::number(prime_size));
    this->primeProBar->setMaximum(prime_size);
    this->primeProBar->setValue(0);
    
    this->primeCount->setText(QString::number(min_num));
    this->primeLabel->setText("値の総量");
}

void MainWindow::makeBodyItem(long long row, long long col, QString value) {
    this->bodyItem = new QTableWidgetItem(value);
    this->table->setItem(row, col, bodyItem);
    
}
void MainWindow::makeHeadItem(long long row, QString value) {
    //qDebug() << "makeHeadItem" << row << value;
    this->headerItem = new QTableWidgetItem(value);
    this->table->setItem(row, 0, headerItem);
}

void MainWindow::setRenderValue(long long renderValue) {
    int total = this->renderTotal->text().toLongLong();
    
    if (renderValue == total) {
        this->renderProBar->setValue(renderValue);
    }
    else if(renderValue < total) {
        this->renderProBar->setValue(renderValue % total);
    }
    this->renderCount->setText(QString::number(renderValue));
    

    if (renderValue == this->renderTotal->text().toLongLong()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("提示");
        msgBox.setText("二次元表完成！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void MainWindow::setPrimeValue(long long primeValue) {
    int total = this->primeTotal->text().toLongLong();
    //qDebug() << "setPrimeValue" << primeValue << total << primeValue % total;
    if (primeValue == total) {
        this->primeProBar->setValue(primeValue);
    }
    else if (primeValue < total) {
        
        this->primeProBar->setValue(primeValue % total);
    }
    
    this->primeCount->setText(QString::number(primeValue));
}

MainWindow::~MainWindow()
{
//    delete this->is_prime_check;
//    delete this->label;
//    delete this->layout;
//    delete this->min_num_edit;
//    delete this->max_num_edit;

//    delete this->is_happy_check;

//    delete this->is_prime_check;
//    delete this->checkbox_layout;
//    delete this->tableOkButton;
//    delete this->tableMsg;
//    delete this->tableTitle;
//    delete this->table;

//    delete this->judge_edit;
//    delete this->judgeOkButton;
//    delete this->judgeMsg;
//    delete this->widget;
//    delete this->layout;
//    delete this->ui;

}

