#!/bin/bash
# Simple script to test multithreading capabilities of the server

# Number of concurrent requests
$RequestCount = 10

# Base URL
$BaseUrl="http://localhost:8080/users/"

# Make requests
1..$RequestCount | ForEach-Object {
    Start-Job -ScriptBlock {
        param($Url)
        Invoke-WebRequest -Uri $Url
    } -ArgumentList ("$BaseUrl$_")
}

# Wait for completion
Get-Job | Wait-Job
echo "All requests have been sent."

# Output results and clean up
Get-Job | ForEach-Object {
    Receive-Job -Job $_
    Remove-Job -Job $_
}

Write-Host "All requests have been sent"