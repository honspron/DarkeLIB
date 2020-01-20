#include <std.h>
#define EXCEPTS ({"spell.c","long_term_spell.c"})

inherit DAEMON;

void do_dump(string path);

int cmd_spelldump(string str)
{
   string path,file;

    seteuid(getuid(this_player()));
    path = "/std/spells";
   do_dump(path);
   return 1;
}

void do_dump(string path)
{
    object spell;
   string *files, name, skill, type;
   object *foo;
   int i,x,ct,mp,dev,fdev,level,notarget;

   files = get_dir(path+"/");

    write_file("/wizards/zortek/spell_list.txt", "Name\tSkill\tLevel\tTime\tMana\tDev\tFast Dev\tSpell Type\tNo Target");
    for(i = 0; i < sizeof(files); i++) {
    if(file_size(path+"/"+files[i]) == -1) continue;
    if(file_size(path+"/"+files[i]) == -2) continue;
    if(member_array(files[i], EXCEPTS) != -1) continue;
    if(catch(spell = new(path+"/"+files[i]))) {
      write_file("/wizards/zortek/spell_error.txt", files[i]+"\n");
      catch(spell->clean_up());
      continue;
    }
    if(!spell->is_spell()) { spell->cleanup(); continue; }
    name = spell->query_property("name");
    level = spell->query_property("spell level");
    skill = spell->query_property("skill");
    mp = spell->query_property("base mp cost");
    ct = spell->query_property("casting time");
    dev = spell->query_property("dev cost");
    fdev = spell->query_property("fast dev cost");
    type = spell->query_property("spell type");
    notarget = spell->query_property("no target");
    if(!name || name == "") name = base_name(spell);
    if(!level) level = 0;
    if(!mp) mp = 0;
    if(!ct) ct = 0;
    if(!dev) dev = 0;
    if(!fdev) fdev = 0;
    if(!type) type = "undefined";
    if(!notarget) notarget = 0;
    if(!skill || skill == "") skill = "NONE";
    write_file("/wizards/zortek/spell_list.txt",
      name+"\t"+
      skill+"\t"+
      level+"\t"+
      ct+"\t"+
      mp+"\t"+
      dev+"\t"+
      fdev+"\t"+
      type+"\t"+
      notarget+"\t"+
    );
    write("Name:  "+name);
   foo = children(path+"/"+files[i]);
   for(x=0;x<sizeof(foo);x++) destruct(foo[x]);
    }

   foo = children(path+"/_spelldump.c");
   foo = children("/wizards/zortek/bin/_spelldump.c");
   return;
}

int get_dirs(string file, string path)
{
   return (file_size(path+"/"+file) == -2);
}

int help() {
  write( @TEXT
Syntax: <find [directory to start] [filename]>

Finds the full path names of files with <filename> in their name.  If
[directory to start] is given, it will look in that dirdctory and
subdirectories; otherwise, it will use your current directory.

See also: work, diff, ex.
TEXT
  );
  return 1;
}
