# Realtime_publisher_ROS2

Dedicating a whole CPU core to a particular program
    
on terminal type: 
$ sudo nano /etc/default/grub
to open the grub file.

Change the default line
GRUB_CMDLINE_LINUX_DEFAULT="quiet spash"
to
GRUB_CMDLINE_LINUX_DEFAULT="cpuidle.off=1 idle=poll isolcpus=0 nohz_full=5 maxcpus=6"

Save and exit grub file.

On terminal type:
$sudo update-grub

Exit and reboot.
