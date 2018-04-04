#ifndef MMU_H
#define MMU_H

#include <QString>
#include <QList>
#include <iostream>
#include <vector>

#include "program.h"
#include "node.h"

using namespace std;

class MMU
{
public:
    MMU();
    int program_amount;
    int page_frames_amount;
    int algorithm; // 0=FIFO, 1=2da Oport, 2=LRU, 3=OPT, 4=NRU
    vector<vector<int>> page_table;
    vector<int> page_failures;
//    QString** page_table;
    Program* first_program;
    Program* last_program;
    QList<Program*> program_exec_list;
    void add_program(Program *program);
    void create_page_table(int page_amount);
    void add_program_to_exec_list(Program* program);
    void setup_page_table();
    int get_oldest_program_FIFO(QList<Program*> list);
    int create_program_id(int random_number);
    int get_next_position_in_list(Program* program, QList<Program*> list, int last_position);
    int get_farthest_position(QList<int> list);
    double get_performance();
    Program* get_first_program();
    Program* get_program_by_id(int id, Program* program);
    Program* get_program_by_name(QString name, Program* program);
};

#endif // MMU_H
