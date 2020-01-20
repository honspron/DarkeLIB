#include <socket.h>
 
#ifndef SOCKET
#define SOCKET "/adm/daemons/network/socket.c"
#endif
 
#define SOCK_MUD      0
#define SOCK_STREAM   1
#define SOCK_DATAGRAM 2
 
#define I3_MODULES		"/adm/daemons/network/I3/"
#undef I3_DEBUGGING
#define I3_ROUTER	"205.218.122.131 9000"
#define I3_PORT                 __PORT__+3
#define I3_MUDLIB		"Tmi-2 1.3 pre3"
#define I3_BASE_LIB		"Tmi-2 1.3 pre3"
#define I3_SAVE_FILE		"/adm/etc/I3"
#define I3_TTL                  5
#define I3_DAEMON		"/adm/daemons/network/I3"
#define I3_SERVICE_DETECT	"Yes"
#define I3_SERVICES	([ "ftp" : __PORT__ -1,\
			"smtp" : __PORT__ -4,\
			  "http" : __PORT__ -5 ])
 
#define PRT_AUTH_MUD_REPLY	"auth-mud-reply"
#define PRT_AUTH_MUD_REQ        "auth-mud-req"
#define PRT_MUDLIST             "mudlist"
#define PRT_STARTUP_REQ_1       "startup-req-1"
#define PRT_STARTUP_REPLY       "startup-reply"
#define PRT_ERROR               "error"
#define PRT_LOCATE_REQ          "locate-req"
#define PRT_LOCATE_REPLY        "locate-reply"
#define PRT_WHO_REQ             "who-req"
#define PRT_WHO_REPLY           "who-reply"
#define PRT_TELL		"tell"
#define PRT_FINGER_REQ		"finger-req"
#define PRT_FINGER_REPLY	"finger-reply"
#define PRT_CHANLIST_REQ	"chanlist-req"
#define PRT_CHANLIST_REPLY	"chanlist-reply"
#define PRT_CHANNEL_M		"channel-m"
#define PRT_CHANNEL_E		"channel-e"
#define PRT_CHANNEL_T		"channel-t"
 
#define SIZ_AUTH_MUD_REPLY      7
#define SIZ_AUTH_MUD_REQ        6
#define SIZ_MUDLIST             8
#define SIZ_STARTUP_REPLY       8
#define SIZ_LOCATE_REPLY        8
#define SIZ_LOCATE_REQ          7
#define SIZ_WHO_REQ             6
#define SIZ_WHO_REPLY           7
#define SIZ_TELL		8
#define SIZ_FINGER_REQ		7
#define SIZ_FINGER_REPLY	15
#define SIZ_CHANLIST_REQ	7
#define SIZ_CHANLIST_REPLY	8
#define SIZ_CHANNEL_M		9
#define SIZ_CHANNEL_E		9
#define SIZ_ERROR		9
#define SIZ_CHANNEL_T		13
 
/* OOB values are 0 for now */
#define OOB_TCP			(__PORT__ + 3)
#define OOB_UDP                 0
 
#define ROUTER_NAME             "*gjs"
#define MUD_STAGE		"Mudlib Development"

