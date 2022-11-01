/*
 *
 */

#ifndef HB_NUKLEAR_XLIB_H_
#define HB_NUKLEAR_XLIB_H_

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

#include "../nuklear.h"
#include "nuklear_xlib.h"

#define HB_ERR_ARGS() ( hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS ) )

#endif /* end HB_NUKLEAR_XLIB_H_ */
