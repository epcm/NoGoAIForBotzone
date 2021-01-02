private
 slots :     void on_start_clicked();          //开始      void on_up_clicked();//加速      void on_down_clicked();//减速      void on_stop_clicked();//停止      void on_Close_clicked();//关闭 signals:     void sendValue(int);//传值 private:     Ui::Widget *ui;     int i;//变量     QTimer *timerStart;//开始定时器     QTimer *timerUp;//加速定时器     QTimer *timerDown;//减速定时器     Dialog *dialog;//子对话框 (6)主界面类构造函数中进行成员变量的初始化。示例代码如下： this->setFixedSize(width(),height());      ui->progressBar->setValue(0);//初始值为0 
    ui->progressBar->setRange(0, MAXSIZE - 1); //设置进度条值的范围     //红底     ui->progressBar->setStyleSheet("QProgressBar::chunk { background-color: rgb(255, 0, 0) }");      timerStart=new QTimer(this);     timerUp=new QTimer(this);     timerDown=new QTimer(this);     connect(timerStart,SIGNAL(timeout()),this,SLOT(on_start_clicked()));     connect(timerUp,SIGNAL(timeout()),this,SLOT(on_up_clicked()));     connect(timerDown,SIGNAL(timeout()),this,SLOT(on_down_clicked()));      i=0;     dialog=new Dialog;     connect(this,SIGNAL(sendValue(int)),dialog,SLOT(getValue(int)));     dialog->show();      i=0;      ui->start->setEnabled(true);     ui->up->setEnabled(false);     ui->down->setEnabled(false);     ui->stop->setEnabled(false); (7)分别为五个PushButton添加信号对应的槽(类似消息响应函数)，代码如下： //开始 void Widget::on_start_clicked() {     ui->start->setEnabled(false);     ui->up->setEnabled(true);     ui->down->setEnabled(true);     ui->stop->setEnabled(true);      timerStart->start(1);     timerUp->stop();     timerDown->stop();      if(i >=MAXSIZE-1 )     {         ui->progressBar->setValue(MAXSIZE-1);         emit sendValue(MAXSIZE-1);         timerStart->stop(); 
        QMessageBox::information(this, tr("提示"), tr("结束！"), QMessageBox::Ok | QMessageBox::Default);
         return;
     
}
      //赋值     ui->progressBar->setValue(i);     i+=I;     emit sendValue(i);     ui->label_2->setText("4"); } //加速 void Widget::on_up_clicked() {     timerUp->start(1);     timerDown->stop();     timerStart->stop();      if(i >=MAXSIZE-1 )     {         ui->progressBar->setValue(MAXSIZE-1);         emit sendValue(MAXSIZE-1);         timerUp->stop();         QMessageBox::information(this,tr("提示"),tr("结束！"),QMessageBox::Ok|QMessageBox::Default);         return;     }     ui->progressBar->setValue(i);     i+=UP;     emit sendValue(i);     ui->label_2->setText("7"); } //减速 void Widget::on_down_clicked() {     timerDown->start(1);     timerStart->stop();     timerUp->stop();      if(i >=MAXSIZE-1 )     {         ui->progressBar->setValue(MAXSIZE-1);         emit sendValue(MAXSIZE-1);         timerDown->stop(); 
        QMessageBox::information(this, tr("提示"), tr("结束！"), QMessageBox::Ok | QMessageBox::Default);
         return;
     
}
     ui->progressBar->setValue(i);
     i += DOWN;
     emit sendValue(i);
     ui->label_2->setText("1");
 
}
  //停止 void Widget::on_stop_clicked() {      ui->start->setEnabled(true);     ui->up->setEnabled(false);     ui->down->setEnabled(false);     ui->stop->setEnabled(false);      timerStart->stop();     timerDown->stop();     timerUp->stop();      ui->label_2->setText("0"); } //关闭 void Widget::on_Close_clicked() {     this->close();     dialog->close(); }