# Simple script to test multithreading capabilities of the server

Add-Type -AssemblyName System.Net.Http

# Create HttpClient instance
$httpClient = New-Object System.Net.Http.HttpClient

# Number of concurrent requests
$requestCount = 200

# Base URL
$baseUrl = "http://localhost:8080/users/"

# Initialize an array to hold timing information for each request
$requestDurations = New-Object System.Collections.ArrayList

# Measure start time for total duration
$totalStartDateTime = Get-Date

for ($i = 1; $i -le $requestCount; $i++) {
    $url = $baseUrl + $i

    # Start the timer for this request
    $requestStartDateTime = Get-Date

    # Asynchronously send the HTTP request and wait for the result
    $response = $httpClient.GetAsync($url).Result

    # Stop the timer for this request and calculate the duration
    $requestEndDateTime = Get-Date
    $duration = $requestEndDateTime - $requestStartDateTime
    $requestDurations.Add($duration.TotalMilliseconds) | Out-Null

    Write-Host "Request $i completed in $($duration.TotalMilliseconds) ms"
}

# Measure end time for total duration
$totalEndDateTime = Get-Date
$totalDuration = $totalEndDateTime - $totalStartDateTime

Write-Host "Total time taken for $requestCount requests: $($totalDuration.TotalSeconds) seconds"

# Calculate average request time
$averageRequestTime = ($requestDurations | Measure-Object -Average).Average
Write-Host "Average time per request: $averageRequestTime ms"

$httpClient.Dispose()
Write-Host "All requests have been sent"
