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
                <p class="text-2xl" id="vibration-level">512 G</p>
            </div>
            <div class="bg-white shadow-lg rounded-lg p-4 text-center">
                <span class="material-icons text-blue-600 text-5xl">visibility</span>
                <h3 class="mt-2 font-semibold">Motion Status</h3>
                <p class="text-2xl" id="motion-status">Motion Detected</p>
            </div>
            <div class="bg-white shadow-lg rounded-lg p-4 text-center">
                <span class="material-icons text-blue-600 text-5xl">thermostat</span>
                <h3 class="mt-2 font-semibold">Temperature</h3>
                <p class="text-2xl" id="temperature">28.5ºC</p>
            </div>
            <div class="bg-white shadow-lg rounded-lg p-4 text-center">
                <span class="material-icons text-blue-600 text-5xl">water</span>
                <h3 class="mt-2 font-semibold">Humidity</h3>
                <p class="text-2xl" id="humidity">32%</p>
            </div>
            <!-- Added soil moisture level -->
            <div class="bg-white shadow-lg rounded-lg p-4 text-center">
                <span class="material-icons text-blue-600 text-5xl">nature</span>
                <h3 class="mt-2 font-semibold">Soil Moisture Level</h3>
                <p class="text-2xl" id="moisture-level">45</p>
            </div>
        </div>

        <h3 class="text-xl font-semibold mb-2">Recent Incidents</h3>
        <div class="bg-white shadow-lg rounded-lg p-4 mb-8">
            <table class="min-w-full table-auto">
                <thead>
                    <tr>
                        <th class="px-4 py-2">Incident</th>
                        <th class="px-4 py-2">Temperature (ºC)</th>
                        <th class="px-4 py-2">Humidity (%)</th>
                        <th class="px-4 py-2">Vibration Level (G)</th>
                        <th class="px-4 py-2">Soil Moisture</th>
                        <th class="px-4 py-2">Motion Status</th>
                        <th class="px-4 py-2">Timestamp</th>
                    </tr>
                </thead>
                <tbody id="incident-table-body">
                    <!-- Data will be inserted dynamically here -->
                </tbody>
            </table>
        </div>

        <h3 class="text-xl font-semibold mb-2">Vibration Trends</h3>
        <div class="bg-white shadow-lg rounded-lg p-4">
            <canvas id="vibrationChart"></canvas>
        </div>
    </main>

    <script>
        // Example data fetched from Laravel API
        const data = @json($data);

        // Populate recent incidents table
        const tableBody = document.getElementById('incident-table-body');
        data.forEach((incident) => {
            const row = `
                <tr class="bg-gray-100">
                    <td class="border px-4 py-2">${incident.incident}</td>
                    <td class="border px-4 py-2">${incident.temperature}</td>
                    <td class="border px-4 py-2">${incident.humidity}</td>
                    <td class="border px-4 py-2">${incident.vibration_level}</td>
                    <td class="border px-4 py-2">${incident.moisture_level}</td>
                    <td class="border px-4 py-2 ${incident.motion_level ? 'text-red-600' : ''}">${incident.motion_level ? 'Motion Detected' : 'No Motion'}</td>
                    <td class="border px-4 py-2">${new Date(incident.created_at).toLocaleString()}</td>
                </tr>
            `;
            tableBody.insertAdjacentHTML('beforeend', row);
        });

        // Set real-time stats
        document.getElementById('vibration-level').textContent = data[0].vibration_level + ' G';
        document.getElementById('motion-status').textContent = data[0].motion_level ? 'Motion Detected' : 'No Motion';
        document.getElementById('temperature').textContent = data[0].temperature + 'ºC';
        document.getElementById('humidity').textContent = data[0].humidity + '%';
        document.getElementById('moisture-level').textContent = data[0].moisture_level;

        // Chart for vibration trends
        const ctx = document.getElementById('vibrationChart').getContext('2d');
        const vibrationChart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: data.map((d, i) => `Incident ${i + 1}`),
                datasets: [{
                    label: 'Vibration Level (G)',
                    data: data.map(d => d.vibration_level),
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
                            text: 'Incident',
                        }
                    }
                }
            }
        });
    </script>

</body>

</html>