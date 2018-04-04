#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //cuando uno sustituye otro, y el sustituido entra de nuevo, creo que la edad no se resetea
    ui->setupUi(this);
    counter = 0;
    mmu = new MMU();
    ui->program_size_edit->setValidator(new QIntValidator(0,999,this));
    ui->page_amount_edit->setValidator(new QIntValidator(0,999,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_save_program_button_clicked()
{
    ui->program_combo_box->clear();
    mmu->add_program(new Program("0", 1, mmu->create_program_id(rand()%5000+1)));
    mmu->add_program(new Program("1", 1, mmu->create_program_id(rand()%5000+1)));
    mmu->add_program(new Program("2", 1, mmu->create_program_id(rand()%5000+1)));
    mmu->add_program(new Program("3", 1, mmu->create_program_id(rand()%5000+1)));
    mmu->add_program(new Program("4", 1, mmu->create_program_id(rand()%5000+1)));
    mmu->add_program(new Program("5", 1, mmu->create_program_id(rand()%5000+1)));
    mmu->add_program(new Program("6", 1, mmu->create_program_id(rand()%5000+1)));
    mmu->add_program(new Program("7", 1, mmu->create_program_id(rand()%5000+1)));
//    mmu->add_program(new Program(ui->program_name_edit->text(), ui->program_size_edit->text().toInt(), mmu->create_program_id(rand()%5000+1)));
    update_combo_box();
}

void MainWindow::on_page_amount_save_btn_clicked()
{
    if(mmu->program_amount > 0)
    {
        mmu->create_page_table(ui->page_amount_edit->text().toInt());
    }
}

void MainWindow::on_setup_btn_clicked()
{
    if(ui->algorithm_combo_box->currentText() == "FIFO")
    {
        mmu->algorithm = 0;
    }
    else if(ui->algorithm_combo_box->currentText() == "2da Oportunidad")
    {
        mmu->algorithm = 1;
    }
    else if(ui->algorithm_combo_box->currentText() == "LRU")
    {
        mmu->algorithm = 2;
    }
    else if(ui->algorithm_combo_box->currentText() == "Optimo")
    {
        mmu->algorithm = 3;
    }
    if(mmu->program_amount > 0)
    {
        mmu->create_page_table(ui->page_amount_edit->text().toInt());
    }
    counter++;
    if(counter>1)
    {
        cout<<counter<<endl;
    }
    ui->tableWidget->clear();
    if(mmu->program_exec_list.size() > 0)
    {
        ui->tableWidget->setColumnCount(mmu->program_exec_list.size());
        ui->tableWidget->setRowCount(mmu->page_frames_amount+1);
        table_header.clear();
        for(int x = 0; x < mmu->program_exec_list.size(); x++)
        {
            table_header.append(mmu->program_exec_list.at(x)->name);
        }
        ui->tableWidget->setHorizontalHeaderLabels(table_header);
    }
    mmu->setup_page_table();
    for(int x = 0; x < mmu->page_table.size(); x++)
    {
        for(int y = 0; y < mmu->page_table.at(x).size(); y++)
        {
            ui->tableWidget->setItem(y, x, new QTableWidgetItem(mmu->get_program_by_id(mmu->page_table.at(x).at(y), mmu->first_program)->name));
        }
    }
    //setup page failures
    for(int x = 0; x < mmu->program_exec_list.size(); x++)
    {
        ui->tableWidget->setItem(this->mmu->page_frames_amount, x, new QTableWidgetItem(QString::number(mmu->page_failures.at(x))));
    }
    ui->lcdNumber->display(this->mmu->get_performance());
}

void MainWindow::update_combo_box()
{
    Program* program;
    program = mmu->first_program;

    int count;
    while(program!=NULL)
    {
        ui->program_combo_box->addItem(program->name);
        program = program->next;
        count++;
    }
    delete program;
}

void MainWindow::on_add_to_exec_btn_clicked()
{

    //1.2.3.3.5.2.1.1.6.2.7.6.3


//    mmu->add_program_to_exec_list(mmu->get_program_by_name("2", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("3", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("2", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("1", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("5", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("2", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("4", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("5", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("3", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("2", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("5", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("2", mmu->first_program));

//examen
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("1", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("2", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("3", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("3", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("5", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("2", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("1", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("1", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("6", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("2", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("7", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("6", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name("3", mmu->first_program));

    mmu->add_program_to_exec_list(mmu->get_program_by_name("0", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("4", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("1", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("4", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("2", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("4", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("3", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("4", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("2", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("4", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("0", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("4", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("1", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("4", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("2", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("4", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("3", mmu->first_program));
    mmu->add_program_to_exec_list(mmu->get_program_by_name("4", mmu->first_program));
//    mmu->add_program_to_exec_list(mmu->get_program_by_name(ui->program_combo_box->currentText(), mmu->first_program));
}
