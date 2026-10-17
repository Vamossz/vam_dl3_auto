from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='vam_dl3_auto',
            executable='distance_sensor',
            name='distance_sensor',
            output='screen',
        ),
        Node(
            package='vam_dl3_auto',
            executable='auto_controller',
            name='auto_controller',
            output='screen',
        ),
    ])
