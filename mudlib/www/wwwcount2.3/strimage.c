/*
 *  StringImage - creates an Image from string
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
 *      muquit@semcor.com   09-Sep-95   first cut
 */

#include "combine.h"
#include "gdfonts.h"
#include "count.h"

void StringImage(str)
char
    *str;
{
    Image
        *fimage,
        *image;

    int
        str_length;

    FrameInfo
        frame_info;
    SFontInfo
        font_info;

    str_length=(int) strlen(str);
    image=CreateBaseImage(gdFontSmall->w*str_length+10,
        gdFontSmall->h+10,0,0,0,DirectClass);

    if (image == (Image *) NULL)
    {
        (void) fprintf (stderr," Unable to create base image for string!\n");
        return;
    }
    
    font_info.do_bg=True;
    font_info.bgr=0;
    font_info.bgg=0;
    font_info.bgb=0;

    font_info.fgr=255;
    font_info.fgg=255;
    font_info.fgb=0;

    ImageString(image,gdFontSmall,5,5,str,&font_info);
    GetFrameInfo(image->columns,image->rows,&frame_info);
    fimage=FrameImage(image,&frame_info);
    if (fimage != (Image *) NULL)
    {
        DestroyAnyImageStruct(&image);
        image=fimage;
    }
    WriteGIFImage(image,(char *) NULL);
    
}
