/*
 *
 */

#ifndef HBX11_H_
#define HBX11_H_

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

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "nuklear.h"
#include "nuklear_xlib.h"

HB_EXTERN_BEGIN

/* Display */
extern Display* hb_Display_Param( int iParam );
extern Display* hb_Display_ParamGet( int iParam );
extern Display* hb_Display_ItemGet( PHB_ITEM pItem );
extern PHB_ITEM hb_Display_ItemPut( PHB_ITEM pItem, Display * pDisplay );
extern void     hb_Display_ItemClear( PHB_ITEM pItem );
extern void     hb_Display_Return( Display * pDisplay );

/* nk_context */
typedef struct nk_context nk_context;
extern HB_EXPORT nk_context* hb_nk_context_Param( int iParam );
extern HB_EXPORT nk_context* hb_nk_context_ParamGet( int iParam );
extern HB_EXPORT nk_context* hb_nk_context_ItemGet( PHB_ITEM pItem );
extern HB_EXPORT PHB_ITEM    hb_nk_context_ItemPut( PHB_ITEM pItem, nk_context* pnk_context );
extern HB_EXPORT void        hb_nk_context_ItemClear( PHB_ITEM pItem );
extern HB_EXPORT void        hb_nk_context_Return( nk_context* pnk_context );

HB_EXTERN_END

#define HB_ERR_ARGS() ( hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS ) )

#endif /* end HBX11_H_ */
