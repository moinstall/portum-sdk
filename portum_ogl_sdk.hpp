//  Copyright © 2016 Honeycomb. All rights reserved.
#pragma once

#include <array>
#include <string>
#include <vector>

#ifdef __ANDROID__
#include <GLES2/gl2.h>
#else
#include <GL/glew.h>
#endif

#if defined( _WIN32 ) || defined( _WIN64 )
#define API_EXPORT
#else
#define API_EXPORT __attribute__( ( visibility( "default" ) ) )
#endif

namespace portum
{
namespace ogl
{

struct ad;

struct oglconfig {
    portum::config core_config = portum::config();
    texture_assets textureassets;
};

/**
 * @brief SDK initialization called at once at app start
 *
 * @threading any
 *
 * @return true - success, false - failure
 */
API_EXPORT bool init( const oglconfig& _config );

/**
 * @brief setup camera params, this method should be called after init and each
 * time when camera params changes
 *
 * @threading any
 *
 * @param mvpCamera MVP (Model View Projection) camera matrix
 * @param cameraPostion camera absolutute postion
 *
 * @return true - success, false - failure
 */
API_EXPORT bool update_camera( float mvpCamera[16] );

/**
 * @brief request ad for placement Id, will return instance of `portum_ogl_ad`
 * which will have texture
 * (texture_id) and array of vertices (vao_id) which will be used to show it. By
 * default ad mesh will
 * be in zero point, then developer will be able to resize/translate the ad how
 * it wanna to
 *
 * @threading GL thread only
 *
 * @param adUnitId Ad Unit Id
 *
 * @return portum_ogl_ad structure
 */
API_EXPORT ad* request_ad( std::string adUnitId );

/**
 * @brief request ad for placement Id, will return instance of `portum_ogl_ad`
 * which will have texture
 * (texture_id) and array of vertices (vao_id) which will be used to show it. By
 * default ad mesh will
 * be in zero point, then developer will be able to resize/translate the ad how
 * it wanna to
 *
 * @threading any
 *
 * @param adUnitId Ad Unit Id
 *
 * @return portum_ogl_ad structure
 */
API_EXPORT ad* request_ad_asynch( std::string adUnitId );

/**
 * @brief used for case if vertices place of ad has been changed, only quad mesh
 * supported (4 vertices)
 *
 * @threading GL thread only
 *
 * @param ad opaque porinter to ad structure
 * @param vertices new vertices
 * @param component_per_vertex how many coords in array related to single vertex
 * @return success or not
 */
API_EXPORT bool bind_ad_vertices( ad* ad, std::vector<float> vertixes,
                                  size_t component_per_vertex );

/**
 * @brief used for case if vertices place of ad has been changed, unlimited
 * vertices supported
 *
 * @threading GL thread only
 *
 * @param ad opaque porinter to ad structure
 * @param vertices new vertices
 * @param component_per_vertex how many coords in array related to single vertex
 * @return success or not
 */
API_EXPORT bool bind_ad_vertices_with_texcoords( ad* ad,
                                                 std::vector<float> vertixes,
                                                 size_t component_per_vertex,
                                                 std::vector<float> texcoords );

/**
 * @brief used for change ad sufrace culling, by default GL_BACK enabled
 *
 * @threading GL thread only
 *
 * @param ad opaque porinter to ad structure
 * @param mode see
 * https://www.khronos.org/opengles/sdk/docs/man/xhtml/glCullFace.xml param mode
 *
 * @return success or not
 */
API_EXPORT bool set_ad_cull_face( ad* ad, GLenum mode );

/**
 * @brief used for change ad drawing mode for glDrawArrays
 *
 * @threading GL thread only
 *
 * @param ad opaque porinter to ad structure
 * @param mode see
 * https://www.opengl.org/sdk/docs/man/html/glDrawArrays.xhtml param mode
 *
 * @return success or not
 */
API_EXPORT bool set_ad_draw_mode( ad* ad, GLenum mode );

/**
 * @brief force to refresh ad banner
 *
 * @threading any
 *
 * @param ad opaque porinter to ad structure
 *
 * @return success or not
 */
API_EXPORT bool refresh_ad( ad* ad );

/**
 * @brief refresh ad
 *
 * @threading GL thread only
 *
 * @param ad opaque porinter to ad structure
 * @param interval time between ad refresh
 *
 * @return success or not
 */
API_EXPORT bool set_ad_refresh_interval( ad* ad, uint32_t interval );

/**
 * @brief easy flag to enable/disable SDK, may be useful if you will need
 * disable ads for 'premium users'
 * By default SDK enabled after initialyzing
 *
 * @threading any
 *
 * @param enable true to enable SDK, false to disable SDK
 */
API_EXPORT void enable( bool enable );

/**
 * @brief allows visibility control for certain ad, this may be useful when several
 * OpenGL surfaces should display own set of ads, other applications requires hide or show ads
 * By default every requested ad is visible
 *
 * @threading any
 *
 * @param ad - ad pointer ( returned during request_ad/request_adasynch )
 * @param enable - true to show ad and vice versa
 */
API_EXPORT void show_ad( ad* ad, bool enable );

/**
 * @brief should be called on any step before buffer swap
 *
 * @threading GL thread only
 */
API_EXPORT void on_draw( GLint attribute_coord3d, GLint attribute_texcoord,
                         GLint uniform_texture );

/**
 * @brief call this if app minimized for proper statistic calculation
 *
 * @threading GL thread only
 */
API_EXPORT void pause();

/**
 * @brief call this when app opened after minimization again / but when GL
 * context already recreated
 *
 * @threading GL thread only
 */
API_EXPORT void resume();

/**
 * @brief elease resources related to particular ad
 *
 * @threading GL thread only
 *
 * @param ad which you wanna to release
 * @return true - success, false - failure
 */
API_EXPORT bool release_ad( ad* ad );

/**
 * @brief last step before to finish work with SDK
 *
 * @threading GL thread only
 *
 * @return true - success, false - failure
 */
API_EXPORT bool finalize();
}
} // end namespaces
