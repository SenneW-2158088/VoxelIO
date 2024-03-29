//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_COMMAND_H
#define VOXELIO_COMMAND_H


template<class T>
class Command {
public:
    virtual ~Command() = default;

    virtual void execute(T *) = 0;

    virtual void undo(T *) = 0;
};


#endif //VOXELIO_COMMAND_H
