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
//                                                                                                      .***,.   . .,/##%###(/.  ...,,.
/*  LAZARUS ENGINE */

//  TODO:
//  Update docs
//    - glm / glfw / glew need to be installed with homebrew
//    - OpenGL itself is available by default but is no longer supported by apple

#ifndef LAZARUS_GL_INCLUDES_H
#define LAZARUS_GL_INCLUDES_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION

    #ifndef __gl_h_
      #include <OpenGL/gl3.h>
    #endif
    #include <OpenGL/gl3ext.h>
#endif

#ifdef __linux__
    #include <GL/gl.h>
#endif

#endif