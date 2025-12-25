/**
 * @file position_wrapper.cpp
 * @brief manual control node (ROS 2 version)
 * @author Koki Aoyama
 * @date 2025.6.16
 * @details Converted from ROS 1 to ROS 2 Humble
 */

#include <rclcpp/rclcpp.hpp>
#include "dynamixel_wrapper/dynamixel_wrapper.h"
#include <std_msgs/msg/float64_multi_array.hpp>
#include <iostream>
#include <string>
#include <cmath>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("positioning_node");

    rclcpp::Rate loop_rate(10.0);

    // ===== Publisher (motor_state) =====
    auto motor_state_pub =
        node->create_publisher<std_msgs::msg::Float64MultiArray>("motor_state", 10);
    std_msgs::msg::Float64MultiArray motor_state_msg;
    motor_state_msg.data.resize(8); 

    // Dynamixel hub setting
    std::string port0_name = "/dev/ttyUSB0";
    //std::string port1_name = "/dev/ttyUSB2";
    int baudrate = 1000000;
    dynamixel_wrapper::dynamixel_wrapper_base dxl_base0(port0_name, baudrate);
    //dynamixel_wrapper::dynamixel_wrapper_base dxl_base1(port1_name, baudrate);

    // Dynamixel motor setting
    int motor0_id = 2;
    int motor1_id = 1;
    int motor2_id = 0;
    int motor3_id = 15;
    int motor4_id = 14;
    int motor5_id = 13;
    int motor6_id = 12;
    int motor7_id = 11;
    /*int Motor0_id = 1;
    int Motor1_id = 2;
    int Motor2_id = 3;
    int Motor3_id = 4;
    int Motor4_id = 5;
    int Motor5_id = 6;*/

    int operating_mode = 5;  // e.g., current base position control
    int operating_mode2 = 1; // e.g.,current control
    dynamixel_wrapper::dynamixel_wrapper motor0(motor0_id, dxl_base0, dynamixel_wrapper::XH540_W270_T, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper motor1(motor1_id, dxl_base0, dynamixel_wrapper::XH540_W270_T, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper motor2(motor2_id, dxl_base0, dynamixel_wrapper::XH540_W270_T, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper motor3(motor3_id, dxl_base0, dynamixel_wrapper::XM430_W350_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper motor4(motor4_id, dxl_base0, dynamixel_wrapper::XM430_W350_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper motor5(motor5_id, dxl_base0, dynamixel_wrapper::XM430_W350_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper motor6(motor6_id, dxl_base0, dynamixel_wrapper::XM430_W350_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper motor7(motor7_id, dxl_base0, dynamixel_wrapper::XM430_W350_R, operating_mode);
    
    
    /*dynamixel_wrapper::dynamixel_wrapper Motor0(Motor0_id, dxl_base1, dynamixel_wrapper::PH54_200_S500_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper Motor1(Motor1_id, dxl_base1, dynamixel_wrapper::PH54_200_S500_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper Motor2(Motor2_id, dxl_base1, dynamixel_wrapper::PH54_100_S500_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper Motor3(Motor3_id, dxl_base1, dynamixel_wrapper::PH54_100_S500_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper Motor4(Motor4_id, dxl_base1, dynamixel_wrapper::PH42_020_S300_R, operating_mode);
    dynamixel_wrapper::dynamixel_wrapper Motor5(Motor5_id, dxl_base1, dynamixel_wrapper::PH42_020_S300_R, operating_mode);*/


    // motor configuration
    motor0.setTorqueEnable(false);
    motor1.setTorqueEnable(false);
    motor2.setTorqueEnable(false);
    motor3.setTorqueEnable(true);
    motor4.setTorqueEnable(false);
    motor5.setTorqueEnable(false);
    motor6.setTorqueEnable(true);
    motor7.setTorqueEnable(true);


    /*Motor0.setTorqueEnable(false);
    Motor0.setCurrentLimit(2000.0);
    Motor0.setTorqueEnable(true);

    Motor1.setTorqueEnable(false);
    Motor1.setCurrentLimit(2000.0);
    Motor1.setTorqueEnable(true);

    Motor2.setTorqueEnable(false);
    Motor2.setCurrentLimit(2000.0);
    Motor2.setTorqueEnable(true);

    Motor3.setTorqueEnable(false);
    Motor3.setCurrentLimit(2000.0);
    Motor3.setTorqueEnable(true);

    Motor4.setTorqueEnable(false);
    Motor4.setCurrentLimit(2000.0);
    Motor4.setTorqueEnable(true);

    Motor5.setTorqueEnable(false);
    Motor5.setCurrentLimit(2000.0);
    Motor5.setTorqueEnable(true);*/

    double goal_angle = 0.0;

    while (rclcpp::ok()) {

        motor3.setGoalPosition(180.0);
        motor6.setGoalPosition(180.0);
        motor7.setGoalPosition(180.0);

        double m2 = motor0.getPresentPosition() - 180.0;
        double m1 = motor1.getPresentPosition() - 270.0;
        double m0 = motor2.getPresentPosition() - 180.0;
        double m15 = - 1 * (motor3.getPresentPosition() + 180.0) / 3.0 -90.0;
        double m14 = motor4.getPresentPosition() - 180.0;
        double m13 = motor5.getPresentPosition() - 180.0;
        double m12 = motor6.getPresentPosition() - 180.0;
        double m11 = motor7.getPresentPosition() - 180.0;
        
        

        motor_state_msg.data[0] = m2;
        motor_state_msg.data[1] = m1;
        motor_state_msg.data[2] = m0;
        motor_state_msg.data[3] = m15;
        motor_state_msg.data[4] = m14;
        motor_state_msg.data[5] = m13;
        motor_state_msg.data[6] = m12;
        motor_state_msg.data[7] = m11;
        motor_state_pub->publish(motor_state_msg);

        /*Motor0.setGoalPosition(m15);
        Motor1.setGoalPosition(m1);
        Motor2.setGoalPosition(m0);
        Motor3.setGoalPosition(m11);
        Motor4.setGoalPosition(m13);
        Motor5.setGoalPosition(m12);
        motor1.setGoalCurrent(katapich_goal_current);
        motor2.setGoalCurrent(hiji_goal_current);*/
     

        /*RCLCPP_INFO(node->get_logger(), "Motor0 angle: %.2f [deg]", motor0.getPresentPosition());
        RCLCPP_INFO(node->get_logger(), "Motor1 angle: %.2f [deg]", motor1.getPresentPosition());
        RCLCPP_INFO(node->get_logger(), "Motor2 angle: %.2f [deg]", motor2.getPresentPosition());
        RCLCPP_INFO(node->get_logger(), "Motor3 angle: %.2f [deg]", motor3.getPresentCurrent());
        RCLCPP_INFO(node->get_logger(), "Motor4 angle: %.2f [deg]", motor4.getPresentCurrent());
        RCLCPP_INFO(node->get_logger(), "Motor5 angle: %.2f [deg]", motor5.getPresentPosition());   

        RCLCPP_INFO(node->get_logger(), "Motor0 angle: %.2f [deg]", Motor0.getPresentPosition());
        RCLCPP_INFO(node->get_logger(), "Motor1 angle: %.2f [deg]", Motor1.getPresentPosition());
        RCLCPP_INFO(node->get_logger(), "Motor2 angle: %.2f [deg]", Motor2.getPresentPosition());
        RCLCPP_INFO(node->get_logger(), "Motor3 angle: %.2f [deg]", Motor3.getPresentPosition());
        RCLCPP_INFO(node->get_logger(), "Motor4 angle: %.2f [deg]", Motor4.getPresentPosition());
        RCLCPP_INFO(node->get_logger(), "Motor5 angle: %.2f [deg]", Motor5.getPresentPosition());*/
        
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
