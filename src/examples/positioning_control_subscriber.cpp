#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include "dynamixel_wrapper/dynamixel_wrapper.h"

class MotorStateController : public rclcpp::Node
{
public:
  MotorStateController()
  : Node("positioning_control_subscriber_node"),
    dxl_base_("/dev/ttyUSB2", 1000000),
    Motor0_(1, dxl_base_, dynamixel_wrapper::PH54_200_S500_R, 5),
    Motor1_(2, dxl_base_, dynamixel_wrapper::PH54_200_S500_R, 5),
    Motor2_(3, dxl_base_, dynamixel_wrapper::PH54_100_S500_R, 5),
    Motor3_(4, dxl_base_, dynamixel_wrapper::PH54_100_S500_R, 5),
    Motor4_(5, dxl_base_, dynamixel_wrapper::PH42_020_S300_R, 5),
    Motor5_(6, dxl_base_, dynamixel_wrapper::PH42_020_S300_R, 5)
  {
    
    enableMotor(Motor0_);
    enableMotor(Motor1_);
    enableMotor(Motor2_);
    enableMotor(Motor3_);
    enableMotor(Motor4_);
    enableMotor(Motor5_);

    sub_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "motor_state",
      10,
      std::bind(&MotorStateController::callback, this, std::placeholders::_1)
    );

    RCLCPP_INFO(this->get_logger(), "MotorStateController started");
  }

private:
  void enableMotor(dynamixel_wrapper::dynamixel_wrapper &m)
  {
    m.setTorqueEnable(false);
    m.setCurrentLimit(2000.0);
    m.setTorqueEnable(true);
  }

  void callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg)
  {
    if (msg->data.size() < 6) {
      RCLCPP_WARN(this->get_logger(), "motor_state size < 6");
      return;
    }

    Motor0_.setGoalPosition(msg->data[1]); // m15
    Motor1_.setGoalPosition(msg->data[0]); // m1
    Motor2_.setGoalPosition(msg->data[2]); // m0
    Motor3_.setGoalPosition(msg->data[5]); // m11
    Motor4_.setGoalPosition(msg->data[3]); // m13
    Motor5_.setGoalPosition(msg->data[4]); // m12
  }

  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr sub_;

  dynamixel_wrapper::dynamixel_wrapper_base dxl_base_;
  dynamixel_wrapper::dynamixel_wrapper Motor0_, Motor1_, Motor2_, Motor3_, Motor4_, Motor5_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MotorStateController>());
  rclcpp::shutdown();
  return 0;
}
