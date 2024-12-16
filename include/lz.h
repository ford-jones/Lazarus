//              .,                                                                                                          .(*      ,*,                
//                ((.     (.    ,                                                                          */*  ,%##%%%%%%%%%%%%%%%#(*           .      
//         .//**/#%%%%%%%%%%%%%%#*   .,                                                             ,**   .(%%%%%%#(******,***,/#%%%%%%%%###(/,         
//             #%%%#*.#%/***,,..,*(%(.    ,,                                                     *     /#%##/*****,,,,,,,,,.,...,,#%,  .#%#.            
//    .,     *%&#/   %#**,,*..,....,.*#,     ..                                               *     ,%#%#/*,,*,*,,,,,.,.,,.,...,...((     /#(//*/**.    
//           (%#    *#*...,.,,..........*/      ,                                          .      *#%(#(**,,,,,,,,..,..,..,,........(.     *#(          
//           *#     *(......,.............(#      ,                                       .     ,((, ##,,,.....,.................. ./       **  .,.     
//            *     ./........ ...........*#*,                                          ,      ,(,  ./*,,,..,,.................  .. *                   
//                   /, ........    ... ../(  *.                                              ,*     /,...,,.,,.....   ............**                   
//                    *... .............  /    ,                                             *,      ,*,,............  ,....     ...                    
//                     *.   ..... .... ..*                                                  .*        *...................   .  ...                     
//               *       ... ......... ,.                                                   ,          ... ..........  ...     ..       ,               
//                ((        .,.,.. ...                                                                   .  . .. .  .  ... .  ..      //                
//              ,/(#%#*                                                                                     .....  ... ......       .#*                 
//                 /((##%#(*                                                                                      .......        ,(#(*,                 
//               (.           .,,,,,                                                                                        .*#%%(                      
//                                        
/*  LAZARUS ENGINE */

#ifndef LAZARUS_GL_INCLUDES_H
    #include "lz_gl_includes.h"
#endif

#include "lz_globals_manager.h"
#include "lz_window_manager.h"
#include "lz_event_manager.h"
#include "lz_mesh.h"
#include "lz_transforms.h"
#include "lz_shader.h"
#include "lz_light.h"
#include "lz_camera.h"
#include "lz_fps_counter.h"
#include "lz_file_reader.h"
#include "lz_audio_manager.h"
#include "lz_text_manager.h"
#include "lz_world_fx.h"

#ifndef LAZARUS_H
#define LAZARUS_H

namespace Lazarus
{
    using ::WorldFX;
    using ::TextManager;
    using ::GlobalsManager;
    using ::WindowManager;
    using ::EventManager;
    using ::MeshManager;
    using ::Transform;
    using ::Shader;
    using ::LightManager;
    using ::CameraManager;
    using ::FpsCounter;
    using ::FileReader;
    using ::AudioManager;
}

#endif
