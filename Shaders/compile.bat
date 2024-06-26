%~dp0glslc.exe %~dp0phong.vert -o phongVS.spv
%~dp0glslc.exe %~dp0phong.frag -o phongPS.spv
%~dp0glslc.exe %~dp0dissolve.frag -o dissolvePS.spv
%~dp0glslc.exe %~dp0sprite.vert -o spriteVS.spv
%~dp0glslc.exe %~dp0sprite.frag -o spritePS.spv
%~dp0glslc.exe %~dp0flat.vert -o flatVS.spv
%~dp0glslc.exe %~dp0flat.frag -o flatPS.spv
%~dp0glslc.exe %~dp0quad.vert -o quadVS.spv
%~dp0glslc.exe %~dp0quad.frag -o quadPS.spv
%~dp0glslc.exe %~dp0quad2.vert -o quad2VS.spv
%~dp0glslc.exe %~dp0quad2.frag -o quad2PS.spv
%~dp0glslc.exe %~dp0postEffect.vert -o postEffectVS.spv
%~dp0glslc.exe %~dp0postEffect.frag -o postEffectPS.spv
%~dp0glslc.exe %~dp0Luminance.vert -o LuminanceVS.spv
%~dp0glslc.exe %~dp0Luminance.frag -o LuminancePS.spv
%~dp0glslc.exe %~dp0Blur.vert -o BlurVS.spv
%~dp0glslc.exe %~dp0Blur.frag -o BlurPS.spv
%~dp0glslc.exe %~dp0PBR.vert -o PBRVS.spv
%~dp0glslc.exe %~dp0PBROnly.frag -o PBROnlyPS.spv
%~dp0glslc.exe %~dp0PBRIBL.frag -o PBRIBLPS.spv
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
%~dp0glslc.exe %~dp0skybox.vert -o skyboxVS.spv
%~dp0glslc.exe %~dp0skybox.frag -o skyboxPS.spv
%~dp0glslc.exe %~dp0computeParticle.vert -o computeParticleVS.spv
%~dp0glslc.exe %~dp0computeParticle.frag -o computeParticlePS.spv
%~dp0glslc.exe %~dp0computeParticle.comp -o computeParticleCS.spv
%~dp0glslc.exe %~dp0miss.rmiss --target-env=vulkan1.3 -o  miss.rmiss.spv
%~dp0glslc.exe %~dp0raygen.rgen  --target-env=vulkan1.3 -o raygen.rgen.spv
%~dp0glslc.exe %~dp0closesthit.rchit --target-env=vulkan1.3 -o closesthit.rchit.spv
pause