#!/bin/bash
ROOT_PATH=$(pwd)
CONF=$ROOT_PATH/conf/server.conf
BIN=$ROOT_PATH/udp_server
SERVER_PID=0

proc=$(basename $0)
function usage(){
	printf "%s%s\n" "Usage: $proc" " [start(-s)|stop(-t)|restart(-r)|status(-a)]"
}

function check_server()
{
	name=$(basename $BIN)
	is_exist=$(pidof $name)
	[ -z "$is_exist" ] && return 1
	SERVER_PID=$is_exist
	return 0
}

function start_server()
{
	if check_server; then
		echo "server is already exist"
		return 1
	fi
	local _ip=$(grep -E '^SERVER_IP:' $CONF | awk -F':' '{print $NF}')
	local _port=$(grep -E '^SERVER_PORT:' $CONF | awk -F':' '{print $NF}')
	$BIN "$_ip" "$_port"
	if check_server; then
		echo "server is start success..."
	else
		echo "server is start faile..."
	fi
}

function stop_server(){
	if ! check_server; then
		echo "server is not exist"
		return 1
	fi

	kill -9 $SERVER_PID

	if check_server; then
		echo "server stop failed..."
	else 
		echo "server stop success..."
	fi
}

function restart_server(){
	stop_server
	start_server
}

function status_server(){
	if check_server; then
		echo "server is running now, pid is : $SERVER_PID"
	else
		echo "server is not running now"
	fi
}

if [ $# -ne 1 ];then
	usage
	exit 1
fi

case $1 in
	'start' | '-s' )
		service iptables stop
		start_server
	;;
	'stop' | '-t' )
		stop_server
		service iptables start
	;;
	'restart' | '-r' )
		restart_server
	;;
	'status' | '-a' )
		status_server
	;;
	* )
		usage
		exit 2
	;;
esac
