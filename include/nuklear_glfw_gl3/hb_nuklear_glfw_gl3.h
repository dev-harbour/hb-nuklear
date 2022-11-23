/*
 *
 */

#ifndef HB_NUKLEAR_GLFW_GL3_H_
#define HB_NUKLEAR_GLFW_GL3_H_

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

#include <GLFW/glfw3.h>

#include "../nuklear.h"
#include "nuklear_glfw_gl3.h"

HB_EXTERN_BEGIN

extern HB_EXPORT GLFWwindow *hb_window_Param( int iParam );
extern HB_EXPORT GLFWwindow *hb_window_ParamGet( int iParam );
extern HB_EXPORT GLFWwindow *hb_window_ItemGet( PHB_ITEM pItem );
extern HB_EXPORT PHB_ITEM    hb_window_ItemPut( PHB_ITEM pItem, GLFWwindow *pGLFW );
extern HB_EXPORT void        hb_window_ItemClear( PHB_ITEM pItem );
extern HB_EXPORT void        hb_window_Return( GLFWwindow *pGLFW );

HB_EXTERN_END

#define HB_ERR_ARGS() ( hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS ) )

#endif /* end HB_NUKLEAR_GLFW_GL3_H_ */
