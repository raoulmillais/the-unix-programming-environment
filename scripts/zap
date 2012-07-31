#! /bin/bash
# zap: kill a process by name

PATH=/bin:/usr/bin

case $# in
	0) echo 'Usage: zap processname' 2>&1; exit 2;
esac

processname=$1; shift

ps aux | grep "${processname}" | sed 1q | awk '{print $2;}' | xargs kill ${@-\-9}
