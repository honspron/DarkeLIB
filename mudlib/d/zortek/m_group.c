/* FILE:    /adm/obj/master/m_group.c
 * AUTHOR:  zortek@trekverse
 * This is the master module for security group generation
 */
#include <database.h>

mapping generate_groups()
{
  string *lines;
  string grp,
         str;
  int i,
      max;

  groups = ([]);
  if(!(max=sizeof(lines=explode(read_file(GROUPS_DB), "\n"))))
  {
    write("ERROR: m_group.c->generate_groups(): corrupt groups database.\n");
//    shutdown();
    return;
  }
//ZNOTE: This needs to be a recursive function for Phase 3 support
  for(i=0; i<max; i++)
  {
    if(!lines[i] || lines[i] == "" || lines[i][0] == '#') continue;
    if(sscanf(lines[i], "(%s): %s", grp, str) != 2)
    {
      write("FAILURE: master.c->load_groups() Parse error line: "+(i+1)+".\n");
      shutdown();
      return;
    }
//ZNOTE: There should never be an empty group definition (but just in case)
    if(!sizeof(groups[grp] = explode(str, " ")))
      map_delete(groups, grp);
  }
  return groups;
}
