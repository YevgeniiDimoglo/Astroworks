%~dp0glslc.exe %~dp0phong.vert -o phongVS.spv
%~dp0glslc.exe %~dp0phong.frag -o phongPS.spv
%~dp0glslc.exe %~dp0dissolve.frag -o dissolvePS.spv
%~dp0glslc.exe %~dp0sprite.vert -o spriteVS.spv
%~dp0glslc.exe %~dp0sprite.frag -o spritePS.spv
%~dp0glslc.exe %~dp0flat.vert -o flatVS.spv
%~dp0glslc.exe %~dp0flat.frag -o flatPS.spv
%~dp0glslc.exe %~dp0quad.vert -o quadVS.spv
%~dp0glslc.exe %~dp0quad.frag -o quadPS.spv
%~dp0glslc.exe %~dp0pbrtexture.vert -o pbrtextureVS.spv
%~dp0glslc.exe %~dp0pbrtexture.frag -o pbrtexturePS.spv
%~dp0glslc.exe %~dp0shadowMapCaster.vert -o shadowMapCasterVS.spv
%~dp0glslc.exe %~dp0shadowMapCaster.frag -o shadowMapCasterPS.spv
%~dp0glslc.exe %~dp0water.vert -o waterVS.spv
%~dp0glslc.exe %~dp0water.frag -o waterPS.spv
pause