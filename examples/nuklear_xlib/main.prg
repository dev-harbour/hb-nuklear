/*
 *
 */

#include "nuklear_xlib.ch"

#define DTIME    20

PROCEDURE Main()

   LOCAL aWin
   LOCAL lExit := .F.
   LOCAL nStarted
   LOCAL nEventType
   LOCAL cTitle := "H e l l o  H a r b o u r"
   LOCAL nDt

   aWin := CreateWindow( 720, 450, "Nuklear xlib" )

   WHILE( ! lExit )

      nStarted := TimeStamp()

      nk_input_begin( aWin[ CTX ] )
      DO WHILE( XPending( aWin[ DPY ] ) != 0 )

         XNextEvent( aWin[ DPY ], @nEventType )

         IF( nEventType == ClientMessage )
            lExit := .T.
            EXIT
         ENDIF
         IF( XFilterEvent( @nEventType, aWin[ WIN ] ) )
            LOOP
         ENDIF

         nk_xlib_handle_event( aWin[ DPY ], aWin[ SCREEN ], aWin[ WIN ], @nEventType )

      ENDDO
      nk_input_end( aWin[ CTX ] )

      IF( nk_begin( aWin[ CTX ], cTitle, { 50, 50, 200, 200 }, NK_WINDOW_BORDER + NK_WINDOW_MOVABLE + NK_WINDOW_SCALABLE + NK_WINDOW_CLOSABLE + NK_WINDOW_MINIMIZABLE + NK_WINDOW_TITLE ) )
         // Here your data
      ENDIF
      nk_end( aWin[ CTX ] )

      IF( nk_window_is_hidden( aWin[ CTX ], cTitle ) )
         EXIT
      ENDIF

      XClearWindow( aWin[ DPY ], aWin[ WIN ] )
      nk_xlib_render( aWin[ WIN ], nk_rgb( 38, 77, 115 ) )
      XFlush( aWin[ DPY ] )

      nDt := TimeStamp() - nStarted
      if( nDt < DTIME )
         sleep_for( DTIME - nDt )
      ENDIF

   ENDDO

   CloseWindow( aWin )

   RETURN
