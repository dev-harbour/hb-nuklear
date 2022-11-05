/*
 * Nuklear library: nuklear_sdl_gl2.c
 *
 * Copyright 2022 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hb_nuklear_sdl_gl2.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* SDL_Window */
static HB_GARBAGE_FUNC( hb_window_destructor )
{
   SDL_Window **ppSDL_Window = ( SDL_Window **) Cargo;

   if( *ppSDL_Window )
   {
      SDL_Window *pSDL_Window = *ppSDL_Window;
      *ppSDL_Window = NULL;
      SDL_DestroyWindow( pSDL_Window );
   }
}

static const HB_GC_FUNCS s_gcWindowFuncs =
{
   hb_window_destructor,
   hb_gcDummyMark
};

SDL_Window *hb_window_Param( int iParam )
{
   SDL_Window **ppSDL_Window = ( SDL_Window **) hb_parptrGC( &s_gcWindowFuncs, iParam );

   if( ppSDL_Window && *ppSDL_Window )
   {
      return *ppSDL_Window;
   }
   else
   {
      HB_ERR_ARGS();
      return NULL;
   }
}

PHB_ITEM hb_window_ItemPut( PHB_ITEM pItem, SDL_Window *pSDL_Window )
{
   SDL_Window **ppSDL_Window = ( SDL_Window **) hb_gcAllocate( sizeof( SDL_Window *), &s_gcWindowFuncs );
   *ppSDL_Window = pSDL_Window;
   return hb_itemPutPtrGC( pItem, ppSDL_Window );
}

void hb_window_Return( SDL_Window *pSDL_Window )
{
   if( pSDL_Window )
   {
      hb_window_ItemPut( hb_param( -1, HB_IT_ANY ), pSDL_Window );
   }
   else
   {
      hb_ret();
   }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* SDL_GLContext */
static HB_GARBAGE_FUNC( hb_glContext_destructor )
{
   SDL_GLContext *pGLContext = ( SDL_GLContext *) Cargo;

   if( *pGLContext )
   {
      SDL_GLContext glContext = *pGLContext;
      *pGLContext = NULL;
      SDL_GL_DeleteContext( glContext );
   }
}

static const HB_GC_FUNCS s_gcGlContextFuncs =
{
   hb_glContext_destructor,
   hb_gcDummyMark
};

SDL_GLContext hb_glContext_Param( int iParam )
{
   SDL_GLContext *pGLContext = ( SDL_GLContext *) hb_parptrGC( &s_gcGlContextFuncs, iParam );

   if( pGLContext && *pGLContext )
   {
      return *pGLContext;
   }
   else
   {
      HB_ERR_ARGS();
      return NULL;
   }
}

PHB_ITEM hb_glContext_ItemPut( PHB_ITEM pItem, SDL_GLContext glContext )
{
   SDL_GLContext *pGLContext = ( SDL_GLContext *) hb_gcAllocate( sizeof( SDL_GLContext ), &s_gcGlContextFuncs );
   *pGLContext = glContext;
   return hb_itemPutPtrGC( pItem, pGLContext );
}

void hb_glContext_Return( SDL_GLContext glContext )
{
   if( glContext )
   {
      hb_glContext_ItemPut( hb_param( -1, HB_IT_ANY ), glContext );
   }
   else
   {
      hb_ret();
   }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* SDL */

// extern DECLSPEC SDL_Window * SDLCALL SDL_CreateWindow(const char *title, int x, int y, int w, int h, Uint32 flags);
HB_FUNC( SDL_CREATEWINDOW )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL &&
       hb_param( 2, HB_IT_INTEGER ) != NULL &&
       hb_param( 3, HB_IT_INTEGER ) != NULL &&
       hb_param( 4, HB_IT_INTEGER ) != NULL &&
       hb_param( 5, HB_IT_INTEGER ) != NULL &&
       hb_param( 6, HB_IT_INTEGER ) != NULL )
   {
      hb_window_Return( SDL_CreateWindow( hb_parc( 1 ), hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ), hb_parni( 5 ), ( Uint32 ) hb_parni( 6 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern DECLSPEC void SDLCALL SDL_DestroyWindow(SDL_Window * window);
HB_FUNC( SDL_DESTROYWINDOW )
{
   SDL_Window **ppSDL_Window = ( SDL_Window **) hb_parptrGC( &s_gcWindowFuncs, 1 );

   if( ppSDL_Window && *ppSDL_Window )
   {
      SDL_Window *pSDL_Window = *ppSDL_Window;
      *ppSDL_Window = NULL;
      SDL_DestroyWindow( pSDL_Window );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern DECLSPEC void SDLCALL SDL_GetWindowSize(SDL_Window * window, int *w, int *h);
HB_FUNC( SDL_GETWINDOWSIZE )
{
   SDL_Window *window = hb_window_Param( 1 );

   if( window && hb_param( 2, HB_IT_BYREF ) != NULL && hb_param( 3, HB_IT_BYREF ) != NULL )
   {
      int w, h;
      SDL_GetWindowSize( window, &w, &h );
      hb_stornint( w, 2 );
      hb_stornint( h, 3 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern DECLSPEC SDL_GLContext SDLCALL SDL_GL_CreateContext(SDL_Window * window);
HB_FUNC( SDL_GL_CREATECONTEXT )
{
   SDL_Window *window = hb_window_Param( 1 );

   if( window )
   {
      hb_glContext_Return( SDL_GL_CreateContext( window ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern DECLSPEC void SDLCALL SDL_GL_DeleteContext(SDL_GLContext context);
HB_FUNC( SDL_GL_DELETECONTEXT )
{
   SDL_GLContext *pGLContext = ( SDL_GLContext *) hb_parptrGC( &s_gcGlContextFuncs, 1 );

   if( pGLContext && *pGLContext )
   {
      SDL_Window *glContext = *pGLContext;
      *pGLContext = NULL;
      SDL_DestroyWindow( glContext );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern DECLSPEC int SDLCALL SDL_GL_SetAttribute(SDL_GLattr attr, int value);
HB_FUNC( SDL_GL_SETATTRIBUTE )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {

      SDL_GL_SetAttribute( hb_parni( 1 ), hb_parni( 2 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern DECLSPEC void SDLCALL SDL_GL_SwapWindow(SDL_Window * window);
HB_FUNC( SDL_GL_SWAPWINDOW )
{
   SDL_Window *window = hb_window_Param( 1 );

   if( window )
   {
      SDL_GL_SwapWindow( window );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern DECLSPEC int SDLCALL SDL_Init(Uint32 flags);
HB_FUNC( SDL_INIT )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( SDL_Init( ( Uint32 ) hb_parni( 1 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern DECLSPEC int SDLCALL SDL_PollEvent(SDL_Event * event);
HB_FUNC( SDL_POLLEVENT )
{
   if( hb_param( 1, HB_IT_BYREF ) != NULL )
   {
      SDL_Event event;
      hb_retl( SDL_PollEvent( &event ) );
      hb_stornint( event.type, 1 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// extern DECLSPEC void SDLCALL SDL_Quit(void);
HB_FUNC( SDL_QUIT )
{
   SDL_Quit();
}

// extern DECLSPEC SDL_bool SDLCALL SDL_SetHint(const char *name, const char *value);
HB_FUNC( SDL_SETHINT )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL && hb_param( 2, HB_IT_STRING ) != NULL )
   {
      hb_retl( SDL_SetHint( hb_parc( 1 ), hb_parc( 2 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* nuklear_sdl_gl2 */
// NK_API struct nk_context* nk_sdl_init(SDL_Window *win);
HB_FUNC( NK_SDL_INIT )
{
   SDL_Window *window = hb_window_Param( 1 );
   if( window )
   {
      hb_retptr( nk_sdl_init( window ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// NK_API void nk_sdl_font_stash_begin(struct nk_font_atlas **atlas);
HB_FUNC( NK_SDL_FONT_STASH_BEGIN )
{
   if( hb_param( 1, HB_IT_NIL ) == NULL )
   {
      struct nk_font_atlas *atlas;
      nk_sdl_font_stash_begin( &atlas );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// NK_API void nk_sdl_font_stash_end(void);
HB_FUNC( NK_SDL_FONT_STASH_END )
{
   nk_sdl_font_stash_end();
}

// NK_API int nk_sdl_handle_event(SDL_Event *evt);
HB_FUNC( NK_SDL_HANDLE_EVENT )
{
   if( hb_param( 1, HB_IT_BYREF ) != NULL )
   {
      SDL_Event event;
      hb_retni( nk_sdl_handle_event( &event ) );
      hb_stornint( event.type, 1 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// NK_API void nk_sdl_render(enum nk_anti_aliasing);
HB_FUNC( NK_SDL_RENDER )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      nk_sdl_render( hb_parni( 1 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// NK_API void nk_sdl_shutdown(void);
HB_FUNC( NK_SDL_SHUTDOWN )
{
   nk_sdl_shutdown();
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* GL */
// void glClear( GLbitfield mask )
HB_FUNC( GLCLEAR )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      glClear( hb_parni( 1 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void glClearColor( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
HB_FUNC( GLCLEARCOLOR )
{
   if( hb_param( 1, HB_IT_DOUBLE ) != NULL && hb_param( 2, HB_IT_DOUBLE ) != NULL && hb_param( 3, HB_IT_DOUBLE ) != NULL && hb_param( 4, HB_IT_DOUBLE ) != NULL )
   {
      glClearColor( ( float ) hb_parnd( 1 ), ( float ) hb_parnd( 2 ), ( float ) hb_parnd( 3 ), ( float ) hb_parnd( 4 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void glViewport( GLint x, GLint y, GLsizei width, GLsizei height )
HB_FUNC(GLVIEWPORT)
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL && hb_param( 3, HB_IT_INTEGER ) != NULL && hb_param( 4, HB_IT_INTEGER ) != NULL )
   {
      glViewport( hb_parni( 1 ), hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}
