#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPainter>
#include <QString>
#include <QFont>
#include <iostream>

class RF : public QWidget {

    public:
    RF (QWidget *parent = 0): QWidget(parent) {

    QPushButton *show_btn = new QPushButton("Show flag", this);
    QPushButton *hide_btn = new QPushButton("Hide flag", this);
    QPushButton *name_btn = new QPushButton("Author", this);

    lbl = new QLabel(author, this);
    lbl->setFont(QFont("Purisa",24));
    lbl->setStyleSheet("QLabel {color: #ffffff;}");
    lbl->setVisible(author_visible);

    // QGridLayout *grid = new QGridLayout(this);
    // grid->addWidget(show_btn, 0, 0);
    // grid->addWidget(hide_btn, 0, 1);
    // grid->addWidget(name_btn, 0, 2);
    //grid->addWidget(lbl, 1, 1);
    show_btn->setGeometry(QRect(QPoint(25, 25), QSize(100, 50)));
    hide_btn->setGeometry(QRect(QPoint(150, 25), QSize(100, 50)));
    name_btn->setGeometry(QRect(QPoint(275, 25), QSize(100, 50)));
    lbl->setGeometry(75, 150, 300, 50);

    connect(show_btn, &QPushButton::clicked, this, &RF::show_flag);
    connect(hide_btn, &QPushButton::clicked, this, &RF::hide_flag);
    connect(name_btn, &QPushButton::clicked, this, &RF::show_author);
}

protected:
void paintEvent(QPaintEvent *e) {
    //Q_UNUSED(e);
    if (flag){
        QPainter pen(this);
        pen.setBrush(QBrush("#ffffff"));
        pen.drawRect(50, 100, 300, 50);
        pen.setBrush(QBrush("#0000ff"));
        pen.drawRect(50, 150, 300, 50);
        pen.setBrush(QBrush("#ff0000"));
        pen.drawRect(50, 200, 300, 50);
    }
}
private slots:
void show_flag(){
    flag = true;
    update();
}
void hide_flag(){
    flag = false;
    update();
}
void show_author(){
    author_visible = !author_visible;
    lbl->setVisible(author_visible);
}
private:
    QLabel *lbl;
    bool flag = false;
    bool author_visible = false;
    QString author = "me0w";
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    RF window;

    window.resize(400, 300);
    window.setWindowTitle("asd");
    window.show();

    return app.exec();
}