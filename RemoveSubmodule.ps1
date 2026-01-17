param (
    [Parameter(Mandatory = $true)]
    [string]$SubmodulePath
)

# Exit on errors
$ErrorActionPreference = "Stop"

Write-Host "Removing submodule '$SubmodulePath'..."

# Normalize path slashes
$SubmodulePath = $SubmodulePath -replace '\\', '/'

# Ensure we're in a Git repo
if (-not (Test-Path ".git")) {
    Write-Error "This script must be run from the root of a Git repository."
    exit 1
}

# Step 1: Deinitialize the submodule
Write-Host "→ Deinitializing submodule..."
git submodule deinit -f $SubmodulePath 2>$null

# Step 2: Remove from index
Write-Host "→ Removing submodule from index..."
git rm -f $SubmodulePath 2>$null