/*
 *
 */

#ifndef HB_NUKLEAR_ALLEGRO5_H_
#define HB_NUKLEAR_ALLEGRO5_H_

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

#include "../nuklear.h"
#include "nuklear_allegro5.h"

HB_EXTERN_BEGIN

extern HB_EXPORT ALLEGRO_DISPLAY *hb_display_Param( int iParam );
extern HB_EXPORT ALLEGRO_DISPLAY *hb_display_ParamGet( int iParam );
extern HB_EXPORT ALLEGRO_DISPLAY *hb_display_ItemGet( PHB_ITEM pItem );
extern HB_EXPORT PHB_ITEM         hb_display_ItemPut( PHB_ITEM pItem, ALLEGRO_DISPLAY *pDisplay );
extern HB_EXPORT void             hb_display_ItemClear( PHB_ITEM pItem );
extern HB_EXPORT void             hb_display_Return( ALLEGRO_DISPLAY *pDisplay );

extern HB_EXPORT ALLEGRO_EVENT_QUEUE *hb_event_queue_Param( int iParam );
extern HB_EXPORT ALLEGRO_EVENT_QUEUE *hb_event_queue_ParamGet( int iParam );
extern HB_EXPORT ALLEGRO_EVENT_QUEUE *hb_event_queue_ItemGet( PHB_ITEM pItem );
extern HB_EXPORT PHB_ITEM             hb_event_queue_ItemPut( PHB_ITEM pItem, ALLEGRO_EVENT_QUEUE *pEvent_queue );
extern HB_EXPORT void                 hb_event_queue_ItemClear( PHB_ITEM pItem );
extern HB_EXPORT void                 hb_event_queue_Return( ALLEGRO_EVENT_QUEUE *pEvent_queue );

HB_EXTERN_END

#define HB_ERR_ARGS() ( hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS ) )

#endif /* end HB_NUKLEAR_ALLEGRO5_H_ */
