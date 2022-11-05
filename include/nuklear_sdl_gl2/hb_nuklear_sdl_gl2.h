/*
 *
 */

#ifndef HB_NUKLEAR_SDL_GL2_H_
#define HB_NUKLEAR_SDL_GL2_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <time.h>

#include "hbapi.h"
#include "hbapierr.h"
#include "hbapiitm.h"
#include "hbstack.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "../nuklear.h"
#include "nuklear_sdl_gl2.h"

HB_EXTERN_BEGIN

extern HB_EXPORT SDL_Window *hb_window_Param( int iParam );
extern HB_EXPORT PHB_ITEM    hb_window_ItemPut( PHB_ITEM pItem, SDL_Window *pSDL_Window );
extern HB_EXPORT void        hb_window_Return( SDL_Window *pSDL_Window );

extern HB_EXPORT SDL_GLContext hb_glContext_Param( int iParam );
extern HB_EXPORT PHB_ITEM      hb_glContext_ItemPut( PHB_ITEM pItem, SDL_GLContext glContext );
extern HB_EXPORT void          hb_glContext_Return( SDL_GLContext glContext );

HB_EXTERN_END

#define HB_ERR_ARGS() ( hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS ) )

#endif /* end HB_NUKLEAR_SDL_GL2_H_ */
