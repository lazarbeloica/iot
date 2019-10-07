 #! /bin/sh

 ### BEGIN INIT INFO
 # Provides:          noip
 # Required-Start:    $remote_fs $syslog
 # Required-Stop:     $remote_fs $syslog
 # Default-Start:     2 3 4 5
 # Default-Stop:      0 1 6
 # Short-Description: Simple script to start a program at boot
 ### END INIT INFO

 #change /direct/path/to/your/application to the path your application is in.
 cd /home/pi/pi_app      # example cd /home/pi/myprogram/

 #change YourProgramExactName to Exact name of your program that you want to auto start
 DEV_NAME=devTest6
 CHIP_NAME=bme280

 ./pi_app start ${DEV_NAME} ${CHIP_NAME} &> test-${DEV_NAME}_${CHIP_NAME}.log &

 exit 0