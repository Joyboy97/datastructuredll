/*
 * MainDLL.cpp
 *
 *  Created on: Mar 10, 2022
 *      Author: winne
 */
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "TaskManager.hpp"
using namespace std;

int main() {
	srand(time(NULL));
    cout<<"hello world"<<endl;
	TaskManager *list = new TaskManager("ListofTasks.txt");
    list->list->pop()->printTask();
    cout<<endl;
    list->list->printList();
}

