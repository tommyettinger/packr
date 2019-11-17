call fips set config win32-vstudio-release
call fips clean
call fips build
call copy ..\fips-deploy\packr\win32-vstudio-release\packr.exe ..\..\resources\packr-windows.exe
