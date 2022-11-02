/*
 * Nuklear library: nuklear_glfw_gl2.c
 *
 * Copyright 2022 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hb_glfw_opengl2.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* GLFWwindow */
static HB_GARBAGE_FUNC( hb_glfw_Destructor )
{
   GLFWwindow **ppGLFW = ( GLFWwindow **) Cargo;

   if( *ppGLFW )
   {
      GLFWwindow *pGLFW = *ppGLFW;
      glfwDestroyWindow( pGLFW );
      *ppGLFW = NULL;
   }
}

static const HB_GC_FUNCS s_gcGLFWFuncs =
{
   hb_glfw_Destructor,
   hb_gcDummyMark
};

GLFWwindow *hb_window_Param( int iParam )
{
   GLFWwindow **ppGLFW = ( GLFWwindow **) hb_parptrGC( &s_gcGLFWFuncs, iParam );

   if( ppGLFW && *ppGLFW )
   {
      return *ppGLFW;
   }
   else
   {
      HB_ERR_ARGS();
      return NULL;
   }
}

GLFWwindow *hb_window_ParamGet( int iParam )
{
   GLFWwindow **ppGLFW = ( GLFWwindow **) hb_parptrGC( &s_gcGLFWFuncs, iParam );

   return ppGLFW ? *ppGLFW : NULL;
}

GLFWwindow *hb_window_ItemGet( PHB_ITEM pItem )
{
   GLFWwindow **ppGLFW = ( GLFWwindow **) hb_itemGetPtrGC( pItem, &s_gcGLFWFuncs );

   return ppGLFW ? *ppGLFW : NULL;
}

PHB_ITEM hb_window_ItemPut( PHB_ITEM pItem, GLFWwindow *pGLFW )
{
   GLFWwindow **ppGLFW = ( GLFWwindow **) hb_gcAllocate( sizeof( GLFWwindow *), &s_gcGLFWFuncs );
   *ppGLFW = pGLFW;
   return hb_itemPutPtrGC( pItem, ppGLFW );
}

void hb_window_ItemClear( PHB_ITEM pItem )
{
   GLFWwindow **ppGLFW = ( GLFWwindow **) hb_itemGetPtrGC( pItem, &s_gcGLFWFuncs );

   if( ppGLFW )
   {
      *ppGLFW = NULL;
   }
}

void hb_window_Return( GLFWwindow *pGLFW )
{
   if( pGLFW )
   {
      hb_window_ItemPut( hb_param( -1, HB_IT_ANY ), pGLFW );
   }
   else
   {
      hb_ret();
   }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

// GLFWAPI int glfwInit(void);
HB_FUNC( GLFWINIT )
{
   hb_retl( glfwInit() );
}

// GLFWAPI void glfwTerminate(void);
HB_FUNC( GLFWTERMINATE )
{
   glfwTerminate();
}

// GLFWAPI void glfwInitHint(int hint, int value);
HB_FUNC( GLFWINITHINT )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      glfwInitHint( hb_parni( 1 ), hb_parni( 2 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI void glfwInitAllocator(const GLFWallocator* allocator);

#if defined( VK_VERSION_1_0 )
// GLFWAPI void glfwInitVulkanLoader(PFN_vkGetInstanceProcAddr loader);
#endif

// GLFWAPI void glfwGetVersion(int* major, int* minor, int* rev);
HB_FUNC( GLFWGETVERSION )
{
   if( hb_param( 1, HB_IT_BYREF ) != NULL && hb_param( 2, HB_IT_BYREF ) != NULL && hb_param( 3, HB_IT_BYREF ) != NULL )
   {
      int major, minor, revision;
      glfwGetVersion( &major, &minor, &revision );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI const char* glfwGetVersionString(void);
HB_FUNC(  )
{
   hb_retc( glfwGetVersionString() );
}

// GLFWAPI int glfwGetError(const char** description);

// GLFWAPI GLFWerrorfun glfwSetErrorCallback(GLFWerrorfun callback);

// GLFWAPI int glfwGetPlatform(void);
// HB_FUNC( GLFWGETPLATFORM )
// {
//    hb_retni( glfwGetPlatform() );
// }

// GLFWAPI int glfwPlatformSupported(int platform);
// HB_FUNC( GLFWPLATFORMSUPPORTED )
// {
//    if( hb_param( 1, HB_IT_INTEGER ) != NULL )
//    {
//       hb_retni( glfwPlatformSupported( hb_parni( 1 ) ) );
//    }
//    else
//    {
//       HB_ERR_ARGS();
//    }
// }

// GLFWAPI GLFWmonitor** glfwGetMonitors(int* count);

// GLFWAPI GLFWmonitor* glfwGetPrimaryMonitor(void);

// GLFWAPI void glfwGetMonitorPos(GLFWmonitor* monitor, int* xpos, int* ypos);

// GLFWAPI void glfwGetMonitorWorkarea(GLFWmonitor* monitor, int* xpos, int* ypos, int* width, int* height);

// GLFWAPI void glfwGetMonitorPhysicalSize(GLFWmonitor* monitor, int* widthMM, int* heightMM);

// GLFWAPI void glfwGetMonitorContentScale(GLFWmonitor* monitor, float* xscale, float* yscale);

// GLFWAPI const char* glfwGetMonitorName(GLFWmonitor* monitor);

// GLFWAPI void glfwSetMonitorUserPointer(GLFWmonitor* monitor, void* pointer);

// GLFWAPI void* glfwGetMonitorUserPointer(GLFWmonitor* monitor);

// GLFWAPI GLFWmonitorfun glfwSetMonitorCallback(GLFWmonitorfun callback);

// GLFWAPI const GLFWvidmode* glfwGetVideoModes(GLFWmonitor* monitor, int* count);

// GLFWAPI const GLFWvidmode* glfwGetVideoMode(GLFWmonitor* monitor);

// GLFWAPI void glfwSetGamma(GLFWmonitor* monitor, float gamma);

// GLFWAPI const GLFWgammaramp* glfwGetGammaRamp(GLFWmonitor* monitor);

// GLFWAPI void glfwSetGammaRamp(GLFWmonitor* monitor, const GLFWgammaramp* ramp);

// GLFWAPI void glfwDefaultWindowHints(void);
HB_FUNC( GLFWDEFAULTWINDOWHINTS )
{
   glfwDefaultWindowHints();
}


// GLFWAPI void glfwWindowHint(int hint, int value);
HB_FUNC( GLFWWINDOWHINT )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      glfwWindowHint( hb_parni( 1 ), hb_parni( 2 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI void glfwWindowHintString(int hint, const char* value);
HB_FUNC( GLFWWINDOWHINTSTRING )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL && hb_param( 2, HB_IT_STRING ) != NULL )
   {
      glfwWindowHintString( hb_parni( 1 ), hb_parc( 2 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
HB_FUNC( GLFWCREATEWINDOW )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL && hb_param( 3, HB_IT_STRING ) != NULL )
   {
      hb_window_Return( glfwCreateWindow( hb_parni( 1 ), hb_parni( 2 ), hb_parc( 3 ), NULL, NULL ) );
   }
   else
   {
      HB_ERR_ARGS();
   }

}

// GLFWAPI void glfwDestroyWindow(GLFWwindow* window);
HB_FUNC( GLFWDESTROYWINDOW )
{
   GLFWwindow **ppGLFW = ( GLFWwindow **) hb_parptrGC( &s_gcGLFWFuncs, 1 );

   if( ppGLFW && *ppGLFW )
   {
      glfwDestroyWindow( *ppGLFW );
      *ppGLFW = NULL;
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI int glfwWindowShouldClose(GLFWwindow* window);
HB_FUNC( GLFWWINDOWSHOULDCLOSE )
{
   GLFWwindow *window = hb_window_Param( 1 );

   if( window )
   {
      hb_retl( glfwWindowShouldClose( window ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI void glfwSetWindowShouldClose(GLFWwindow* window, int value);
HB_FUNC( GLFWSETWINDOWSHOULDCLOSE )
{
   GLFWwindow *window = hb_window_Param( 1 );

   if( window && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      glfwSetWindowShouldClose( window, hb_parni( 2 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI void glfwSetWindowTitle(GLFWwindow* window, const char* title);

// GLFWAPI void glfwSetWindowIcon(GLFWwindow* window, int count, const GLFWimage* images);

// GLFWAPI void glfwGetWindowPos(GLFWwindow* window, int* xpos, int* ypos);
HB_FUNC( GLFWGETWINDOWPOS )
{
   GLFWwindow *window = hb_window_Param( 1 );

   if( window && hb_param( 2, HB_IT_BYREF ) != NULL && hb_param( 3, HB_IT_BYREF ) != NULL )
   {
      int width, height;
      glfwGetWindowPos( window, &width, &height );
      hb_storni( width, 2 );
      hb_storni( height, 3 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI void glfwSetWindowPos(GLFWwindow* window, int xpos, int ypos);

// GLFWAPI void glfwGetWindowSize(GLFWwindow* window, int* width, int* height);
HB_FUNC( GLFWGETWINDOWSIZE )
{
   GLFWwindow *window = hb_window_Param( 1 );

   if( window && hb_param( 2, HB_IT_BYREF ) != NULL && hb_param( 3, HB_IT_BYREF ) != NULL )
   {
      int width, height;
      glfwGetWindowSize( window, &width, &height );
      hb_storni( width, 2 );
      hb_storni( height, 3 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI void glfwSetWindowSizeLimits(GLFWwindow* window, int minwidth, int minheight, int maxwidth, int maxheight);

// GLFWAPI void glfwSetWindowAspectRatio(GLFWwindow* window, int numer, int denom);

// GLFWAPI void glfwSetWindowSize(GLFWwindow* window, int width, int height);

// GLFWAPI void glfwGetFramebufferSize(GLFWwindow* window, int* width, int* height);
HB_FUNC( GLFWGETFRAMEBUFFERSIZE )
{
   GLFWwindow *window = hb_window_Param( 1 );

   if( window && hb_param( 2, HB_IT_BYREF ) != NULL && hb_param( 3, HB_IT_BYREF ) != NULL )
   {
      int width, height;
      glfwGetFramebufferSize( window, &width, &height );
      hb_storni( width, 2 );
      hb_storni( height, 3 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI void glfwGetWindowFrameSize(GLFWwindow* window, int* left, int* top, int* right, int* bottom);

// GLFWAPI void glfwGetWindowContentScale(GLFWwindow* window, float* xscale, float* yscale);

// GLFWAPI float glfwGetWindowOpacity(GLFWwindow* window);

// GLFWAPI void glfwSetWindowOpacity(GLFWwindow* window, float opacity);

// GLFWAPI void glfwIconifyWindow(GLFWwindow* window);

// GLFWAPI void glfwRestoreWindow(GLFWwindow* window);

// GLFWAPI void glfwMaximizeWindow(GLFWwindow* window);

// GLFWAPI void glfwShowWindow(GLFWwindow* window);

// GLFWAPI void glfwHideWindow(GLFWwindow* window);

// GLFWAPI void glfwFocusWindow(GLFWwindow* window);

// GLFWAPI void glfwRequestWindowAttention(GLFWwindow* window);

// GLFWAPI GLFWmonitor* glfwGetWindowMonitor(GLFWwindow* window);

// GLFWAPI void glfwSetWindowMonitor(GLFWwindow* window, GLFWmonitor* monitor, int xpos, int ypos, int width, int height, int refreshRate);

// GLFWAPI int glfwGetWindowAttrib(GLFWwindow* window, int attrib);

// GLFWAPI void glfwSetWindowAttrib(GLFWwindow* window, int attrib, int value);

// GLFWAPI void glfwSetWindowUserPointer(GLFWwindow* window, void* pointer);

// GLFWAPI void* glfwGetWindowUserPointer(GLFWwindow* window);

// GLFWAPI GLFWwindowposfun glfwSetWindowPosCallback(GLFWwindow* window, GLFWwindowposfun callback);

// GLFWAPI GLFWwindowsizefun glfwSetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun callback);

// GLFWAPI GLFWwindowclosefun glfwSetWindowCloseCallback(GLFWwindow* window, GLFWwindowclosefun callback);

// GLFWAPI GLFWwindowrefreshfun glfwSetWindowRefreshCallback(GLFWwindow* window, GLFWwindowrefreshfun callback);

// GLFWAPI GLFWwindowfocusfun glfwSetWindowFocusCallback(GLFWwindow* window, GLFWwindowfocusfun callback);

// GLFWAPI GLFWwindowiconifyfun glfwSetWindowIconifyCallback(GLFWwindow* window, GLFWwindowiconifyfun callback);

// GLFWAPI GLFWwindowmaximizefun glfwSetWindowMaximizeCallback(GLFWwindow* window, GLFWwindowmaximizefun callback);

// GLFWAPI GLFWframebuffersizefun glfwSetFramebufferSizeCallback(GLFWwindow* window, GLFWframebuffersizefun callback);

// GLFWAPI GLFWwindowcontentscalefun glfwSetWindowContentScaleCallback(GLFWwindow* window, GLFWwindowcontentscalefun callback);

// GLFWAPI void glfwPollEvents(void);
HB_FUNC( GLFWPOLLEVENTS )
{
   glfwPollEvents();
}

// GLFWAPI void glfwWaitEvents(void);

// GLFWAPI void glfwWaitEventsTimeout(double timeout);

// GLFWAPI void glfwPostEmptyEvent(void);

// GLFWAPI int glfwGetInputMode(GLFWwindow* window, int mode);

// GLFWAPI void glfwSetInputMode(GLFWwindow* window, int mode, int value);

// GLFWAPI int glfwRawMouseMotionSupported(void);

// GLFWAPI const char* glfwGetKeyName(int key, int scancode);

// GLFWAPI int glfwGetKeyScancode(int key);

// GLFWAPI int glfwGetKey(GLFWwindow* window, int key);

// GLFWAPI int glfwGetMouseButton(GLFWwindow* window, int button);

// GLFWAPI void glfwGetCursorPos(GLFWwindow* window, double* xpos, double* ypos);

// GLFWAPI void glfwSetCursorPos(GLFWwindow* window, double xpos, double ypos);

// GLFWAPI GLFWcursor* glfwCreateCursor(const GLFWimage* image, int xhot, int yhot);

// GLFWAPI GLFWcursor* glfwCreateStandardCursor(int shape);

// GLFWAPI void glfwDestroyCursor(GLFWcursor* cursor);

// GLFWAPI void glfwSetCursor(GLFWwindow* window, GLFWcursor* cursor);

// GLFWAPI GLFWkeyfun glfwSetKeyCallback(GLFWwindow* window, GLFWkeyfun callback);

// GLFWAPI GLFWcharfun glfwSetCharCallback(GLFWwindow* window, GLFWcharfun callback);

// GLFWAPI GLFWcharmodsfun glfwSetCharModsCallback(GLFWwindow* window, GLFWcharmodsfun callback);

// GLFWAPI GLFWmousebuttonfun glfwSetMouseButtonCallback(GLFWwindow* window, GLFWmousebuttonfun callback);

// GLFWAPI GLFWcursorposfun glfwSetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback);

// GLFWAPI GLFWcursorenterfun glfwSetCursorEnterCallback(GLFWwindow* window, GLFWcursorenterfun callback);

// GLFWAPI GLFWscrollfun glfwSetScrollCallback(GLFWwindow* window, GLFWscrollfun callback);

// GLFWAPI GLFWdropfun glfwSetDropCallback(GLFWwindow* window, GLFWdropfun callback);

// GLFWAPI int glfwJoystickPresent(int jid);

// GLFWAPI const float* glfwGetJoystickAxes(int jid, int* count);

// GLFWAPI const unsigned char* glfwGetJoystickButtons(int jid, int* count);

// GLFWAPI const unsigned char* glfwGetJoystickHats(int jid, int* count);

// GLFWAPI const char* glfwGetJoystickName(int jid);

// GLFWAPI const char* glfwGetJoystickGUID(int jid);

// GLFWAPI void glfwSetJoystickUserPointer(int jid, void* pointer);

// GLFWAPI void* glfwGetJoystickUserPointer(int jid);

// GLFWAPI int glfwJoystickIsGamepad(int jid);

// GLFWAPI GLFWjoystickfun glfwSetJoystickCallback(GLFWjoystickfun callback);

// GLFWAPI int glfwUpdateGamepadMappings(const char* string);

// GLFWAPI const char* glfwGetGamepadName(int jid);

// GLFWAPI int glfwGetGamepadState(int jid, GLFWgamepadstate* state);

// GLFWAPI void glfwSetClipboardString(GLFWwindow* window, const char* string);

// GLFWAPI const char* glfwGetClipboardString(GLFWwindow* window);

// GLFWAPI double glfwGetTime(void);

// GLFWAPI void glfwSetTime(double time);

// GLFWAPI uint64_t glfwGetTimerValue(void);

// GLFWAPI uint64_t glfwGetTimerFrequency(void);

// GLFWAPI void glfwMakeContextCurrent(GLFWwindow* window);
HB_FUNC( GLFWMAKECONTEXTCURRENT )
{
   GLFWwindow *window = hb_window_Param( 1 );

   if( window )
   {
      glfwMakeContextCurrent( window );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI GLFWwindow* glfwGetCurrentContext(void);

// GLFWAPI void glfwSwapBuffers(GLFWwindow* window);
HB_FUNC( GLFWSWAPBUFFERS )
{
   GLFWwindow *window = hb_window_Param( 1 );

   if( window )
   {
      glfwSwapBuffers( window );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI void glfwSwapInterval(int interval);
HB_FUNC( GLFWSWAPINTERVAL )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      glfwSwapInterval( hb_parni( 1 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// GLFWAPI int glfwExtensionSupported(const char* extension);

// GLFWAPI GLFWglproc glfwGetProcAddress(const char* procname);

// GLFWAPI int glfwVulkanSupported(void);

// GLFWAPI const char** glfwGetRequiredInstanceExtensions(uint32_t* count);

#if defined( VK_VERSION_1_0 )
// GLFWAPI GLFWvkproc glfwGetInstanceProcAddress(VkInstance instance, const char* procname);
// GLFWAPI int glfwGetPhysicalDevicePresentationSupport(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily);
// GLFWAPI VkResult glfwCreateWindowSurface(VkInstance instance, GLFWwindow* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);
#endif

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* nuklear_glfw_gl2 */

//NK_API struct nk_context* nk_glfw3_init(GLFWwindow *win, enum nk_glfw_init_state);
HB_FUNC( NK_GLFW3_INIT )
{
   GLFWwindow *window = hb_window_Param( 1 );

   if( window && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retptr( nk_glfw3_init( window, hb_parni( 2 ) ) );
      {
         struct nk_font_atlas *atlas;
         nk_glfw3_font_stash_begin( &atlas );
         nk_glfw3_font_stash_end();
      }
   }
   else
   {
      HB_ERR_ARGS();
   }
}

//NK_API void nk_glfw3_font_stash_begin(struct nk_font_atlas **atlas);
// HB_FUNC( NK_GLFW3_FONT_STASH_BEGIN )
// {
//    if( hb_param( 1, HB_IT_BYREF ) != NULL )
//    {
//       struct nk_font_atlas *atlas;
//       nk_glfw3_font_stash_begin( &atlas );
//    }
//    else
//    {
//       HB_ERR_ARGS();
//    }
// }

//NK_API void nk_glfw3_font_stash_end(void);

//NK_API void nk_glfw3_new_frame(void);
HB_FUNC( NK_GLFW3_NEW_FRAME )
{
   nk_glfw3_new_frame();
}

//NK_API void nk_glfw3_render(enum nk_anti_aliasing);
HB_FUNC( NK_GLFW3_RENDER )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      nk_glfw3_render( hb_parni( 1 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

//NK_API void nk_glfw3_shutdown(void);
HB_FUNC( NK_GLFW3_SHUTDOWN )
{
   nk_glfw3_shutdown();
}

//NK_API void nk_glfw3_char_callback(GLFWwindow *win, unsigned int codepoint);
//NK_API void nk_gflw3_scroll_callback(GLFWwindow *win, double xoff, double yoff);

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* GL */

// void glClear( GLbitfield mask )
HB_FUNC( GLCLEAR )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      glClear( hb_parni( 1 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void glClearColor( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
HB_FUNC( GLCLEARCOLOR )
{
   if( hb_param( 1, HB_IT_DOUBLE ) != NULL && hb_param( 2, HB_IT_DOUBLE ) != NULL && hb_param( 3, HB_IT_DOUBLE ) != NULL && hb_param( 4, HB_IT_DOUBLE ) != NULL )
   {
      glClearColor( ( float ) hb_parnd( 1 ), ( float ) hb_parnd( 2 ), ( float ) hb_parnd( 3 ), ( float ) hb_parnd( 4 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void glViewport( GLint x, GLint y, GLsizei width, GLsizei height )
HB_FUNC(GLVIEWPORT)
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL && hb_param( 2, HB_IT_INTEGER ) != NULL && hb_param( 3, HB_IT_INTEGER ) != NULL && hb_param( 4, HB_IT_INTEGER ) != NULL )
   {
      glViewport( hb_parni( 1 ), hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}
