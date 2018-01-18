#pragma once

#include <QMainWindow>
#include <QStackedWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

public slots:

    void createButton();

signals:

    void test();

private:
    Ui::MainWindow *ui;

    QStackedWidget mainWindowQStackedWidget;
};
