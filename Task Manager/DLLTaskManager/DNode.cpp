/*
 * DNode.cpp
 *
 *  Created on: Mar 10, 2022
 *      Author: winne
 */

#include <stdlib.h>
#include <iostream>
#include "DNode.hpp"
using namespace std;


DNode::DNode(string t, int p, int h, int m){
/*You need to write this!!!! */
	task=new Task(t, p, h, m);
	next = NULL;
	prev = NULL;
}


DNode::DNode(){
	task = NULL;
	next = NULL;
	prev = NULL;

}




