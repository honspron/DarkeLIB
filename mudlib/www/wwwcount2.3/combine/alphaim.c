/*
 *  AlphaImage () - creates an alpha channel
 *
 *  RCS:
 *      $Revision: 2.3 $
 *      $Date: 1996/05/03 02:21:34 $
 *
 *  Security:
 *      Unclassified
 *
 *  Description:
 *      From ImageMagick
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
 *      muquit@semcor.com   24-Aug-95   first cut
 */
#include "combine.h"

#if __STDC__ || defined(sgi) || defined(_AIX)
void AlphaImage (Image *image,
    unsigned char red,unsigned char green,unsigned char blue)
#else
void AlphaImage (image,red,green,blue)
Image
    *image;
unsigned char
    red,
    green,
    blue;
#endif
{
#define DeltaX  16

    register Runlength
        *p;

    register int
        i;

    p=image->pixels;
    switch(image->class)
    {
        case DirectClass:
        {
            if (!image->alpha)
            {
                for (i=0; i < image->packets; i++)
                {
                    p->index=Opaque;
                    p++;
                }
                image->alpha=True;
                p=image->pixels;
            }

            for (i=0; i < image->packets; i++)
            {
                if (((int) p->red < (int) (red+DeltaX)) &&
                    ((int) p->red > (int) (red-DeltaX)) &&
                    ((int) p->green < (int) (green+DeltaX)) &&
                    ((int) p->green > (int) (green-DeltaX)) &&
                    ((int) p->blue < (int) (blue+DeltaX)) &&
                    ((int) p->blue > (int) (blue-DeltaX)))
                p->index=Transparent;
               p++;
                
             }
            break;
        }
        case PseudoClass:
        {
            double
                distance_squared,
                min_distance;

            int
                distance;

            register int
                index;

             min_distance=3.0*(MaxRGB+1)*(MaxRGB+1);
             index=0;

             for (i=0; i < image->colors; i++)
             {
                distance=(int) red-(int) image->colormap[i].red;
                distance_squared=(unsigned int) (distance*distance);
                distance=(int) green-(int) image->colormap[i].green;
                distance_squared+=(unsigned int) (distance*distance);
                distance=(int) blue-(int) image->colormap[i].blue;
                distance_squared+=(unsigned int) (distance*distance);
                if (distance_squared < min_distance)
                {
                    min_distance=distance_squared;
                    index=i;
                }
             }

             image->class=DirectClass;
             image->alpha=True;
             for (i=0; i < image->packets; i++)
             {
                if (p->index == index)
                    p->index=Transparent;
                else
                    p->index=Opaque;
                p++;
             }
             break;
        }
    }
}
