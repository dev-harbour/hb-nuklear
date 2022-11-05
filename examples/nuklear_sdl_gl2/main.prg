/*
 * Harbour - public domain
 */

#include "nuklear_sdl_gl2.ch"

#define EASY 0
#define HARD 1

PROCEDURE Main()

   LOCAL pWin
   LOCAL glContext
   LOCAL nWidth, nHeight
   LOCAL lExit := .T.
   LOCAL pCtx
   LOCAL nEvent
   LOCAL op := EASY
   LOCAL property := 20
   LOCAL aBg := { 0.10, 0.18, 0.24, 1.0 }

   SDL_SetHint( SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0" )

   SDL_Init( SDL_INIT_VIDEO )

   SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 )
   SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 )
   SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 )
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 )
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 )

   pWin := SDL_CreateWindow( "Nuklear sdl gl2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 450, SDL_WINDOW_OPENGL + SDL_WINDOW_SHOWN + SDL_WINDOW_ALLOW_HIGHDPI )
   glContext := SDL_GL_CreateContext( pWin )

   SDL_GetWindowSize( pWin, @nWidth, @nHeight )

   pCtx := nk_sdl_init( pWin )

   nk_sdl_font_stash_begin( NIL )
   nk_sdl_font_stash_end()

   WHILE( lExit )

      nk_input_begin( pCtx )

      WHILE( SDL_PollEvent( @nEvent ) )
         IF( nEvent == SDL_QUIT )
            lExit := .F.
         ENDIF

         nk_sdl_handle_event( @nEvent )

      ENDDO

      nk_input_end( pCtx )

      IF( nk_begin( pCtx, "Demo", nk_rect( 50, 50, 230, 250 ), NK_WINDOW_BORDER + NK_WINDOW_MOVABLE + NK_WINDOW_SCALABLE + NK_WINDOW_MINIMIZABLE + NK_WINDOW_TITLE ) )

         nk_layout_row_static( pCtx, 30, 80, 1 )
         IF( nk_button_label( pCtx, "button" ) )
            OutStd( e"button pressed\n" )
         ENDIF

         nk_layout_row_dynamic( pCtx, 30, 2 )

         IF( nk_option_label( pCtx, "easy", op == EASY ) )
            op := EASY
         ENDIF

         IF( nk_option_label( pCtx, "hard", op == HARD ) )
            op := HARD
         ENDIF

         nk_layout_row_dynamic( pCtx, 25, 1 )
         nk_property_int( pCtx, "Compression:", 0, @property, 100, 10, 1 )

         nk_layout_row_dynamic( pCtx, 20, 1 )
         nk_label( pCtx, "background:", NK_TEXT_LEFT )
         nk_layout_row_dynamic( pCtx, 25, 1 )

         IF( nk_combo_begin_color( pCtx, aBg, nk_vec2( nk_widget_width( pCtx ), 400 ) ) )
            nk_layout_row_dynamic( pCtx, 120, 1 )
            aBg := nk_color_picker( pCtx, aBg, NK_RGBA )
            nk_layout_row_dynamic( pCtx, 25, 1 )
            aBg[ 1 ] := nk_propertyf( pCtx, "#R:", 0, aBg[ 1 ], 1.0, 0.01, 0.005 )
            aBg[ 2 ] := nk_propertyf( pCtx, "#G:", 0, aBg[ 2 ], 1.0, 0.01, 0.005 )
            aBg[ 3 ] := nk_propertyf( pCtx, "#B:", 0, aBg[ 3 ], 1.0, 0.01, 0.005 )
            aBg[ 4 ] := nk_propertyf( pCtx, "#A:", 0, aBg[ 4 ], 1.0, 0.01, 0.005 )
            nk_combo_end( pCtx )
         ENDIF
      ENDIF

      nk_end( pCtx )

      SDL_GetWindowSize( pWin, @nWidth, @nHeight )
      glViewport( 0, 0, nWidth, nHeight )
      glClear( GL_COLOR_BUFFER_BIT )
      glClearColor( aBg[ 1 ], aBg[ 2 ], aBg[ 3 ], aBg[ 4 ] )
      nk_sdl_render( NK_ANTI_ALIASING_ON )
      SDL_GL_SwapWindow( pWin )

   ENDDO

   nk_sdl_shutdown()
   SDL_GL_DeleteContext( glContext )
   SDL_DestroyWindow( pWin )
   SDL_Quit()

   RETURN
