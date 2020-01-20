/*
 *  WWW document access counter
 *
 *  RCS:
 *      $Revision: 2.3 $
 *      $Date: 1996/05/03 02:20:22 $
 *
 *  Security:
 *      Unclassified
 *
 *  Description:
 *     main routine for WWW homepage access counter
 *  
 *  Input Parameters:
 *      type    identifier  description
 *
 *      N/A
 *
 *  Output Parameters:
 *      type    identifier  description
 *
 *      N/A
 *
 *  Return Values:
 *      value   description
 *
 *  Side Effects:
 *      None
 *
 *  Limitations and Comments:
 *      None
 *
 *  Development History:
 *      who                 when        why
 *      muquit@semcor.com   10-Apr-95   first cut
 *      muquit@semcor.com   06-07-95    release 1.2
 *      muquit@semcor.com   07-13-95    release 1.3
 */

#define __Main__
#include "cdebug.h"
#include "combine.h"
#include "count.h"


#ifdef SYS_WIN32
#include "configNT.h"
#else
#include "config.h"
#endif

static char *ImagePrefix[]=
{
    "zero", "one", "two", "three", "four", "five", 
    "six", "seven", "eight", "nine",
};


void main (argc, argv)
int
    argc;
char
    **argv;

{
    int
        rc = 0;

    unsigned int
        ignore_site=False;

    register int
        i;

    char
        *browser_type,
        *remote_ip,
        *query_string;

    int
        n;

    int
        counter_length;

    int
        left_pad;

    char
        filename[MaxTextLength];

    char
        tmpbuf[MaxTextLength];

    char
        digitbuf[MaxTextLength];

    int
        fd;

    char
        format[10],
        buf[50];

    int
        count,
        counter;

    int
        tagdigit;

    int
        MaxDigits=10;

    DigitInfo
        digit_info;

    FrameInfo
        frame_info;

    unsigned int
        use_st;
    
    int
        min_dig1,
        min_dig2;

    int
        mon_dig1,
        mon_dig2,
        day_dig1,
        day_dig2,
        year_dig1,
        year_dig2;

     char
        hour[10],
        min[10],
        ampm[10];

    int
        display_what;

    unsigned int
        untrusted_browser=False;


#ifdef ACCESS_AUTH
    char
        *rem_refh;
#endif

/*
**---------initialize globals------Starts---
*/
    for (i=0; i < MaxSites; i++)
    {
        GrefererHost[i] = (char *) NULL;
        GignoreSite[i] = (char *) NULL;
    }
    Grhost=0;
    Gsite=0;
    Gdebug=False;
    Gauto_file_creation=0;
    Gstrict_mode=1;
    GrgbMappingIsError=1;
/*
**---------initialize globals------Ends---
*/
    count=1;
    *hour='\0';
    *min='\0';
    *ampm='\0';
    *format='\0';
    *buf='\0';
    *filename = '\0';
    *digitbuf='\0';
    *tmpbuf = '\0';
    counter = 0;
    tagdigit=9;
    left_pad=MaxDigits;
    use_st=False;
    display_what=SHOW_COUNTER;
    remote_ip=(char *) NULL;

    /*
    ** parse command line, this is only used for testing at commandline
    ** no command line flag is allowed in the web page while calling
    ** the program
    */

    for (i=1; i < argc; i++)
    {
        if (!strncmp(argv[i],"-debug",(int)strlen("-debug")))
        {
            Gdebug=True;
            break;
        }
    }

    Debug2("[%s] Count %s: --Debug--",GetTime(),Version);

#ifdef TEST_RRR
    /*************REMOVE****************/
    env_test=getenv("PATH_INFO");
    if (env_test == (char *) NULL)
    {
        (void) strcpy(tmpbuf,"PATH_INFO is NULL");
    }
    else
    {
        (void) sprintf(tmpbuf,"PATH_INFO is=%s\n",env_test);
    }
    Warning(tmpbuf);

    env_test=getenv("PATH_TRANSLATED");
    if (env_test == (char *) NULL)
    {
        (void) strcpy(tmpbuf,"PATH_TRANSLATED is NULL");
    }
    else
    {
        (void) sprintf(tmpbuf,"PATH_TRANSLATED=%s\n",env_test);
    }
    Warning(tmpbuf);
    /*************REMOVE****************/
#endif
    rc=CheckDirs();
    if (rc == 1)
    {
        *tmpbuf='\0';
        (void) sprintf(tmpbuf,"ConfigDir,DigitDir,DataDir,LogDir must differ");
        Warning(tmpbuf);
        PrintHeader();
        StringImage(tmpbuf);
        exit(1);
    }

    /*
    ** parse the authorization list
    */
    rc = ParseConfig ();

    switch (rc)
    {
        case ConfigOpenFailed:
        {
            *tmpbuf='\0';
            (void) sprintf (tmpbuf, 
                "Faliled to open configuration file: \"%s/%s\"",
                    ConfigDir,ConfigFile);
            Warning (tmpbuf);
            PrintHeader ();
            StringImage (tmpbuf);
            exit(1);
            break;
        }

        case NoAutofcBlock:
        {
            *tmpbuf='\0';
            (void) sprintf (tmpbuf,
                "No auto file creation block in conf file: \"%s/%s\"",
                    ConfigDir,ConfigFile);
            Warning(tmpbuf);
            PrintHeader ();
            StringImage(tmpbuf);
            exit(1);
            break;
        }

        case NoStrictBlock:
        {
            *tmpbuf='\0';
            (void) sprintf (tmpbuf,
                "No Strict mode block in conf file: \"%s/%s\"",
                    ConfigDir,ConfigFile);
            Warning(tmpbuf);
            PrintHeader ();
            StringImage(tmpbuf);
            exit(1);
            break;
        }
        case NoIgnoreHostsBlock:
        {
            *tmpbuf='\0';
            (void) sprintf (tmpbuf,
                "No IgnoreHosts Block in the configuration file: \"%s/%s\"",
                    ConfigDir,ConfigFile);

            Warning(tmpbuf);
            PrintHeader ();
            StringImage(tmpbuf);
            exit(1);
        }

        case NoRefhBlock:
        {
            *tmpbuf='\0';
            (void) sprintf(tmpbuf,"Compiled with -DACCESS_AUTH,but no such block in configuration file!");
            Warning(tmpbuf);
            PrintHeader ();
            StringImage(tmpbuf);
            exit(1);
        }

        case UnpexpectedEof:
        {
            *tmpbuf='\0';
            (void) sprintf (tmpbuf, 
            "Unexpected EOF in configuration file: \"%s/%s\"",
                ConfigDir,ConfigFile);
            Warning(tmpbuf);
            PrintHeader ();
            StringImage(tmpbuf);
            exit(1);
        }

    } /* switch (rc) */


        Debug2("Gsite: %d",Gsite,0);
        Debug2("Gauto_file_creation= %d",Gauto_file_creation,0);
        Debug2("Gstrict_mode= %d",Gstrict_mode,0);

#ifdef ACCESS_AUTH
    /*
    ** check if the referer is a remote host or not. refere should
    ** be the local host.
    */

    rem_refh = (char *) getenv("HTTP_REFERER");
    if (rem_refh != (char *) NULL)
    {
        char
            http_ref[1024],
            Rhost[1024];
        *http_ref = '\0';
        *Rhost = '\0';
        /*
        ** this will be same as your host when accessed from your
        ** page. if the host is anything else, it is an unauthorized
        ** access. handle it.
        */
        *tmpbuf='\0';
        (void) strcpy (http_ref, rem_refh);
        GetRemoteReferer(http_ref, Rhost);

        /*
            (void) sprintf(tmpbuf,"http_ref=%s",http_ref);
            Warning(tmpbuf);
        */

        Debug2("Grhost= %d",Grhost,0);
        Debug2("Rhost= %s",Rhost,0);

        if (*Rhost != '\0')
        {
            if (Grhost > 0)
            {
                for (i=0; i < Grhost; i++)
                {
                    rc=mystrcasecmp(Rhost,GrefererHost[i]);
                    if (rc == 0)
                        break;
                }
            }
            if (rc != 0)
            {
                *tmpbuf='\0';
              (void) sprintf(tmpbuf,
              "Host: \"%s\" is not in the auth block of the conf file",Rhost);
                Warning(tmpbuf);                    
                PrintHeader();
                StringImage(tmpbuf);
                exit(1);
            }
        }
    }

#endif /* ACCESS_AUTH */
    /*
    ** get the user name from query string
    */
    query_string = (char *) getenv("QUERY_STRING");

    if (query_string == (char *) NULL)
    {
        *tmpbuf='\0';
        (void) sprintf(tmpbuf,"%s","Empty QUERY_STRING!");
        Warning(tmpbuf);
        PrintHeader ();
        StringImage(tmpbuf);
        exit(1);
    }

    rc=ParseQueryString(query_string,&digit_info,&frame_info);

    Debug2("\n",0,0);
    Debug2("Parsed QUERY_STRING",0,0); 
    Debug2(" ft=%d",frame_info.width,0);
    Debug4(" rgb=%d,%d,%d", frame_info.matte_color.red,
        frame_info.matte_color.green, frame_info.matte_color.blue,0);
    Debug2(" tr=%d",digit_info.alpha,0);
    Debug4(" trgb=%d,%d,%d",digit_info.alpha_red,
        digit_info.alpha_green,digit_info.alpha_blue,0);
    Debug2(" replace_color=%d",digit_info.replace_color,0);
    Debug4(" srgb=%d,%d,%d",
        digit_info.opaque_red,
        digit_info.opaque_green,
        digit_info.opaque_blue,
        0);
    Debug4(" prgb=%d,%d,%d",
        digit_info.pen_red,
        digit_info.pen_green,
        digit_info.pen_blue,
        0);
    Debug2(" maxdigits=%d",digit_info.maxdigits,0);
    Debug2(" wxh [ignored,exists for compatibity] =%dx%d", 
        digit_info.width, digit_info.height);
    Debug2(" md=%d", digit_info.maxdigits,0);
    Debug2(" pad=%d", digit_info.leftpad,0);
    Debug2(" ddhead=%s",digit_info.ddhead,0);
    Debug2(" st=%d",digit_info.st,0);
    Debug2(" sh=%d", digit_info.show,0);
    Debug2(" df=%s",digit_info.datafile,0);
    Debug2(" lit=%s",digit_info.literal,0);
    Debug2(" incr=%d",digit_info.increment_counter,0);
    Debug2(" negate=%d",digit_info.negate,0);
    Debug2(" rotate=%d",digit_info.rotate,0);
    Debug2(" degrees=%d",digit_info.rotate_degrees,0);
    Debug2(" timezone=%s",digit_info.time_z,0);
    Debug2(" timeformat=%d",digit_info.time_format,0);
    Debug2(" istrip=%d",digit_info.use_strip,0);
    Debug2(" image=%s", digit_info.gif_file,0);
    Debug2(" parsed QS--\n",0,0);

    if (rc)
    {
        Debug2("rc from from ParseQueryString()=%d",rc,0);
        exit(1);
    }

    if (digit_info.leftpad == True)
    {
        MaxDigits=digit_info.maxdigits;

        if ((MaxDigits < 5) || (MaxDigits > 10))
        {
            Warning("Maxdigits (md) must be >= 5 and <= 10");
            PrintHeader ();
            StringImage("Maxdigits (md) must be >= 5 and <= 10");
            exit(1);
        }
    }

    /*
    ** now find out what we'r trying to display
    */
    display_what=digit_info.display_type;

    if (display_what == SHOW_COUNTER)
    {
        if (checkfilename (digit_info.datafile) != 0)
        {
            *tmpbuf='\0';
            (void) sprintf(tmpbuf,"Illegal datafile path!");
            Warning(tmpbuf);
            PrintHeader ();
            StringImage(tmpbuf);
            exit(1);
        }
    }
    /*
    ** get frameinfo
    */

    if (frame_info.width > 1)
        digit_info.Frame=True;
    else
        digit_info.Frame=False;
    /*
    ** get the IP address of the connected machine to check if we need
    ** to increment the counter
    */
    if (display_what == SHOW_COUNTER)
    {
        remote_ip = (char *) getenv("REMOTE_ADDR");
        if (remote_ip == (char *) NULL)
        {
            /*
            ** put a dummy here
            */
            remote_ip = "dummy_ip";
        }
        else
        {
            for (i=0; i < Gsite; i++)
            {
                ignore_site=CheckRemoteIP(remote_ip,GignoreSite[i]);
                if (ignore_site == True)
                {
                    Debug2("Not counting IP: %s",remote_ip,0);
                    Debug2("GignoreSite[%d]:%s",i,GignoreSite[i]);
                    break;
                }
            }
        }
    }

    /*
    ** initialize Limit array
    */


    if (display_what == SHOW_COUNTER)
    {
        Debug2("Maxdigits=%d",MaxDigits,0);
    }

#ifdef ACCESS_AUTH 
    if (Gstrict_mode == 1)
    {
        if (rem_refh == (char *) NULL)
        {
            untrusted_browser=True;
        /*
        ** no HTTP_REFERER env variable found.
        ** display a literal string. this will make sure that even if
        ** someone with a broken browser tries to access the counter
        ** remotely, will not mess up the datafile. of course we'll
        ** miss some counts. because anyone accesses the page with a 
        ** broken browser like this will see a literal string
        */
            (void) strcpy(digit_info.literal,"888888");
        /*
        if (remote_ip != (char *) NULL)
        {
            (void) sprintf(tmpbuf,"No HTTP_REFERER supplied from %s",
                remote_ip);
            Warning(tmpbuf);
        }
        */
        /*
        ** try to get the browser name, it will give us a good
        ** feedback.
        */
            browser_type=(char *) getenv("HTTP_USER_AGENT");
            if (browser_type != (char *) NULL)
            {
                if (remote_ip != (char *) NULL)
                {
                *tmpbuf='\0';
                (void) sprintf(tmpbuf,"Untrusted browser %s",browser_type);
                Warning(tmpbuf);
                }
            }
        }
    }   /* Gstrict_mode == 1 */
#endif

    switch (display_what)
    {

        case SHOW_CLOCK: /* act as a clock*/
        {
            time_t
                daytime,
                tm;

            struct tm
                *Tm=(struct tm *) NULL;

            long
                diff;   /* in seconds */

            if (untrusted_browser == False)
            {
                tm=time(NULL);
                if (*digit_info.time_z != '\0')
                {
                    /*
                    ** no more TZ, 03/26/96
                    */
                    diff=checkTimezone(digit_info.time_z);

                    Tm=gmtime(&tm);
#ifdef HAVE_MKTIME
                    daytime=mktime(Tm);
#else
                    daytime=netMktime(Tm);
#endif
                    daytime += diff;
                    Tm=localtime(&daytime);

                }
                else
                {
                    Debug2("No timezone",0,0);
                    Tm=localtime(&tm);
                } 
                if (digit_info.time_format == 12)
                {
                    if ((Tm)->tm_hour < 12)
                        (void) strcpy(ampm,"A");
                    else
                        (void) strcpy(ampm,"P");
        
                    if ((Tm)->tm_hour > 12)
                        (Tm)->tm_hour = (Tm)->tm_hour-12;
  
                    if ((Tm)->tm_hour == 0)  
                        (Tm)->tm_hour=12;
                }
            /*
            ** take off strftime(), 1/13/95, muquit
            */
                (void) sprintf(hour,"%d",(Tm)->tm_hour);
             
            /*
            ** I like to keep leading zeros for minutes
            */
                min_dig1=(Tm->tm_min - (Tm->tm_min % 10)) / 10;
                min_dig2=Tm->tm_min % 10;
                (void) sprintf(min,"%d%d",min_dig1,min_dig2);
                (void) sprintf(buf,"%s:%s%s",hour,min,ampm);
            } 
            else
            {
               (void) strcpy(buf,"888888");
            }
         
            Debug2(" time buf= %s",buf,0);

            *digitbuf='\0';
            (void) strcpy(digitbuf,buf);
            WriteCounterImage(digitbuf, &digit_info,&frame_info);
            
            /*
            ** we will not be here
            */
            exit(0);
            break;
        }

        case SHOW_DATE:
        {
            time_t
                daytime,
                tm;

            struct tm
                *Tm;

            long
                diff;   /* in seconds */

            if (untrusted_browser == False)
            {
                tm=time(NULL);
                if (*digit_info.time_z != '\0')
                {

                    /*
                    ** no more TZ, 03/26/96
                    */
                    diff=checkTimezone(digit_info.time_z);
                    Tm=gmtime(&tm);
#ifdef HAVE_MKTIME
                    daytime=mktime(Tm);
#else
                    daytime=netMktime(Tm);
#endif
                    daytime += diff;
                    Tm=localtime(&daytime);
                }
                else
                {
                    Tm=localtime(&tm);
                }
                Tm->tm_mon++;

                Debug2(" Inside SHOW_DATE",0,0);

                /*
                ** padding, saw in xdaliclock
                */
                mon_dig1=(Tm->tm_mon-(Tm->tm_mon % 10)) / 10;
                mon_dig2=Tm->tm_mon % 10;

                day_dig1=(Tm->tm_mday-(Tm->tm_mday % 10)) / 10;
                day_dig2=Tm->tm_mday % 10;

                year_dig1=(Tm->tm_year-(Tm->tm_year % 10)) / 10;
                year_dig2=Tm->tm_year % 10;


                switch (digit_info.date_format)
                {
                    case DATE_MMDDYY:
                    default:
                    {
                        (void) sprintf(buf,"%d%d-%d%d-%d%d",
                    mon_dig1,mon_dig2,day_dig1,day_dig2,year_dig1,year_dig2);
                        break;
                    }

                    case DATE_DDMMYY:
                    {
                        (void) sprintf(buf,"%d%d-%d%d-%d%d",
                    day_dig1,day_dig2,mon_dig1,mon_dig2,year_dig1,year_dig2);
                        break;
                    }

                    case DATE_YYMMDD:
                    {
                        (void) sprintf(buf,"%d%d-%d%d-%d%d",
                    year_dig1,year_dig2,mon_dig1,mon_dig2,day_dig1,day_dig2);
                        break;
                    }

                    case DATE_YYDDMM:
                    {
                        (void) sprintf(buf,"%d%d-%d%d-%d%d",
                    year_dig1,year_dig2,day_dig1,day_dig2,mon_dig1,mon_dig2);
                        break;
                    }

                    case DATE_MMYYDD:
                    {
                        (void) sprintf(buf,"%d%d-%d%d-%d%d",
                    mon_dig1,mon_dig2,year_dig1,year_dig2,day_dig1,day_dig2);
                        break;
                    }

                    case DATE_DDYYMM:
                    {
                        (void) sprintf(buf,"%d%d-%d%d-%d%d",
                    day_dig1,day_dig2,year_dig1,year_dig2,mon_dig1,mon_dig2);
                        break;
                    }
                }

                Debug2(" date buf=%s",buf,0);
            }
            else
            {
                (void) strcpy(buf,"888888");
            }

            (void) strcpy(digitbuf,buf);
            WriteCounterImage (digitbuf, &digit_info,&frame_info);
            /*
            ** we won't be here
            */
            break;
        }

        case SHOW_GIF_FILE:
        {
            if (*digit_info.gif_file == '\0')
            {
                PrintHeader();
                StringImage("No GIF file specified to dispaly");
                exit(1);
            }
            (void) sprintf(digitbuf,"%s/%s/%s",
                DigitDir,digit_info.ddhead,digit_info.gif_file);
            WriteCounterImage(digitbuf,&digit_info,&frame_info);
            /*
            ** we won't be here
            */
            break;
        }
        case SHOW_COUNTER:
        default:
        {

            if (digit_info.comma == True)
                digit_info.leftpad=False;
            if ((int) strlen(digit_info.literal) > 0)
            {
                /*
                ** only copy 10 digits, otherwise we take the risk
                ** of buffer overflow
                */
                if (strlen(digit_info.literal) > 10)
                    (void) strncpy(buf, digit_info.literal,10);
                else
                {
                    (void) strcpy(buf, digit_info.literal);
                }
                if (digit_info.comma == True)
                    (void) sprintf(buf,"%d",atoi(buf));
                digit_info.leftpad=False;
            }
            else if (mystrcasecmp(digit_info.datafile,DfForRandom) == 0)
            {
                srand(time(NULL));  /* Seed number generator */
                counter = rand();   /* My psychic prediction of counter value */

                /*
                ** we do not want to overflow buffer
                */
                Debug2("random number=%d",counter,0);

                *tmpbuf='\0';
                (void) sprintf(tmpbuf,"%d",counter);
                if (strlen(tmpbuf) > 10)
                    (void) strncpy(buf,tmpbuf,10);
                else
                    (void) strcpy(buf,tmpbuf);
              Debug2("random number after bound checning=%s",buf,0);
              digit_info.leftpad=False;
            }
            else
            {

            (void) strcpy(filename, DataDir);
            (void) strcat(filename, "/");
            (void) strcat (filename, digit_info.datafile);

            /*
            ** check if the counter file exists or not
            */
        if (Gauto_file_creation == 0)
        {
            if (CheckFile (filename) != 0)
            {
                *tmpbuf='\0';
                (void) sprintf (tmpbuf,
                    "Counter datafile \"%s\" must be created first!", filename);
                Warning(tmpbuf);
                PrintHeader ();
                StringImage (tmpbuf);
                exit(1);
            }

        }
        else
        {
            if (CheckFile (filename) != 0)
                use_st=True;
        }
#ifdef SYS_WIN32
        fd=sopen(filename,_O_RDWR | _O_CREAT, _SH_DENYWR, _S_IREAD |_S_IWRITE);
#else
        fd = open (filename, O_RDWR | O_CREAT,0644);
#endif
        if (fd < 0)
        {
            *tmpbuf='\0';
            if (Gauto_file_creation == 1)
            {
                if (CheckFile (filename) != 0)
                    (void) sprintf(tmpbuf,
                    "Could not create data file: \"%s\"",filename);
                else
                    (void) sprintf (tmpbuf,
                    "Could not write to counter file: \"%s\"", filename);
            }
            else
                (void) sprintf (tmpbuf,
                "Could not write to counter file: \"%s\"", filename);

            Warning(tmpbuf);
            PrintHeader ();
            StringImage(tmpbuf);
            exit(1);
        }

#ifdef SYS_UNIX
        SetLock(fd);
#endif
        /*
        ** try to read from the file
        */

        lseek(fd,0L,0);
        /*        n = read(fd, buf, MaxDigits);*/
        n = read(fd, buf, 10);

        if (n > 0)
        {


            /*
            ** check if the datafile is edited, 
            ** NULL terminate at first non-digit
            */
            for (i=0; i < n; i++)
            {
                if (!isdigit(buf[i]))
                {
                    buf[i]='\0';
                    break;
                }
            }
            if (i == n)
                buf[n]='\0';

            Debug2("In buffer=%s",buf,0);

            if (*buf == '\0')
                counter=0;
            else
                counter = atoi(buf);

            if (counter < 0)
            {
                /*
                ** possibly we reached the limit, the digit didn't fit
                ** in an int
                */
                PrintHeader();
                StringImage("The digit did not fit in a signed int!");
                exit(1);
            }

            *buf='\0';
            (void) sprintf(buf,"%d",counter);
        
            Debug2(" before increment=%d",counter,0);
            if (counter == 0)
                counter_length = 1;
            else
            {

                if (digit_info.increment_counter == True)
                    counter++;
                (void) sprintf(buf, "%d", counter);
                counter_length = (int) strlen(buf);
            } 

            Debug2(" after increment=%d",counter,0);

            if (ignore_site  == False)
            {
                lseek(fd,0L,0);
                (void) write(fd, buf, (int)strlen(buf));
                (void) close (fd); /*unlocks as well */
            }
        }
        else
        {
            if (use_st == True)
            {
                counter=digit_info.st;
                Debug2("counter=%d",counter,0);
            }
            Debug2(" n < 0",0,0);
            Debug2(" before increment=%d",counter,0);

            if ( digit_info.increment_counter==True )
                 counter++;

            (void) sprintf(buf, "%d", counter);
            Debug2(" after increment=%d",counter,0);

            lseek(fd,0L,0);
            write (fd, buf, (int) strlen(buf));
            (void) close (fd);
        }

#ifdef SYS_UNIX
        UnsetLock(fd);
#endif
    }

    counter_length = (int) strlen(buf);

        if (digit_info.show == False)
        {
            Image
                *image;

            image=CreateBaseImage(1,1,0,0,0,DirectClass);
            if (image == (Image *) NULL)
            {
                PrintHeader();
                StringImage("Failed to create 1x1 GIF image");
                exit(1);
            }

            AlphaImage(image,0,0,0);
            PrintHeader();
            (void) WriteGIFImage (image, (char *)NULL);
            DestroyAnyImageStruct (&image);
            exit(0);
        }

       if (digit_info.leftpad == False)    /* no left padding */
       {
            (void) strcpy(digitbuf,buf);
            WriteCounterImage(digitbuf,&digit_info,&frame_info);
            /*
            ** we will not be here, we'll exit from LoadDigits()
            */
        }
        else
        {
            if (counter_length < MaxDigits)
                left_pad = MaxDigits - counter_length;
            else
                left_pad=0;

            Debug2(" MaxDigits=%d",MaxDigits,0);
            Debug2(" left_pad=%d",left_pad,0);

              if ((left_pad < MaxDigits) && (left_pad != 0))
              {

                (void) strcpy(digitbuf,"0");
                for (i=1; i < left_pad; i++)
                {
                    (void) sprintf(digitbuf,"%s0",digitbuf);
                }
                (void) sprintf(digitbuf,"%s%s",digitbuf,buf);
                WriteCounterImage(digitbuf,&digit_info,&frame_info);
                /*
                ** we will not be here
                */
              }
              else    /* MaxDigits*/
              {

                Debug2(" We are in MaxDigits=%d",MaxDigits,0);

                (void) strcpy(digitbuf,buf);
                    WriteCounterImage(digitbuf,&digit_info,&frame_info);
                /*
                ** we won't be here
                */
               }

            }
            exit(0);
        } /* case SHOW_COUNTER*/
    }
}

/*
 * checkfilename:
 * - check to see if a path was specified - return 1 if so, 0 otherwise
 * it might not be foolproof, but I can't come up with
 * any other ways to specify paths.
 * by carsten@group.com (07/27/95)
 * ..\filename was not getting ignored on NT
 * reported by asolberg@pa.net>
 * fixed: 04/19/96
 */

int checkfilename(str)
char
    *str;
{
    while (*str)
    {
        if ((*str == '/') || 
            (*str == '\\') || 
            (*str == ':') ||
            (*str == '~'))
            return 1;
        str ++;
    }
    return 0;
}

/*
** check if the counter file exists
*/

int CheckFile (filename)
char
    *filename;
{
    int
        rc=0;

    rc = access (filename, F_OK);
    return rc;
}

/*
** something went wrong..write the built in GIF image to stdout
*/

void SendErrorImage (bits, length)
unsigned char
    *bits;
int
    length;
{
    register unsigned char
        *p;

    register int
        i;

    p = bits;
    for (i=0; i < length; i++)
    {
        (void) fputc((char) *p, stdout);
        (void) fflush (stdout);
        p++;
    }
}

void PrintHeader ()
{
    if (Gdebug == False)
    {
        (void) fprintf (stdout,
            "Content-type: image/gif%c%c",LF,LF);
        (void) fflush (stdout);
    }
    return;
}

void WriteCounterImage(digitbuf,digit_info,frame_info)
char
    *digitbuf;
DigitInfo
    *digit_info;
FrameInfo
    *frame_info;
{
   Image
        *image;


   if (digit_info->display_type == SHOW_GIF_FILE)
   {
       Debug2("Displaying GIF file=\"%s\"",digitbuf,0);
       image=ReadImage(digitbuf);
   }
   else
   {
        image=CombineImages(digitbuf,digit_info);
   }

   if (image != (Image *) NULL)
   {
        MogrifyImage(&image,digit_info,frame_info);
        PrintHeader();
        (void) WriteGIFImage (image, (char *)NULL);
   }
   else
   {
        PrintHeader();
        StringImage("Failed! Check DigitDir in config.h or dd in QUERY_STRING");
   }


   exit(1);
}

Image *CombineImages(digitbuf,digit_info)
char
    *digitbuf;
DigitInfo
    *digit_info;
{
    register char
        *p;

    char
        tmpbuf[MaxTextLength];

    int
        rc=0;

    unsigned int
        bwidth,
        bheight,
        gbW,
        gbH,
        base_width,
        base_height;

    Image
        *strip_image,
        *sub_image,
        *base_image;

    int
        nsegment,
        segment;

    int
        *seg_array=(int *) NULL;

    RectangleInfo
        rinfo;
    int
        n;
 
    int
        i;
    char
        *token;

    segment=0;
    bwidth=0;
    bheight=0;
    gbW=0;
    gbH=0;
    base_width=0;
    base_height=0;
    strip_image=(Image *) NULL;

    /*
    ** if comma is requesed, commaize (my new invented word!) the
    ** digit. also it's meaningness to left pad while commizing,
    ** therefore, don't left pad with zeros as well
    */
    if ((digit_info->display_type == (unsigned int) SHOW_COUNTER) &&
        (digit_info->comma == True))
    {
        Commaize(digitbuf);
        Debug2("after commaze=%s",digitbuf,0);
    }
    /*
    ** if image strip is not used, we'll handle it as usual
    */
if (digit_info->use_strip == False)
{
    for (p=digitbuf; *p != '\0'; p++)
    {
        *tmpbuf='\0';
        if(isdigit(*p))
            (void) sprintf(tmpbuf,"%s/%s/%s.gif",
                DigitDir,digit_info->ddhead,ImagePrefix[(int)*p-'0']);
        else
        {
            if (*p == ':')
                (void) sprintf(tmpbuf,"%s/%s/%s.gif",
                    DigitDir,digit_info->ddhead,"colon");
            else if ((*p == 'A') || (*p == 'a'))
                (void) sprintf(tmpbuf,"%s/%s/%s.gif",
                    DigitDir,digit_info->ddhead,"am");
            else if ((*p == 'P') || (*p == 'p'))
                (void) sprintf(tmpbuf,"%s/%s/%s.gif",
                    DigitDir,digit_info->ddhead,"pm");
            else if (*p == ',')
                (void) sprintf(tmpbuf,"%s/%s/%s.gif",
                    DigitDir,digit_info->ddhead,"comma");
            else
                if (*p == '-')
                (void) sprintf(tmpbuf,"%s/%s/%s.gif",
                    DigitDir,digit_info->ddhead,"dash");
        }
        rc=GetGIFsize(tmpbuf,&gbW,&gbH);
        if (rc)
        {
            PrintHeader();
            StringImage("Unable to determine digit image size!");
            exit(1);
        }
        bwidth += gbW;
        if (gbH > bheight)
            bheight=gbH;
    }
}
else
{
    /*
    ** strip is in use. First of all, we will determine the with of the
    ** base image. The segments in the strip may be of varaible widths,
    ** we'll handle it
    */
    (void) sprintf(tmpbuf,"%s/%s/strip.gif",DigitDir,digit_info->ddhead);
    strip_image=ReadImage(tmpbuf);
    if (strip_image == (Image *) NULL)
    {
        PrintHeader();
        StringImage("Unable to read strip image!");
        exit(1);
    }
    if (strip_image->comments != (char *) NULL)
    {
        rc=sscanf(strip_image->comments,"%d",&nsegment);
        Debug2("segments=%d rc=%d",nsegment,rc);
        if (rc != 1)
        {
            PrintHeader();
            StringImage("No string segment info found in GIF comment ext.!");
            exit(1);
        }

        seg_array=(int *) malloc((nsegment+2)*sizeof(int));
        if (seg_array == (int *) NULL)
        {
            PrintHeader();
            StringImage("Memory Allocation Failed for seg_array!");
            exit(1);   
        }
        p=strip_image->comments;
        i=0;
        while ((token=mystrtok(p,":")) != (char *) NULL)
        {
            p=(char *) NULL;
            if (token != (char *) NULL)
                seg_array[i]=atoi(token);
            i++;
        }
        /*
        ** the info about strip in the comment extension of the GIF image
        ** does not match. we'll abort
        ** btw, if the strip is created with my mkstrip program, the info
        ** should be correct. possibly someone is using a strip made by
        ** some other program. Tough luck!
        */
        if (i != (nsegment+2))
        {
            PrintHeader();
            StringImage("Strip info mismatch in GIF comment ext.!");
            exit(1);
        }

        for (p=digitbuf; *p != '\0'; p++)
        {
            if (isdigit(*p))
            {
                n=(*p-'0');
                bwidth += (seg_array[n+2]-seg_array[n+1]);
            }
            else
            {
                if (*p == ':')
                {
                    rinfo.x=seg_array[11];
                    bwidth += (seg_array[12]-seg_array[11]);
                }

                if ((*p == 'A') || (*p == 'a'))
                {
                    rinfo.x=seg_array[12];
                    bwidth += (seg_array[13]-seg_array[12]);
                }
                if ((*p == 'P') || (*p == 'p'))
                {
                    rinfo.x=seg_array[13];
                    bwidth += (seg_array[14]-seg_array[13]);
                }
                if (*p == ',')
                {
                    rinfo.x=seg_array[14];
                    bwidth += (seg_array[15]-seg_array[14]);
                }
                if (*p == '-')
                {
                    rinfo.x=seg_array[15];
                    bwidth += (seg_array[16]-seg_array[15]);
                }
            }
        }
        bheight=strip_image->rows;
    }
    else
    {
        PrintHeader();
        StringImage("No info about strip found in GIF comment ext.!");
        exit(1);
    }
}
    base_image= CreateBaseImage (bwidth,bheight,0,0,0,DirectClass);

    if (base_image == (Image *) NULL)
    {
        PrintHeader();
        StringImage("Unable to create base image!");
        exit(1);
    }

if (digit_info->use_strip == False)
{
    for (p=digitbuf; *p != '\0'; p++)
    {
        *tmpbuf='\0';
        if(isdigit(*p))
            (void) sprintf(tmpbuf,"%s/%s/%s.gif",
                DigitDir,digit_info->ddhead,ImagePrefix[(int)*p-'0']);
        else
        {
            if (*p == ':')
                (void) sprintf(tmpbuf,"%s/%s/%s.gif",
                    DigitDir,digit_info->ddhead,"colon");
            if ((*p == 'A') || (*p == 'a'))
                (void) sprintf(tmpbuf,"%s/%s/%s.gif",
                    DigitDir,digit_info->ddhead,"am");
            if ((*p == 'P') || (*p == 'p'))
                (void) sprintf(tmpbuf,"%s/%s/%s.gif",
                    DigitDir,digit_info->ddhead,"pm");
            if (*p == ',')
                (void) sprintf(tmpbuf,"%s/%s/%s.gif",
                    DigitDir,digit_info->ddhead,"comma");
            if (*p == '-')
                (void) sprintf(tmpbuf,"%s/%s/%s.gif",
                    DigitDir,digit_info->ddhead,"dash");
        }

        sub_image=ReadImage(tmpbuf);
        if (sub_image != (Image *) NULL)
        {
            FlattenImage(base_image,sub_image,ReplaceCompositeOp,
                base_width,0);
            base_width += sub_image->columns;
            DestroyAnyImageStruct(&sub_image);
        }
        else
        {
            PrintHeader();
            StringImage(" FAILED to combine digit images!");
            exit(1);
        }
    }
}
else
{
   rinfo.y=0;
   rinfo.width=15;
   rinfo.height=strip_image->rows;
    for (p=digitbuf; *p != '\0'; p++)
    {
        *tmpbuf='\0';
        if (isdigit(*p))
        {
            n=(*p-'0');
            rinfo.x=seg_array[n+1];
            rinfo.width=seg_array[n+2]-seg_array[n+1];
        }
        else
        {
            if (*p == ':')
            {
                rinfo.x=seg_array[11];
                rinfo.width=seg_array[12]-seg_array[11];
            }
            if ((*p == 'A') || (*p == 'a'))
            {
                rinfo.x=seg_array[12];
                rinfo.width=seg_array[13]-seg_array[12];
            }
            if ((*p == 'P') || (*p == 'p'))
            {
                rinfo.x=seg_array[13];
                rinfo.width=seg_array[14]-seg_array[13];
            }
            if (*p == ',')
            {
                rinfo.x=seg_array[14];
                rinfo.width=seg_array[15]-seg_array[14];
            }
            if (*p == '-')    
            {
                rinfo.x=seg_array[15];
                rinfo.width=seg_array[16]-seg_array[15];
            }    
        }

        sub_image=CropImage(strip_image,&rinfo);
        if (sub_image != (Image *) NULL)
        {
            FlattenImage(base_image,sub_image,ReplaceCompositeOp, base_width,0);
            base_width += sub_image->columns;
            DestroyAnyImageStruct(&sub_image); 
        }
        else
        {
            PrintHeader();
            StringImage("Failed to extract image from strip!");
            exit(1);
        }    
    } 
}
    return(base_image);
}

/*
** buf is modified
*/
void Commaize(buf)
char
    *buf;
{
    char
        tmpbuf[100];

    register char
        *p,
        *q;

    int
        m=0;
    int
        i=-1;

    *tmpbuf='\0';

    if (*buf != '\0')
    {
        m=0;
        m=m+strlen(buf)/3;
        if (strlen(buf)%3 == 0)
            m--;

        p=buf+strlen(buf)-1;
        tmpbuf[strlen(buf)+m]='\0';
        q=tmpbuf+strlen(buf)+m-1;
        while (1)
        {
            if (p < buf)
                break;
            if (++i == 3)
                i=0, *q-- = ',';
             *q-- = *p--;
        }
        (void) strcpy(buf,tmpbuf);
    }

}

/*
** mogrify image if needed
*/
void MogrifyImage(image,digit_info,frame_info)
Image
    **image;
DigitInfo
    *digit_info;
FrameInfo
    *frame_info;
{
    Image
        *framed_image,
        *rotated_image;

    if (*image != (Image *) NULL)
    {
        if (digit_info->negate == True)
            NegateImage(*image);
            
        if (digit_info->Frame == True) 
        {
            RGB 
               color,
               matte_color;
            
            matte_color.red=frame_info->matte_color.red;
            matte_color.green=frame_info->matte_color.green;
            matte_color.blue=frame_info->matte_color.blue;

            frame_info->height=frame_info->width;
            frame_info->outer_bevel=(frame_info->width >> 2)+1;
            frame_info->inner_bevel=frame_info->outer_bevel;
            frame_info->x=frame_info->width;
            frame_info->y=frame_info->height;
            frame_info->width=(*image)->columns+(frame_info->width << 1);
            frame_info->height=(*image)->rows+(frame_info->height << 1);
            frame_info->matte_color=matte_color; 
        
            XModulate(&color,matte_color.red,matte_color.green,
                matte_color.blue, HighlightModulate);
            frame_info->highlight_color.red=color.red;
            frame_info->highlight_color.green=color.green;
            frame_info->highlight_color.blue=color.blue;

            XModulate(&color,matte_color.red,matte_color.green,
                matte_color.blue, ShadowModulate);
            frame_info->shadow_color.red=color.red;
            frame_info->shadow_color.green=color.green;
            frame_info->shadow_color.green=color.green;

            framed_image=FrameImage(*image,frame_info);
            if (framed_image != (Image *) NULL)
            {
                DestroyAnyImageStruct (image);
                framed_image->class=DirectClass;
                *image=framed_image;
            }
        }    
        
        (*image)->comments = (char *) malloc (1024*sizeof(char));
        if ((*image)->comments != (char *) NULL)
        {
            (void) sprintf((*image)->comments,"\n%s %s \n%s %s\n%s %s\n",
                "Count.cgi", Version, "By", Author, "URL:", Url);
        }
        

        if (digit_info->replace_color == True)
        {
            OpaqueImage(*image,
                digit_info->opaque_red,
                digit_info->opaque_green,
                digit_info->opaque_blue,
                digit_info->pen_red,
                digit_info->pen_green,
                digit_info->pen_blue);

        }

        if (digit_info->alpha == True)
        {
             AlphaImage(*image,digit_info->alpha_red,digit_info->alpha_green,
                digit_info->alpha_blue);
        }
         if (digit_info->rotate == True)
         {
            rotated_image=RotateImage(*image,digit_info->rotate_degrees);
            if (rotated_image != (Image *) NULL)
            {
                DestroyAnyImageStruct (image);
                *image=rotated_image;
            }
            else
            {
                (void) fprintf (stderr," Could not rotate %d degrees\n",
                    digit_info->rotate_degrees);
            }
         }
    }
}
