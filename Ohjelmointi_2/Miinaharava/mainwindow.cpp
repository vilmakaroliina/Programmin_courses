#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    create_board();
    create_timer();
    create_buttons();
    create_text_browser();
    ask_seed();

    board = new GameBoard;
    board->init(seed_);
}

MainWindow::~MainWindow()
{
    delete board;
    delete ui;
}


void MainWindow::create_board()
{
    for (int x = 1; x <= BOARD_SIDE; x++)
{
    for (int y  = 1; y <= BOARD_SIDE; y++)
    {
        QPushButton* newButton = new QPushButton(this);
        newButton -> setGeometry(0+x*50, 50+y*50, 50, 50);
        newButton->setEnabled(false);

        connect(newButton, &QPushButton::clicked, this, &MainWindow::button_clicked);
        std::pair new_pair = {x, y};
        all_buttons_.insert({new_pair, newButton});
    }
}
}


void MainWindow::create_timer()
{
    minLCDNumber = new QLCDNumber(this);
    minLCDNumber->setGeometry(400, 250, 100, 25);
    minLCDNumber->setStyleSheet("background: red");
    secLCDNumber = new QLCDNumber(this);
    secLCDNumber->setGeometry(400, 300, 100, 25);
    secLCDNumber->setStyleSheet("background: grey");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timer_function);
}


void MainWindow::create_buttons()
{
    startPushButton = new QPushButton("Start game", this);
    startPushButton->setGeometry(400, 20, 100, 25);
    connect(startPushButton, &QPushButton::clicked, this, &MainWindow::start_game);

    resetPushButton = new QPushButton("Reset", this);
    resetPushButton->setGeometry(400, 55, 100, 25);
    connect(resetPushButton, &QPushButton::clicked, this, &MainWindow::reset_game);

    flagPushButton = new QPushButton("Set flag", this);
    flagPushButton->setGeometry(50, 70, 55, 25);
    flagPushButton->setStyleSheet("background-color: red");
    connect(flagPushButton, &QPushButton::clicked, this, &MainWindow::add_flag);

    removePushButton = new QPushButton("Remove flag", this);
    removePushButton->setGeometry(125, 70, 100, 25);
    removePushButton->setStyleSheet("background-color: grey");
    connect(removePushButton, &QPushButton::clicked, this, &MainWindow::remove_flag);
}


void MainWindow::create_text_browser()
{
    printed_text = new QTextBrowser(this);
    printed_text->setGeometry(400, 100, 100, 100);
}


void MainWindow::ask_seed()
{
    text =new QLabel("Give a seed value and/or click start game:", this);
    text->setGeometry(50, 20, 275, 25);

    seed = new QLineEdit(this);
    seed->setGeometry(50, 40, 200, 25);
    connect(seed, &QLineEdit::editingFinished, this, &MainWindow::set_seed);
}


void MainWindow::set_seed()
{
    if (seed->text() == "")
    {
        seed_ = time(NULL);
    }
    else
    {
        seed_ = seed->text().toInt();
    }
}


void MainWindow::timer_function()
{
    if (sec_ == 60)
    {
        sec_ = 0;
        min_ += 1;
    }
    else
    {
    sec_+=1;
    }
    secLCDNumber->display(sec_);
    minLCDNumber->display(min_);
}


void MainWindow::start_game()
{
    set_seed();
    for (auto& btn : all_buttons_)
    {
        btn.second->setEnabled(true);
    }

    timer -> start(1000);

    startPushButton->setEnabled(false);
}


void MainWindow::reset_game()
{
    timer ->stop();

    min_ = 0;
    sec_ = 0;

    secLCDNumber->display(sec_);
    minLCDNumber->display(min_);

    seed -> setText("");
    seed_ = 0;

    printed_text->setText("");

    for (auto btn : all_buttons_)
    {
        btn.second->setIcon(QIcon());
        btn.second->setEnabled(false);
    }

    delete board;
    set_seed();
    board = new GameBoard;
    board -> init(seed_);

    startPushButton->setEnabled(true);

}


void MainWindow::button_clicked()
{
    QPushButton* clicked_button = nullptr;
    int x = 0;
    int y = 0;

    for (auto btn : all_buttons_)
    {
        if (btn.second == sender())
        {
            clicked_button = btn.second;
            x = btn.first.first;
            y = btn.first.second;
        }
    }

    Square clicked_square = (*board).getSquare(x-1, y-1);

    if (delete_flag == false and set_flag == false)
    {
    clicked_square.open();
    }
    (*board).setSquare(clicked_square, x-1, y-1);

    change_icon(clicked_square, clicked_button, x, y);
}


void MainWindow::change_icon(Square clicked_square,
                             QPushButton* clicked_button,
                             int x, int y)
{
    if (delete_flag == true or set_flag == true)
    {
        change_flag_icon(clicked_square, clicked_button,
                         x, y);
    }
    else
    {
        clicked_button->setEnabled(false);
        if (clicked_square.hasMine())
    {
        clicked_button->setIcon(QIcon
                        ("/home/ttvile/ttvile/student/13"
                         "/minesweeper_gui/Resources/bomb_icon.png"));
    }
        else if (clicked_square.hasFlag())
        {
            if (not clicked_square.isReady())
            {
                int mines = clicked_square.countAdjacent();
                clicked_button->setIcon(QIcon(numbers[mines]));
                stop_game();
            }
            else
            {
                delete_flag = true;
                change_flag_icon(clicked_square, clicked_button, x ,y);
                change_icon(clicked_square, clicked_button, x, y);
            }
        }
        else
    {
        for ( int x = 1; x <= BOARD_SIDE; ++x)
        {
            for (int y = 1; y <= BOARD_SIDE; ++y)
            {
                Square current_square = (*board).getSquare(x-1, y-1);
                if (current_square.isOpen() and not current_square.hasMine())
                {
                    if (current_square.hasFlag())
                    {
                    }
                    else
                    {
                    QPushButton* current_button = get_button(x, y);
                    int mines = current_square.countAdjacent();
                    current_button ->setIcon(QIcon(numbers[mines]));
                    current_button -> setEnabled(false);
                    }
                }
            }
        }
    }


    if (not clicked_square.isReady())
    {
        stop_game();
    }
    }

    if (board->isGameOver())
    {
        win();
    }

}


void MainWindow::change_flag_icon(Square clicked_square,
                                  QPushButton* clicked_button,
                                  int x, int y)
{
    if (delete_flag == true)
    {
        clicked_square.removeFlag();
        (*board).setSquare(clicked_square, x-1, y-1);
        delete_flag = false;
        clicked_button->setIcon(QIcon());
    }
    if (set_flag == true)
    {
        clicked_button->setIcon(QIcon("/home/ttvile/ttvile/student/13"
                                      "/minesweeper_gui/Resources/flag.png"));
        clicked_square.addFlag();
        (*board).setSquare(clicked_square, x-1, y-1);
        set_flag = false;
    }
}


void MainWindow::add_flag()
{
    set_flag = true;
}

void MainWindow::remove_flag()
{
    delete_flag = true;
}

void MainWindow::stop_game()
{
    timer->stop();

    printed_text->setText("You lost :(");

    for (auto btn : all_buttons_)
    {
        btn.second->setEnabled(false);
    }
}

QPushButton* MainWindow::get_button(int x, int y)
{
    for (auto btn : all_buttons_)
    {
        if (btn.first.first == x and btn.first.second == y)
        {
            return btn.second;
        }
    }
    return nullptr;
}

void MainWindow::win()
{
    timer->stop();

    printed_text->setText("You won :)");

    for (auto btn : all_buttons_)
    {
        btn.second->setEnabled(false);
    }
}



