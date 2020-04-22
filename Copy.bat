
cd..
cd..

xcopy .\GameEngine\Include\*.h .\Engine\Include\ /s /d /y
xcopy .\GameEngine\Include\*.inl .\Engine\Include\ /s /d /y
xcopy .\GameEngine\Include\*.hpp .\Engine\Include\ /s /d /y
xcopy .\GameEngine\Bin\*.lib .\Engine\Bin\ /s /d /y
xcopy .\GameEngine\Bin\*.dll .\Engine\Bin\ /s /d /y
xcopy .\GameEngine\Bin\*.lib .\Client2D\Bin\ /s /d /y
xcopy .\GameEngine\Bin\*.dll .\Client2D\Bin\ /s /d /y
xcopy .\GameEngine\Bin\*.lib .\Editor2D\Bin\ /s /d /y
xcopy .\GameEngine\Bin\*.dll .\Editor2D\Bin\ /s /d /y
xcopy .\GameEngine\Bin\Resource\*.* .\Client2D\Bin\Resource\ /s /d /y
xcopy .\GameEngine\Bin\Resource\*.* .\Engine\Bin\Resource\ /s /d /y

xcopy .\GameEngine\Bin\Resource\*.* .\Editor2D\Bin\Resource\ /s /d /y



xcopy .\GameEngine\Bin\*.lib .\GameEditorTest\Bin\ /s /d /y
xcopy .\GameEngine\Bin\*.dll .\GameEditorTest\Bin\ /s /d /y
xcopy .\GameEngine\Bin\Resource\*.* .\GameEditorTest\Bin\Resource\ /s /d /y