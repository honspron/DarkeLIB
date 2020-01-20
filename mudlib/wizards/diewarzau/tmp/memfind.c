/*
 * A memory profiler to track down objects eating memory.
 */

class obj {
  string fname;
  int usage;
}

void find_eaters(int max) {
  class obj *mlist;
  object *objs, ob;
  int idx = -1;
  int i;
  int use;
  string out;
  
  if(max > 100) max = 100;
  mlist = allocate(max);
  objs = objects();
  foreach(ob in objs) {
    use = memory_info(ob);
    if(idx < 0) {
      mlist[0] = new(class obj);
      mlist[0]->fname = file_name(ob);
      mlist[0]->usage = use;
      idx = 0;
    } else if(use >= mlist[idx]->usage) {
      i = idx;
      while(i >= 0 && use >= mlist[i]->usage) {
        if(i + 1 < max)
          mlist[i + 1] = copy(mlist[i]);
         i--;
      }
      i++;
      mlist[i] = new(class obj);
      mlist[i]->fname = file_name(ob);
      mlist[i]->usage = use;
      if(idx < (max-1)) idx++;
    }
  }

  out = "Memory report:\n"
  "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
  for(i=0; i<max; i++) {
    if(!mlist[i]) continue;
    out += sprintf("%-40s  Usage: ", mlist[i]->fname);
    use = mlist[i]->usage;
    switch(use) {
    case 0..999:
    default:
      out += sprintf("%d\n", use);
      break;
    case 1000..999999:
      out += sprintf("%d,%03d\n", use/1000, use%1000);
      break;
    case 1000000..999999999:
      out += sprintf("%d,%03d,%03d\n", use/1000000, (use%1000000)/1000, use%1000);
      break;
    }
  }
  this_player()->more(explode(out, "\n"));
  return;
}

