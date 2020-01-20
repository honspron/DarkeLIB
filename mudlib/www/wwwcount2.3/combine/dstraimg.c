/*
 *	DestroyAnyImageStruct()	-	frees Image Struct
 *
 *	RCS:
 *		$Revision: 2.3 $
 *		$Date: 1996/05/03 02:21:34 $
 *
 *	Security:
 *		Unclassified
 *
 *	Description:
 *		text
 *
 *	Input Parameters:
 *		type	identifier	description
 *
 *		text
 *
 *	Output Parameters:
 *		type	identifier	description
 *
 *		text
 *
 *	Return Values:
 *		value	description
 *
 *	Side Effects:
 *		text
 *
 *	Limitations and Comments:
 *		text
 *
 *	Development History:
 *		when	who		why
 *	6/29/94		muquit	first cut
 *	10/10/94	muquit	pass &anyimage so it can be NULLed properly
 */
#include "combine.h"
#include "defines.h"

void DestroyAnyImageStruct (anyimage)
Image
	**anyimage;
{
		

	if ((*anyimage)->fp != (FILE *) NULL)
	{
		(*anyimage)->fp = (FILE *) NULL;
	}
	if ((*anyimage)->comments != (char *) NULL)
	{
		(void) free ((char *) (*anyimage)->comments);
		(*anyimage)->comments=(char *) NULL;
	}

	if ((*anyimage)->colormap != (RGB *) NULL)
	{
		(void) free ((char *) (*anyimage)->colormap);
		(*anyimage)->colormap = (RGB *)NULL;
	}

	if ((*anyimage)->signature != (char *) NULL)
	{
		(void) free ((char *) (*anyimage)->signature);
		(*anyimage)->signature=(char *)NULL;
	}

	if ((*anyimage)->pixels != (Runlength *) NULL)
	{
		(void) free ((char *) (*anyimage)->pixels);
		(*anyimage)->pixels=(Runlength *) NULL;
	}


	if (*anyimage != (Image *) NULL)
	{
		(void) free ((char *) *anyimage);
		*anyimage = (Image *) NULL;
	}
}
