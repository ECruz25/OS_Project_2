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
    this->page_frames_amount = page_frames_amount;
    page_table.clear();
    for(int x = 0; x < program_exec_list.size(); x++){
        vector<int> page_column;
        page_column.reserve(page_frames_amount);
        page_table.push_back(page_column);
    }
}

void MMU::add_program_to_exec_list(Program *program)
{
    program_exec_list.append(program);
}

void MMU::setup_page_table()
{
    page_failures.clear();
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
            programs_in_execution.at(y)->age++;
            if(program_exec_list.at(x)->id == programs_in_execution.at(y)->id)
            {
                page_failures.push_back(0);
                if(algorithm==2)
                {
                    programs_in_execution.at(y)->age = 1;
                }
                added_program = true;
            }
        }

        while(!added_program)
        {
            if(programs_in_execution.size() < page_frames_amount)
            {
                programs_in_execution.append(program_exec_list.at(x));
                programs_in_execution.at(programs_in_execution.size()-1)->age++;
                page_failures.push_back(1);
                added_program = true;
            }
            else
            {
                switch (algorithm)
                {
                case 0:
                {
                    int position = get_oldest_program_FIFO(programs_in_execution);
                    programs_in_execution.insert(position, program_exec_list.at(x));
                    programs_in_execution.at(position+1)->age = 0;
                    programs_in_execution.removeAt(position+1);
                    programs_in_execution.at(position)->age++;
                    page_failures.push_back(1);
                    added_program = true;
                }
                    break;
                case 2:
                {
                    int position = get_oldest_program_FIFO(programs_in_execution);
                    programs_in_execution.insert(position, program_exec_list.at(x));
                    programs_in_execution.at(position+1)->age = 0;
                    programs_in_execution.removeAt(position+1);
                    programs_in_execution.at(position)->age++;
                    page_failures.push_back(1);
                    added_program = true;
                }
                    break;
                case 3:
                {
                    QList<int> positions;
                    for(int z = 0; z < programs_in_execution.size(); z++)
                    {
                        positions.append(this->get_next_position_in_list(programs_in_execution.at(z), program_exec_list, x));
                    }
                    int position = get_farthest_position(positions);
                    if(position == -1)
                    {
                        QList<Program*> programs_not_being_used_again;
                        for (int p = 0; p < positions.size(); p++)
                        {
                            if(positions.at(p) == -1)
                            {
                                programs_not_being_used_again.append(programs_in_execution.at(p));
                            }
                        }
                        position = get_oldest_program_FIFO(programs_not_being_used_again);
                    }
                    programs_in_execution.insert(position, program_exec_list.at(x));
                    programs_in_execution.at(position+1)->age = 0;
                    programs_in_execution.removeAt(position+1);
                    programs_in_execution.at(position)->age++;
                    page_failures.push_back(1);
                    added_program = true;
                }
                    break;

                default:
                    cout<<"aca";
                    added_program = true;
                    break;
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

int MMU::get_oldest_program_FIFO(QList<Program *> list)
{
    Program* oldest = list.at(0);
    for(int y = 0; y < list.size(); y++)
    {
        if(list.at(y)->age > oldest->age)
        {
            oldest = list.at(y);
        }
    }
    for(int y = 0; y < list.size(); y++)
    {
        if(list.at(y)->id == oldest->id)
        {
            return y;
        }
    }
    return -1;
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

int MMU::get_next_position_in_list(Program *program, QList<Program *> list, int last_position)
{
    for (int x = last_position; x < list.size(); x++)
    {
        if(list.at(x)->id == program->id){
            return x;
        }
    }
    return -1;
}

int MMU::get_farthest_position(QList<int> list)
{
    int farthest_number = list.at(0);
    for (int x = 0; x < list.size(); x++)
    {
        if (list.at(x) == -1)
        {
            return -1;
        }
        else if (list.at(x) > farthest_number)
        {
            farthest_number = list.at(x);
        }
    }
    for (int x = 0; x < list.size(); x++)
    {
        if (list.at(x) == farthest_number)
        {
            return x;
        }
    }
    return -1;
}

double MMU::get_performance()
{
    int total_failures = 0;
    for (int x = 0; x < page_failures.size(); ++x)
    {
        total_failures+=page_failures.at(x);
    }
    double total = 1 - ((double)total_failures/(double)page_failures.size());
    return total;
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
