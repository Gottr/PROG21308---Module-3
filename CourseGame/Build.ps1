param([Parameter(Mandatory=$true)][string]$EngineRoot)
$ErrorActionPreference='Stop'
$project=Join-Path $PSScriptRoot 'CourseGame.uproject'
& (Join-Path $EngineRoot 'Engine/Build/BatchFiles/Build.bat') CourseGameEditor Win64 Development "-Project=$project" -WaitMutex -NoHotReloadFromIDE
if($LASTEXITCODE -ne 0) { throw "Unreal build failed: $LASTEXITCODE" }
