package com.portum.opengl.sdk;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;

/**
 * Facade for Portum ad platform.
 * Single point which provide control on ads
 */
public final class PortumGLES20 {

    public static final long NO_AD = 0;

    /**
     * To correctly work with portum SDK we need to know egl context creation
     * @param glView
     */
    public static void glSurfaceViewPrepare(GLSurfaceView glView);

    /**
     * To correctly work with portum SDK we need to know egl context creation
     * @param glView
     * @param eglContextFactory if you are use custom GLSurfaceView.EGLContextFactory provide it
     * @param eglSurfaceFactory if you are use custom GLSurfaceView.EGLWindowSurfaceFactory provide it
     */
    public static void glSurfaceViewPrepare(GLSurfaceView glView,
                                            GLSurfaceView.EGLContextFactory eglContextFactory,
                                            GLSurfaceView.EGLWindowSurfaceFactory eglSurfaceFactory);

    /**
     * Init library
     *
     * @threading any
     *
     * @param context
     */
    public static void glInit(final Context context);

    /**
     * @brief setup camera params, this method should be called after init and each time when camera params changes
     *
     * @threading any
     *
     * @param mvpMatrix MVP (Model View Projection) camera matrix
     *
     * @return true - success, false - failure
     */
    public static native boolean glUpdateMVP(float[] mvpMatrix);

    /**
     * @brief request ad for placement Id, will return instance of `portum_ogl_ad` which will have texture
     * (texture_id) and array of vertices (vao_id) which will be used to show it. By default ad mesh will
     * be in zero point, then developer will be able to resize/translate the ad how it wanna to
     *
     * @threading any
     *
     * @param adUnitId Ad Unit Id
     *
     * @return portum_ogl_ad name
     */
    public static native long glGenAd(String adUnitId);

    /**
     * @brief used for case if vertices place of ad has been changed (for quad surface only)
     *
     * @threading GL thread only
     *
     * @param ad ad name
     * @param vertices new vertices
     *
     * @return success
     */
    public static native boolean glBindAdVertices(long ad, float vertices[], int components);

    /**
     * @brief used for case if vertices place of ad has been changed
     *
     * @param ad ad name
     * @param vertices new vertices
     *
     * @return success
     */
    public static native boolean glBindAdVerticesWithTexcoords(long ad, float vertices[], int components, float texcoords[]);

    /**
     * @brief force to refresh ad banner
     *
     * @threading GL thread only
     *
     * @param ad ad name
     *
     * @return success or not
     */
    public static native boolean glRefreshAd(long ad);

    /**
     * @brief used for change ad sufrace culling, by default GL_BACK enabled
     *
     * @threading GL thread only
     *
     * @param ad ad name
     * @param mode see
     * https://www.khronos.org/opengles/sdk/docs/man/xhtml/glCullFace.xml param mode
     *
     * @return success or not
     */
    public static native boolean glSetAdCullface(long ad, int mode);
	
	/**
     * @brief used for change ad drawing mode (glDrawArrays)
     *
     * @threading GL thread only
     *
     * @param ad ad name
     * @param mode see
     * https://www.khronos.org/opengles/sdk/docs/man3/html/glDrawArrays.xhtml param mode
     *
     * @return success or not
     */
    public static native boolean glSetAdDrawMode(long ad, int mode);

    /**
     * @brief easy flag to enable/disable SDK, may be useful if you will need disable ads for 'premium users'
     * By default SDK enabled after initializing
     *
     * @threading any
     *
     * @param enable true to enable SDK, false to disable SDK
     */
    public static native void glEnable(boolean enable);
	
	/**
     * @brief easy method to show/hide certain Ad
     * By default SDK enabled after initializing
     *
     * @threading any
     *
     * @param show true to make specific Ad visible, all Ads are visible by default
     */
    public static native void glShowAd(long ad, boolean show);

    /**
     * @brief should be called on any step before buffer swap
     *
     * @threading GL thread only
     */
    public static native void glDrawAds(int attributeCoordinates, int attributeTextureCoordinates, int uniformTexture);

    /**
     * @brief call this if app minimized for proper statistic calculation
     *
     * @threading GL thread only
     */
    public static native void glPause();

    /**
     * @brief call this when app opened after minimization again
     *
     * @threading GL thread only
     */
    public static native void glResume();

    /**
     * @brief elease resources related to particular ad
     *
     * @threading GL thread only
     *
     * @param ad name
     * @return true - success, false - failure
     */
    public static native boolean glDeleteAd(long ad);

    /**
     * @brief last step before to finish work with SDK
     *
     * @threading GL thread only
     * 
     * @return true - success, false - failure
     */
    public static native boolean glFinalize();
}
