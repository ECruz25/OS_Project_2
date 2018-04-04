#include "program.h"

Program::Program()
{

}

Program::Program(QString name, int size, int id)
{
    this->name = name;
    this->size = size;
    this->id = id;
    this->next = NULL;
    this->previous = NULL;
    this->reference_bit = 0;
    this->age = 0;
}
