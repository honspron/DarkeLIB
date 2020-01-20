// Wiz toy by Excelsior
// 6-7-96
// Do not remove this header


#include <daemons.h>

#define WHAT ({"a","b","c","d","e","f","g","h","i","j","k","l","m", \
	"n","o","p","q","r","s","t","u","v","w","x","y","z"," ","1","2","3","4","5", \
	"6","7","8","9","0","|","/",",",".",">","<","?","!","=","`","'","\"",":",";"})
#define TOP_LINE ({"/_\\","|_>","|~~","|~\\","|_~","|~~","/~_","|_|","~|~", \
	"~|~","|_/","|  ","A A","|\\|","|~|","|~|","|~|","|~|","(_~","~|~","| |", \
	"\\ /","|A|","\\_/","\\_/","~/ ","   ","/| ","~] ","~~/","/| ","[~", \
	"|_ ","~~/","[~]","[~]","[~]"," | "," /"," "," ","\\ ","/ ","~_)", \
	" | ","---","\\","/","||","o","o"})   
#define BOTTOM_LINE ({"| |","|_>","|__","|_/","|__","|~~","\\_/","| |","_|_", \
	"\\/ ","| \\","|__","|V|","| V","|_|","|~ ","|_\\","|~\\","__)"," | ", \
	"|_|"," V ","V V","/ \\"," | ","/_ ","   ","_|_","[_ ","__\\","~|~", \
	"_]","|_|"," / ","[~]"," ~|","[_]"," | ","/ ","/","o","/ ","\\ ", \
	" | "," o ","---"," "," ","  ","o","/" })

inherit "/std/Object";

string verb;

void init() {
	add_action("speak","speak");
	add_action("what_channel","set_channel");
}

int speak(string str) {
	int i,t,tmp;
	string top,bottom;
	i = strlen(str);
	t = 0;
	if(i < 1) {
		notify_fail("Loud speak what?\n");
		return 0;
	}
	top = "";
	bottom = "";
	str = lower_case(str);
	while( t < i ) {
		tmp = member_array(str[t..t],WHAT);
		if(tmp < 0) {
			write("Illegal character: "+str[t..t]);
			return 1;
		}
		top += TOP_LINE[tmp]+" ";
		bottom += BOTTOM_LINE[tmp]+" ";
		t++;
	}
	CHAT_D->do_chat(verb,"\n"+top+"\n"+bottom);
	return 1;
}

int what_channel(string str) {
	verb = str;
	write("Channel changed.");
	return 1;
}

void create() {
	::create();
	set_name("loudspeaker");
	set("short","loudspeaker");
	set("long","This is a nifty wiz toy by excelsior. Type 'set_channel <channel>' "+
		"to the channel you wish to speak over, and 'speak <mssg>' to make "+
		"use of this amplifier. Don't say anything too long or it wont fit.");
	set_value(1);
	set_weight(1);
	set_id(({"loudspeaker","speaker","toy","megaphone"}));
	verb = "darke";
}
