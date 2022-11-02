/*
 *
 */

#include "nuklear_glfw_gl2.ch"

#define EASY 0
#define HARD 1

PROCEDURE Main()

   LOCAL pWin
   LOCAL nWidth := 0, nHeight := 0
   LOCAL pCtx
   LOCAL nOp := EASY
   LOCAL nProperty := 20
   LOCAL aBg := { 0.10, 0.18, 0.24, 1.0 }

   IF( ! glfwInit() )
      OutStd( e"[GFLW] failed to init! \n" )
   ENDIF

   pWin := glfwCreateWindow( 720, 450, "Nuklear glfw gl2" )
   glfwMakeContextCurrent( pWin )
   glfwGetWindowSize( pWin, @nWidth, @nHeight )

   pCtx := nk_glfw3_init( pWin, NK_GLFW3_INSTALL_CALLBACKS )

   WHILE( ! glfwWindowShouldClose( pWin ) )

      glfwPollEvents()
      nk_glfw3_new_frame()

      IF( nk_begin( pCtx, "Demo", nk_rect( 50, 50, 230, 250 ), NK_WINDOW_BORDER + NK_WINDOW_MOVABLE + NK_WINDOW_SCALABLE + NK_WINDOW_MINIMIZABLE + NK_WINDOW_TITLE ) )

         nk_layout_row_static( pCtx, 30, 80, 1 )

         IF( nk_button_label( pCtx, "button" ) )
            OutStd( e"button pressed \n" )
         ENDIF

         nk_layout_row_dynamic( pCtx, 30, 2 )

         IF( nk_option_label( pCtx, "easy", nOp == EASY ) )
            nOp := EASY
         ENDIF

         IF( nk_option_label( pCtx, "hard", nOp == HARD ) )
            nOp = HARD
         ENDIF

         nk_layout_row_dynamic( pCtx, 25, 1 )
         nk_property_int( pCtx, "Compression:", 0, @nProperty, 100, 10, 1 )

         nk_layout_row_dynamic( pCtx, 20, 1 )

         nk_label( pCtx, "background:", NK_TEXT_LEFT )

         nk_layout_row_dynamic( pCtx, 25, 1 )

         IF( nk_combo_begin_color( pCtx, nk_rgb_cf( aBg ), nk_vec2( nk_widget_width( pCtx ), 400 ) ) )

            nk_layout_row_dynamic( pCtx, 120, 1 )

            aBg := nk_color_picker( pCtx, aBg, 1 )

            nk_layout_row_dynamic( pCtx, 25, 1)
            aBg[ 1 ] = nk_propertyf( pCtx, "#R:", 0, aBg[ 1 ], 1.0, 0.01, 0.005 )
            aBg[ 2 ] = nk_propertyf( pCtx, "#G:", 0, aBg[ 2 ], 1.0, 0.01, 0.005 )
            aBg[ 3 ] = nk_propertyf( pCtx, "#B:", 0, aBg[ 3 ], 1.0, 0.01, 0.005 )
            aBg[ 4 ] = nk_propertyf( pCtx, "#A:", 0, aBg[ 4 ], 1.0, 0.01, 0.005 )
            nk_combo_end( pCtx )
         ENDIF

      ENDIF

      nk_end( pCtx )

      glfwGetWindowSize( pWin, @nWidth, @nHeight )
      glViewport( 0, 0, nWidth, nHeight )
      glClear( GL_COLOR_BUFFER_BIT )
      glClearColor( aBg[ 1 ], aBg[ 2 ], aBg[ 3 ], aBg[ 4 ] )

      nk_glfw3_render( NK_ANTI_ALIASING_ON )

      glfwSwapBuffers( pWin )

   ENDDO

   nk_glfw3_shutdown()
   glfwTerminate()

   RETURN
