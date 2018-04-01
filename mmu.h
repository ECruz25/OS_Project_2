#ifndef MMU_H
#define MMU_H

#include <QString>
#include <QList>
#include <iostream>

#include "program.h"

using namespace std;

class MMU
{
public:
    MMU();
    int program_amount;
    int page_frames_amount;
    int algorithm; // 0=FIFO, 1=2da Oport
    QString** page_table;
    Program* first_program;
    Program* last_program;
    QList<Program*> program_exec_list;
    void add_program(Program *program);
    void create_page_table(int page_amount);
    void add_program_to_exec_list(Program* program);
    int setup_page_table();
    int create_program_id(int random_number);
    Program* get_first_program();
    Program* get_program_by_id(int id, Program* program);
    Program* get_program_by_name(QString name, Program* program);
};

#endif // MMU_H
