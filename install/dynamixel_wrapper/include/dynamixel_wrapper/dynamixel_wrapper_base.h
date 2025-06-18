/**
* @file dynamixel_wrapper_base.h
* @brief easy use for dynamixel_sdk
* @author Koki Aoyama
* @date 2025.6.12
* @details 
*/

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <string>
#include <dynamixel_sdk/dynamixel_sdk.h>

namespace dynamixel_wrapper {

class dynamixel_wrapper_base {
public:
    dynamixel_wrapper_base(const std::string& port_name, const int& baudrate, const float& protocol_version = 2.0);
    dynamixel_wrapper_base() {}

    dynamixel::PortHandler* portHandler;
    dynamixel::PacketHandler* packetHandler;

private:
    rclcpp::Logger logger_ = rclcpp::get_logger("dynamixel_wrapper_base");
};

dynamixel_wrapper_base::dynamixel_wrapper_base(const std::string& port_name, const int& baudrate, const float& protocol_version) {
    portHandler = dynamixel::PortHandler::getPortHandler(port_name.c_str());
    packetHandler = dynamixel::PacketHandler::getPacketHandler(protocol_version);

    if (!portHandler->openPort()) {
        RCLCPP_ERROR(logger_, "Failed to open the port!");
    }

    if (!portHandler->setBaudRate(baudrate)) {
        RCLCPP_ERROR(logger_, "Failed to set the baudrate!");
    }
}

}  // namespace dynamixel_wrapper