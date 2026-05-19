$AsioUrl = "https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-30-2.zip"
$ZipFile = "asio.zip"
$ExtractPath = "asio_temp"
$IncludeDir = "include"

Write-Host "Downloading Asio..."
Invoke-WebRequest -Uri $AsioUrl -OutFile $ZipFile

Write-Host "Extracting..."
Expand-Archive -Path $ZipFile -DestinationPath $ExtractPath -Force

Write-Host "Installing Headers..."
if (-not (Test-Path $IncludeDir)) {
    New-Item -ItemType Directory -Path $IncludeDir
}

# The zip structure is typically asio-{tag}/asio/include
$AsioRoot = Get-ChildItem -Path $ExtractPath -Directory | Select-Object -First 1
Write-Host "Root: $($AsioRoot.FullName)"

$AsioSubDir = Join-Path $AsioRoot.FullName "asio"
if (-not (Test-Path $AsioSubDir)) {
    # Maybe it's directly in root?
    $AsioSubDir = $AsioRoot.FullName
}

$SourceInclude = Join-Path $AsioSubDir "include"
Write-Host "Source Include: $SourceInclude"

if (Test-Path $SourceInclude) {
    Copy-Item -Path "$SourceInclude\*" -Destination $IncludeDir -Recurse -Force
    Write-Host "Asio installed successfully."
}
else {
    Write-Error "Could not find 'include' directory in $AsioSubDir"
    Get-ChildItem $AsioSubDir -Depth 1 | Select-Object Name
}

# Write-Host "Cleaning up..."
# Remove-Item -Path $ZipFile -Force
# Remove-Item -Path $ExtractPath -Recurse -Force
