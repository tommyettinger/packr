call fips set config win64-vstudio-release
call fips clean
call fips build
call copy ..\fips-deploy\packr\win64-vstudio-release\packr.exe ..\..\resources\packr-windows-x64.exe
