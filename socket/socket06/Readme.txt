server
    socket -> connect -> read/write
client
	socket -> bind -> listen -> accept ->read/write
	
add by mengpl on 2014/10/22
usage : client ip/hostname port
usage : server port


add by mengpl on 2014/10/22
you can send more times to server
you can send a line to server

add by mengpl on 2014/10/23
server can accept more than one client one time
modify LOG micro

add by mengpl on 2014/11/03
based on socket04 add select