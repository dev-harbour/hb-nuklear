/*
 *
 */

#ifndef HBX11_CH_
#define HBX11_CH_

#include "nuklear.ch"

#define HB_BITOR( x )   ( hb_bitShift( 1, ( x ) ) )

/*****************************************************************
 *  COLOR MAP STUFF
 *****************************************************************/

/* For CreateColormap */
#define AllocNone                0 /* create map with no entries */
#define AllocAll                 1 /* allocate entire map writeable */

/*****************************************************************
 * EVENT DEFINITIONS
 *****************************************************************/

/* Input Event Masks. Used as event-mask window attribute and as arguments
   to Grab requests.  Not to be confused with event names. */
#define NoEventMask              0
#define KeyPressMask             HB_BITOR( 0 )
#define KeyReleaseMask           HB_BITOR( 1 )
#define ButtonPressMask          HB_BITOR( 2 )
#define ButtonReleaseMask        HB_BITOR( 3 )
#define EnterWindowMask          HB_BITOR( 4 )
#define LeaveWindowMask          HB_BITOR( 5 )
#define PointerMotionMask        HB_BITOR( 6 )
#define PointerMotionHintMask    HB_BITOR( 7 )
#define Button1MotionMask        HB_BITOR( 8 )
#define Button2MotionMask        HB_BITOR( 9 )
#define Button3MotionMask        HB_BITOR( 10 )
#define Button4MotionMask        HB_BITOR( 11 )
#define Button5MotionMask        HB_BITOR( 12 )
#define ButtonMotionMask         HB_BITOR( 13 )
#define KeymapStateMask          HB_BITOR( 14 )
#define ExposureMask             HB_BITOR( 15 )
#define VisibilityChangeMask     HB_BITOR( 16 )
#define StructureNotifyMask      HB_BITOR( 17 )
#define ResizeRedirectMask       HB_BITOR( 18 )
#define SubstructureNotifyMask   HB_BITOR( 19 )
#define SubstructureRedirectMask HB_BITOR( 20 )
#define FocusChangeMask          HB_BITOR( 21 )
#define PropertyChangeMask       HB_BITOR( 22 )
#define ColormapChangeMask       HB_BITOR( 23 )
#define OwnerGrabButtonMask      HB_BITOR( 24 )

/*****************************************************************
 * WINDOW DEFINITIONS
 *****************************************************************/

/* Window classes used by CreateWindow */
/* Note that CopyFromParent is already defined as 0 above */
#define InputOutput  1
#define InputOnly    2

/* Window attributes for CreateWindow and ChangeWindowAttributes */
#define CWBackPixmap             HB_BITOR( 1, 0 )
#define CWBackPixel              HB_BITOR( 1, 1 )
#define CWBorderPixmap           HB_BITOR( 1, 2 )
#define CWBorderPixel            HB_BITOR( 1, 3 )
#define CWBitGravity             HB_BITOR( 1, 4 )
#define CWWinGravity             HB_BITOR( 1, 5 )
#define CWBackingStore           HB_BITOR( 1, 6 )
#define CWBackingPlanes          HB_BITOR( 1, 7 )
#define CWBackingPixel           HB_BITOR( 1, 8 )
#define CWOverrideRedirect       HB_BITOR( 1, 9 )
#define CWSaveUnder              HB_BITOR( 1, 10 )
#define CWEventMask              HB_BITOR( 1, 11 )
#define CWDontPropagate          HB_BITOR( 1, 12 )
#define CWColormap               HB_BITOR( 1, 13 )
#define CWCursor                 HB_BITOR( 1, 14 )

/* ConfigureWindow structure */
#define CWX                      HB_BITOR( 1, 0 )
#define CWY                      HB_BITOR( 1, 1 )
#define CWWidth                  HB_BITOR( 1, 2 )
#define CWHeight                 HB_BITOR( 1, 3 )
#define CWBorderWidth            HB_BITOR( 1, 4 )
#define CWSibling                HB_BITOR( 1, 5 )
#define CWStackMode              HB_BITOR( 1, 6 )

/*
 * Data structure for setting window attributes.
 */
#define BACKGROUND_PIXMAP        1    /* background or None or ParentRelative */
#define BACKGROUND_PIXEL         2    /* background pixel */
#define BORDER_PIXMAP            3    /* border of the window */
#define LONG BORDER_PIXEL        4    /* border pixel value */
#define BIT_GRAVITY              5    /* one of bit gravity values */
#define WIN_GRAVITY              6    /* one of the window gravity values */
#define BACKING_STORE            7    /* NotUseful, WhenMapped, Always */
#define BACKING_PLANES           8    /* planes to be preseved if possible */
#define BACKING_PIXEL            9    /* value to use in restoring planes */
#define SAVE_UNDER               10   /* should bits under be saved? (popups) */
#define EVENT_MASK               11   /* set of events that should be saved */
#define DO_NOT_PROPAGATE_MASK    12   /* set of events that should not propagate */
#define OVERRIDE_REDIRECT        13   /* boolean value for override-redirect */
#define COLORMAP                 14   /* color map to be associated with window */
#define CURSOR                   15   /* cursor to be displayed (or None) */

/* Event names.  Used in "type" field in XEvent structures.  Not to be
confused with event masks above.  They start from 2 because 0 and 1
are reserved in the protocol for errors and replies. */
#define KeyPress                 2
#define KeyRelease               3
#define ButtonPress              4
#define ButtonRelease            5
#define MotionNotify             6
#define EnterNotify              7
#define LeaveNotify              8
#define FocusIn                  9
#define FocusOut                 10
#define KeymapNotify             11
#define Expose                   12
#define GraphicsExpose           13
#define NoExpose                 14
#define VisibilityNotify         15
#define CreateNotify             16
#define DestroyNotify            17
#define UnmapNotify              18
#define MapNotify                19
#define MapRequest               20
#define ReparentNotify           21
#define ConfigureNotify          22
#define ConfigureRequest         23
#define GravityNotify            24
#define ResizeRequest            25
#define CirculateNotify          26
#define CirculateRequest         27
#define PropertyNotify           28
#define SelectionClear           29
#define SelectionRequest         30
#define SelectionNotify          31
#define ColormapNotify           32
#define ClientMessage            33
#define MappingNotify            34
#define GenericEvent             35
#define LASTEvent                36   /* must be bigger than any event # */

#endif /* end HBX11_CH_ */
