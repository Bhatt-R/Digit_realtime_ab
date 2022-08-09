//R_B

#include <iostream>
#include <chrono>
#include <memory>

#include "rttest/rttest.h"
#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/int32.hpp"


using namespace std::chrono_literals;
using std::placeholders::_1;


class RTPublisher : public rclcpp::Node
{
public:

    RTPublisher(): Node("rt_pub_node"), count(0)            
    {
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("topic", 10);
        timer_ = this->create_wall_timer(1ms, std::bind(&RTPublisher::timer_callback, this));
    }

private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
    size_t count;

    void timer_callback() {                     
    
        auto message = std_msgs::msg::Int32();
        message.data = count++;
        publisher_->publish(message);
        
    }   
};

int main(int argc, char * argv[])
{
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);

    rclcpp::init(argc,argv);
    auto node = std::make_shared<RTPublisher>();

    int cpu_id = 0;
    cpu_set_t cpuset;
    auto spin_thread = std::thread(
        [&](){
            
            rclcpp::spin(node);
        }
    );
    const pid_t thread_ID = getpid();
    CPU_ZERO(&cpuset);
    CPU_SET(cpu_id, &cpuset);
    sched_setaffinity(thread_ID, sizeof(cpu_set_t), &cpuset);
    
    rttest_set_sched_priority(98, SCHED_RR);
    
    spin_thread.join();
    rclcpp::shutdown();
    return 0;
}

