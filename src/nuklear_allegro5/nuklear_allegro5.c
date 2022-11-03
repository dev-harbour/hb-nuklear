/*
 * Nuklear library: nuklear_allegro5.c
 *
 * Copyright 2022 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hb_nuklear_allegro5.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* ALLEGRO_DISPLAY */
static HB_GARBAGE_FUNC( hb_display_Destructor )
{
   ALLEGRO_DISPLAY **ppDisplay = ( ALLEGRO_DISPLAY **) Cargo;

   if( *ppDisplay )
   {
      ALLEGRO_DISPLAY *pDisplay = *ppDisplay;
      al_destroy_display( pDisplay);
      *ppDisplay = NULL;
   }
}

static const HB_GC_FUNCS s_gcDisplayFuncs =
{
   hb_display_Destructor,
   hb_gcDummyMark
};

ALLEGRO_DISPLAY *hb_display_Param( int iParam )
{
   ALLEGRO_DISPLAY **ppDisplay = ( ALLEGRO_DISPLAY **) hb_parptrGC( &s_gcDisplayFuncs, iParam );

   if( ppDisplay && *ppDisplay )
   {
      return *ppDisplay;
   }
   else
   {
      HB_ERR_ARGS();
      return NULL;
   }
}

ALLEGRO_DISPLAY *hb_display_ParamGet( int iParam )
{
   ALLEGRO_DISPLAY **ppDisplay = ( ALLEGRO_DISPLAY **) hb_parptrGC( &s_gcDisplayFuncs, iParam );

   return ppDisplay ? *ppDisplay : NULL;
}

ALLEGRO_DISPLAY *hb_display_ItemGet( PHB_ITEM pItem )
{
   ALLEGRO_DISPLAY **ppDisplay = ( ALLEGRO_DISPLAY **) hb_itemGetPtrGC( pItem, &s_gcDisplayFuncs );

   return ppDisplay ? *ppDisplay : NULL;
}

PHB_ITEM hb_display_ItemPut( PHB_ITEM pItem, ALLEGRO_DISPLAY *pDisplay )
{
   ALLEGRO_DISPLAY **ppDisplay = ( ALLEGRO_DISPLAY **) hb_gcAllocate( sizeof( ALLEGRO_DISPLAY *), &s_gcDisplayFuncs );
   *ppDisplay = pDisplay;
   return hb_itemPutPtrGC( pItem, ppDisplay );
}

void hb_display_ItemClear( PHB_ITEM pItem )
{
   ALLEGRO_DISPLAY **ppDisplay = ( ALLEGRO_DISPLAY **) hb_itemGetPtrGC( pItem, &s_gcDisplayFuncs );

   if( ppDisplay )
   {
      *ppDisplay = NULL;
   }
}

void hb_display_Return( ALLEGRO_DISPLAY *pDisplay )
{
   if( pDisplay )
   {
      hb_display_ItemPut( hb_param( -1, HB_IT_ANY ), pDisplay );
   }
   else
   {
      hb_ret();
   }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* ALLEGRO_EVENT_QUEUE *event_queue */
static HB_GARBAGE_FUNC( hb_event_queue_Destructor )
{
   ALLEGRO_EVENT_QUEUE **ppEvent_queue = ( ALLEGRO_EVENT_QUEUE **) Cargo;

   if( *ppEvent_queue )
   {
      ALLEGRO_EVENT_QUEUE *pEvent_queue = *ppEvent_queue;
      al_destroy_event_queue( pEvent_queue );
      *ppEvent_queue = NULL;
   }
}

static const HB_GC_FUNCS s_gcEvent_queueFuncs =
{
   hb_event_queue_Destructor,
   hb_gcDummyMark
};

ALLEGRO_EVENT_QUEUE *hb_event_queue_Param( int iParam )
{
   ALLEGRO_EVENT_QUEUE **ppEvent_queue = ( ALLEGRO_EVENT_QUEUE **) hb_parptrGC( &s_gcEvent_queueFuncs, iParam );

   if( ppEvent_queue && *ppEvent_queue )
   {
      return *ppEvent_queue;
   }
   else
   {
      HB_ERR_ARGS();
      return NULL;
   }
}

ALLEGRO_EVENT_QUEUE *hb_event_queue_ParamGet( int iParam )
{
   ALLEGRO_EVENT_QUEUE **ppEvent_queue = ( ALLEGRO_EVENT_QUEUE **) hb_parptrGC( &s_gcEvent_queueFuncs, iParam );

   return ppEvent_queue ? *ppEvent_queue : NULL;
}

ALLEGRO_EVENT_QUEUE *hb_event_queue_ItemGet( PHB_ITEM pItem )
{
   ALLEGRO_EVENT_QUEUE **ppEvent_queue = ( ALLEGRO_EVENT_QUEUE **) hb_itemGetPtrGC( pItem, &s_gcEvent_queueFuncs );

   return ppEvent_queue ? *ppEvent_queue : NULL;
}

PHB_ITEM hb_event_queue_ItemPut( PHB_ITEM pItem, ALLEGRO_EVENT_QUEUE *pEvent_queue )
{
   ALLEGRO_EVENT_QUEUE **ppEvent_queue = ( ALLEGRO_EVENT_QUEUE **) hb_gcAllocate( sizeof( ALLEGRO_EVENT_QUEUE *), &s_gcEvent_queueFuncs );
   *ppEvent_queue = pEvent_queue;
   return hb_itemPutPtrGC( pItem, ppEvent_queue );
}

void hb_event_queue_ItemClear( PHB_ITEM pItem )
{
   ALLEGRO_EVENT_QUEUE **ppEvent_queue = ( ALLEGRO_EVENT_QUEUE **) hb_itemGetPtrGC( pItem, &s_gcEvent_queueFuncs );

   if( ppEvent_queue )
   {
      *ppEvent_queue = NULL;
   }
}

void hb_event_queue_Return( ALLEGRO_EVENT_QUEUE *pEvent_queue )
{
   if( pEvent_queue )
   {
      hb_event_queue_ItemPut( hb_param( -1, HB_IT_ANY ), pEvent_queue );
   }
   else
   {
      hb_ret();
   }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* Allegro */

// AL_FUNC(void, al_clear_to_color, ( ALLEGRO_COLOR color ) );
HB_FUNC( AL_CLEAR_TO_COLOR )
{
   PHB_ITEM pArray;

   if( ( pArray = hb_param( 1, HB_IT_ARRAY ) ) != NULL )
   {
      ALLEGRO_COLOR color;
      color.r = ( float ) hb_arrayGetND( pArray, 1 );
      color.g = ( float ) hb_arrayGetND( pArray, 2 );
      color.b = ( float ) hb_arrayGetND( pArray, 3 );
      color.a = ( float ) hb_arrayGetND( pArray, 4 );

      al_clear_to_color( color );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// AL_FUNC(ALLEGRO_DISPLAY*, al_create_display, (int w, int h));
HB_FUNC( AL_CREATE_DISPLAY )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL  )
   {
      hb_display_Return( al_create_display( hb_parni( 1 ), hb_parni( 2 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// AL_FUNC(ALLEGRO_EVENT_QUEUE*, al_create_event_queue, (void));
HB_FUNC( AL_CREATE_EVENT_QUEUE )
{
   hb_event_queue_Return( al_create_event_queue() );
}

// AL_FUNC(void, al_destroy_display, (ALLEGRO_DISPLAY *display));
HB_FUNC( AL_DESTROY_DISPLAY )
{
   ALLEGRO_DISPLAY **ppDisplay = ( ALLEGRO_DISPLAY **) hb_parptrGC( &s_gcDisplayFuncs, 1 );

   if( ppDisplay && *ppDisplay )
   {
      al_destroy_display( *ppDisplay );
      *ppDisplay = NULL;
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// AL_FUNC(void, al_destroy_event_queue, (ALLEGRO_EVENT_QUEUE*));
HB_FUNC( AL_DESTROY_EVENT_QUEUE )
{
   ALLEGRO_EVENT_QUEUE **ppEvent_queue = ( ALLEGRO_EVENT_QUEUE **) hb_parptrGC( &s_gcEvent_queueFuncs, 1 );

   if( ppEvent_queue && *ppEvent_queue )
   {
      al_destroy_event_queue( *ppEvent_queue );
      *ppEvent_queue = NULL;
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// AL_FUNC(void, al_flip_display, (void));
HB_FUNC( AL_FLIP_DISPLAY )
{
   al_flip_display();
}

// AL_FUNC(ALLEGRO_EVENT_SOURCE *, al_get_display_event_source, (ALLEGRO_DISPLAY *display));
HB_FUNC( AL_GET_DISPLAY_EVENT_SOURCE )
{
   ALLEGRO_DISPLAY *pDisplay = hb_display_Param( 1 );

   if( pDisplay )
   {
      hb_retptr( al_get_display_event_source( pDisplay ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// AL_FUNC(ALLEGRO_EVENT_SOURCE *, al_get_keyboard_event_source, (void));
HB_FUNC( AL_GET_KEYBOARD_EVENT_SOURCE )
{
   hb_retptr( al_get_keyboard_event_source() );
}

// AL_FUNC(ALLEGRO_EVENT_SOURCE *, al_get_mouse_event_source, (void));
HB_FUNC( AL_GET_MOUSE_EVENT_SOURCE )
{
   hb_retptr( al_get_mouse_event_source() );
}

// AL_FUNC(bool, al_get_next_event, (ALLEGRO_EVENT_QUEUE*, ALLEGRO_EVENT *ret_event));
HB_FUNC( AL_GET_NEXT_EVENT )
{
   ALLEGRO_EVENT_QUEUE *pEvent_queue = hb_event_queue_Param( 1 );

   if( pEvent_queue  && hb_param( 2, HB_IT_BYREF ) != NULL )
   {
      ALLEGRO_EVENT event;                                        // union ALLEGRO_EVENT ?
      hb_retl( al_get_next_event( pEvent_queue, &event ) );
      hb_stornint( event.type, 2 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// AL_FUNC(void, al_init_timeout, (ALLEGRO_TIMEOUT *timeout, double seconds));
HB_FUNC( AL_INIT_TIMEOUT )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      ALLEGRO_TIMEOUT timeout;

      /* NOTE */
      al_init_timeout( &timeout, hb_parnd( 1 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// al_init() ( al_install_system( ALLEGRO_VERSION_INT, atexit ) )
HB_FUNC( AL_INIT )
{
   hb_retl( al_init() );
}

// AL_FUNC(bool, al_install_keyboard, (void));
HB_FUNC( AL_INSTALL_KEYBOARD )
{
   hb_retl( al_install_keyboard() );
}

// AL_FUNC(bool, al_install_mouse, (void));
HB_FUNC( AL_INSTALL_MOUSE )
{
   hb_retl( al_install_mouse() );
}

// AL_FUNC( ALLEGRO_COLOR, al_map_rgb, ( unsigned char r, unsigned char g, unsigned char b ) );
HB_FUNC( AL_MAP_RGB )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL && hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
      ALLEGRO_COLOR color = al_map_rgb( ( unsigned char ) hb_parni( 1 ) / 255, ( unsigned char ) hb_parni( 2 ) / 255, ( unsigned char ) hb_parni( 3 ) / 255 );

      PHB_ITEM pArray = hb_itemArrayNew( 4 );

      hb_arraySetNI( pArray, 1, color.r );
      hb_arraySetNI( pArray, 2, color.g );
      hb_arraySetNI( pArray, 3, color.b );
      hb_arraySetNI( pArray, 4, color.a );

      hb_itemReturnRelease( pArray );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// AL_FUNC( void, al_register_event_source, ( ALLEGRO_EVENT_QUEUE*, ALLEGRO_EVENT_SOURCE* ) );
HB_FUNC( AL_REGISTER_EVENT_SOURCE )
{
   ALLEGRO_EVENT_QUEUE *pEvent_queue = hb_event_queue_Param( 1 );
   ALLEGRO_EVENT_SOURCE *pEvent_source = hb_parptr( 2 );
   if( pEvent_queue && pEvent_source )
   {
      al_register_event_source( pEvent_queue, pEvent_source );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// AL_FUNC(void, al_set_mouse_wheel_precision, (int precision));
HB_FUNC( AL_SET_MOUSE_WHEEL_PRECISION )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      al_set_mouse_wheel_precision( hb_parni( 1 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// AL_FUNC(void, al_set_new_display_flags, (int flags));
HB_FUNC( AL_SET_NEW_DISPLAY_FLAGS )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      al_set_new_display_flags( hb_parni( 1 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// AL_FUNC(void, al_set_new_display_option, (int option, int value, int importance));
HB_FUNC( AL_SET_NEW_DISPLAY_OPTION )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL && hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
      al_set_new_display_option( hb_parni( 1 ), hb_parni( 2 ), hb_parni( 3 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// AL_FUNC( void, al_set_window_title, ( ALLEGRO_DISPLAY *display, const char *title ) );
HB_FUNC( AL_SET_WINDOW_TITLE )
{
   ALLEGRO_DISPLAY *pDisplay = hb_display_Param( 1 );

   if( pDisplay && hb_param( 2, HB_IT_STRING ) != NULL )
   {
      al_set_window_title( pDisplay, hb_parc( 2 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// AL_FUNC(bool, al_wait_for_event_until, (ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT *ret_event, ALLEGRO_TIMEOUT *timeout));
HB_FUNC( AL_WAIT_FOR_EVENT_UNTIL )
{
   ALLEGRO_EVENT_QUEUE *pEvent_queue = hb_event_queue_Param( 1 );

   if( pEvent_queue && hb_param( 2, HB_IT_BYREF ) != NULL )
   {
      ALLEGRO_EVENT event;
      ALLEGRO_TIMEOUT timeout;

      /* NOTE */
      hb_retl( al_wait_for_event_until( pEvent_queue, &event, &timeout ) );
      hb_stornint( event.type, 2 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* nuklear_allegro5 */

// NK_API struct nk_context* nk_allegro5_init(NkAllegro5Font *font, ALLEGRO_DISPLAY *dsp, unsigned int width, unsigned int height);
HB_FUNC( NK_ALLEGRO5_INIT )
{
   NkAllegro5Font *pFont = hb_parptr( 1 );
   ALLEGRO_DISPLAY *pDisplay = hb_display_Param( 2 );

   if( pFont && pDisplay && hb_param( 3, HB_IT_INTEGER ) != NULL && hb_param( 4, HB_IT_INTEGER ) != NULL )
   {
      hb_retptr( nk_allegro5_init( pFont, pDisplay, ( unsigned int ) hb_parni( 3 ), ( unsigned int ) hb_parni( 4 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// NK_API int nk_allegro5_handle_event(ALLEGRO_EVENT *ev);
HB_FUNC( NK_ALLEGRO5_HANDLE_EVENT )
{

   if( hb_param( 1, HB_IT_BYREF ) != NULL )
   {
      ALLEGRO_EVENT event;
      hb_retni( nk_allegro5_handle_event( &event ) );
      hb_stornint( event.type, 1 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// NK_API void nk_allegro5_shutdown(void);
HB_FUNC( NK_ALLEGRO5_SHUTDOWN )
{
   nk_allegro5_shutdown();
}

// NK_API void nk_allegro5_render(void);
HB_FUNC( NK_ALLEGRO5_RENDER )
{
   nk_allegro5_render();
}

// NK_API struct nk_image*       nk_allegro5_create_image(const char* file_name);
// NK_API void                   nk_allegro5_del_image(struct nk_image* image);

/* Fonts. We wrap normal allegro fonts in some nuklear book keeping */
// NK_API NkAllegro5Font* nk_allegro5_font_create_from_file(const char *file_name, int font_size, int flags);
HB_FUNC( NK_ALLEGRO5_FONT_CREATE_FROM_FILE )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL && hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
      hb_retptr( nk_allegro5_font_create_from_file( hb_parc( 1 ), hb_parni( 2 ), hb_parni( 3 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// NK_API void nk_allegro5_font_del(NkAllegro5Font *font);
HB_FUNC( NK_ALLEGRO5_FONT_DEL )
{
   NkAllegro5Font *pFont = hb_parptr( 1 );

   if( pFont )
   {
      nk_allegro5_font_del( pFont );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

/* NOTE : just use NkAllegro5Font instead of nk_user_font, since the former just extends the latter*/
// NK_API void                   nk_allegro5_font_set_font(NkAllegro5Font *font);
