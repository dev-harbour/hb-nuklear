/*
 * Nuklear library: nuklear_xlib.c
 *
 * Copyright 2022 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hb_nuklear_xlib.h"

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
