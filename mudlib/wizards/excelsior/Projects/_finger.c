#include <daemons.h>
#include <std.h>
#include <socket.h>

inherit DAEMON;

void remote_finger(object me, string target, string mud);

int cmd_finger(string str) {
    object ob;
    string wer, wo;
    if(!str)
      this_player()->more(explode((string)FINGER_D->general_finger_display(),
        "\n"));
    else if(sscanf(str, "%s@%s", wer, wo))
      remote_finger(this_player(), (wer ? wer : ""), wo);
    else
this_player()->more(explode((string)FINGER_D->user_finger_display(str),"\n"));
    return 1;
}

void remote_finger(object ob, string who, string mud) {
    int tc_flag, ud_flag, id;
    ud_flag = NETWORK_D->mud_exists(mud);
    if(!ud_flag && !tc_flag)
        message("info", sprintf("%s is not listed as part of the tcp or udp "
        "networks.", mud), this_player());
    else if(who == "" && !tc_flag)
      SERVICES_D->send_gfinger_q(mud, 0, this_player());
    else if(!tc_flag || (ud_flag && who != ""))
      SERVICES_D->send_gfinger_q(mud, who, this_player());
}
