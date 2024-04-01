//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_COMMAND_H
#define VOXELIO_COMMAND_H


/**
 * @brief The Command class is an interface for all commands that can be executed on a given object.
 * @tparam T The type of object on which the command can be executed.
 */
template<class T>
class Command {
public:
    virtual ~Command() = default;

    virtual void execute(T *) = 0;

    virtual void undo(T *) = 0;
};


#endif //VOXELIO_COMMAND_H
