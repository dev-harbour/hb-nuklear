/*
 *
 */

#include "nuklear_allegro5.ch"

#define EASY 0
#define HARD 1

PROCEDURE Main()

   LOCAL nWidth := 720, nHeight := 450
   LOCAL pDisplay
   LOCAL pEvent_queue
   LOCAL pFont
   LOCAL pCtx
   LOCAL lGet_event
   LOCAL nEvent
   LOCAL nOp       := EASY
   LOCAL nProperty := 20

   IF( ! al_init() )
      OutStd( e"failed to initialize allegro5!\n" )
      RETURN
   ENDIF

   al_install_mouse()
   al_set_mouse_wheel_precision( 150 )
   al_install_keyboard()

   al_set_new_display_flags( ALLEGRO_WINDOWED + ALLEGRO_RESIZABLE + ALLEGRO_OPENGL )
   al_set_new_display_option( ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST )
   al_set_new_display_option( ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST )

   pDisplay := al_create_display( nWidth, nHeight )
   IF( pDisplay == NIL )
      OutStd( e"failed to create pDisplay!\n" )
      RETURN
   ENDIF

   pEvent_queue := al_create_event_queue()
   IF( pEvent_queue == NIL )
      OutStd( e"failed to create pEvent_queue!\n" )
      al_destroy_display( pDisplay )
      RETURN
   ENDIF

   al_set_window_title( pDisplay, "Harbour, Nuklear and Allegro" )

   al_register_event_source( pEvent_queue, al_get_display_event_source( pDisplay ) )
   al_register_event_source( pEvent_queue, al_get_mouse_event_source() )
   al_register_event_source( pEvent_queue, al_get_keyboard_event_source() )

   pFont := nk_allegro5_font_create_from_file( "../font/9x18.ttf", 20, 0 )

   pCtx := nk_allegro5_init( pFont, pDisplay, nWidth, nHeight )

   WHILE( .T. )

      al_init_timeout( 0.01 )

      lGet_event := al_wait_for_event_until( pEvent_queue, @nEvent )

      IF( lGet_event .AND. nEvent == ALLEGRO_EVENT_DISPLAY_CLOSE )
         EXIT
      ENDIF

      nk_input_begin( pCtx )
      IF( lGet_event )

         WHILE( lGet_event )
            nk_allegro5_handle_event( @nEvent )
            lGet_event := al_get_next_event( pEvent_queue, @nEvent )
         ENDDO

      ENDIF
      nk_input_end( pCtx )

      IF( nk_begin( pCtx, "Demo", nk_rect( 50, 50, 200, 200 ), NK_WINDOW_BORDER + NK_WINDOW_MOVABLE + NK_WINDOW_SCALABLE + NK_WINDOW_CLOSABLE + NK_WINDOW_MINIMIZABLE + NK_WINDOW_TITLE ) )

         nk_layout_row_static( pCtx, 30, 80, 1 )

         IF( nk_button_label( pCtx, "button" ) )
            OutStd( e"button pressed\n" )
         ENDIF

         nk_layout_row_dynamic( pCtx, 30, 2 )

         IF( nk_option_label( pCtx, "easy", nOp == EASY ) )
            nOp := EASY
         ENDIF

         IF( nk_option_label( pCtx, "hard", nOp == HARD ) )
            nOp := HARD
         ENDIF

         nk_layout_row_dynamic( pCtx, 22, 1 )
         nk_property_int( pCtx, "Compression:", 0, @nProperty, 100, 10, 1 )

      ENDIF
      nk_end( pCtx )

      al_clear_to_color( { 30 / 255, 69 / 255, 34 / 255, 1.0 } )

      nk_allegro5_render()
      al_flip_display()

   ENDDO

   nk_allegro5_font_del( pFont )
   nk_allegro5_shutdown()
   al_destroy_display( pDisplay )
   al_destroy_event_queue( pEvent_queue )

   RETURN
