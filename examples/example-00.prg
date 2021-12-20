/*
 *
 */

#include "hbX11.ch"

#define DPY      1
#define VIS      2
#define CMAP     3
#define WIN      4
#define SCREEN   5
#define FONT     6
#define WIDTH    7
#define HEIGHT   8
#define WIN_NAME 9
#define CTX      10

#define DTIME    20

PROCEDURE Main()

   LOCAL aWin
   LOCAL lExit := .F.
   LOCAL nStarted
   LOCAL nEventType
   LOCAL nDt

   aWin := hb_Open( 720, 450, "H e l l o  H a r b o u r" )

   DO WHILE( ! lExit )

      /* Input */
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

      /* GUI */
      IF( nk_begin( aWin[ CTX ], "H e l l o  N u k l e a r", { 50, 50, 200, 200 }, NK_WINDOW_BORDER + NK_WINDOW_MOVABLE + NK_WINDOW_SCALABLE + NK_WINDOW_CLOSABLE + NK_WINDOW_MINIMIZABLE + NK_WINDOW_TITLE ) )
         // Here your data
      ENDIF
      nk_end( aWin[ CTX ] )

      IF( nk_window_is_hidden( aWin[ CTX ], "H e l l o  N u k l e a r" ) )
         EXIT
      ENDIF

      /* Draw */
      XClearWindow( aWin[ DPY ], aWin[ WIN ] )
      nk_xlib_render( aWin[ WIN ], nk_rgb( 160, 60, 60 ) )
      XFlush( aWin[ DPY ] )

      /* Timing */
      nDt := TimeStamp() - nStarted
      if( nDt < DTIME )
         sleep_for( DTIME - nDt )
      ENDIF

   ENDDO

   hb_Close()

   RETURN
