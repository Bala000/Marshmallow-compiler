//
// Created by bsampat5 on 4/13/2018.
//

#ifndef SER502_SPRING2018_TEAM15_BREAKNODE_H
#define SER502_SPRING2018_TEAM15_BREAKNODE_H


#include <string>
#include <ostream>
#include "StatementNode.h"

class BreakNode : public StatementNode {
    std::string name;

public:
    BreakNode( std::string &name);
    std::string getType();
};


#endif //SER502_SPRING2018_TEAM15_BREAKNODE_H
