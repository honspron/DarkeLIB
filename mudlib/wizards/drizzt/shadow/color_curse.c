//Thanks to Misery for his wordcurse, upon this was based.
//Created for DarkeMUD by Yoda 5-24-96
#include <std.h>
#include <security.h>
inherit "/std/spells/shadows/shadow";
private object me;
void sh_init(object ob)
{
/*    if(shadowp(ob)){}*/

    begin_shadow(ob);
    me = ob;
//    tell_object(find_living("yoda"),"bing");
    call_out("remove_me", random(60) + 85);
}

void receive_message(string msg_class, string msg)
{
    string *tmp, text;
    int i,p;
//    tell_object(find_living("yoda"),"bang");
    tmp = explode(msg, " ");
    for(i = 0; i < sizeof(tmp); i++)
    {
        text = (tmp[i]);
        if (stringp(text))
        {
          p = random(14);
          switch (p)
          {
            case 0:
             tmp[i]="%^BOLD%^%^WHITE%^"+text+"%^RESET%^";
             break;
            case 1:
             tmp[i]="%^RED%^"+text+"%^RESET%^";
             break;
            case 2:
             tmp[i]="%^BOLD%^%^RED%^"+text+"%^RESET%^";
             break;
            case 3:
             tmp[i]="%^GREEN%^"+text+"%^RESET%^";
             break;
            case 4:
             tmp[i]="%^BOLD%^%^GREEN%^"+text+"%^RESET%^";
             break;
            case 5:
             tmp[i]="%^YELLOW%^"+text+"%^RESET%^";
             break;
            case 6:
             tmp[i]="%^BOLD%^%^YELLOW%^"+text+"%^RESET%^";
             break;
            case 7:
             tmp[i]="%^BLUE%^"+text+"%^RESET%^";
             break;
            case 8:
             tmp[i]="%^BOLD%^%^BLUE%^"+text+"%^RESET%^";
             break;
            case 9:
             tmp[i]="%^MAGENTA%^"+text+"%^RESET%^";
             break;
            case 10:
             tmp[i]="%^BOLD%^%^MAGENTA%^"+text+"%^RESET%^";
             break;
            case 11:
             tmp[i]="%^CYAN%^"+text+"%^RESET%^";
             break;
            case 12:
             tmp[i]="%^BOLD%^%^CYAN%^"+text+"%^RESET%^";
             break;
            case 13:
             tmp[i]="%^WHITE%^"+text+"%^RESET%^";
             break;
          }

        }
    }
//  tell_object(find_living("yoda"),"boom");
    return me->receive_message(msg_class, implode(tmp, " "));
}

void remove_me() {
//  tell_object(find_living("yoda"),"kablooey");
//darkover.revnet.com 6000
    stop_shadow();
    remove();
}
