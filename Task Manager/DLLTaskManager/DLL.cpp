
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
//#include <stdlib.h>
//#include <d2d1_1helper.h>

using namespace std;


	DLL::DLL(){  // constructor - initializes an empty list
		last = NULL;
		first = NULL;
		numTasks = 0;
		tothrs = 0;
		totmin = 0;
	}
	DLL::DLL(string t, int p, int h, int m){  // constructor, initializes a list with one new node with data x
		DNode *n = new DNode (t,p,h,m);
		first = n;
		last = n;
		//cout<<"constructor first " <<first->task->priority<<" Task priority"<<endl;
		numTasks=1;
		tothrs = h;
		totmin = m;
	}

	/***************************************************************************************************/
	/*Part 1																																		*/
	/***************************************************************************************************/

	void DLL::push(string n, int p, int h, int m) {
    // does what you'd think, with a caveat that if the
	//priority isn't 3, it will move the task up to the end of the set of tasks with that priority.
	//In other words, if the priority is 1, it will traverse the list in reverse order until it finds a
	//task with a priority of 1, and insert the new task between the last task with a priority of
	//1 and the first task with a priority of 2
	//it also updates the total time of the list

		DNode *newNode=new DNode(n,p,h,m);
        DNode *tmp=last;

		if(tmp){
            //get to insertion point
            while( tmp->prev && tmp->task->priority>p){
                tmp=tmp->prev;
            }

            //make sure new node connects to the right nodes
            newNode->prev=tmp;

            //if temp has a node after make sure it points to new node
            if (tmp->next) {
                newNode->next=tmp->next;
                newNode->next->prev = newNode;
            }else{
                last=newNode;
            }
            //make sure next node is new node in list
            tmp->next=newNode;

        }else {
            first = newNode;
            last = newNode;
        }
        addTime(h,m);
        numTasks+=1;
	}
	Task *DLL::pop() {
	//does what you'd think - make sure to update the total time of the list.
	//Note -this isn’t all that necessary for this particular project, but I
	//kinda had to make you write pop because it’s //fundamental to so much of
	//linked list data type uses (e.g., stack, undo).
        removeTime(last->task->hr, last->task->min);
        Task *t=last->task;
		last=last->prev;
        last->next=NULL;
		delete last->next;
		numTasks-=1;
		return t;
	}

	void DLL::printList() {
		//prints out the entire list, along with the total time necessary to complete all tasks
		//on the list
		DNode *tmp=first;
		while(tmp){
			tmp->task->printTask();
			tmp=tmp->next;
		}
		cout<<"The total time to complete list of tasks is "<<tothrs<<":"<<totmin<<endl;

	}

	void DLL::printList(int p) {
		//print out only all the tasks with a priority of p, along with the total time necessary
		//to complete the tasks with a priority of p
		DNode *tmp=first;
        int prioritymin=0,priorityhrs=0;
		if(p<4&&p>0){
            while(tmp){
                if(tmp->task->priority>p) break;
                if(tmp->task->priority==p) {
                    prioritymin+=tmp->task->min;
                    priorityhrs+=tmp->task->hr;
                    tmp->task->printTask();
                }
                tmp=tmp->next;
            }

            priorityhrs+= prioritymin/60;
            prioritymin = prioritymin%60;
            cout<<"The total time to complete all tasks with a priority level "<<p<<" is "<<priorityhrs<<":"<<prioritymin<<endl;
		}else cout<<"This priority does not exist"<<endl<<endl;
	}

	void DLL::moveUp(int t) {
		// moves task with number tn up one in the list.
	    //If it is at the beginning of the list,
        //it will be moved to the end of the list.
		// NOTE: if this moves a task up before a task with a higher priority (1 is
		// higher priority than 2 - I know the wording is a bit weird), then this
		// changes the priority of the task being moved to that higher priority

		DNode *tmp=first;
        while(tmp&&tmp->task->tasknum!=t) tmp=tmp->next;
        if (tmp->prev){
            if (tmp->prev==first){

            }else {
//            if (tmp->prev->task->priority!= tmp->task->priority){
//                changePriority(tmp->task->tasknum,tmp->prev->task->priority);
//            }

                //is order matters deeply so I dont think this is parallelizable
                tmp->prev->next = tmp->next;
                if (tmp->next && tmp->next->prev) tmp->next->prev = tmp->prev;

                if (tmp->prev->prev) tmp->prev->prev->next = tmp;
                tmp->prev->prev = tmp;

                tmp->next = tmp->prev;
                tmp->prev = tmp->prev->prev;

                if (first->prev == tmp) first = tmp;
            }
        }else{
            first= tmp->next;
            first->prev= NULL;

            tmp->prev=last;
            last->next=tmp;

            last=tmp;
            last->next=NULL;
        }
        if(tmp->prev&&tmp->prev->task->priority!=tmp->task->priority){
            changePriority(tmp->task->tasknum,tmp->prev->task->priority);
        }

	}

	void DLL::listDuration(int *th, int *tm,int p) {
		// gets the list duration in hours and minutes (passed
		//in as pointers) of a particular priority (so the total time
		//needed to complete all tasks with priority of p)
		// I had you pass in the parameters as pointers for practice.
		DNode *tmpld=first;

		while(tmpld!=NULL){
			if(tmpld->task->priority==p){
				*th+=tmpld->task->hr;
				*tm+=tmpld->task->min;
			}
				tmpld=tmpld->next;
			}
		*th=*th+*tm/60;
		*tm=*tm%60;
		//cout<<*th<<"  "<<*tm<<endl;

	}


	void DLL::moveDown(int tn) {
		//moves task with task number tn down one in the list.
		//If it is at the end of the list, it will move to
		//beginning of the list.
		//NOTE: if this moves a task after a task with a lower priority (again, 3 is
		//a lower priority than 2) then this changes the priority of the task being
		//moved.

        DNode *tmp=first;
        while(tmp&&tmp->task->tasknum!=tn) tmp=tmp->next;
        if (tmp->next){
            if (tmp->next==last){

            }else{
                //this order matters deeply so I dont think this is parallelizable
                tmp->next->prev=tmp->prev;
                if(tmp->prev && tmp->prev->next) tmp->prev->next=tmp->next;

                tmp->prev=tmp->next;
                tmp->next=tmp->next->next;

                tmp->prev->next=tmp;
                tmp->next->prev=tmp;

                if(last->next==tmp) last=tmp;
            }

        }else{
            last=tmp->prev;
            last->next=NULL;

            tmp->next=first;
            first->prev=tmp;

            first=tmp;
            first->prev=NULL;

        }
//        if(tmp->next&&tmp->next->task->priority!=tmp->task->priority){
//            changePriority(tmp->task->tasknum,tmp->next->task->priority);
//        }
	}

	int DLL::remove(int tn) {
		//removes a task (based on its number) and updates the total time of the list
		//Make sure you link the next to the previous and the previous to the next.  The
		//biggest catch with this method is making sure you test to make sure the node
		//after and/or the node before the node you’re deleting aren’t NULL (i.e., you’re
		//not deleting the first or last node in the list)

		DNode *tmpr=first,*b,*i;

		while(tmpr&&tmpr->task->tasknum!=tn) tmpr=tmpr->next;
        if (!tmpr) return -1;
		b=tmpr->prev;
		i=tmpr->next;
		if(tmpr->prev==NULL){//first
			//cout<<"remove first"<<endl;
			i->prev=b;
			first=i;
		}else if(tmpr->next==NULL){//last
			//cout<<"remove last"<<endl;
			b->next=i;
			last=b;
		}else{
			//cout<<"remove "<<endl;
			i->prev=b;
			b->next=i;
		}

        removeTime(tmpr->task->hr,tmpr->task->min);
		return tmpr->task->tasknum;
	}

	void DLL::changePriority(int tn, int newp) {
		//changes the priority of the task.  This method also moves the task to the end
		//of the set of tasks with
		//that priority.  In other words, if you have the following:
		/*task1, 1, 2:20
		task2, 1, 3:20
		task3, 1, 1:15
		task4, 2, 3:10
		task5, 2, 1:10
		task6, 3, 3:15
		task7, 3, 2:54

		And you change task6’s priority to 1, the resulting list should be:
		task1, 1, 2:20
		task2, 1, 3:20
		task3, 1, 1:15
		task6, 1, 3:15
		task4, 2, 3:10
		task5, 2, 1:10
		task7, 3, 2:54
		*/

		DNode *tmppc=first;
		while(tmppc&&tmppc->task->tasknum!=tn) tmppc=tmppc->next;

		if(newp>0&&newp<4){
            if(tmppc->prev) {
                if (tmppc->prev->task->priority == newp) {
                    tmppc->task->priority = newp;
                }
            }else {
                moveDown(tn);
            }
		}
	}

	DLL::~DLL(){
		DNode *tmp = first;
		DNode *tmp2 = first->next;
		while (tmp != NULL) {
			delete tmp;
			tmp = tmp2;
			if (tmp != NULL) {
				tmp2 = tmp2->next;
			}
		}
		first = NULL;
		last = NULL;
		numTasks = 0;
		tothrs = 0;
		totmin = 0;
	}

	/******************Optional Helper Methods********************************/
	void DLL::addTime(int h, int m) {
        totmin += m%60;
        tothrs += h+totmin/60;
        totmin %= 60;
	}

	void DLL::removeTime(int h, int m) {
        if (m>totmin){
            h+=1;
            totmin=60+totmin-m;
        }
        else{
            totmin-=m;
        }
	    tothrs -= h;
    }
	/********************End of Optional Helper Methods ********************/
