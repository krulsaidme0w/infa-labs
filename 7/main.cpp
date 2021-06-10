#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPainter>
#include <QString>
#include <QMouseEvent>
#include <iostream>
#include <unistd.h>
#include <QDebug>

class RF : public QWidget {

public:

    int x, speed, key_flag;

    explicit RF (QWidget *parent = nullptr) : QWidget(parent), x(100), speed(2), key_flag(0) {

    auto show_btn = new QPushButton("Show flag", this);
    auto hide_btn = new QPushButton("Hide flag", this);
    auto name_btn = new QPushButton("Author", this);
    auto change_btn = new QPushButton("Change direction", this);

    lbl = new QLabel(author, this);
    lbl->setFont(QFont("Purisa",24));
    lbl->setStyleSheet("QLabel {color: #000000;}");
    lbl->setVisible(author_visible);

    show_btn->setGeometry(QRect(QPoint(25, 25), QSize(100, 50)));
    hide_btn->setGeometry(QRect(QPoint(150, 25), QSize(100, 50)));
    name_btn->setGeometry(QRect(QPoint(275, 25), QSize(100, 50)));
    change_btn->setGeometry(QRect(QPoint(400, 25), QSize(150, 50)));
    lbl->setGeometry(75, 150, 300, 50);

    connect(show_btn, &QPushButton::clicked, this, &RF::show_flag);
    connect(hide_btn, &QPushButton::clicked, this, &RF::hide_flag);
    connect(name_btn, &QPushButton::clicked, this, &RF::show_author);
    connect(change_btn, &QPushButton::clicked, this, &RF::change_direction);
}

protected:

    void mouseReleaseEvent(QMouseEvent *event) override {
        if(event->button() ==  Qt::LeftButton) {
            key_flag = 1;
        }
        else if(event->button() == Qt::RightButton) {
            key_flag = 0;
        }
    }

    void paintEvent(QPaintEvent *e) override {

        if(key_flag == 1) {
            x += speed;
        }

        if (flag){
            QPainter pen(this);
            pen.setBrush(QBrush("#ffffff"));
            pen.drawRect(x, 100, 300, 50);
            pen.setBrush(QBrush("#0000ff"));
            pen.drawRect(x, 150, 300, 50);
            pen.setBrush(QBrush("#ff0000"));
            pen.drawRect(x, 200, 300, 50);
        }
        usleep(3 * 10000);
        update();
    }

private slots:
    void show_flag(){
        flag = true;
        update();
    }
    void hide_flag(){
        flag = false;
        key_flag = 0;
        update();
    }
    void show_author(){
        if(key_flag || flag) {
            return;
        }
        author_visible = !author_visible;
        lbl->setVisible(author_visible);
    }
    void change_direction() {
        speed *= -1;
    }
private:
    QLabel *lbl;
    bool flag = false;
    bool author_visible = false;
    QString author = "Прилуцкий Е. С.";
};


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    RF window;
    window.resize(600, 300);
    window.setWindowTitle("7, 8");
    window.show();

    return QApplication::exec();
}