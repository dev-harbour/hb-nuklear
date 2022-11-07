/*
 * Nuklear library: nuklear_xlib.c
 *
 * Copyright 2022 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hb_nuklear_xlib.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* Custom implementation */
typedef struct _NuklearXlib
{
   Display             *dpy;
   Visual              *vis;
   Colormap             cmap;
   Window               win;
   int                  screen;
   XFont               *font;
   unsigned int         width;
   unsigned int         height;
   const char          *win_name;
   struct nk_context   *ctx;
   //
   Window               root;
   XWindowAttributes    attr;
   XSetWindowAttributes swa;
   Atom                 wm_delete_window;
} NuklearXlib;

static NuklearXlib w;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// NuklearXlib CreateWindow( unsigned width, unsigned height, const char* win_name )
HB_FUNC( CREATEWINDOW )
{
   memset( &w, 0, sizeof( w ) );

   w.dpy = XOpenDisplay( NULL );
   if( ! w.dpy )
   {
      printf( "Could not open a display\n perhaps $DISPLAY is not set?" );
   }

   w.width    = ( unsigned int ) hb_parni( 1 );
   w.height   = ( unsigned int ) hb_parni( 2 );
   w.win_name = hb_parc( 3 );
   w.root     = DefaultRootWindow( w.dpy );
   w.screen   = XDefaultScreen( w.dpy );
   w.vis      = XDefaultVisual( w.dpy, w.screen );
   w.cmap     = XCreateColormap( w.dpy, w.root, w.vis, AllocNone );

   w.swa.colormap = w.cmap;
   w.swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPress | ButtonReleaseMask| ButtonMotionMask |
      Button1MotionMask | Button3MotionMask | Button4MotionMask | Button5MotionMask| PointerMotionMask | KeymapStateMask;

   w.win = XCreateWindow( w.dpy, w.root, 0, 0, w.width, w.height, 0, XDefaultDepth( w.dpy, w.screen ), InputOutput,
      w.vis, CWEventMask | CWColormap, &w.swa );

   XStoreName(w.dpy, w.win, w.win_name);
   XSetIconName(w.dpy, w.win, w.win_name);

   XChangeProperty( w.dpy, w.win,
         XInternAtom( w.dpy, "_NET_WM_NAME", False ),
         XInternAtom( w.dpy, "UTF8_STRING", False ),
         8, PropModeReplace, ( unsigned char * ) w.win_name,
         strlen( w.win_name ) );
   XChangeProperty( w.dpy, w.win,
         XInternAtom( w.dpy, "_NET_WM_ICON_NAME", False ),
         XInternAtom( w.dpy, "UTF8_STRING", False ),
         8, PropModeReplace, ( unsigned char * ) w.win_name,
         strlen( w.win_name ) );

   XClassHint * classhint = XAllocClassHint();
   if( classhint )
   {
      classhint->res_name = classhint->res_class = ( char * ) w.win_name;
      XSetClassHint( w.dpy, w.win, classhint );

      XChangeProperty( w.dpy, w.win,
            XInternAtom( w.dpy, "_NET_WM_VISIBLE_NAME", False ),
            XInternAtom( w.dpy, "UTF8_STRING", False ),
            8, PropModeReplace, ( unsigned char * ) w.win_name,
            strlen( w.win_name ) );

      XFree( classhint );
   }

   XMapWindow( w.dpy, w.win );

   w.wm_delete_window = XInternAtom( w.dpy, "WM_DELETE_WINDOW", False );
   XSetWMProtocols( w.dpy, w.win, &w.wm_delete_window, 1 );

   XGetWindowAttributes( w.dpy, w.win, &w.attr );
   w.width  = ( unsigned int ) w.attr.width;
   w.height = ( unsigned int ) w.attr.height;

   w.font = nk_xfont_create( w.dpy, "fixed" );
   w.ctx = nk_xlib_init( w.font, w.dpy, w.screen, w.win, w.width, w.height );

   PHB_ITEM pArray = hb_itemArrayNew( 10 );

   hb_arraySetPtr( pArray, 1,                  w.dpy );
   hb_arraySetPtr( pArray, 2,                  w.vis );
   hb_arraySetNI(  pArray, 3, ( Colormap )     w.cmap );
   hb_arraySetNI(  pArray, 4, ( Window )       w.win );
   hb_arraySetNI(  pArray, 5,                  w.screen );
   hb_arraySetPtr( pArray, 6,                  w.font );
   hb_arraySetNI(  pArray, 7, ( unsigned int ) w.width );
   hb_arraySetNI(  pArray, 8, ( unsigned int ) w.height );
   hb_arraySetC(   pArray, 9,                  w.win_name );
   hb_arraySetPtr( pArray, 10,                 w.ctx );

   hb_itemReturnRelease( pArray );
}

// int CloseWindow( NuklearXlib w )
HB_FUNC( CLOSEWINDOW )
{
   PHB_ITEM pArray;

   if( ( pArray = hb_param( 1, HB_IT_ARRAY ) ) != NULL )
   {
      NuklearXlib s_w;

      s_w.dpy  =              hb_arrayGetPtr( pArray, 1 );
      s_w.cmap = ( Colormap ) hb_arrayGetNI(  pArray, 3 );
      s_w.win  = ( Window )   hb_arrayGetNI(  pArray, 4 );
      s_w.font =              hb_arrayGetPtr( pArray, 6 );

      nk_xfont_del( s_w.dpy, s_w.font );
      nk_xlib_shutdown();
      XUnmapWindow( s_w.dpy, s_w.win );
      XFreeColormap( s_w.dpy, s_w.cmap );
      XDestroyWindow( s_w.dpy, s_w.win );
      XCloseDisplay( s_w.dpy );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* xlib */
// extern Display *XOpenDisplay( _Xconst char* display_name );
HB_FUNC( XOPENDISPLAY )
{
   hb_retptr( XOpenDisplay( NULL ) );
}

// extern Window XDefaultRootWindow( Display *display );
HB_FUNC( XDEFAULTROOTWINDOW )
{
   Display *display = hb_parptr( 1 );

   if( display )
   {
      hb_retnl( ( unsigned long ) XDefaultRootWindow( display ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern int XDefaultScreen( Display *display );
HB_FUNC( XDEFAULTSCREEN )
{
   Display *display = hb_parptr( 1 );

   if( display )
   {
      hb_retni( XDefaultScreen( display ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern Visual *XDefaultVisual( Display *display, int screen_number );
HB_FUNC( XDEFAULTVISUAL )
{
   Display *display = hb_parptr( 1 );

   if( display && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retptr( XDefaultVisual( display, hb_parni( 2 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern Colormap XCreateColormap( Display *display, Window w, Visual *visual, int alloc );
HB_FUNC( XCREATECOLORMAP )
{
   Display *display = hb_parptr( 1 );
   Visual *visual = hb_parptr( 3 );

   if( display && hb_param( 2, HB_IT_LONG ) != NULL && visual && hb_param( 4, HB_IT_INTEGER ) != NULL )
   {
      hb_retnl( ( unsigned long ) XCreateColormap( display, ( unsigned long ) hb_parnl( 2 ), visual, hb_parni( 4 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

/* extern Window XCreateWindow( Display *display, Window parent, int x, int y, unsigned int width, unsigned int height, unsigned int border_width,
                                int depth, unsigned int class, Visual *visual, unsigned long valuemask, XSetWindowAttributes* attributes ); */
HB_FUNC( XCREATEWINDOW )
{
   Display *display = hb_parptr( 1 );
   Visual *visual = hb_parptr( 10 );
   PHB_ITEM pItem;

   if( display &&
      hb_param( 2, HB_IT_LONG ) != NULL &&
      hb_param( 3, HB_IT_INTEGER ) != NULL &&
      hb_param( 4, HB_IT_INTEGER ) != NULL &&
      hb_param( 5, HB_IT_INTEGER ) != NULL &&
      hb_param( 6, HB_IT_INTEGER ) != NULL &&
      hb_param( 7, HB_IT_INTEGER ) != NULL &&
      hb_param( 8, HB_IT_INTEGER ) != NULL &&
      hb_param( 9, HB_IT_INTEGER ) != NULL &&
      hb_param( 10, HB_IT_POINTER ) != NULL &&
      hb_param( 11, HB_IT_NUMERIC ) != NULL &&
      ( pItem = hb_param( 12, HB_IT_ARRAY ) ) != NULL )
   {
      XSetWindowAttributes swa;
      memset( &swa, 0, sizeof( swa ) );

      swa.background_pixmap     = hb_arrayGetNL( pItem, 1 );   // Pixmap
      swa.background_pixel      = hb_arrayGetNL( pItem, 2 );   // unsigned long
      swa.border_pixmap         = hb_arrayGetNL( pItem, 3 );   // Pixmap
      swa.border_pixel          = hb_arrayGetNL( pItem, 4 );   // unsigned long
      swa.bit_gravity           = hb_arrayGetNI( pItem, 5 );   // int
      swa.win_gravity           = hb_arrayGetNI( pItem, 6 );   // int
      swa.backing_store         = hb_arrayGetNI( pItem, 7 );   // int
      swa.backing_planes        = hb_arrayGetNL( pItem, 8 );   // unsigned long
      swa.backing_pixel         = hb_arrayGetNL( pItem, 9 );   // unsigned long
      swa.save_under            = hb_arrayGetL ( pItem, 10 );  // Bool
      swa.event_mask            = hb_arrayGetNL( pItem, 11 );  // long
      swa.do_not_propagate_mask = hb_arrayGetNL( pItem, 12 );  // long
      swa.override_redirect     = hb_arrayGetL ( pItem, 13 );  // Bool
      swa.colormap              = hb_arrayGetNL( pItem, 14 );  // Colormap
      swa.cursor                = hb_arrayGetNI( pItem, 15 );  // Cursor

      hb_retnl( ( unsigned long ) XCreateWindow( display, ( unsigned long ) hb_parnl( 2 ), hb_parni( 3 ), hb_parni( 4 ), ( unsigned int ) hb_parni( 5 ),
         ( unsigned int ) hb_parni( 6 ), ( unsigned int ) hb_parni( 7 ), hb_parni( 8 ), ( unsigned int ) hb_parni( 9 ), visual,
         ( unsigned long ) hb_parnl( 11 ), &swa ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern int XDefaultDepth( Display *display, int screen_number );
HB_FUNC( XDEFAULTDEPTH )
{
   Display *display = hb_parptr( 1 );

   if( display && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( XDefaultDepth( display, hb_parni( 2 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern int XStoreName( Display *display, Window w, _Xconst char* window_name );
HB_FUNC( XSTORENAME )
{
   Display *display = hb_parptr( 1 );

   if( display &&
      hb_param( 2, HB_IT_LONG ) != NULL &&
      hb_param( 3, HB_IT_STRING ) != NULL )
   {
      hb_retni( XStoreName( display, ( unsigned long ) hb_parnl( 2 ), hb_parc( 3 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern int XMapWindow( Display *display, Window w );
HB_FUNC( XMAPWINDOW )
{
   Display *display = hb_parptr( 1 );

   if( display && hb_param( 2, HB_IT_LONG ) != NULL )
   {
      hb_retni( XMapWindow( display, ( unsigned long ) hb_parnl( 2 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern Atom XInternAtom( Display *display, _Xconst char* atom_name, Bool only_if_exists );
HB_FUNC( XINTERNATOM )
{
   Display *display = hb_parptr( 1 );

   if( display &&
      hb_param( 2, HB_IT_STRING ) != NULL  &&
      hb_param( 3, HB_IT_LOGICAL ) != NULL )
   {
      hb_retnl( ( unsigned long ) XInternAtom( display, hb_parc( 2 ), hb_parl( 3 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern Status XSetWMProtocols( Display *display, Window w, Atom* protocols, int count );
HB_FUNC( XSETWMPROTOCOLS )
{
   Display *display = hb_parptr( 1 );

   if( display &&
      hb_param( 2, HB_IT_LONG ) != NULL &&
      hb_param( 3, HB_IT_LONG ) != NULL &&
      hb_param( 4, HB_IT_INTEGER ) != NULL )
   {
      Atom protocols;
      hb_retni( XSetWMProtocols( display, ( unsigned long ) hb_parnl( 2 ), &protocols, hb_parni( 4 ) ) );
      hb_stornl( protocols, 3 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern Status XGetWindowAttributes( Display *display, Window w, XWindowAttributes* window_attributes_return );
HB_FUNC( XGETWINDOWATTRIBUTES )
{
   Display *display = hb_parptr( 1 );

   if( display && hb_param( 2, HB_IT_LONG ) != NULL )
   {
      XWindowAttributes wa;

      hb_retni( XGetWindowAttributes( display, ( unsigned long ) hb_parnl( 2 ), &wa ) );

      hb_reta( 23 );
      hb_storvni(  wa.x,                     -1, 1 );
      hb_storvni(  wa.y,                     -1, 2 );
      hb_storvni(  wa.width,                 -1, 3 );
      hb_storvni(  wa.height,                -1, 4 );
      hb_storvni(  wa.border_width,          -1, 5 );
      hb_storvni(  wa.depth,                 -1, 6 );
      hb_storvptr( wa.visual,                -1, 7 );
      hb_storvnl(  wa.root,                  -1, 8 );
      hb_storvni(  wa.class,                 -1, 9 );
      hb_storvni(  wa.bit_gravity,           -1, 10 );
      hb_storvni(  wa.win_gravity,           -1, 11 );
      hb_storvni(  wa.backing_store,         -1, 12 );
      hb_storvnl(  wa.backing_planes,        -1, 13 );
      hb_storvnl(  wa.backing_pixel,         -1, 14 );
      hb_storvl(   wa.save_under,            -1, 15 );
      hb_storvnl(  wa.colormap,              -1, 16 );
      hb_storvl(   wa.map_installed,         -1, 17 );
      hb_storvni(  wa.map_state,             -1, 18 );
      hb_storvnl(  wa.all_event_masks,       -1, 19 );
      hb_storvnl(  wa.your_event_mask,       -1, 20 );
      hb_storvnl(  wa.do_not_propagate_mask, -1, 21 );
      hb_storvl(   wa.override_redirect,     -1, 22 );
      hb_storvptr( wa.screen,                -1, 23 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern int XPending( Display* display );
HB_FUNC( XPENDING )
{
   Display* display = hb_parptr( 1 );

   if( display )
   {
      hb_retni( XPending( display ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern int XNextEvent( Display *display, XEvent *event_return );
HB_FUNC( XNEXTEVENT )
{
   Display* display = hb_parptr( 1 );
   XEvent event;

   if( display && hb_param( 2, HB_IT_BYREF ) != NULL )
   {
      hb_retni( XNextEvent( display, &event ) );
      hb_stornint( event.type, 2 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern Bool XFilterEvent( XEvent* event, Window window );
HB_FUNC( XFILTEREVENT )
{
   XEvent event;

   if( hb_param( 1, HB_IT_BYREF ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( XFilterEvent( &event, ( Window ) hb_parni( 2 ) ) );
      hb_stornint( event.type, 1 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern int XClearWindow( Display* display, Window w );
HB_FUNC( XCLEARWINDOW )
{
   Display* display = hb_parptr( 1 );

   if( display && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( XClearWindow( display, ( Window ) hb_parni( 2 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern int XFlush( Display* display );
HB_FUNC( XFLUSH )
{
   Display* display = hb_parptr( 1 );

   if( display )
   {
      hb_retni( XFlush( display ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// long TimeStamp( void )
HB_FUNC( TIMESTAMP )
{
   struct timeval tv;
   if( gettimeofday( &tv, NULL ) < 0 )
   {
      hb_retni( 0 );
   }
   hb_retnl( ( long ) ( ( long ) tv.tv_sec * 1000 + ( long ) tv.tv_usec / 1000 ) );
}

// void Sleep_for( long t )
HB_FUNC( SLEEP_FOR )
{
   long t = hb_parnl( 1 );
   struct timespec req;
   const time_t sec = ( int ) ( t / 1000 );
   const long ms = t - ( sec * 1000 );
   req.tv_sec = sec;
   req.tv_nsec = ms * 1000000L;
   while( -1 == nanosleep( &req, &req ) );
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* nuklear_xlib.h */

// struct nk_context* nk_xlib_init(XFont*, Display*, int scrn, Window root, unsigned w, unsigned h);
/* implemented in the library */

// int nk_xlib_handle_event(Display*, int scrn, Window, XEvent*);
HB_FUNC( NK_XLIB_HANDLE_EVENT )
{
   XEvent event;

   if( hb_param( 1, HB_IT_POINTER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL && hb_param( 3, HB_IT_INTEGER ) != NULL && hb_param( 4, HB_IT_BYREF ) != NULL )
   {
      hb_retni( nk_xlib_handle_event( w.dpy, hb_parni( 2 ), hb_parni( 3 ), &event ) );
      hb_stornint( event.type, 4 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void nk_xlib_render(Drawable screen, struct nk_color clear);
HB_FUNC( NK_XLIB_RENDER )
{
   PHB_ITEM pArray;

   if( hb_param( 1, HB_IT_INTEGER ) != NULL && ( pArray = hb_param( 2, HB_IT_ARRAY ) ) != NULL )
   {
      struct nk_color color;

      color.r = ( nk_byte ) hb_arrayGetNI(  pArray, 1 );
      color.g = ( nk_byte ) hb_arrayGetNI(  pArray, 2 );
      color.b = ( nk_byte ) hb_arrayGetNI(  pArray, 3 );
      color.a = ( nk_byte ) hb_arrayGetNI(  pArray, 4 );

      nk_xlib_render( hb_parni( 1 ), color );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void nk_xlib_shutdown(void);
// void                 nk_xlib_set_font(XFont*);
// void                 nk_xlib_push_font(XFont*);
// void                 nk_xlib_paste(nk_handle, struct nk_text_edit*);
// void                 nk_xlib_copy(nk_handle, const char*, int len);

/* Image */
// #ifdef NK_XLIB_INCLUDE_STB_IMAGE
// struct nk_image nk_xsurf_load_image_from_file(char const *filename);
// struct nk_image nk_xsurf_load_image_from_memory(const void *membuf, nk_uint membufSize);
// #endif

/* Font */
// NK_API XFont* nk_xfont_create(Display *dpy, const char *name);

// NK_API void nk_xfont_del(Display *dpy, XFont *font);
/* implemented in the library */
