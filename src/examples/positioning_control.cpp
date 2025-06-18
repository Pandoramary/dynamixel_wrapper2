/**
 * @file position_wrapper.cpp
 * @brief manual control node (ROS 2 version)
 * @author Koki Aoyama
 * @date 2025.6.16
 * @details Converted from ROS 1 to ROS 2 Humble
 */

#include <rclcpp/rclcpp.hpp>
#include "dynamixel_wrapper/dynamixel_wrapper.h"

#include <iostream>
#include <string>
#include <cmath>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("positioning_node");

    rclcpp::Rate loop_rate(10.0);

    // Dynamixel hub setting
    std::string port0_name = "/dev/ttyUSB0";
    std::string port1_name = "/dev/ttyUSB1";
    int baudrate = 1000000;
    dynamixel_wrapper::dynamixel_wrapper_base dxl_base0(port0_name, baudrate);
    dynamixel_wrapper::dynamixel_wrapper_base dxl_base1(port1_name, baudrate);

    // Dynamixel motor setting
    int motor0_id = 11;
    int motor1_id = 12;
    int motor2_id = 13;
    int motor3_id = 14;
    int hiji_id = 3;
    int katayo_id = 1;
    int katapich_id = 2;
    int operating_mode = 5;  // e.g., current base position control
    int operating_mode2 = 1; // e.g.,current control
    dynamixel_wrapper::dynamixel_wrapper motor0(motor0_id, dxl_base0, dynamixel_wrapper::XM430_W350_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper motor1(motor1_id, dxl_base0, dynamixel_wrapper::XM430_W350_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper motor2(motor2_id, dxl_base0, dynamixel_wrapper::XM430_W350_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper motor3(motor3_id, dxl_base0, dynamixel_wrapper::XM430_W350_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper hiji(hiji_id, dxl_base1, dynamixel_wrapper::PH54_100_S500_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper katayo(katayo_id, dxl_base1, dynamixel_wrapper::PH54_200_S500_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper katapich(katapich_id, dxl_base1, dynamixel_wrapper::PH54_200_S500_R, operating_mode);


    // motor configuration
    motor0.setTorqueEnable(false);
    motor0.setCurrentLimit(200.0);
    motor0.setTorqueEnable(true);

    motor1.setTorqueEnable(false);
    motor1.setCurrentLimit(200.0);
    motor1.setTorqueEnable(true);

    motor2.setTorqueEnable(false);
    motor2.setCurrentLimit(200.0);
    motor2.setTorqueEnable(true);

    motor3.setTorqueEnable(false);
    motor3.setCurrentLimit(200.0);
    motor3.setTorqueEnable(true);

    hiji.setTorqueEnable(false);
    hiji.setCurrentLimit(1400.0);
    hiji.setTorqueEnable(true);

    katayo.setTorqueEnable(false);
    katayo.setCurrentLimit(1400.0);
    katayo.setTorqueEnable(true);

    katapich.setTorqueEnable(false);
    katapich.setCurrentLimit(3000.0);
    katapich.setTorqueEnable(true);

    double goal_angle = 0.0;

    while (rclcpp::ok()) {
        double katapich_goal_angle = motor1.getPresentPosition() - 180.0;
        double katayo_goal_angle = motor0.getPresentPosition();
        double hiji_goal_angle = motor2.getPresentPosition() - 90.0;
        double hiji_goal_current = hiji.getPresentCurrent()/ -10.0;
        double katapich_goal_current = katapich.getPresentCurrent()/ -10.0;


        motor0.setGoalPosition(0);
        motor1.setGoalPosition(180);
        motor2.setGoalPosition(90);
        motor3.setGoalPosition(180);
        katayo.setGoalPosition(katayo_goal_angle);
        katapich.setGoalPosition(katapich_goal_angle);
        hiji.setGoalPosition(hiji_goal_angle);
        /*motor1.setGoalCurrent(katapich_goal_current);
        motor2.setGoalCurrent(hiji_goal_current);*/
     

        RCLCPP_INFO(node->get_logger(), "Motor angle: %.2f [deg]", motor2.getPresentPosition());
        RCLCPP_INFO(node->get_logger(), "Motor angle: %.2f [deg]", hiji.getPresentPosition());
        RCLCPP_INFO(node->get_logger(), "Motor current: %.2f [mA]", hiji.getPresentCurrent());
        RCLCPP_INFO(node->get_logger(), "Motor current: %.2f [mA]", katapich.getPresentCurrent());
        RCLCPP_INFO(node->get_logger(), "Motor angle: %.2f [deg]", motor1.getPresentPosition());
        

        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
