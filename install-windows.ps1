# Resolve directory where this script is located
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path

# Executable details
$ExeName      = "keyboard-settings.exe"
$ExePath      = Join-Path $ScriptDir $ExeName
$ShortcutName = "Keyboard Settings.lnk"

# Startup folder (current user)
$StartupFolder = [Environment]::GetFolderPath("Startup")
$ShortcutPath  = Join-Path $StartupFolder $ShortcutName

# Safety check
if (-not (Test-Path $ExePath)) {
    Write-Error "Executable not found: $ExePath"
    exit 1
}

# Create shortcut (overwrite if it already exists)
$Shell    = New-Object -ComObject WScript.Shell
$Shortcut = $Shell.CreateShortcut($ShortcutPath)

$Shortcut.TargetPath = $ExePath
$Shortcut.Save()

Write-Host "Startup shortcut created: $ShortcutPath"
