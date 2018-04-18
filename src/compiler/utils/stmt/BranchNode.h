//
// Created by bsampat5 on 4/13/2018.
//

#ifndef SER502_SPRING2018_TEAM15_BRANCHNODE_H
#define SER502_SPRING2018_TEAM15_BRANCHNODE_H


#include <string>
#include <ostream>
#include "StatementNode.h"

class BranchNode : public StatementNode{
    std::string name;
    Node* condition;
    Node* bodyBlock;
    Node* branch;

public:
    BranchNode( std::string &name, Node *condition, Node *bodyBlock, Node *branch);

    std::string getType();
};


#endif //SER502_SPRING2018_TEAM15_BRANCHNODE_H
