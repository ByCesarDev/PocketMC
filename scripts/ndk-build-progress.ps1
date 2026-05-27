param(
    [int]$Jobs = 4,
    [string]$NdkPath = "C:\Android\ndk\25.2.9519653",
    [string]$Repo = (Get-Location).Path,
    [string]$AppAbi = "armeabi-v7a",
    [string]$AppStl = "c++_static"
)

# Compute junction base like build.ps1 does
$junctionBase = "C:/m"
if (-not (Test-Path "C:\m")) {
    Write-Host "Creating junction C:\m -> $Repo" -ForegroundColor Yellow
    & cmd.exe /c "mklink /J \"C:\m\" \"$Repo\"" | Out-Null
}

# Path to Android.mk under junction
$androidMk = "$junctionBase/project/android/jni/Android.mk"
if (-not (Test-Path $androidMk)) {
    Write-Host "Android.mk not found at $androidMk" -ForegroundColor Red
    exit 1
}

# Quick parse to count candidate source files (.c, .cc, .cpp)
$mkText = Get-Content $androidMk -Raw
# Count occurrences of file extensions (simple heuristic)
$total = ([regex]::Matches($mkText, '\.c(pp)?\b|\.cc\b|\.c\b', 'IgnoreCase')).Count
if ($total -eq 0) { $total = 1 }

Write-Host "Detected approx. $total source entries in Android.mk" -ForegroundColor Cyan

$ndkCmd = Join-Path $NdkPath 'ndk-build.cmd'
$ndkArgs = "NDK_PROJECT_PATH=`"$junctionBase/project/android`" APP_BUILD_SCRIPT=`"$junctionBase/project/android/jni/Android.mk`" APP_STL=$AppStl APP_ABI=$AppAbi -j$Jobs"

$env:NDK_MODULE_PATH = "$junctionBase/project/lib_projects"

$done = 0
$start = Get-Date

# Run ndk-build and parse output streaming
$psi = New-Object System.Diagnostics.ProcessStartInfo
$psi.FileName = $ndkCmd
$psi.Arguments = $ndkArgs
$psi.RedirectStandardOutput = $true
$psi.RedirectStandardError = $true
$psi.UseShellExecute = $false
$psi.CreateNoWindow = $true

$proc = New-Object System.Diagnostics.Process
$proc.StartInfo = $psi
$proc.Start() | Out-Null

# Asynchronously read both stdout and stderr
$stdOut = $proc.StandardOutput
$stdErr = $proc.StandardError

while (-not $stdOut.EndOfStream -or -not $stdErr.EndOfStream -or -not $proc.HasExited) {
    if (-not $stdOut.EndOfStream) {
        $line = $stdOut.ReadLine()
        if ($line) {
            Write-Host $line
            if ($line -match 'Compile\+\+|Compile ' ) { $done++ }
            # show progress line
            $pct = [math]::Floor(($done / $total) * 100)
            $elapsed = (Get-Date) - $start
            $avg = if ($done -gt 0) { $elapsed.TotalSeconds / $done } else { 0 }
            $remaining = if ($done -gt 0) { [TimeSpan]::FromSeconds($avg * ($total - $done)) } else { [TimeSpan]::Zero }
            Write-Host ('Progress: {0}/{1} ({2}%) - ETA: {3:hh\:mm\:ss}' -f $done, $total, $pct, $remaining) -ForegroundColor Cyan
        }
    }
    if (-not $stdErr.EndOfStream) {
        $line = $stdErr.ReadLine()
        if ($line) {
            Write-Host $line -ForegroundColor Red
            if ($line -match 'Compile\+\+|Compile ' ) { $done++ }
            $pct = [math]::Floor(($done / $total) * 100)
            $elapsed = (Get-Date) - $start
            $avg = if ($done -gt 0) { $elapsed.TotalSeconds / $done } else { 0 }
            $remaining = if ($done -gt 0) { [TimeSpan]::FromSeconds($avg * ($total - $done)) } else { [TimeSpan]::Zero }
            Write-Host ('Progress: {0}/{1} ({2}%) - ETA: {3:hh\:mm\:ss}' -f $done, $total, $pct, $remaining) -ForegroundColor Cyan
        }
    }
    Start-Sleep -Milliseconds 50
}

$proc.WaitForExit()
$end = Get-Date
$tot = $end - $start
Write-Host "ndk-build finished (exit $($proc.ExitCode)). Total time: $([int]$tot.TotalMinutes)m $($tot.Seconds)s" -ForegroundColor Green
exit $proc.ExitCode
