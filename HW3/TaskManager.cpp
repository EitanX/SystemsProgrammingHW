#include "TaskManager.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include "Person.h"
#include "Task.h"
#include "SortedList.h"

using mtm::SortedList;
using std::ostream;
using std::string;

// C'tor:
TaskManager::TaskManager() : assignId(0) {}

// Our Functions:
// addPerson - creates person in the workers arrays
void TaskManager::addPerson(const std::string& name) {
    int i = 0;
    for (; i < this->MAX_PERSONS && this->workers[i].getName() != ""; i++){}
    if (i == 10) {
        throw std::runtime_error("");
    }
    this->workers[i] = Person(name);
}
// assignTaskId - straight forward
void TaskManager::assignTaskId(Task &task) {
    task.setId(this->assignId);
    this->assignId++;
}
// printTasksFromList - give a list, prints the tasks one by one
void TaskManager::printTasksFromList(const SortedList<Task> &list) const {
    SortedList<Task>::ConstIterator iter(list.begin());
    for (int i = 0; i < list.length(); ++i) {
        std::cout << (*iter) << std::endl;
        // making sure not going out of bounds
        if (i + 1 < list.length()) {
            ++iter;
        }
    }
}
// buildTaskListByConditionAndPrint - given a CONDITION, build list accordingly and calls printTasks
template<typename Condition>
void TaskManager::buildTaskListByConditionAndPrint(Condition condition) const {
    SortedList<Task> newList;

    // build a new list of all tasks sorted by priority:
    // only taking the tasks filtered by CONDITION
    for (int i = 0; i < this->MAX_PERSONS && this->workers[i].getName() != ""; ++i) {
        SortedList<Task>::ConstIterator iter(this->workers[i].getTasks().begin());
        const int amountOfTasks = this->workers[i].getTasks().length();
        for (int j = 0; j < amountOfTasks; ++j) {
            if (condition(*iter)) {
                newList.insert(*iter);
            }
            // making sure not going out of bounds
            if (j + 1 < amountOfTasks) {
                ++iter;
            }
        }
    }

    // start printing tasks one by one
    printTasksFromList(newList);
}

// HW Functions:
void TaskManager::assignTask(const std::string &personName, const Task &task) {
    Task newTask(task.getPriority(), task.getType(), task.getDescription());

    int i = 0;
    // find the person in the workers list
    // if not found, init this person.
    for (; i < this->MAX_PERSONS && this->workers[i].getName() != ""; i++) {
        if (this->workers[i].getName() == personName) {
            this->assignTaskId(newTask);
            this->workers[i].assignTask(newTask);
            return;
        }
    }

    this->addPerson(personName);
    this->assignTaskId(newTask);
    this->workers[i].assignTask(newTask);
}
void TaskManager::completeTask(const string &personName) {
    // straight forward
    for (int i = 0; i < this->MAX_PERSONS && this->workers[i].getName() != ""; i++) {
        if (this->workers[i].getName() == personName) {
            this->workers[i].completeTask();
            return;
        }
    }
}
void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    // non positive priority - just return.
    if(priority <= 0)
    {
        return;
    }

    // for eash person in Workers array
    for (int i = 0; i < this->MAX_PERSONS && this->workers[i].getName() !=""; ++i) {

        SortedList<Task> list = this->workers[i].getTasks();
        SortedList<Task> newList;
        // apply priorityBump with a filter, only on the wanted tasks.
        newList = list.apply([type, priority](Task task) {
            if (task.getType() == type) {
                const int newPriority = task.getPriority() + priority;
                Task newTask(newPriority, task.getType(), task.getDescription());
                newTask.setId(task.getId());
                return newTask;
            }
            // if the tast.type is not the wanted one, return task as is.
            return task;
        });

        // set the newList (after bump) to be the persons list of tasks.
        this->workers[i].setTasks(newList);
    }
}

// Methods:
void TaskManager::printAllEmployees() const {
    for (int i = 0; this->workers[i].getName() != "" && i < this->MAX_PERSONS; ++i) {
        // Person << Operator
        std::cout << this->workers[i] << std::endl;
    }
}
void TaskManager::printAllTasks() const {
    this->buildTaskListByConditionAndPrint([](const Task &task) {
        return true;
    });
}
void TaskManager::printTasksByType(TaskType type) const {
    this->buildTaskListByConditionAndPrint([type](const Task &task) {
        if (task.getType() == type) {
            return true;
        }
        return false;
    });
}
