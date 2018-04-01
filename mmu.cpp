#include "mmu.h"

MMU::MMU()
{
    first_program = NULL;
    last_program = NULL;
    program_amount = 0;
}

void MMU::add_program(Program* program)
{
    if(first_program == NULL)
    {
        first_program = program;
        last_program = program;
        program_amount++;
        return;
    }
    last_program->next = program;
    program->previous = last_program;
    last_program = program;
    program_amount++;
}

void MMU::create_page_table(int page_amount)
{
    this->page_frames_amount = page_amount;
    page_table = new QString*[page_amount];
    for(int i = 0; i < page_amount + 1; i++)
    {
        page_table[i] = new QString[program_exec_list.size()];
    }
    for(int x = 0; x < page_amount + 1 ; x++){
        for(int y = 0; y < program_exec_list.size(); y++)
        {
            page_table[x][y] = "";
        }
    }
}

void MMU::add_program_to_exec_list(Program *program)
{
    program_exec_list.append(program);
}

int MMU::setup_page_table()
{
    QList<Program*> programs_in_execution;

    for(int x = 0; x < program_exec_list.size(); x++)
    {
        if(programs_in_execution.size() < page_frames_amount)
        {
            programs_in_execution.append(program_exec_list.at(x));
        }
        else
        {
            switch (algorithm)
            {
                case 0:
//                    if()
                    break;
                default:
                    break;
            }
        }
        for(int y = 0; y < programs_in_execution.size(); y++)
        {
            page_table[x][y] = programs_in_execution.at(y)->name;
        }

    }
}

int MMU::create_program_id(int random_number)
{
    if(get_program_by_id(random_number, this->get_first_program())==NULL)
    {
        return random_number;
    }
    else
    {
        return create_program_id(rand()%5000+1);
    }
}

Program *MMU::get_first_program()
{
    return this->first_program;
}

Program *MMU::get_program_by_id(int id, Program* program)
{
    if(program==NULL)
    {
        return NULL;
    }
    else
    {
        if(program->id == id)
        {
            return program;
        }
        else
        {
            return get_program_by_id(id, program->next);
        }
    }
}

Program *MMU::get_program_by_name(QString name, Program *program)
{
    if(program==NULL)
    {
        return NULL;
    }
    else
    {
        if(program->name == name)
        {
            return program;
        }
        else
        {
            return get_program_by_name(name, program->next);
        }
    }
}
