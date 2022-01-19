/*
 *
 */

#include "hbX11.h"

typedef struct
{
   Display *    dpy;
   Visual *     vis;
   Colormap     cmap;
   Window       win;
   int          screen;
   XFont *      font;
   unsigned int width;
   unsigned int height;
   const char*  win_name;
   struct nk_context* ctx;
   Window      root;
   XWindowAttributes attr;
   XSetWindowAttributes swa;
   Atom wm_delete_window;

} XWINDOW, PXWINDOW;

static PXWINDOW xw;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// pWinArray hb_Open( unsigned width, unsigned height, const char* win_name )
HB_FUNC( HB_OPEN )
{
   memset( &xw, 0, sizeof( xw ) );

   xw.dpy = XOpenDisplay( NULL );
   if( ! xw.dpy )
   {
      printf( "Could not open a display\n perhaps $DISPLAY is not set?" );
   }

   xw.width    = ( unsigned int ) hb_parni( 1 );
   xw.height   = ( unsigned int ) hb_parni( 2 );
   xw.win_name = hb_parc( 3 );
   xw.root     = DefaultRootWindow( xw.dpy );
   xw.screen   = XDefaultScreen( xw.dpy );
   xw.vis      = XDefaultVisual( xw.dpy, xw.screen );
   xw.cmap     = XCreateColormap( xw.dpy, xw.root, xw.vis, AllocNone );

   xw.swa.colormap = xw.cmap;
   xw.swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPress | ButtonReleaseMask| ButtonMotionMask |
      Button1MotionMask | Button3MotionMask | Button4MotionMask | Button5MotionMask| PointerMotionMask | KeymapStateMask;

   xw.win = XCreateWindow( xw.dpy, xw.root, 0, 0, xw.width, xw.height, 0, XDefaultDepth( xw.dpy, xw.screen ), InputOutput,
      xw.vis, CWEventMask | CWColormap, &xw.swa );

   XStoreName(xw.dpy, xw.win, xw.win_name);
   XChangeProperty( xw.dpy, xw.win, XInternAtom( xw.dpy, "_NET_WM_NAME", False ),
      XInternAtom( xw.dpy, "UTF8_STRING", False ), 8, PropModeReplace, ( unsigned char * ) xw.win_name, strlen( xw.win_name ) );

   XSetIconName(xw.dpy, xw.win, xw.win_name);
   XChangeProperty( xw.dpy, xw.win, XInternAtom( xw.dpy, "_NET_WM_ICON_NAME", False ),
      XInternAtom( xw.dpy, "UTF8_STRING", False ), 8, PropModeReplace, ( unsigned char * ) xw.win_name, strlen( xw.win_name ) );

   XMapWindow( xw.dpy, xw.win );

   xw.wm_delete_window = XInternAtom( xw.dpy, "WM_DELETE_WINDOW", False );
   XSetWMProtocols( xw.dpy, xw.win, &xw.wm_delete_window, 1 );

   XGetWindowAttributes( xw.dpy, xw.win, &xw.attr );
   xw.width  = ( unsigned int ) xw.attr.width;
   xw.height = ( unsigned int ) xw.attr.height;

    /* GUI */
   xw.font = nk_xfont_create( xw.dpy, "fixed" );
   xw.ctx = nk_xlib_init( xw.font, xw.dpy, xw.screen, xw.win, xw.width, xw.height );

   PHB_ITEM pItem = hb_itemArrayNew( 10 );

   hb_arraySetPtr( pItem, 1,                  xw.dpy );
   hb_arraySetPtr( pItem, 2,                  xw.vis );
   hb_arraySetNI(  pItem, 3, ( Colormap )     xw.cmap );
   hb_arraySetNI(  pItem, 4, ( Window )       xw.win );
   hb_arraySetNI(  pItem, 5,                  xw.screen );
   hb_arraySetPtr( pItem, 6,                  xw.font );
   hb_arraySetNI(  pItem, 7, ( unsigned int ) xw.width );
   hb_arraySetNI(  pItem, 8, ( unsigned int ) xw.height );
   hb_arraySetC(   pItem, 9,                  xw.win_name );
   hb_arraySetPtr( pItem, 10,                 xw.ctx );

   hb_itemReturnRelease( pItem );
}


// void hb_Close( void )
HB_FUNC( HB_CLOSE )
{
   nk_xfont_del( xw.dpy, xw.font );
   nk_xlib_shutdown();
   XUnmapWindow( xw.dpy, xw.win );
   XFreeColormap( xw.dpy, xw.cmap );
   XDestroyWindow( xw.dpy, xw.win );
   XCloseDisplay( xw.dpy );
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

// int nk_xlib_handle_event(Display*, int scrn, Window, XEvent*);
HB_FUNC( NK_XLIB_HANDLE_EVENT )
{
   XEvent event;

   if( xw.dpy && hb_param( 2, HB_IT_INTEGER ) != NULL && hb_param( 3, HB_IT_INTEGER ) != NULL && hb_param( 4, HB_IT_BYREF ) != NULL )
   {
      hb_retni( nk_xlib_handle_event( xw.dpy, hb_parni( 2 ), hb_parni( 3 ), &event ) );
      hb_stornint( event.type, 1 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void nk_xlib_render(Drawable screen, struct nk_color clear);
HB_FUNC( NK_XLIB_RENDER )
{
   PHB_ITEM pItem;

   if( hb_param( 1, HB_IT_INTEGER ) != NULL && ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 3 )
   {
      struct nk_color color;

      color.r = ( nk_byte ) hb_arrayGetNI(  pItem, 1 );
      color.g = ( nk_byte ) hb_arrayGetNI(  pItem, 2 );
      color.b = ( nk_byte ) hb_arrayGetNI(  pItem, 3 );
      color.a = ( nk_byte ) hb_arrayGetNI(  pItem, 4 );

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
// NK_API XFont*               nk_xfont_create(Display *dpy, const char *name);
// NK_API void nk_xfont_del(Display *dpy, XFont *font);


