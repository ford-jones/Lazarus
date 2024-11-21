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
#include "lz_sound_manager.h"
#include "lz_text_manager.h"

#ifndef LAZARUS_H
#define LAZARUS_H

namespace Lazarus
{
    using ::TextManager;
    using ::GlobalsManager;
    using ::WindowManager;
    using ::EventManager;
    using ::Mesh;
    using ::Transform;
    using ::Shader;
    using ::Light;
    using ::Camera;
    using ::FpsCounter;
    using ::FileReader;
    using ::SoundManager;
}

#endif
