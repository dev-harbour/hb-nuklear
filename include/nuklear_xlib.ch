/*
 *
 */

#ifndef NUKLEAR_XLIB_CH_
#define NUKLEAR_XLIB_CH_

#include "nuklear.ch"

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
#define KeyPressMask             1
#define KeyReleaseMask           2
#define ButtonPressMask          4
#define ButtonReleaseMask        8
#define EnterWindowMask          16
#define LeaveWindowMask          32
#define PointerMotionMask        64
#define PointerMotionHintMask    128
#define Button1MotionMask        256
#define Button2MotionMask        512
#define Button3MotionMask        1024
#define Button4MotionMask        2048
#define Button5MotionMask        4096
#define ButtonMotionMask         8192
#define KeymapStateMask          16384
#define ExposureMask             32768
#define VisibilityChangeMask     65536
#define StructureNotifyMask      131072
#define ResizeRedirectMask       262144
#define SubstructureNotifyMask   524288
#define SubstructureRedirectMask 1048576
#define FocusChangeMask          2097152
#define PropertyChangeMask       4194304
#define ColormapChangeMask       8388608
#define OwnerGrabButtonMask      16777216

/*****************************************************************
 * WINDOW DEFINITIONS
 *****************************************************************/

/* Window classes used by CreateWindow */
/* Note that CopyFromParent is already defined as 0 above */
#define InputOutput  1
#define InputOnly    2

/* Window attributes for CreateWindow and ChangeWindowAttributes */
#define CWBackPixmap             1
#define CWBackPixel              2
#define CWBorderPixmap           4
#define CWBorderPixel            8
#define CWBitGravity             16
#define CWWinGravity             32
#define CWBackingStore           64
#define CWBackingPlanes          128
#define CWBackingPixel           256
#define CWOverrideRedirect       512
#define CWSaveUnder              1024
#define CWEventMask              2048
#define CWDontPropagate          4096
#define CWColormap               8192
#define CWCursor                 16384

/* ConfigureWindow structure */
#define CWX                      1
#define CWY                      2
#define CWWidth                  4
#define CWHeight                 8
#define CWBorderWidth            16
#define CWSibling                32
#define CWStackMode              64

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

#endif /* end NUKLEAR_XLIB_CH_ */
