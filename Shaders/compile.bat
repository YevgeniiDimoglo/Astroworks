%~dp0glslc.exe %~dp0phong.vert -o phongVS.spv
%~dp0glslc.exe %~dp0phong.frag -o phongPS.spv
%~dp0glslc.exe %~dp0dissolve.frag -o dissolvePS.spv
%~dp0glslc.exe %~dp0sprite.vert -o spriteVS.spv
%~dp0glslc.exe %~dp0sprite.frag -o spritePS.spv
%~dp0glslc.exe %~dp0flat.vert -o flatVS.spv
%~dp0glslc.exe %~dp0flat.frag -o flatPS.spv
%~dp0glslc.exe %~dp0quad.vert -o quadVS.spv
%~dp0glslc.exe %~dp0quad.frag -o quadPS.spv
%~dp0glslc.exe %~dp0postEffect.vert -o postEffectVS.spv
%~dp0glslc.exe %~dp0postEffect.frag -o postEffectPS.spv
%~dp0glslc.exe %~dp0Luminance.vert -o LuminanceVS.spv
%~dp0glslc.exe %~dp0Luminance.frag -o LuminancePS.spv
%~dp0glslc.exe %~dp0Blur.vert -o BlurVS.spv
%~dp0glslc.exe %~dp0Blur.frag -o BlurPS.spv
%~dp0glslc.exe %~dp0pbrtexture.vert -o pbrtextureVS.spv
%~dp0glslc.exe %~dp0pbrtexture.frag -o pbrtexturePS.spv
%~dp0glslc.exe %~dp0shadowMapCaster.vert -o shadowMapCasterVS.spv
%~dp0glslc.exe %~dp0shadowMapCaster.frag -o shadowMapCasterPS.spv
%~dp0glslc.exe %~dp0water.vert -o waterVS.spv
%~dp0glslc.exe %~dp0water.frag -o waterPS.spv
%~dp0glslc.exe %~dp0billboard.vert -o billboardVS.spv
%~dp0glslc.exe %~dp0fireball.frag -o fireballPS.spv
%~dp0glslc.exe %~dp0OIT.vert -o OITVS.spv
%~dp0glslc.exe %~dp0OITColor.frag -o OITColorPS.spv
%~dp0glslc.exe %~dp0OITReveal.frag -o OITRevealPS.spv
%~dp0glslc.exe %~dp0OITResult.frag -o OITResult.spv
%~dp0glslc.exe %~dp0DemoOIT.vert -o DemoOITVS.spv
%~dp0glslc.exe %~dp0DemoOITColor.frag -o DemoOITColorPS.spv
%~dp0glslc.exe %~dp0DemoOITReveal.frag -o DemoOITRevealPS.spv
%~dp0glslc.exe %~dp0DemoOITResult.frag -o DemoOITResult.spv
%~dp0glslc.exe %~dp0skybox.vert -o skyboxPS.spv
%~dp0glslc.exe %~dp0skybox.frag -o skyboxVS.spv
pause