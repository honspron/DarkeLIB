#include "combine.h"
#include "count.h"
#include "cdebug.h"

#ifdef SYS_WIN32
#include "configNT.h"
#else
#include "config.h"
#endif


/*
 *  ParseAuthorizationList() -   parses the authorization list
 *
 *  RCS:
 *      $Revision: 2.3 $
 *      $Date: 1996/05/03 02:20:22 $
 *
 *  Security:
 *      Unclassified
 *
 *  Description:
 *      text
 *
 *  Input Parameters:
 *      type    identifier  description
 *
 *      text
 *
 *  Output Parameters:
 *      type    identifier  description
 *
 *      text
 *
 *  Return Values:
 *      value   description
 *
 *  Side Effects:
 *      text
 *
 *  Limitations and Comments:
 *      text
 *
 *  Development History:
 *      who                 when        why
 *      muquit@semcor.com   05-Jun-95   first cut
 */

int ParseConfig ()
{
    FILE
        *fp;

    int
        i;

    char
        buf[MaxLineLength+1];

    i=0;

    *buf='\0';
    (void) sprintf(buf,"%s/%s",ConfigDir,ConfigFile);
    fp = fopen(buf, "r");
    if (fp == (FILE *) NULL)
    {
        return (ConfigOpenFailed);
    }

    /*
    ** first block: automatic file creation. If the block contains 1,
    ** automatic file creation is allowed. if 0, not allowed.
    ** automatic file creation is a bad thing, but some sites may want
    ** it because they are running their server behind a firewall and
    ** they trust their users
    ** BLOCK 1
    */

    *buf='\0';
    (void) GetLine(fp, buf);
    if (strcmp(buf, "{") != 0)
    {
        (void) fclose ((FILE *) fp);
        return(NoAutofcBlock);
    }
    while (True)
    {
        if (!GetLine (fp, buf))
        {
            (void) fclose ((FILE *) fp);
             return (UnpexpectedEof);                       
        }
        if (strcmp(buf, "}") == 0)
            break;
        RemoveTrailingSp (buf);
        Gauto_file_creation=atoi(buf);
    }

    /*
    ** strict mode block
    ** BLOCK 2
    */
    *buf='\0';
    (void) GetLine(fp, buf);
    if (strcmp(buf, "{") != 0)
    {
        (void) fclose ((FILE *) fp);
        return(NoStrictBlock);
    }
    while (True)
    {
        if (!GetLine (fp, buf))
        {
            (void) fclose ((FILE *) fp);
             return (UnpexpectedEof);                       
        }
        if (strcmp(buf, "}") == 0)
            break;
        RemoveTrailingSp (buf);
        Gstrict_mode=atoi(buf);
    }

    /*
    ** rgb coloname lookup 
    ** BLOCK 3
    */
    *buf='\0';
    (void) GetLine(fp, buf);
    if (strcmp(buf, "{") != 0)
    {
        (void) fclose ((FILE *) fp);
        return(NoRgbMappingBlock);
    }
    while (True)
    {
        if (!GetLine (fp, buf))
        {
            (void) fclose ((FILE *) fp);
             return (UnpexpectedEof);                       
        }
        if (strcmp(buf, "}") == 0)
            break;
        RemoveTrailingSp (buf);
        GrgbMappingIsError=atoi(buf);
    }

    /*
    ** ignore count block
    ** BLOCK 4
    */
    *buf='\0';
    (void) GetLine (fp, buf);
    if (strcmp (buf, "{") != 0)
    {
        (void) fclose ((FILE *) fp);
        return (NoIgnoreHostsBlock);
    }

    while (True)
    {
        if (!GetLine (fp, buf))
        {
            (void) fclose ((FILE *) fp);
            return (UnpexpectedEof);
        }

        if (strcmp(buf, "}") == 0)
            break;
        RemoveTrailingSp (buf);
        GignoreSite[Gsite++] = mystrdup (buf);
    }

        if (Gsite > 0)
        {
            Debug2("Ignore Hosts:",0,0);
        }
        else
        {
            Debug2("Will count access from any host",0,0);
        }
        for (i=0; i < Gsite; i++)
        {
            Debug2("Site[%d] %s",i,GignoreSite[i]);
        }

#ifdef ACCESS_AUTH
    (void) GetLine (fp, buf);
    if (strcmp(buf, "{") != 0)
    {
       (void) fclose ((FILE *) fp);
        return (NoRefhBlock);
    }
    while (True)
    {
        if (!GetLine (fp, buf))
        {
            (void) fclose ((FILE *) fp);
            return (UnpexpectedEof);
        }
        if (strcmp (buf, "}") == 0)
            break;
        RemoveTrailingSp (buf);
        GrefererHost[Grhost++]= mystrdup(buf);

    }

        if (Grhost > 0)
        {
            Debug2("-Referer Hosts-",0,0);
        }
        else
        {
            Debug2("Grhost: %d", Grhost,0);
        }
        for (i=0; i < Grhost; i++)
        {
            Debug2("Referer[%d] %s",i,GrefererHost[i]);
        }

#endif /* ACCESS_AUTH */
    (void) fclose ((FILE *) fp);
    return (0);
}

#ifdef TEST

void main (argc, argv)
int
    argc;
char
    **argv;
{
    ParseAuthorizationList ();
}
#endif /* TEST */


/*
 *  GetLine () - reads a line from the passed file pointer and puts the
 *               line in the passed array
 *
 *  RCS:
 *      $Revision: 2.3 $
 *      $Date: 1996/05/03 02:20:22 $
 *
 *  Security:
 *      Unclassified
 *
 *  Description:
 *      borrowed from wusage 2.3
 *
 *  Input Parameters:
 *      type    identifier  description
 *
 *      text
 *
 *  Output Parameters:
 *      type    identifier  description
 *
 *      text
 *
 *  Return Values:
 *      value   description
 *
 *  Side Effects:
 *      text
 *
 *  Limitations and Comments:
 *      text
 *
 *  Development History:
 *      who                 when        why
 *      muquit@semcor.com   05-Jun-95   first cut
 */

int GetLine (fp, string)
FILE
    *fp;
char
    *string;
{
    int
        s,
        i;

    int
        length;

    char
        *x;
    while (!feof (fp))
    {
        x = fgets (string, 80, fp);
        if (x == (char *) NULL)
            return (0);

        if (*string == '#') /* a comment */
            continue;

        if (string[(int) strlen(string)-1] == '\n')
            string[(int) strlen(string)-1] = '\0'; /* NULL terminate*/

        if (*string == '\0')
            continue;

        length = (int) strlen(string);
        s=0;

        for (i=0; i < length; i++)
        {
            if (isspace (string[i]))
                s++;
            else
                break;
        }

        if (s)
        {
            char buf[81];
            (void) strcpy (buf, string+s);
            (void) strcpy(string,buf);
        }

        length = (int) strlen(string);
        for (i=(length-1); i >= 0; i--)
        {
            if (isspace(string[i]))
                string[i]='\0';
            else
                break;
        }
        return (1);
    }
    return (0);
}

/*
** from wusage 2.3
*/
void RemoveTrailingSp (string)
char
    *string;
{
    while (True)
    {
        int
            l;

        l = (int) strlen (string);
        if (!l)
            return;

        if (string[l-1] == ' ')
            string[l-1] = '\0';
        else
            return;
    }
}

/*
** duplicate a string
*/
char *mystrdup (string)
char
    *string;
{
    char
        *tmp;

    if (string == (char *) NULL)
        return ((char *) NULL);

    tmp = (char *) malloc ((int) strlen(string) + 1);

    if (tmp == (char *) NULL)
        return ((char *) NULL);

    (void) strcpy(tmp, string);
    return (tmp);
}

/*
** check if the data file has correct ownership
*/

/*
** Return values
** 0 - nothing matches (group or owner)
** 1 - owner of the file and the owner found in query string matches
** 2 - memory allocation problem
** 3 - owner of the file and the owner found in query string matches but
**     the group id of the child process of httpd and the group id of the
**     file does not match
*/

#ifdef _USE_ME_PLEASE_
int CheckOwner (owner,file)
char
    *owner;
char
    *file;
{
    char
        *tmp;

    struct stat
        statbuf;

    int
        uid,
        gid;

    struct passwd
        *p;

    tmp = mystrdup(owner);
    if (tmp == (char *) NULL)
        return 2;

    while ((p=getpwent()) != NULL)
    {
        if (strcmp(tmp, p->pw_name) == 0)
        {
            uid = p->pw_uid;                        
            stat(file, &statbuf);
            if (uid == statbuf.st_uid)
            {
                /*
                ** now check the group id of the child process of httpd
                ** and group id of the data file, they must match
                */
                gid = getgid();
                if (gid != statbuf.st_gid)
                {
                    char
                        buf[BUFSIZ];
                    *buf = '\0';
                    (void) sprintf (buf, "Group Id of the counter data file \"%s\" is %d, it should be %d, httpd's child processes run with group id %d",file,statbuf.st_gid,gid,gid);
                Warning(buf);
                (void) free ((char *) tmp);
                    return 3;
                }
                (void) free ((char *) tmp);
                return (1);
            }
            else
            {
                (void) free ((char *) tmp);
                return (0); 
            }
        } 
    }

    (void) free ((char *) tmp);
    return (0);
}
#endif /* _USE_ME_PLEASE */
/*
 *  ParseQueryString() - parses the QUERY_STRING for Count.cgi
 *
 *  RCS:
 *      $Revision: 2.3 $
 *      $Date: 1996/05/03 02:20:22 $
 *
 *  Security:
 *      Unclassified
 *
 *  Description:
 *      text
 *
 *  Input Parameters:
 *      type    identifier  description
 *
 *      char        *qs
 *      DigitInfo   *digit_info
 *      FrameInfo   *frame_info
 *
 *  Output Parameters:
 *      type    identifier  description
 *
 *      DigitInfo   *digit_info
 *      FrameInfo   *frame_info
 *
 *  Return Values:
 *      value   description
 *      0   on success
 *      1   on failure
 *
 *  Side Effects:
 *      text
 *
 *  Limitations and Comments:
 *      text
 *
 *  Development History:
 *      who                 when        why
 *      muquit@semcor.com   22-Aug-95   first cut
 */

int ParseInteger(given,sets,min,max)
char
    *given;
int
    *sets;
int
    min,
    max;
{
    if (sscanf(given, "%d", sets) == 1)
    {
        *sets = AbsoluteValue(*sets);
        if (*sets >= min && ( max == 0 || *sets <= max ))
            return(True);
    }
    return(False);
}

int ParseDigitsString(given,sets,maxlen)
char 
    *given;
char 
    *sets;
int 
    maxlen;
{
    for ( ; *given != (char) 0; given++, sets++, maxlen-- )
    {
        if (isdigit(*given) && maxlen >= 0)
            *sets = *given;
        else
            return(False);
    }
    return(True);
}

int ParseOptionString(given,sets)
char
    *given;
int
    *sets;
{
   if (mystrcasecmp(given,"counter") == 0)
   {
        *sets=SHOW_COUNTER;
        return (True);
   } 
   else if (mystrcasecmp(given,"clock") == 0)
   {
        *sets=SHOW_CLOCK;
        return (True);
   }
   else if (mystrcasecmp(given,"date") == 0)
   {
        *sets=SHOW_DATE;
        return (True);
   }
   else if (mystrcasecmp(given,"image") == 0)
   {
        *sets=SHOW_GIF_FILE;
        return (True);
   }
   else
        return (False);

return (False);
}

int ParseDateFormat(given,sets)
char
    *given;
int
    *sets;
{
    if (mystrcasecmp(given,"MMDDYY") == 0)
    {
       *sets=DATE_MMDDYY;
       return(True); 
    }
    else if (mystrcasecmp(given,"DDMMYY") == 0)
    {
       *sets=DATE_DDMMYY;
       return(True); 
    }
    else if (mystrcasecmp(given,"YYMMDD") == 0)
    {
       *sets=DATE_YYMMDD;
       return(True); 
    }
    else if (mystrcasecmp(given,"YYDDMM") == 0)
    {
       *sets=DATE_YYDDMM;
       return(True); 
    }
    else if (mystrcasecmp(given,"MMYYDD") == 0)
    {
       *sets=DATE_MMYYDD;
       return(True); 
    }
    else if (mystrcasecmp(given,"DDYYMM") == 0)
    {
       *sets=DATE_MMYYDD;
       return(True); 
    }
    else
        return (False);

return (False);
}

int ParseBool(given,sets )
char 
    *given;
int 
    *sets;
{
    if ((int)strlen(given) != 1)
        return(False);

    switch(*given)
    {
        case '1':
        case 'T':
        case 't':
        case 'Y':
        case 'y':
            *sets = True;
            break;
        case '0':
        case 'F':
        case 'f':
        case 'N':
        case 'n':
            *sets = False;
            break;
        default:
            return(False);
    }
    return(True);
}

#if __STDC__
int ParseRGB(char *given,unsigned char *set_r,unsigned char *set_g,
    unsigned char *set_b)
#else
int ParseRGB(given,set_r,set_g,set_b)
char 
    *given;
unsigned char 
    *set_r, 
    *set_g, 
    *set_b;
#endif
{
    int
        rc,
        red, 
        green, 
        blue, 
        items,
        found = False;

    FILE 
        *handle = NULL;

    char
        rgbname[MaxLineLength],
        fromfile[MaxLineLength],
        *emsg = fromfile;                   /* Reuse space! */

    rc=True;
    /*rc=sscanf(given, "%d;%d;%d",&red,&green,&blue);*/

    if ((sscanf(given, "%d;%d;%d",&red,&green,&blue) == 3) ||
        (sscanf(given,"%02x%02x%02x",&red,&green,&blue) == 3) ||
        (sscanf(given,"#%02x%02x%02x",&red,&green,&blue) == 3) ||
        (sscanf(given,"%*02x%02x%*02x%02x%*02x%02x",&red,&green,&blue) == 6)||
        (sscanf(given,"#%*02x%02x%*02x%02x%*02x%02x",&red,&green,&blue) == 6))
    {
        rc=True;
    }
    else
        rc=False;


    if (rc == False) 
    {
        handle=fopen(RgbMappingDict, "r");
        if (handle != (FILE *) NULL)
        {
            while(fgets(fromfile, sizeof(fromfile), handle) )
            {
                /*items=sscanf(fromfile,"%d %d %d %s %*s",
                    &red,&green,&blue,rgbname);*/
                items=sscanf(fromfile,"%d %d %d %[^\n]\n",
                    &red,&green,&blue,rgbname);
                 if (items != 4)
                    continue;
                 if (mystrcasecmp(rgbname, given) == 0)
                 {
                    if ( Gdebug == True )
                       fprintf(stderr, "Found \"%d %d %d %s\" in %s\n",
                               red, green, blue, rgbname, RgbMappingDict);
                        if (GrgbMappingIsError == 1)
                        {
                            sprintf(emsg, "Please specify \"%d;%d;%d\" instead of \"%s\" for color.", red, green, blue, rgbname);
                            PrintHeader();
                            StringImage(emsg);
                        }
                        else
                        {
                            found=True;
                            break;
                        }
                   }
            }
            (void) fclose(handle);
            if ( found == False )
                return(False);
        }
    }

    if ( red   < 0 ) red   = 0; else if ( red   > MaxRGB ) return(False);
    if ( green < 0 ) green = 0; else if ( green > MaxRGB ) return(False);
    if ( blue  < 0 ) blue  = 0; else if ( blue  > MaxRGB ) return(False);

    *set_r = (unsigned char) red;
    *set_g = (unsigned char) green;
    *set_b = (unsigned char) blue;
    return(True);
}

int ParseSize(given,set_w,set_h )
char
    *given;
int 
    *set_w, 
    *set_h;
{
    int
        rc;

    rc=sscanf(given, "%d;%d", set_w, set_h);

    if (rc != 2)
        return(False);

    *set_w = AbsoluteValue(*set_w);
    *set_h = AbsoluteValue(*set_h);
    return(True);
}

int ParseError(keyword, value, current_rc, blurb)
char
    *keyword,
    *value;
int
    current_rc;
char
    *blurb;
{
    char 
        emsg[MaxTextLength];

    sprintf(emsg, "Parameter \"%s=\" followed by %s value \"%s\"", 
        keyword, blurb, value);

    PrintHeader();
    StringImage(emsg);
    current_rc++;
    return(current_rc);
}

int ParseQueryString(qs, digit_info, frame_info)
char
    *qs;
DigitInfo
    *digit_info;
FrameInfo
    *frame_info;
{
    char
        emsg[MaxTextLength],
        query_string[MaxTextLength];

    char
        *keyword,
        *value,
        *p;

    int
        dummy;

    int
        rc=0;

#define MissingValue    DefaultThickness

    /*
    ** default opaque color. 
    */
    digit_info->replace_color=False;
    digit_info->opaque_red=(unsigned char) 0;
    digit_info->opaque_green=(unsigned char) 255;
    digit_info->opaque_blue=(unsigned char) 0;

    digit_info->pen_red=(unsigned char) 0;
    digit_info->pen_green=(unsigned char) 255;
    digit_info->pen_blue=(unsigned char) 255;

    frame_info->width=(unsigned int) MissingValue;
    digit_info->alpha=(unsigned int) MissingValue;
    digit_info->width=(unsigned int) 15;
    digit_info->height=(unsigned int) 20;
    digit_info->maxdigits=(int) DefaultMaxDigits;
    digit_info->leftpad=(unsigned int) DefaultLeftpad;
    frame_info->matte_color.red=(unsigned char) Default_FrameRed;
    frame_info->matte_color.green=(unsigned char) DefaultFrameGreen;
    frame_info->matte_color.blue=(unsigned char) DefaultFrameBlue;
    digit_info->alpha_red=(unsigned char) DefaultTransparentRed;
    digit_info->alpha_green=(unsigned char) DefaultTransparentGreen;
    digit_info->alpha_blue=(unsigned char) DefaultTransparentBlue;
    digit_info->st=(unsigned int) DefaultStartCount;
    digit_info->show=(unsigned int) DefaultShowCount;
    digit_info->increment_counter=(unsigned int) True;
    digit_info->negate=False;
    digit_info->rotate=False;
    digit_info->rotate_degrees=270;
    (void) strcpy(digit_info->datafile,DefaultDatafile);
    (void) strcpy(digit_info->ddhead,DefaultDigitsStyle);
    *digit_info->literal = '\0';
    digit_info->display_type=SHOW_COUNTER;
    *digit_info->time_z='\0';
    digit_info->date_format=DATE_MMDDYY;
    digit_info->time_format=12;
    digit_info->use_strip=True;
    digit_info->comma=False;
    digit_info->nsegment=15;
    *digit_info->gif_file='\0';

    (void) strcpy(query_string,qs);
    p = query_string;

    Debug2("Parsing \"%s\"",p,0);

    while((keyword=mystrtok(p, "=")) != (char *) NULL)
    {
        p = (char *) NULL;
        value=mystrtok(p,ParamDelimiters);
        if (value == (char *) NULL)
        {
            (void) sprintf(emsg,
                "Parameter \"%s=\" requires a value\n", keyword);
            PrintHeader();
            StringImage(emsg);
            rc++;
            break;
        }

        Debug2("Keyword={%s}; value={%s}",keyword,value);

        /********************************************************************
        * Use of "mystrcasecmp()" is slow but fast to implement.  Will fix.
        * Error return does not occur until after entire query string is
        * parsed; this allows all errors to be shown to user in first pass.
        * Hence "rc" is incremented with each error found.
        ********************************************************************/
        if (mystrcasecmp(keyword,"ft") == 0)
        {
            if (!ParseInteger(value,&dummy,0,255))
                rc = ParseError(keyword,value,rc,
                    "badly specified frame thickness");
            else
                frame_info->width= (unsigned int) dummy;
        }
        else if (mystrcasecmp(keyword,"frgb") == 0)
        {
            if ( ! ParseRGB(value,
                &(frame_info->matte_color.red),
                &(frame_info->matte_color.green),
                &(frame_info->matte_color.blue)))
                rc = ParseError(keyword,value,rc,"badly specified RGB");
            if ( frame_info->width == MissingValue )
                frame_info->width= (unsigned int) FRGB_ImpliedFt;

        }
        else if (mystrcasecmp(keyword,"chcolor") == 0)
        {
            if (!ParseBool(value, &dummy))
                rc = ParseError(keyword,value,rc,"non-Boolean");
            else
                digit_info->replace_color=(unsigned int) dummy;
        }
        else if (mystrcasecmp(keyword,"srgb") == 0)
        {
            if (!ParseRGB(value,
                &(digit_info->opaque_red),
                &(digit_info->opaque_green),
                &(digit_info->opaque_blue)))
                rc=ParseError(keyword,value,rc,
                    "badly specified source RGB");
        }
        else if (mystrcasecmp(keyword,"prgb") == 0)
        {
            if (!ParseRGB(value,
                &(digit_info->pen_red),
                &(digit_info->pen_green),
                &(digit_info->pen_blue)))
                rc=ParseError(keyword,value,rc,
                    "badly specified pen RGB");
            else
                digit_info->replace_color=True;
        }
        else if (mystrcasecmp(keyword,"tr") == 0)
        {
            if (!ParseBool(value,&dummy))
                rc = ParseError(keyword,value,rc,"non-Boolean");
            else
                digit_info->alpha=(unsigned int) dummy;
        }
        else if (mystrcasecmp(keyword, "trgb") == 0)
        {
            if ( ! ParseRGB(value,
                &(digit_info->alpha_red),
                &(digit_info->alpha_green),
                &(digit_info->alpha_blue)))
                rc = ParseError(keyword,value,rc,"badly specified RGB");
            if ( digit_info->alpha == MissingValue )
                digit_info->alpha = (unsigned int) TRGBImpliedTr;
        }
        else if (mystrcasecmp(keyword,"md") == 0)
        {
            if (!ParseInteger(value,&(digit_info->maxdigits),5,10))
                rc = ParseError(keyword,value,rc,"bad max digits");
        }
        else if (mystrcasecmp(keyword,"pad") == 0)
        {
            if (!ParseBool(value, &dummy))
                rc = ParseError(keyword,value,rc,"non-Boolean");
            else
                digit_info->leftpad=(unsigned int) dummy;
        }
        else if (mystrcasecmp(keyword,"dd") == 0)
        {
            (void) strcpy(digit_info->ddhead,value);
        }
        else if (mystrcasecmp(keyword,"st") == 0)
        {
            if (!ParseInteger(value, &dummy, 1,999999999))
                rc = ParseError(keyword,value,rc,"bad starting");
            else
                digit_info->st=(unsigned int) dummy;
        }
        else if (mystrcasecmp( keyword, "sh") == 0)
        {
            if (!ParseBool(value, &dummy))
                rc = ParseError(keyword,value,rc,"non-Boolean");
            else
                digit_info->show=(unsigned int) dummy;
        }
        else if (mystrcasecmp(keyword,"istrip") == 0)
        {
            if (!ParseBool(value, &dummy))
               rc = ParseError(keyword,value,rc,"non-Boolean");
            else
               digit_info->use_strip=(unsigned int) dummy;

        }
        else if (mystrcasecmp(keyword,"comma") == 0)
        {
            if (!ParseBool(value, &dummy))
               rc = ParseError(keyword,value,rc,"non-Boolean");
            else
               digit_info->comma=(unsigned int) dummy;
        }
        else if (mystrcasecmp(keyword,"nsegment") == 0)
        {
            if (!ParseInteger(value, &(digit_info->nsegment), 1,999999999))
                rc = ParseError(keyword,value,rc,"bad starting");
        }
        else if (mystrcasecmp(keyword,"df") == 0)
        {
            (void) strcpy(digit_info->datafile,value);
        }
        else if (mystrcasecmp( keyword,"incr") == 0)
        {
            if (!ParseBool(value, &dummy))
                rc = ParseError(keyword,value,rc,"non-Boolean");
            else
                digit_info->increment_counter=(unsigned int) dummy;
        }
        else if (mystrcasecmp( keyword,"negate") == 0)
        {
            if (!ParseBool(value, &dummy))
                rc = ParseError(keyword,value,rc,"non-Boolean");
            else
                digit_info->negate=(unsigned int) dummy;
        }
        else if (mystrcasecmp( keyword,"wxh") == 0)
        {
            /*
            ** do nothing, this keyword is here just for backward
            ** compatibility with Count 1.5. in the current version
            ** we determine digit dimensions automatically
            */
        }
        else if (mystrcasecmp( keyword,"rotate") == 0)
        {
            if (!ParseBool(value, &dummy))
                rc = ParseError(keyword,value,rc,"non-Boolean");
            else
                digit_info->rotate=(unsigned int) dummy;
        }
        else if (mystrcasecmp(keyword,"degrees") == 0)
        {
            if (!ParseInteger(value,&(digit_info->rotate_degrees),90,360))
                rc = ParseError(keyword,value,rc,
                    "badly specified rotation angle");
            else
                digit_info->rotate=True;
        }
        else if (mystrcasecmp(keyword,"lit") == 0)
        {
     /*if ( ! ParseDigitsString(value, digit_info->literal,MaxTextLength))*/
           if (!ParseLiteralString(value,digit_info->literal,100))
                rc = ParseError(keyword,value,rc,"un-supported or oversized");
        }
        else if (mystrcasecmp(keyword,"display") == 0)
        {
            if (!ParseOptionString(value,&(digit_info->display_type)))
                rc=ParseError(keyword,value,rc,"unknown");
        }
        else if (mystrcasecmp(keyword,"image") == 0)
        {
            digit_info->display_type=SHOW_GIF_FILE;
            (void) strncpy(digit_info->gif_file,value,100);
        }
        else if (mystrcasecmp(keyword,"dformat") == 0)
        {
            if (!ParseDateFormat(value,&(digit_info->date_format)))
                rc=ParseError(keyword,value,rc,"invalid");
        }
        else if (mystrcasecmp(keyword,"tformat") == 0)
        {
            if (!ParseInteger(value,&(digit_info->time_format),12,24))
                rc=ParseError(keyword,value,rc,
                    "badly specified time format, (use 12 or 24)");
        }
        else if (mystrcasecmp(keyword,"script") == 0) /* for cgiwrap*/
        {
        }
        else if (mystrcasecmp(keyword,"user") == 0) /*for cgiwrap*/
        {
        }
        else if (mystrcasecmp(keyword,"timezone") == 0)
        {
            (void) strncpy(digit_info->time_z,value,49);
        }
        else 
        {
            sprintf(emsg, "Bad keyword \"%s\"", keyword);
        PrintHeader();
        StringImage(emsg);
        rc++;
        }
    }

    if ( digit_info->alpha == MissingValue )
        digit_info->alpha = (unsigned char) DefaultTransparency;

    if ( frame_info->width == MissingValue )
        frame_info->width= (unsigned char) DefaultThickness;

    return(rc);
}

/*
** get current time
*/

char *GetTime ()
{
    time_t
        tm;

    char
        *times;

    tm = time (NULL);
    times = ctime(&tm);
    times[(int) strlen(times)-1] = '\0';
    return (times);
}

void Warning (message)
char
    *message;
{
    char
        *times;
    FILE
        *fp= (FILE *) NULL;
    char
        buf[1024];

    *buf='\0';
    (void) sprintf(buf,"%s/%s",LogDir,LogFile);
    times = GetTime();
    fp = fopen(buf, "a");

    if (fp == (FILE *) NULL)
    {
        (void) fprintf (stderr,"[%s] Count %s: Could not open CountLog file %s/%s\n ",times, Version, LogDir,LogFile);
        fp = stderr;
    }
        (void) fprintf (fp,"[%s] Count %s: %s\n", 
            times, Version,message);
    if (fp != stderr)
        (void) fclose (fp);
}

/*
 *  GetRemoteReferer - returns the remote referer
 *
 *  RCS:
 *      $Revision: 2.3 $
 *      $Date: 1996/05/03 02:20:22 $
 *
 *  Security:
 *      Unclassified
 *
 *  Description:
 *      text
 *
 *  Input Parameters:
 *      type    identifier  description
 *
 *      char    *host       remote referer HTML
 *
 *
 *  Output Parameters:
 *      type    identifier  description
 *
 *      char    *rem_host   retuns the host
 *
 *  Return Values:
 *      value   description
 *
 *  Side Effects:
 *      text
 *
 *  Limitations and Comments:
 *      text
 *
 *  Development History:
 *      who                 when        why
 *      muquit@semcor.com   12-Aug-95   first cut
 */

#include <stdio.h>
#include <string.h>

void GetRemoteReferer (host, rem_host)
char
    *host;
char
    *rem_host;
{
    register char
        *p,
        *q;

    int
        x;

    *rem_host = '\0';
    q=rem_host;

    for (p=host; *p != '\0'; p++)
    {
        if (*p == '/')
        {
            p += 2;
            break;
        }
    }
    while ((*p != '/') && (*p != '\0'))
        *q++ = *p++;

    *q = '\0';

    /*
    ** randerso@bite.db.uth.tmc.edu added the following lines of code
    ** to account for port numbers at the end of a url
    */

    x=0;
    while ((x < (int) strlen(rem_host)) && (rem_host[x] != ':'))
        x++;
    rem_host[x]='\0';
}

#ifdef SYS_UNIX
void SetLock (fd)
int
    fd;
{
#ifdef HAVE_FLOCK
    (void) flock(fd,LOCK_EX);
#else
    lseek(fd,0L,0);
    (void) lockf(fd,F_LOCK,0L);
#endif
}

void UnsetLock (fd)
int
    fd;
{
#ifdef HAVE_FLOCK
    (void) flock(fd,LOCK_UN);
#else
    lseek(fd,0L,0);
    (void) lockf(fd,F_ULOCK,0L);
#endif
}
#endif  /* SYS_UNIX */

int CheckDirs()
{
    if ((strcmp(ConfigDir,DigitDir) == 0) ||
        (strcmp(ConfigDir,DataDir) == 0) ||
        (strcmp(ConfigDir,LogDir) == 0) ||
        (strcmp(ConfigDir,LogDir) == 0) ||
        (strcmp(DigitDir,DataDir) == 0) ||
        (strcmp(DigitDir,LogDir) == 0) ||
        (strcmp(DataDir,LogDir) == 0))
    return (1);
return (0);
}

#ifdef USE_ME
/*
 *  CheckRemoteIP - checks if remote host in the ignore list
 *
 *  RCS:
 *      $Revision: 2.3 $
 *      $Date: 1996/05/03 02:20:22 $
 *
 *  Security:
 *      Unclassified
 *
 *  Description:
 *      text
 *
 *  Input Parameters:
 *      type    identifier  description
 *
 *      text
 *
 *  Output Parameters:
 *      type    identifier  description
 *
 *      text
 *
 *  Return Values:
 *      value   description
 *
 *      True if the remote IP should be ignored (a match)
 *      False remote IP should be counted
 *
 *  Side Effects:
 *      text
 *
 *  Limitations and Comments:
 *      text
 *
 *  Development History:
 *      who                 when        why
 *      muquit@semcor.com   13-Sep-95   -
 */

unsigned int CheckRemoteIP(remote_ip,ip_ign)
char
    *remote_ip,
    *ip_ign;
{
    char
        tmp[10],
        buf[100],
        buf2[100];

    int
        x,
        y,
        z,
        w,
        xx,
        yy,
        zz,
        ww;

    int
        rc;

    *tmp='\0';
    *buf='\0';
    *buf2='\0';

    /*
    ** REMOTE_ADDR
    */

    (void) strcpy(buf,remote_ip);
    rc=sscanf(buf,"%d.%d.%d.%d",&xx,&yy,&zz,&ww);
    if (rc != 4)
        return(False);

    /*
    ** IP from conf file, we'll compare the remote IP with this one.
    ** we'll check for wildcard in the IP from conf file as well
    ** we'll check for all 3 classes of network
    */

    rc=sscanf(ip_ign,"%d.%d.%d.%d",&x,&y,&z,&w);
    if (rc != 4) /* possible wildcard */
    {
        /*
        ** check wildcard for a Class C network
        */
        if ((x >= 192) && (x <= 223))
        {
            /*
            ** we'r concerned with 4th octet
            */
            rc=sscanf(ip_ign,"%d.%d.%d.%s",&x,&y,&z,tmp);
            if (rc != 4) /* screwed up entry, don't ignore*/
                return (False);
            if (strcmp(tmp,"*") == 0)
            {
                if ((x == xx) &&
                    (y == yy) &&
                    (z == zz))
                {
                    return (True);
                }
            }
            else
                return (False);
        }
        else if ((x >= 128) && (x <= 191))
        {
            /*
            ** check wildcard for class B network
            ** we'll check the 3rd octet for wildcard
            */
            (void) fprintf (stderr," Class B\n");
            rc=sscanf(ip_ign,"%d.%d.%s",&x,&y,tmp);
            (void) fprintf (stderr," rc: %d\n",rc);
            (void) fprintf (stderr," tmp:%s\n",tmp);
            if (rc != 3)
                return (False);

            if ((strcmp(tmp,"*") == 0) ||
                (strcmp(tmp,"*.*") == 0))
            {
                (void) fprintf (stderr," xx,yy:%d,%d\n",xx,yy);
                if ((x == xx) &&
                    (y == yy))
                {
                    return (True);
                }
                else
                    return (False);
            }
        }
        else /* x < 128, got to be a Class A network */
        {
            /*
            ** we'll check the 2nd octet for wildcard
            */
            rc=sscanf(ip_ign,"%d.%s",&x,tmp);
            if (rc != 2)
                return (False);

            if ((strcmp(tmp,"*") == 0) ||
                (strcmp(tmp,"*.*") == 0) ||
                (strcmp(tmp,"*.*.*") == 0))
            {
                if (x == xx)
                    return (True);
                 else
                    return (False);
            }
        }
    }
    else
    {
        /*
        ** compare directly
        */
        if (strcmp(buf,ip_ign) == 0)
            return (True);
    }

return (False);
}

#endif /* USE_ME*/

/*
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
** I'm renaming it to mystrtok() in order to avoid conflict with the
** system which might have it
** I also formatted to my coding style
** 10/08/95, muquit@semcor.com
*/

char *mystrtok(s, delim)
char
    *s;
char
    *delim;
{
	register char
        *spanp;

	register int
        c,
        sc;

	char
        *tok;

	static char
        *last;


	if (s == (char *) NULL && (s = last) == (char *) NULL)
		return ((char *) NULL);

	 /*
	 ** Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	 */
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) 
    {
		if (c == sc)
			goto cont;
	}

	if (c == 0) 
    {		/* no non-delimiter characters */
		last = (char *) NULL;
		return ((char *)NULL);
	}
	tok = s - 1;

	/*
	 * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */

	for (;;) 
    {
		c = *s++;
		spanp = (char *)delim;
		do 
        {
			if ((sc = *spanp++) == c) 
            {
				if (c == 0)
					s = (char *) NULL;
				else
					s[-1] = '\0';
				last = s;
				return (tok);
			}
		} while (sc != 0);
	}
	  /* NOTREACHED */
}


/*
** found somewhere in the net
** muquit@semcor.com
*/
int mystrcasecmp(a,b)
char
    *a,
    *b;
{	
    register char
        ac,
        bc;

	for(;;)
    {
		ac = *a++;
		bc = *b++;

		if(ac == 0)
        {
			if(bc == 0)
				return 0;
			else
                return -1;
        }
		else
        { 
            if(bc == 0)
				return 1;
			else 
            {
                if(ac != bc)
                {
					if(islower(ac)) ac = toupper(ac);
					if(islower(bc)) bc = toupper(bc);
					if( ac != bc )
						return ac - bc;
				}
            }
	    }
    }
}

/*
 * the different -- and hopefully self-contained -- version of
 * CheckRemoteIP. Main difference is that ignore host block may
 * contain two IP address fields. First is then IP network address
 * and second is the netmask to be applied for comparision.  
 *
 * Davorin Bengez (Davorin.Bengez@science.hr), Jan 11. 1996.
 */

unsigned int CheckRemoteIP(remote_ip, ip_ign)
char *remote_ip, *ip_ign;
{
    unsigned long my_inet_addr _Declare ((char *));
    unsigned long rem_ip, ignore_ip, ignore_mask;
    char addr_buf[20], mask_buf[20];
    int i;

    ignore_mask = 0xffffffffL;

    rem_ip = my_inet_addr(remote_ip);
    if(rem_ip == (unsigned long)-1) return(False);

    /*
     * if ip_ign has TWO ip-look-alike fields, second field is netmask
     */

    if((i = sscanf(ip_ign, "%s %s", addr_buf, mask_buf)) < 1)
return(False);

    ignore_ip = my_inet_addr(addr_buf);
    if(ignore_ip == (unsigned long)-1) return(False);

    /*
     * try to convert the mask to something usable and fail if it
     * is not the proper IP netmask...
     */

    if(i == 2) {
        ignore_mask = my_inet_addr(mask_buf);
        if(ignore_mask == (unsigned long)-1) return(False);
    }

    /*
     * ...and finally, compare the masked addresses...
     */
  
    if((rem_ip & ignore_mask) == (ignore_ip & ignore_mask))
        return(True);
    else
        return(False);
}

/*
 * and a version of inet_addr - not to link all the network services
 * just because of this one...
 */

unsigned long my_inet_addr(s)
char *s;
{
    unsigned long n;
    int i;

    n = 0;

    for(i = 24; i >= 0; i -= 8) {
        n |= (unsigned long)atoi(s) << i;
        if((s = strchr(s,'.')) == (char *)NULL)
            break;
        ++s;
    }
    return(n);
}

#ifndef HAVE_MKTIME
/*
 * $Author: muquit $
 * $Date: 1996/05/03 02:20:22 $
 * $Id: parse.c,v 2.3 1996/05/03 02:20:22 muquit Exp muquit $
 * $Source: /usr2/sparc/muquit/mysrc/tmp/wwwcount2.3/RCS/parse.c,v $
 *
 * Grr.. on EP/IX I have no mktime(2) routine so I've had to roll my own.
 * Original work 7-Apr-95 by Reg Quinton <reggers@julian.uwo.ca>
*/


/* this is awfully nasty, the epoch began in 1970 UTC and 1968 was
   the preceding leap year. This converts a time structure to the
   number of seconds since the leap year. But assumes I have all
   sorts of good values which might not be there and doesn't do
   any fancy work wrt. time zones (assumes date given is same
   timezone and EST/EDT offset) which obviously isn't true. */

time_t netMktime(v)
struct tm *v;
{
struct	tm	*tm;
	int	leap;
	time_t	n;

	leap= (((v)->tm_year) % 4) ? 0 : 1;

	switch ((v)->tm_mon) {
	case 0:	/* Jan */
		(v)->tm_yday=(v)->tm_mday - 1;
		break;;
	case 1: /* Feb */
		(v)->tm_yday=31 + (v)->tm_mday - 1;
		break;;
	case 2: /* Mar */
		(v)->tm_yday=59 + (v)->tm_mday - 1 + leap;
		break;;
	case 3: /* Apr */
		(v)->tm_yday=90 + (v)->tm_mday - 1 + leap;
		break;;
	case 4: /* May */
		(v)->tm_yday=120 + (v)->tm_mday - 1 + leap;
		break;;
	case 5: /* Jun */
		(v)->tm_yday=151 + (v)->tm_mday - 1 + leap;
		break;;
	case 6: /* Jul */
		(v)->tm_yday=181 + (v)->tm_mday - 1 + leap;
		break;;
	case 7: /* Aug */
		(v)->tm_yday=212 + (v)->tm_mday - 1 + leap;
		break;;
	case 8: /* Sep */
		(v)->tm_yday=243 + (v)->tm_mday - 1 + leap;
		break;;
	case 9: /* Oct */
		(v)->tm_yday=273 + (v)->tm_mday - 1 + leap;
		break;;
	case 10: /* Nov */
		(v)->tm_yday=304 + (v)->tm_mday - 1 + leap;
		break;;
	case 11: /* Dec */
		(v)->tm_yday=334 + (v)->tm_mday - 1 + leap;
		break;;
	}

	/* n is the time value GMT, I need an offset */

	n=(((((((((((v)->tm_year) - 70) * 365 + 
                          (((v)->tm_year) - 68) / 4)  + 
                           ((v)->tm_yday)) * 24 ) +
                           ((v)->tm_hour)) * 60 ) + 
                           ((v)->tm_min))  * 60 ) + 
                           ((v)->tm_sec) );

	/* find the GMT offset and take it off, this fails
	   real bad at the time the timezone changes */

	tm=localtime(&n);	return(n-tm->tm_gmtoff);
}

#endif /* !HAVE_MKTIME */

/*
 *  checkTimezone - parses the GMT+-hhmm and returns the time in seconds
 *
 *  RCS:
 *      $Revision: 2.3 $
 *      $Date: 1996/05/03 02:20:22 $
 *
 *  Security:
 *      Unclassified
 *
 *  Description:
 *      This funcions parses a string like GMT+-hhmm and returns the time
 *      in seconds.
 *
 *  Input Parameters:
 *      type    identifier  description
 *
 *      char    str[]
 *          str holds a string like GMT+-hhmm
 *
 *  Output Parameters:
 *      type    identifier  description
 *
 *      text
 *
 *  Return Values:
 *      value   description
 *      int     diff
 *          hhmm is converted to seconds before returning. the value will
 *          be positive or negative based on GMT+ or GMT-
 *
 *  Side Effects:
 *      text
 *
 *  Limitations and Comments:
 *      text
 *
 *  Development History:
 *      who                 when        why
 *      muquit@semcor.com   26-Mar-96   first cut
 */


long checkTimezone(str)
char
    str[];
{
    int
        hr,
        min;
    int
        d;
    int
        counter=0;

    char
        buf[10];

    long
        diff=0L;

    int
        i;

    *buf='\0';
    hr=0;
    min=0;
    

    if (*str != '\0')
    {
        if (strlen(str) == 8)
        {
            if ((str[3] == '-') || (str[3] == '+'))
            {
                (void) strcpy(buf,&str[4]);   
                for (i=0; i < strlen(buf); i++)
                {
                    d=buf[i];
                    if ((d >= '0') && (d <= '9'))
                    {
                        if (counter < 2)
                            hr=hr*10 +(d-'0');
                        else
                            min=min*10+(d-'0');
                        counter++;
                    }
                }
                diff=(hr*3600)+min*60;
                if (str[3] == '-')
                    diff = -(diff);
            }
        }
    }
    return (diff);
}

/*
** parse literal string
** 04/23/96
*/
int ParseLiteralString(given,sets,maxlen)
char
    *given;
char
    *sets;
int
    maxlen;
{
    for (; *given != (char) 0; given++, sets++,maxlen--)
    {
        if (((isdigit(*given) ||
             (*given == ':')  ||
             (*given == ',')  ||
             (*given == '-')  ||
             (*given == 'a')  ||
             (*given == 'A')  ||
             (*given == 'p')  ||
             (*given == 'P')) &&
            (maxlen >= 0)))
        {
            *sets=*given;
        }
        else
            return (False);
    }
    return (True);
}

