#ifndef PROGRAM_H
#define PROGRAM_H

#include <QString>

class Program
{
public:
    Program();
    Program(QString name, int size, int id);
    int size;
    QString name;
    int id;
    int age;
    int reference_bit;
    Program* previous;
    Program* next;
};

#endif // PROGRAM_H
