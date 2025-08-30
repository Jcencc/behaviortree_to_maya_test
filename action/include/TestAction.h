//
// Created by 17203 on 2025/8/31.
//

#ifndef BEHAVIORTREE_TO_MAYA_TEST_TESTACTION_H
#define BEHAVIORTREE_TO_MAYA_TEST_TESTACTION_H
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/actions/set_blackboard_node.h"

using namespace BT;

class TestAction :public SyncActionNode{

public:
    TestAction(const std::string& name, const NodeConfig& config);

    NodeStatus tick() override;

    static PortsList providedPorts();
};



#endif //BEHAVIORTREE_TO_MAYA_TEST_TESTACTION_H