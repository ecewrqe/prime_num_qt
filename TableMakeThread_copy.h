#pragma once
#pragma once
#include <QThread>
#include<QtCore/QDebug>
#include<QString>
#include<list>
#include"prime_num.h"

class TableMakeThread : public QThread {
    Q_OBJECT
private:
    long long max_num, min_num;
    bool happy, prime;
public slots:
    void setValue(long long max_num, long long min_num, bool happy, bool prime) {
        this->max_num = max_num;
        this->min_num = min_num;
        this->happy = happy;
        this->prime = prime;

    }
signals:
    void proSendValue(long long prime_size, long long min_num, long long max_num);

    void makeBodyItem(long long row, long long col, QString value);
    void makeHeadItem(long long row, QString value);
    void getRenderValue(long long renderValue);
    void getPrimeValue(long long primeValue);

private:
    void run() {
        qDebug() << "thread start";
        // テーブル作成
        //qDebug() << "get value" << max_num << min_num << happy << prime;
        std::list<long long> prime_list = get_primenum_list(this->max_num, this->min_num, this->happy, this->prime);
        // 事前準備
        long long prime_size = prime_list.size();
        long long count = this->min_num;
        //qDebug() << "emit proSendValue" << prime_size << count << max_num;
        emit proSendValue(prime_size, count, this->max_num);
        
        std::list<long long>::iterator it = prime_list.begin();

        long long head;
        long long start_head;
        long long input_head;
        long long input_count;

        QString headerString;
        QString bodyString;

        head = this->min_num / 10;
        start_head = head;
        input_head = head - start_head;
        count = head * 10;
        // ヘッドに値を与える
        headerString = QString::number(head);
        //qDebug() << "make head" << input_head << headerString;
        emit makeHeadItem(input_head, headerString);
        
        // 最小数行の最小数前の空欄に値を付ける
        for (; count < min_num; count++) {
            // bodyの値を送る同時にレンダーに計数を送る
            emit makeBodyItem(input_head, count % 10 + 1, "-");
        }

        //qDebug() << "front of loop" << (it == prime_list.end());
        /*return;*/
        //qDebug() << "loop start";
        int primeCount = 0;
        while (count <= max_num) {
            if(it == prime_list.end()){ 
                // リスト内一つ値もない
                for (; count <= max_num; count++) {
                    
                    if (count - head * 10 == 10) {
                        head = count / 10;
                        input_head = head - start_head;
                        emit makeHeadItem(input_head, QString::number(head));
                    }
                    // bodyの値を送る同時にレンダーに計数を送る
                    input_count = count - min_num;
                    //qDebug() << input_count;
                    emit makeBodyItem(input_head, count % 10 + 1, "*");
                    getRenderValue(input_count);
                    //qDebug() << "pro *" << input_head << head << count;
                    
                }
                break;
            }
            
            // 空いた値を位置に付ける、結尾はheadか*itかの前は比較次第
            // headerすでに付けた、0-9を判断しつつ入れる
            for (; it != prime_list.end();) {
                //qDebug() << "value" << input_head << head << count << *it;
                
                // 累加はちょうど*itと同じ場合は値を付ける、次は執行せずにitを次に進む
                if (count == *it) {
                    // 改行
                    if (count - head * 10 == 10) {
                        head = count / 10;
                        input_head = head - start_head;
                        emit makeHeadItem(input_head, QString::number(head));
                    }
                    // 実在の値を与える時には総数の計数と素数の計数を送る
                    
                    //qDebug() << "value" << input_head << head << count << *it;
                    emit makeBodyItem(input_head, count % 10 + 1, QString::number(*it));
                    
                    getRenderValue(count-min_num);
                    count++;
                    primeCount++;
                    getPrimeValue(primeCount);
                    
                    it++;
                    _sleep(1);
                    continue;
                    
                }

                // まず改行
                if (count - head * 10 == 10) {
                    head = count / 10;
                    input_head = head - start_head;
                    emit makeHeadItem(input_head, QString::number(head));
                }

                // tailは次のヘッドまたは*it
                int tail = *it;
                // head 数列の頭、input_head テーブルの頭、head - start_head = input_head
                // tailは次の行のheadまたは*it
                if (tail >= (head + 1) * 10) {
                    tail = (head + 1) * 10;
                }
                // countからtailまで空欄を付ける、付けずむとcountは次のheadまたは*it相当
                for (; count < tail; count++) {
                    //qDebug() << "value *" << input_head << head << count;
                    emit makeBodyItem(input_head, count % 10 + 1, "*");
                    getRenderValue(count - min_num);
                    _sleep(1);
                }

                // まず改行
                if (count - head * 10 == 10) {
                    head = count / 10;
                    input_head = head - start_head;
                    emit makeHeadItem(input_head, QString::number(head));
                }
                
                
            }

            // 最終の数から定義した最大範囲まで空いた値を付ける
            for (; count < max_num; count++) {
                if (count - head * 10 == 10) {
                    head = count / 10;
                    input_head = head - start_head;
                    emit makeHeadItem(input_head, QString::number(head));
                }
                emit makeBodyItem(input_head, count % 10 + 1, "*");
                getRenderValue(count-min_num);
                
            }

        }

        qDebug() << "thread end";
    }
};