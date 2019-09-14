call fips set config win32-vs2017-release
call fips clean
call fips build
call copy ..\fips-deploy\packr\win32-vs2017-release\packr.exe ..\..\resources\packr-windows.exe

