<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://cdn.jsdelivr.net/npm/tailwindcss@2.2.19/dist/tailwind.min.css" rel="stylesheet">
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <title>Admin Dashboard - IoT based Mining Security System</title>
</head>

<body class="bg-gray-100">

    <header class="bg-blue-600 text-white py-4">
        <div class="flex justify-between container mx-auto text-center">
            <h1 class="text-3xl font-bold">IoT based Mining Area Security Dashboard</h1>
            <a type="submit" href="/auth/logout"
                class="bg-red-500 px-4 py-2 rounded-lg text-white font-semibold hover:bg-red-600 focus:outline-none focus:ring-2 focus:ring-red-500">
                Logout
            </a>
        </div>
    </header>

    <main class="container mx-auto p-6">
        <h2 class="text-2xl font-bold mb-4">System Status Overview</h2>

        <div class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-4 mb-8">
            <div class="bg-white shadow-lg rounded-lg p-4 text-center">
                <span class="material-icons text-blue-600 text-5xl">vibration</span>
                <h3 class="mt-2 font-semibold">Vibration Level</h3>
                <p class="text-2xl" id="vibration-level">1.5 G</p>
            </div>
            <div class="bg-white shadow-lg rounded-lg p-4 text-center">
                <span class="material-icons text-blue-600 text-5xl">visibility</span>
                <h3 class="mt-2 font-semibold">Motion Status</h3>
                <p class="text-2xl" id="motion-status">No Motion</p>
            </div>
            <div class="bg-white shadow-lg rounded-lg p-4 text-center">
                <span class="material-icons text-blue-600 text-5xl">water</span>
                <h3 class="mt-2 font-semibold">Soil Moisture</h3>
                <p class="text-2xl" id="soil-moisture">20%</p>
            </div>
            <div class="bg-white shadow-lg rounded-lg p-4 text-center">
                <span class="material-icons text-blue-600 text-5xl">notifications</span>
                <h3 class="mt-2 font-semibold">Recent Alerts</h3>
                <ul id="alert-list" class="mt-2">
                    <li class="text-red-500">No Recent Alerts</li>
                </ul>
            </div>
        </div>

        <h3 class="text-xl font-semibold mb-2">Vibration Trends</h3>
        <div class="bg-white shadow-lg rounded-lg p-4">
            <canvas id="vibrationChart"></canvas>
        </div>
    </main>

    <script>
        // Sample data for the chart
        const ctx = document.getElementById('vibrationChart').getContext('2d');
        const vibrationChart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: ['1', '2', '3', '4', '5', '6', '7'], // Example time intervals
                datasets: [{
                    label: 'Vibration Level (G)',
                    data: [1.2, 1.5, 1.7, 1.3, 1.8, 1.1, 1.4], // Sample data points
                    borderColor: 'rgba(75, 192, 192, 1)',
                    backgroundColor: 'rgba(75, 192, 192, 0.2)',
                    borderWidth: 2,
                    fill: true,
                }]
            },
            options: {
                responsive: true,
                scales: {
                    y: {
                        beginAtZero: true,
                        title: {
                            display: true,
                            text: 'Vibration Level (G)',
                        }
                    },
                    x: {
                        title: {
                            display: true,
                            text: 'Time',
                        }
                    }
                }
            }
        });

        // Sample data update simulation for the chart
        setInterval(() => {
            const newDataPoint = (Math.random() * 3).toFixed(2); // Generate new random data
            vibrationChart.data.datasets[0].data.shift(); // Remove the first data point
            vibrationChart.data.datasets[0].data.push(newDataPoint); // Add the new data point
            vibrationChart.update(); // Update the chart
        }, 3000); // Update every 3 seconds
        // Sample data update simulation
        setInterval(() => {
        // Simulate new data
        document.getElementById('vibration-level').textContent = (Math.random() * 3).toFixed(2) + ' G';
        document.getElementById('motion-status').textContent = Math.random() > 0.5 ? 'Motion Detected' : 'No Motion';
        document.getElementById('soil-moisture').textContent = (Math.random() * 100).toFixed(0) + '%';
        
        // Simulate alerts
        const alerts = ['Vibration Detected', 'Motion Detected', 'Soil Moisture Low'];
        const randomAlert = alerts[Math.floor(Math.random() * alerts.length)];
        const alertList = document.getElementById('alert-list');
        alertList.innerHTML = `<li class="text-red-500">${randomAlert}</li>`;
        }, 3000); // Update every 3 seconds
    </script>

</body>

</html>