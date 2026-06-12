@echo off
setlocal enabledelayedexpansion

echo ========================================
echo   Qt Deployment Script (windeployqt)
echo ========================================
echo.

:: ========== НАСТРОЙКИ (ИЗМЕНИТЕ ПУТИ ПОД СЕБЯ) ==========
:: Путь к папке bin вашего Qt (где лежит windeployqt.exe)
set QTDIR=C:\Qt\6.10.2\mingw_64\bin\

:: Путь к папке с вашим .exe файлом (релизная сборка)
set APP_DIR=D:\1_academy_top\5_sem\Diplom\Ardis\Ardis\build\AppDeploy\

:: Имя вашего .exe файла
set APP_NAME=Ardis.exe

:: Дополнительные параметры (опционально)
set ADD_ARGS=--release --no-translations
:: ========================================================

:: Проверяем существование windeployqt
if not exist "%QTDIR%\windeployqt.exe" (
    echo [ERROR] windeployqt.exe not found in "%QTDIR%"
    echo Please check your Qt path.
    pause
    exit /b 1
)

:: Проверяем существование exe файла
if not exist "%APP_DIR%\%APP_NAME%" (
    echo [ERROR] %APP_NAME% not found in "%APP_DIR%"
    echo Please build the release version first.
    pause
    exit /b 1
)

:: Переходим в папку с exe файлом
cd /d "%APP_DIR%"

echo [INFO] Deploying %APP_NAME% from %APP_DIR%
echo [INFO] Using Qt: %QTDIR%
echo.

:: Запускаем windeployqt
"%QTDIR%\windeployqt.exe" %ADD_ARGS% "%APP_NAME%"

:: Проверяем результат
if %errorlevel% equ 0 (
    echo.
    echo ========================================
    echo   DEPLOYMENT SUCCESSFUL!
    echo ========================================
    echo.
    echo The application dependencies have been copied.
    echo You can now distribute the contents of:
    echo %APP_DIR%
) else (
    echo.
    echo [ERROR] Deployment failed with error code: %errorlevel%
)

echo.
pause