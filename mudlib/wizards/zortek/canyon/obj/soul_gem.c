#include <std.h>
#include <daemons.h>
inherit OBJECT;
string devil_name;
void create() {
   ::create();
   set("name", "gem");
   set("id", ({ "gem", "soul gem" }));
   set("short", "%^BOLD%^%^RED%^Soul Gem%^RESET%^");
   set("long",
	"This is a soul gem that contains the essence of a damned spirit.");
   set("weight", 100);
   set_value(10);
   set_property("enchantment",30);
   set_property("no save", 1);
}
void set_devil_name(string str) {
  devil_name = str;
  set("short", "%^BOLD%^%^RED%^Soul Gem of "+str+"%^RESET%^");
  return;
}
