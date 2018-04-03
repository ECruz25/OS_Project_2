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

void MMU::create_page_table(int page_frames_amount)
{
    // paginas = 5
    // marcos = 3
    this->page_frames_amount = page_frames_amount;
//    page_table.reserve(page_frames_amount);
//    for(int i = 0; i < page_amount + 1; i++)
//    {
//        page_table.at(i).
//        page_table[i] = new QString[program_exec_list.size()];
//    }
//    despues tengo que agregar uno para ver si hubo fallo de pagina
    for(int x = 0; x < page_frames_amount; x++){
        vector<int> page_column;
        page_column.reserve(program_exec_list.size());
        page_table.push_back(page_column);
    }
}

void MMU::add_program_to_exec_list(Program *program)
{
    program_exec_list.append(program);
}

void MMU::setup_page_table()
{
    for(int x = 0; x < page_table.size(); x++)
    {
        page_table.at(x).clear();
    }
    QList<Program*> programs_in_execution;

    for(int x = 0; x < program_exec_list.size(); x++)
    {
        bool added_program = false;
        for(int y = 0; y < programs_in_execution.size(); y++)
        {
            if(program_exec_list.at(x)->id == programs_in_execution.at(y)->id)
            {
                page_failures.push_back(0);
                added_program = true;
            }
        }

        while(!added_program)
        {
            if(programs_in_execution.size() < page_frames_amount)
            {
                programs_in_execution.append(program_exec_list.at(x));
                page_failures.push_back(1);
                added_program = true;
            }
            else
            {
                switch (algorithm)
                {
                    case 0:
                        break;
                    default:
                        break;
                    added_program = true;
                }
            }
        }
        for(int y = 0; y < programs_in_execution.size(); y++)
        {
//            cout<<dynamic_cast<page_table.at(x)><<endl;
            page_table.at(x).push_back(programs_in_execution.at(y)->id);
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
