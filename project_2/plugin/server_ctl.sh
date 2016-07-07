#!/bin/bash
ROOT_PATH=$(pwd)
CONF=$ROOT_PATH/conf/server.conf
PROC=$(basename $0)
BIN=$ROOT_PATH/udp_server
SERVER_PID=
function check_server()
{
	name=$(basename $BIN)
	#procpid
	is_exit=$(pidof $name)
	#check is_exit is null?
	if [ -z "$is_exit" ];then
		SERVER_PID=$is_exit 
		return 1
	fi
	return 0
}

function server_start()
{
	if check_server ;then
		echo "server is already exit"
		return 1
	fi
	_ip=$(grep -E 'SERVER_IP:' $CONF)
	_port=$(grep -E 'SERVER_PORT:' $CONNF | 'awk -F: {print $NF}')
	$BIN $_ip $_port
	if check_server ;then
		echo "server is start success..."
	else
		echo "server is start fail..."
	fi
}
function server_stop()
{
	if ! check_server ;then
		echo "server is not ext"
		return 1
	fi
	kill -9 $SERVER_PID
	if check_server ;then
		echo "server is stop fail..."
	else
		echo "server is stop success..."
	fi
}
function server_restart()
{
	server_stop
	server_start
}
function server_stats()
{
	if check_server ;then
		echo "server is runing,proc_pid:$SERVER_PID"
	else
		echo "server is not exit..."
	fi
}
function Usage()
{
	echo "Usage:[ip][port][start/-s | stop/-t | restart/-r | stats/-a]"
	if [ $# -ne 1 ];then
		echo "Usage:[ip][port][start/-s | stop/-t | restart/-r | stats/-a]"
		exit 1
	fi
	case $1 in
		"start | -s" )
			server_start
			;;
		"stop | -t" )
			server_stop
			;;
		"restart | -r" )
			server_restart
			;;
		"stats | -a" )
			server_stats
			;;
		*)
			Usage
			exit 0
		;;
	esac
}
Usage
