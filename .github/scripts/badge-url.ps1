# This script generates a badge URL for unit test results from a .trx file.
param (
	[Parameter(Position=0, Mandatory=$true)][string]$LogPath
)

$log = Get-Content $LogPath -Raw
if ($log -match '(\d+)\s+tests failed out of (\d+)') {
	$failed = [int]$matches[1]
	$passed = [int]$matches[2] - $failed
	$color = if ($failed -eq 0) { "brightgreen" } else { "red" }
} else {
	# Assume failure
	$failed="???"
	$passed="???"
	$color = "red"
}

"https://img.shields.io/badge/Unit%20tests-Passed%3A${passed}%20Failed%3A${failed}-${color}"
