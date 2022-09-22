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
    this->max_num_edit->setText("17624");
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

    this->make_table();

    // 素数判定
    this->label = new QLabel("素数判定");
    this->layout->addWidget(this->label);
    this->judge_edit = new QLineEdit();
    this->layout->addWidget(this->judge_edit);
    this->judgeOkButton = new QPushButton("確定");
    connect(this->judgeOkButton, SIGNAL(clicked()), this, SLOT(judge_onclick()));

    this->layout->addWidget(this->judgeOkButton);

    this->judgeMsg = new QLabel("fdfsd");
    this->judgeMsg->setStyleSheet("color:black");
    this->layout->addWidget(this->judgeMsg);


    this->widget->setLayout(this->layout);
    this->setCentralWidget(this->widget);

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
        long long prime_num = prime_num_str.toInt(&ok);

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
void MainWindow::toggle_prime(){
    qDebug() << "toggle_prime" << "aaa";
}

void MainWindow::toggle_prime(int prime){
    qDebug() << "toggle_prime" << prime;
    this->prime = !prime;
    this->is_prime_check->setChecked(this->prime);

}
void MainWindow::toggle_happy(int happy){
    qDebug() << "toggle_happy" << happy;
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
        std::list<long long> prime_list = get_primenum_list(max_num, min_num, happy, prime);

        qDebug()<<prime_list.size();
        long long count = min_num;
        this->table->setRowCount((max_num+10)/10-count/10);

        std::list<long long>::iterator it = prime_list.begin();


        long long head;
        long long start_head;
        long long input_head;
        QTableWidgetItem* headerItem;
        QTableWidgetItem* bodyItem;
        head = min_num / 10;
        start_head = min_num/10;
        input_head = head - start_head;
        count = head * 10;



        // 間隔17609-17623, 176713-176741, 間隔 17610-17624
        headerItem = new QTableWidgetItem(QString::number(head));
        this->table->setItem(input_head,0, headerItem);

        // 最小数行の最小数前の空欄を付ける
        for(;count<min_num;count++){
            bodyItem = new QTableWidgetItem("-");
            this->table->setItem(input_head,count % 10 + 1,bodyItem);
        }


        while(count < max_num){
            if(it == prime_list.end()){
                for(;count < max_num; count++){
                    bodyItem = new QTableWidgetItem("*");
                    this->table->setItem(input_head,count % 10 + 1,bodyItem);
                    if(count-head*10==10){
                        head = count / 10;
                        input_head = head - start_head;
                        headerItem = new QTableWidgetItem(QString::number(head));
                        this->table->setItem(input_head,0, headerItem);
                    }
                }
                break;
            }
            // 空いた値を位置に付ける、結尾はheadか*itかの前は比較次第

            // headerすでに付けた、0-9をはんだんしつつ入れる
            for(;it != prime_list.end(); ){
                // 累加はちょうど*itと同じ場合は値を付ける、次は執行せずにitを次に進む

                if(count == *it){
                    bodyItem = new QTableWidgetItem(QString::number(*it));
                    // input_head, count % 10 + 1に置く
                    this->table->setItem(input_head,count % 10 + 1,bodyItem);
                    count++;
                    it++;

                    // 改行
                    if(count-head*10==10){
                        head = count / 10;
                        input_head = head - start_head;
                        headerItem = new QTableWidgetItem(QString::number(head));
                        this->table->setItem(input_head,0, headerItem);
                    }

                    continue;
                }

                // tailは次のヘッドまたは*it
                int tail = *it;
                // head 数列の頭、input_head テーブルの頭、head - start_head = input_head
                // tail は 次の数列のヘッドより大きいの場合はまずこの行を補填する、故tailはこの行の末尾となる
                if(tail >= (head+1)*10){
                    tail = (head+1)*10;
                }
                // countからtailまで空欄を付ける、付けずむとcountは次のhead相当
                for(;count<tail;count++){
                    bodyItem = new QTableWidgetItem("*");
                    this->table->setItem(input_head,count % 10 + 1,bodyItem);
                }
                // 付け済むと改行
                if(count-head*10==10){
                    head = count / 10;
                    input_head = head - start_head;
                    headerItem = new QTableWidgetItem(QString::number(head));
                    this->table->setItem(input_head,0, headerItem);
                }


            }
            // 最後の場合は、count
            // 最終の数から定義した最大範囲まで空いた値を付ける
            for(;count < max_num; count++){
                bodyItem = new QTableWidgetItem("*");
                this->table->setItem(input_head,count % 10 + 1,bodyItem);
                if(count-head*10==10){
                    head = count / 10;
                    input_head = head - start_head;
                    headerItem = new QTableWidgetItem(QString::number(head));
                    this->table->setItem(input_head,0, headerItem);
                }
            }

        }


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

