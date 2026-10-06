param([Parameter(Mandatory=$true)][string]$EngineRoot)
$ErrorActionPreference='Stop'
$exe=Join-Path $EngineRoot 'Engine/Binaries/Win64/UnrealEditor-Cmd.exe'
$project=Join-Path $PSScriptRoot 'CourseGame.uproject'
$evidence=Join-Path $PSScriptRoot 'Evidence/Week03'
New-Item -ItemType Directory -Force -Path $evidence | Out-Null
$distances=@()
foreach($fps in @(30,60,120)) {
    $csv=Join-Path $PSScriptRoot 'Saved/Verification/Week03.csv'
    if(Test-Path -LiteralPath $csv) { Remove-Item -LiteralPath $csv }
    $arguments=@(('"'+$project+'"'),'/Game/Course/Maps/L_Week03','-game','-nullrhi','-unattended','-nosound','-Week03Verify','-NoSplash',('-ExecCmds="t.MaxFPS '+$fps+'"'),('-abslog="'+(Join-Path $evidence "run-$fps.log")+'"'))
    $proc=Start-Process -FilePath $exe -ArgumentList $arguments -WindowStyle Hidden -PassThru
    if(!$proc.WaitForExit(180000)) { Stop-Process -Id $proc.Id; throw "Verification timeout at $fps FPS" }
    $proc.Refresh()
    if(!(Test-Path -LiteralPath $csv)) { throw "Missing verification report at $fps FPS" }
    Copy-Item -LiteralPath $csv -Destination (Join-Path $evidence "run-$fps.csv")
    $data=Get-Content -LiteralPath $csv
    if($proc.ExitCode -ne 0 -or $data -notcontains 'Overall,PASS') { throw "Verification failed at $fps FPS; inspect evidence" }
    $distances += [double]((($data | Where-Object {$_ -like 'RunDistance,*'}) -split ',')[1])
}
$range=($distances | Measure-Object -Maximum).Maximum-($distances | Measure-Object -Minimum).Minimum
$mean=($distances | Measure-Object -Average).Average
if($range/$mean -gt .05) { throw 'Between-cap run-distance variation exceeds 5%' }
"30/60/120 FPS runs passed. Distance range/mean: $($range/$mean)" | Tee-Object -FilePath (Join-Path $evidence 'comparison.txt')
